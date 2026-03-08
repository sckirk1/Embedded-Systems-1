#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpioconstants.h"
#include <wiringPi.h>

static inthornValue = 0;
static bool headlightsOn = false;

// This CircuitButton is a virtual representation of our physical button.
// Any button press on the physical button will be sent to this object, and converted to a QT Signal
// We need this to be static, as WiringPI doesn't allow class methods to be sent into the ISR, meaning the method we run when the ISR is triggered can only access static variables
// When the ISR triggers we use this button to convert the ISR interrupt into a QT signal, allowing us to interact with the UI.
static CircuitButton *circuitButton;

// This is the function called by our ISR.
// WiringPi doesn't allow class methods to be sent into the ISR, so we have this method instead.
// Because it's not a class method, we can only access static variables, which in our case is the circuitButton
// The ISR calls this on both a Rising and Falling edge, and we take it and use our circuitButton to convert it to a QT signal
void circuitButtonISR() {
    if (circuitButton) { //Check if circuitButton is not null, as it is a static object and may not be instantiated yet
        if (digitalRead(circuitButton->getGpioPin())) { // See if this was a button press or release by reading our GPIO pin (Checks for any non 0 value)
            // The value was non zero
            // Have our virtual representation of the button on the circuit send off a QT signal
            circuitButton->onButtonPress();
        } else { 
            // The read came back as 0
            // Have our virtual representation of the button send a QT signal that the button was released
            circuitButton->onButtonRelease();
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Normal QT setup call. Must happen at the creation of the MainWindow
    
    // This QTimer allows us to repeatedly call something without blocking the UI Thread.
    // If we didn't have this and used a normal loop the user would not be able to interact with anything until the loop ended 
    hornTimer->setInterval(1); //How often we want it to run in ms
    hornTimer = new QTimer(this); 
    // This connects our horn timer to our carHorn method, which will make a sound
    // The horn timer will emmit a signal every 1 milisecond, which will then be handled by our carHorn method which acts as a slot
    connect(hornTimer, &QTimer::timeout, this, &MainWindow::carHorn);

    wiringPiSetupGpio(); // This sets up wiringPI, and makes it use the normal RaspberryPI GPIO pin numberings instead of the wiringPi pin numbers

    // Using our GPIO Constants, setup all the GPIO Pins to input or output
    pinMode(HEADLIGHTS_GPIO, OUTPUT); // A GPIO pin we use to control our headlight on our circuit
    pinMode(HORN_GPIO, OUTPUT); // The actual horn that makes a sound
    pinMode(HORN_BUTTON_GPIO, INPUT); // The GPIO pin that we use for our ISR to detect the button press

    // Create the static CircuitButton, which will allow us to convert the ISR notification into a QT signal
    circuitButton = new CircuitButton(this, HORN_BUTTON_GPIO);
    // Setup the ISR to detect when the button on the circuit is pressed
    wiringPiISR(HORN_BUTTON_GPIO, INT_EDGE_BOTH, &circuitButtonISR);
    // Connect our custom signals so that when they are emitted, they will call the appropriate slot.
    // This makes it so when our CircuitButton emits a button pressed, the mainWindow on_Horn_pressed slot will be called
    connect(circuitButton, &CircuitButton::buttonPressed, this, &MainWindow::on_Horn_pressed, Qt::QueuedConnection);
    // This makes it so when our CircuitButton emits a button released, the mainWindow on_Horn_released slot will be called
    connect(circuitButton, &CircuitButton::buttonReleased, this, &MainWindow::on_Horn_released, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_headlights_clicked()
{
    // When the headlights button is clicked on the UI, we change the color of the button itself to represent on or off
    // We also use digitalWrite to turn the actual LED on or off
    if(headlightsOn) { // The headlights were already on, so we want to turn them off
        headlightsOn = false;
        digitalWrite(HEADLIGHTS_GPIO, LOW)
        ui->headlights->setStyleSheet("background-color:rgb(135,135,135)");// headlights now off
    }
    else { // The headlights were off, so we want to turn them on
        headlightsOn = true;
        digitalWrite(HEADLIGHTS_GPIO, HIGH)
        ui->headlights->setStyleSheet("background-color:rgb(255,255,192)");// headlights now on
    }
}

void MainWindow::on_about_clicked()
{
    // Hide the main window
    hide();
    // Create a new About dialog
    about = new About(this);
    //Show the about dialog
    about->show();
}


void MainWindow::on_Horn_pressed()
{
    // When the horn is pressed we start the hornTimer, which allows us to run code without blocking the UI
    // The timer itself will toggle the speaker on and off to make a sound
    hornTimer->start();
    // Update the color of our horn on the UI
    ui->Horn->setStyleSheet("border-radius:80; border-color:rgb(0,0,0); border-style:solid; border-width:3; background-color:rgb(255,0,0)");
}

void MainWindow::carHorn() {
    // This toggles the horn value between 0 and 1 to make a sound
    hornValue = (hornValue + 1) % 2;
    digitalWrite(HORN_GPIO, hornValue);
}


void MainWindow::on_Horn_released()
{
    // Stop the horn timer so that we don't make any more sound
    hornTimer->stop();
    // Reset the horn value to off
    hornValue = 0;
    // Make sure the horn's GPIO pin is off
    digitalWrite(HORN_GPIO, 0);
    // Reset the horn style to normal
    ui->Horn->setStyleSheet("border-radius:80; border-color:rgb(0,0,0); border-style:solid; border-width:3; background-color: rgb(240, 240, 240)");
}

