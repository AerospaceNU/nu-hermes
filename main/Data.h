#ifndef DATA_H
#define DATA_H

class Data
{
    public:
        void initXbee();
        void WaitForSignal(long timeToWait);
        void SendData(int dataToSend);
        int readInt();


    private:
};

#endif DATA_H
