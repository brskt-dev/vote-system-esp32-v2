#include <Arduino.h>
#include "led.h"

//Construtor
Led::Led(int LED){
    led = LED;
    pinMode(LED, OUTPUT);
}

//Bool - On/Off
void Led::on_status(bool status){
    digitalWrite(led, status);
}

//Reset - LED
void Led::reset(){
    delay(200);
    digitalWrite(led, LOW);
}