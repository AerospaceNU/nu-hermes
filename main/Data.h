#ifndef DATA_H
#define DATA_H
#include "XBee.h";

class Data:
{
    public:
        void initXbee();
        void WaitForSignal(long timeToWait);
        void SendData(int dataToSend);
        int readData();


    private:
};

#endif DATA_H
