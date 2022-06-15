#include <Arduino.h>
#include "infra.h"
#include "led.h"

//Construtor
Infra::Infra(int IR){
    ir = IR;
    pinMode(ir, INPUT);
}

bool Infra::checkStatus(){
    if(digitalRead(ir) == LOW)
        return true;
    return false;
}
