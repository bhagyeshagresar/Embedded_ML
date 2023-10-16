#include "USBLib.hpp"
#include <iostream>
#include <iomanip>
#include <thread>
#include <string>

USBPort::USBPort(char* portname){

    errors = 0;
    status = {0};
    connected = false;

    handle = CreateFile(static_cast<LPCSTR>(portname), GENERIC_READ | GENERIC_WRITE,
    0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD errmsg = GetLastError();

    if(errmsg == 2){
        std::cout << "device is not plugged" << std::endl;
    }

    else if (errmsg == 5){
        std::cout << "COM port already in use" << std::endl;
    }

    else if(errmsg == 0){
        
        DCB dcbSerialParameters = {0};

        if(!GetCommState(handle, &dcbSerialParameters)){
            std::cout << "failed to get current serial parameters" << std::endl;

        }
        else{
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if(!SetCommState(handle, &dcbSerialParameters)){
                std::cout << "could not find serial port parameters" << std::endl;
            }
            else{
                connected = true;
                PurgeComm(handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            }

        }
    }    

}


USBPort::~USBPort(){
    if(connected == true){
        
        connected = false;
        CloseHandle(handle);
    }
}


int USBPort::ReadSerialPort(char* buffer, unsigned int buffer_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(handle, &errors, &status);

    //Prepare to read any available bytes, not to exceed the requested number of bytes
    if(status.cbInQue > 0)
    {
        
        if(status.cbInQue > buffer_size)
        {
            toRead = buffer_size;

        }
        
        else
        {
            toRead = status.cbInQue;
        }
    }

    //Read requested ("toRead") bytes into "buffer", and return the number of bytes actually read
    if(ReadFile(handle, buffer, toRead, &bytesRead, NULL))
    {
        return bytesRead;

    }

    return 0;





}

// bool USBPort::WriteSerialPort(char* buffer, unsigned int buffer_size){}

bool USBPort::isConnected(){

    return connected;
}