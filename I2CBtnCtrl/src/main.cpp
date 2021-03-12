#include <main.h>

uint8_t inputPins[4] = {INPUT_PINS};
unsigned long debouncsStarts[INPUT_PIN_COUNT] = {0,0,0,0};
uint8_t pinStates = 0x0U;
uint8_t pendingStateChanges = 0x0U;

void setup() {
  for (int i = 0; i < INPUT_PIN_COUNT; i++)
  {
    pinMode(inputPins[i], INPUT_PULLUP);
    digitalWrite(inputPins[i], HIGH);
  }
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(onRequest);
}

void loop() {
  updateInputPinStates();
  TinyWireS_stop_check();
}

void updateInputPinStates()
{
  for (int i = 0; i < INPUT_PIN_COUNT; i++)
  {
    bool currentPinState = getBit(pinStates,i);
    bool readPinState = digitalRead(inputPins[i])==LOW;
    if (currentPinState==readPinState)
    {
      pendingStateChanges = setBit(pendingStateChanges,i,false);
    }
    else if (!getBit(pendingStateChanges,i))
    {
      pendingStateChanges = setBit(pendingStateChanges,i,true);
      debouncsStarts[i] = micros();
    }
    else if (micros()>debouncsStarts[i]+DEBOUNCE_DELAY)
    {
      currentPinState = setBit(currentPinState,i,readPinState);
      pendingStateChanges = setBit(pendingStateChanges,i,false);
    }
  }
}

void onRequest()
{
  TinyWireS.send(pinStates);
}

bool getBit(uint8_t value, int bitIndex)
{
  uint8_t mask = (0<=bitIndex && bitIndex<8) ? 0 : (0x1u >> bitIndex);
  return value & mask;
}

uint8_t setBit(uint8_t initialValue, int bitIndex, bool bitValue)
{
  uint8_t mask = (0<=bitIndex && bitIndex<8 && bitValue) ? 0 : (0x1u >> bitIndex);
  return initialValue & !mask;
}
