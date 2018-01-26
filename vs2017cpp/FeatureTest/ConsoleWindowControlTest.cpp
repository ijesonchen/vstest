#include <windows.h> 
#include <stdio.h> 
#include <iostream>
using namespace std;


bool ctrlhandler(DWORD fdwctrltype)
{
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

	putchar('q');

	char ch = 0;
	cin >> ch;
	cin >> ch;
	cin >> ch;
}

void ConsoleWindowControlTest(void)
{
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, true))
	{
		printf("\nthe control handler is installed.\n");
		printf("\n -- now try pressing ctrl+c or ctrl+break, or");
		printf("\n try logging off or closing the console...\n");
		printf("\n(...waiting in a loop for events...)\n\n");

		char ch = 0;
		cin >> ch;
	}
	else
	{
		printf("\nerror: could not set control handler");
	}

}