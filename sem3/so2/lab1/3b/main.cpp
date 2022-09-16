#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <conio.h>
#include <tchar.h>

#define BUFFER_SIZE 2048
#define ENV_KEY "SO2"
#define ENV_VAL "NEW"

#define BUF_SIZE 256

TCHAR t_name[] = TEXT("Global\\MyFileMappingObject");
HANDLE h_mutex;

int write_pid_to_memory(const char *dw_pid);
int access_pid_from_memory();

int main(int argc, char **argv)
{
    //Search memory for PID of previous process running this code
    DWORD read_pid = access_pid_from_memory();

    std::cout << "Found PID : " << read_pid << std::endl;

    //Get PID to save
    DWORD dw_pid = GetCurrentProcessId();
    std::stringstream stream;
    stream << dw_pid;
    const char *t_pid = stream.str().c_str();
    std::cout << "My PID: " << dw_pid << std::endl;

    //Write to memory your PID for other process to access it and close you
    write_pid_to_memory(t_pid);

    char c_buffer[BUFFER_SIZE];
    LPCSTR lp_name = ENV_KEY;
    LPSTR lp_buffer = c_buffer;
    DWORD dw_size = BUFFER_SIZE;
    DWORD get_env_var;
    std::string env_val(ENV_VAL);

    //Search for SO2 env variable
    get_env_var = GetEnvironmentVariable(
        lp_name,
        lp_buffer,
        dw_size);

    if (GetLastError() == ERROR_ENVVAR_NOT_FOUND)
    {
        std::cout << "Couldn't find envariamental variable \"SO2\"." << std::endl;
    }

    if (BUFFER_SIZE == get_env_var)
    {
        std::cout << "Buffer for function [GetEnvironmentVariable] is too small. Function failed." << std::endl;
    }

    std::cout << "Envariamental variable = " << lp_buffer << std::endl;
    std::string str_buffer(lp_buffer);
    std::cout << "Env var value length = " << str_buffer.length() << std::endl;
    std::cout << "Env var value compare resault = " << str_buffer.compare(env_val) << std::endl;

    HANDLE h_mutex = NULL;

    LPCSTR str = ENV_KEY;

    //Check for existing mutex
    h_mutex = OpenMutex(
        MUTEX_ALL_ACCESS,
        TRUE,
        str);

    //if there is mutex
    if (NULL != h_mutex)
    {
        //and there is Sys Var = "NEW"
        if (str_buffer.compare(env_val) == 0)
        {
            //Realease previous mutex
            ReleaseMutex(h_mutex);

            //Close previous process:

            HANDLE h_previous_process = OpenProcess(
                PROCESS_TERMINATE,
                FALSE,
                read_pid);
            if (h_previous_process == NULL) {
                throw std::runtime_error("Couldn't close previous instance of a programm");
            }

            LPDWORD p_exit_code;
            BOOL return_value = GetExitCodeProcess(
                h_previous_process,
                p_exit_code);

            if(return_value == FALSE) {
                std::cout <<"GetExitCodeProcess failed: " << GetLastError() << std::endl;
            }

            return_value = TerminateProcess(
                h_previous_process, 
                return_value);

            if(return_value == FALSE) {
                std::cout <<"TerminateProcess: failed" << GetLastError() << std::endl;
            } else {
                std::cout << "Previous process terminated with exit code: " << *p_exit_code << std::endl;
            }
        }
        //no Sys Var = "NEW" - You can't run next instance of a program
        else
        {
            throw std::runtime_error("Instance of a program is already running");
        }
    }

    //If there was no mutex before, or there is Sys Var = "NEW" - Create mutex to stop new insatnce of a programm from running
    h_mutex = CreateMutex(
        NULL,
        FALSE,
        str);

    if (h_mutex == NULL)
    {
        std::cout << "Failed to create mutex: error - " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Mutex created sucesfully" << std::endl;

    DWORD dw_wait_res;

    dw_wait_res = WaitForSingleObject(
        h_mutex,   // handle to mutex
        INFINITE); // no time-out interval

    //idle
    for (;;)
    {
        Sleep(100);
    }

    CloseHandle(h_mutex);
    system("PAUSE");
    return 0;
}

int write_pid_to_memory(const char *t_pid)
{
    _tprintf(TEXT("[write_pid_to_memory] t_pid: (%s).\n"), t_pid);

    HANDLE h_map_file;
    LPCTSTR p_buf;

    h_map_file = CreateFileMapping(
        INVALID_HANDLE_VALUE, // use paging file
        NULL,                 // default security
        PAGE_READWRITE,       // read/write access
        0,                    // maximum object size (high-order DWORD)
        BUF_SIZE,             // maximum object size (low-order DWORD)
        t_name);              // name of mapping object

    if (h_map_file == NULL)
    {
        _tprintf(TEXT("[write_pid_to_memory] Could not create file mapping object (%d).\n"),
                 GetLastError());
        return 1;
    }
    p_buf = (LPTSTR)MapViewOfFile(
        h_map_file,          // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (p_buf == NULL)
    {
        _tprintf(TEXT("[write_pid_to_memory] Could not map view of file (%d).\n"),
                 GetLastError());

        CloseHandle(h_map_file);

        return 1;
    }

    std::cout << "[write_pid_to_memory] strlen(t_pid) * sizeof(char) " << strlen(t_pid) * sizeof(char) << std::endl;

    CopyMemory((PVOID)p_buf, t_pid, (strlen(t_pid) * sizeof(char)));

    // _getch();

    std::cout << "[write_pid_to_memory] p_buf " << p_buf << std::endl;

    // UnmapViewOfFile(p_buf);

    // CloseHandle(h_map_file);

    return 0;
}

int access_pid_from_memory()
{

    HANDLE h_map_file;
    LPCTSTR p_buf;

    h_map_file = OpenFileMapping(
        FILE_MAP_ALL_ACCESS, // read/write access
        FALSE,               // do not inherit the name
        t_name);             // name of mapping object

    if (h_map_file == NULL)
    {
        _tprintf(TEXT("[access_pid_from_memory] Could not open file mapping object (%d).\n"),
                 GetLastError());
        return 1;
    }

    p_buf = (LPTSTR)MapViewOfFile(
        h_map_file,          // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (p_buf == NULL)
    {
        _tprintf(TEXT("[access_pid_from_memory] Could not map view of file (%d).\n"),
                 GetLastError());

        CloseHandle(h_map_file);

        return 1;
    }

    _tprintf(TEXT("[access_pid_from_memory] buffer: (%x).\n"), p_buf);
    _tprintf(TEXT("[access_pid_from_memory] sizeof(buffer): (%d).\n"), sizeof(p_buf));

    MessageBox(NULL, p_buf, TEXT("[access_pid_from_memory] Process2"), MB_OK);

    // UnmapViewOfFile(p_buf);

    // CloseHandle(h_map_file);
    return atoi(p_buf);
}