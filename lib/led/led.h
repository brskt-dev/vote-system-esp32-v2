#ifndef LED_H
#define LED_H
#include <Arduino.h>

class Led{
    public:
        Led(int LED);
        void on_status(bool status);
        void reset();

    private:
        int led;
        
};

#endif