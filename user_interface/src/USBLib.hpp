#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_DATA_BYTES 7
#define WAIT_TIME 2000

class USBPort
{

private:
    HANDLE handle;
    bool connected;
    COMSTAT status;
    DWORD errors;

public:
    USBPort(char* portname);
    ~USBPort();

    int ReadSerialPort(char* buffer, unsigned int buffer_size);
    //bool WriteSerialPort(char* buffer, unsigned int buffer_size);
    bool isConnected();
    
    

};