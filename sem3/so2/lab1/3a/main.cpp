#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include <conio.h>
#include <tchar.h>

using namespace ::std;

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        cout << "No arguments passed to the program:" << *argv << endl;
        cout << "[My PID] -> " << GetCurrentProcessId();

        exit(0);
    }

    if (argc == 2)
    {
        cout << "Argument for process: " << argv[1] << endl;
        cout << "[My PID] -> " << GetCurrentProcessId() << endl;
        exit(0);
    }

    for (int i = 1; i < argc; i++)
    {
        HANDLE h_process;
        HANDLE h_thread;
        STARTUPINFO sui_info;
        PROCESS_INFORMATION pi_info;
        DWORD dw_process_id = 0;

        char *c_argv = (char *)malloc(strlen(argv[0]) + strlen(argv[i]) + 2);
        string s_argv = string(*argv) + " " + string(argv[i]);
        strcpy(c_argv, s_argv.c_str());

        cout << s_argv << endl;

        ZeroMemory(&sui_info, sizeof(sui_info));
        ZeroMemory(&pi_info, sizeof(pi_info));

        if (FALSE == CreateProcess(
                         NULL,
                         c_argv,
                         NULL,
                         NULL,
                         FALSE,
                         0,
                         NULL,
                         NULL,
                         &sui_info,
                         &pi_info))
        {
            cout << "Create process Failed & Error No - " << GetLastError() << endl;
            free(c_argv);
            system("PAUSE");
            return 0;
        }

        cout << "[Created PID] -> " << pi_info.dwProcessId << endl;

        WaitForSingleObject(pi_info.hProcess, INFINITE);

        CloseHandle(pi_info.hThread);
        CloseHandle(pi_info.hProcess);

        free(c_argv);
    }

    system("PAUSE");
    return 0;
}