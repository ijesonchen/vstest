#include <windows.h>
#include <wincon.h>
#include <stdio.h> 
#include <iostream>
using namespace std;


bool ctrlhandler(DWORD fdwctrltype)
{
	cout << "ctrlhandler enter. sleep..." << endl;
	Sleep(1000);
	cout << "ctrlhandler proc: " << endl;
	switch (fdwctrltype)
	{
		// handle the ctrl-c signal. 
	case CTRL_C_EVENT:
		printf("ctrl-c event\n\n");
		return(true);

		// ctrl-close: confirm that the user wants to exit. 
	case CTRL_CLOSE_EVENT:
		printf("ctrl-close event\n\n");
		return(true);

		// pass other signals to the next handler. 
	case CTRL_BREAK_EVENT:
		printf("ctrl-break event\n\n");
		return false;

	case CTRL_LOGOFF_EVENT:
		printf("ctrl-logoff event\n\n");
		return false;

	case CTRL_SHUTDOWN_EVENT:
		printf("ctrl-shutdown event\n\n");
		return false;

	default:
		return false;
	}
}

void ConsoleWindowControlTest(void)
{
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true))
	{
		printf("\nthe control handler is installed.\n");
		printf("\n -- now try pressing ctrl+c or ctrl+break, or");
		printf("\n try logging off or closing the console...\n");
		printf("\n(...waiting in a loop for events...)\n\n");
	
		while (true)
		{
			Sleep(500);

			HANDLE hStdout, hNewScreenBuffer;
			SMALL_RECT srctReadRect;
			SMALL_RECT srctWriteRect;
			CHAR_INFO chiBuffer[160]; // [2][80]; 
			COORD coordBufSize;
			COORD coordBufCoord;
			BOOL fSuccess;

			// Get a handle to the STDOUT screen buffer to copy from and 
			// create a new screen buffer to copy to. 

			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			hNewScreenBuffer = CreateConsoleScreenBuffer(
				GENERIC_READ |           // read/write access 
				GENERIC_WRITE,
				FILE_SHARE_READ |
				FILE_SHARE_WRITE,        // shared 
				NULL,                    // default security attributes 
				CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
				NULL);                   // reserved; must be NULL 
			if (hStdout == INVALID_HANDLE_VALUE ||
				hNewScreenBuffer == INVALID_HANDLE_VALUE)
			{
				printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
				continue;
			}

			// Make the new screen buffer the active screen buffer. 

			if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
			{
				printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
				continue;
			}

			// Set the source rectangle. 

			srctReadRect.Top = 0;    // top left: row 0, col 0 
			srctReadRect.Left = 0;
			srctReadRect.Bottom = 1; // bot. right: row 1, col 79 
			srctReadRect.Right = 79;

			// The temporary buffer size is 2 rows x 80 columns. 

			coordBufSize.Y = 2;
			coordBufSize.X = 80;

			// The top left destination cell of the temporary buffer is 
			// row 0, col 0. 

			coordBufCoord.X = 0;
			coordBufCoord.Y = 0;

			// Copy the block from the screen buffer to the temp. buffer. 

			fSuccess = ReadConsoleOutput(
				hStdout,        // screen buffer to read from 
				chiBuffer,      // buffer to copy into 
				coordBufSize,   // col-row size of chiBuffer 
				coordBufCoord,  // top left dest. cell in chiBuffer 
				&srctReadRect); // screen buffer source rectangle 
			if (!fSuccess)
			{
				printf("ReadConsoleOutput failed - (%d)\n", GetLastError());
				continue;
			}

			// Set the destination rectangle. 

			srctWriteRect.Top = 10;    // top lt: row 10, col 0 
			srctWriteRect.Left = 0;
			srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79 
			srctWriteRect.Right = 79;

			// Copy from the temporary buffer to the new screen buffer. 

			fSuccess = WriteConsoleOutput(
				hNewScreenBuffer, // screen buffer to write to 
				chiBuffer,        // buffer to copy from 
				coordBufSize,     // col-row size of chiBuffer 
				coordBufCoord,    // top left src cell in chiBuffer 
				&srctWriteRect);  // dest. screen buffer rectangle 
			if (!fSuccess)
			{
				printf("WriteConsoleOutput failed - (%d)\n", GetLastError());
				continue;
			}
			Sleep(500);

			// Restore the original active screen buffer. 

			if (!SetConsoleActiveScreenBuffer(hStdout))
			{
				printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
				continue;
			}
		}
	}
	else
	{
		printf("\nerror: could not set control handler");
	}
}