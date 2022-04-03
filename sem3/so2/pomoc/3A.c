#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    if(argc < 2){
        printf("Program wykona³ siê bez argumentów\n");
        exit(0);
    }
    if(argc == 2){
        printf("Argument: %s pid=%d\n", argv[1], GetCurrentProcessId());
        exit(0);
    }
    if(argc > 2){
        int i;
        for(i = 1;i < argc; i++) {
            STARTUPINFO si;
            PROCESS_INFORMATION pi;

            ZeroMemory( &si, sizeof(si) );
            si.cb = sizeof(si);
            ZeroMemory( &pi, sizeof(pi) );

            char * cmd = malloc(strlen(argv[i]) + strlen(argv[0]) + 2);

            strcpy(cmd,argv[0]);
            strcat(cmd, " ");
            strcat(cmd, argv[i]);

            if (!CreateProcess(NULL,   // No module name (use command line)
                               cmd,        // Command line
                               NULL,           // Process handle not inheritable
                               NULL,           // Thread handle not inheritable
                               FALSE,          // Set handle inheritance to FALSE
                               0,              // No creation flags
                               NULL,           // Use parent's environment block
                               NULL,           // Use parent's starting directory
                               &si,            // Pointer to STARTUPINFO structure
                               &pi)           // Pointer to PROCESS_INFORMATION structure
                    ) {
                printf("CreateProcess failed (%d).\n", GetLastError());
                return 0;
            }
            free(cmd);
            CloseHandle( pi.hProcess );
            CloseHandle( pi.hThread );
        }
    }
    return 0;
}

