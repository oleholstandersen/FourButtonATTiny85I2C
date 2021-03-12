#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <TinyWireS.h>

#ifndef I2C_SLAVE_ADDRESS                           //Can also be defined elsewhere
    #define I2C_SLAVE_ADDRESS   0x2                 //I2C slave address - change for multiple slaves
#endif
#define INPUT_PIN_COUNT         4                   //Number on input pins
#define INPUT_PINS              PB1,PB3,PB4,PB5     //Comma separated list on input pins
#define DEBOUNCE_DELAY          10000L              //In micros

void updateInputPinStates();
void onRequest();
bool getBit(uint8_t value, int bitIndex);
uint8_t setBit(uint8_t initialValue, int bitIndex, bool bitValue);

#endif//MAIN_H