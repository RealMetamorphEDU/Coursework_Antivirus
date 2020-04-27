#include <Windows.h>
#pragma comment(lib, "advapi32.lib")
#include <iostream>

char SERVICE_NAME[]{"AService"};
SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE statusHandle;


void WINAPI serviceMain(int argc, char *argv[]);
void WINAPI controlHandler(DWORD control);
void srvInstall();
void srvUninstall();


void main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[2], "install") == 0) // Install service
            srvInstall();
        else if (strcmp(argv[2], "uninstall") == 0) // Uninstall service
            srvUninstall();
        else // Bad usage
            std::cout << "Usage: AService [install | uninstall]" << std::endl;
    } else {
        SERVICE_TABLE_ENTRYA entryTable[2]; // entry point for service
        entryTable[0] = {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTIONA) serviceMain};
        entryTable[1] = {NULL, NULL};
        // Start control dispatcher
        if (!StartServiceCtrlDispatcherA(entryTable)) {
            //Can't start service
        }
        // Service finished
    }
}


void WINAPI serviceMain(DWORD argc, char *argv[]) {
    // Register control event handler
    statusHandle = RegisterServiceCtrlHandlerA(SERVICE_NAME, controlHandler);

}

void WINAPI controlHandler(DWORD control) {

}

void srvInstall() {

}

void srvUninstall() {

}

VOID SvcReportEvent(LPTSTR szFunction) 
{ 
    HANDLE hEventSource;

    hEventSource = RegisterEventSourceA(NULL, SERVICE_NAME);

    if( NULL != hEventSource )
    {
        StringCchPrintf(Buffer, 80, TEXT("%s failed with %d"), szFunction, GetLastError());

        lpszStrings[0] = SVCNAME;
        lpszStrings[1] = Buffer;

        ReportEventA(hEventSource,        // event log handle
                    EVENTLOG_ERROR_TYPE, // event type
                    0,                   // event category
                    SVC_ERROR,           // event identifier
                    NULL,                // no security identifier
                    2,                   // size of lpszStrings array
                    0,                   // no binary data
                    lpszStrings,         // array of strings
                    NULL);               // no binary data

        DeregisterEventSource(hEventSource);
    }
}