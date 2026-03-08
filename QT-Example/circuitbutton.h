#ifndef CIRCUITBUTTON_H
#define CIRCUITBUTTON_H

#include <QObject>

class CircuitButton : public QObject
{
    Q_OBJECT
public:
    explicit CircuitButton(QObject *parent = nullptr);
    explicit CircuitButton(QObject *parent = nullptr, int gpioPin = 0);
    void onButtonPress();
    void onButtonRelease();
    int getGpioPin();

private:
    int gpioPin;

signals:
    void buttonPressed(); // Create a custom QT signal for when the button on the circuit is pressed
    void buttonReleased(); // Create a custom QT signal for when the button on the circuit is released

};

#endif // CIRCUITBUTTON_H
