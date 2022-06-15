#ifndef INFRA_H
#define INFRA_H
#include <Arduino.h>
#include "led.h"

class Infra{
    public:
        Infra(int IR);
        bool checkStatus();
    private:
        int ir;
};

 #endif