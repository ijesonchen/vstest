#include <windows.h> 
#include <stdio.h>  


//////////////////////////////////////////////////////////////////////////
/*
ref:
http://ehsan.company/?t=1184&e=2592433680&ref=brah.ir&z=Semphores+vlues

http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FSemaphore%2FNtQuerySemaphore.html

suggests
inline header with dll functions:
	long QuerySemaphoreCurrent(wchar_t* name)
	long QuerySemaphoreMax(wchar_t* name)
	bool QuerySemaphoreUsed(wchar_t* name) // if semaphore is be owned
*/

typedef LONG NTSTATUS;  

typedef NTSTATUS (NTAPI *_NtQuerySemaphore)(HANDLE SemaphoreHandle,      
											DWORD SemaphoreInformationClass, /* Would be SEMAPHORE_INFORMATION_CLASS */     
											PVOID SemaphoreInformation,      /* but this is to much to dump here     */     
											ULONG SemaphoreInformationLength,      
											PULONG ReturnLength OPTIONAL );   

typedef struct _SEMAPHORE_BASIC_INFORMATION 
{        
	ULONG CurrentCount;      
	ULONG MaximumCount; 
} SEMAPHORE_BASIC_INFORMATION;   

void QuerySemaphoreInfo(void)
{     
	_NtQuerySemaphore NtQuerySemaphore;     
	HANDLE Semaphore;
	SEMAPHORE_BASIC_INFORMATION BasicInfo;
	NTSTATUS Status;
	Semaphore = CreateSemaphore(NULL, 50, 100, L"Test");
	WaitForSingleObject(Semaphore, INFINITE);
	NtQuerySemaphore = (_NtQuerySemaphore)GetProcAddress (GetModuleHandle (L"ntdll.dll"), "NtQuerySemaphore");      
	if (NtQuerySemaphore)     
	{          
		Status = NtQuerySemaphore (Semaphore, 0 /*SemaphoreBasicInformation*/,              
									&BasicInfo,
									sizeof(SEMAPHORE_BASIC_INFORMATION),
									NULL);
		if (Status == ERROR_SUCCESS)         
		{                    
			printf ("CurrentCount: %lu\n", BasicInfo.CurrentCount);         
		}     
	}     

	long a = 1;
	long b = 0;
	ReleaseSemaphore(Semaphore, a, &b);
	CloseHandle (Semaphore); 
} 
