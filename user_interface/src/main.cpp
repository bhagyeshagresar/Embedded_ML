#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include "USBLib.hpp"

char inputData[INPUT_DATA_BYTES];
double inputvalDbl = 0.0;

char comport[] = "COM7";
char* port = comport;


int main(){

    USBPort nucleo(port);

    if(nucleo.isConnected()){
        
        std::cout << "connected to" << port << std::endl;
    }

    else{

        std::cin.get();
    }

    while(nucleo.isConnected()){

        //Read data sent from the nucleo
        nucleo.ReadSerialPort(inputData, INPUT_DATA_BYTES);



        std::cout << "read data from serial port" << std::endl;

        //convert the char[] read from the nucleo in a string
        std::string inputValstr(inputData);

        

        std::cout << inputData << std::endl;

        //convert string into double
        //inputvalDbl = std::stod(inputValstr);

        //Add a carriage return character to bring cursor back to left side,
        // but no newline (\n) to move it to the next line
        //std::cout << std::fixed << std::setprecision(2);
        //std::cout << inputValstr << '\r';

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }

    return 0;
}