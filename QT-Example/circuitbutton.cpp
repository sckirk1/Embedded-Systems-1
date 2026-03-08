#include "circuitbutton.h"

CircuitButton::CircuitButton(QObject *parent, int gpioPin)
    : QObject{parent}
{
    this->gpioPin = gpioPin; // Create a virtual version of or physical button, using this GPIO pin as our interrupt
}


void CircuitButton::onButtonPress() {
    emit buttonPressed(); // Send out a signal that the button on the circuit was pressed
}

void CircuitButton::onButtonRelease() {
    emit buttonReleased(); // Send out a signal that the button on the circuit was released
}

int CircuitButton::getGpioPin() {
    return this->gpioPin; // Get the GPIO pin that our ISR uses to notify us of the button being pressed
}
