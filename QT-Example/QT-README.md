# QT Example
This example contains sample project files for a QT project. This project will not compile or run as there are no UI files or cmake/qmake files, it is meant as a reference. It contains examples of writing to the GPIO pins based on QT signals, opening and closing multiple windows, setting up the GPIO pins, and converting an ISR notification to a QT signal for use in the UI. The following sections will explain the purpose of the files. Each file should be commented to explain most of the logic and calls happening. 

### main.cpp
This is the main entry point for the QTApplication. It creates and instance of the MainWindow and shows it to the user.

### gpioconsstants.h
This file is an example of a nice way to organize all the GPIO pin numberings. The benefit of having these constants in a separate file is that any other file that needs these pins can import this header and have the same pin numbers as everywhere else. This also means that if you end up changing the circuit and need to change the GPIO pins you only need to update this file and do not need to search for every instance of the pin number. 

### circuitbutton.h and circuitbutton.cpp
These files are creating a custom class which lets us convert the ISR interrupt into a QT signal. The benefit of this is that now our circuit interrupt can nicely interact with the UI and not interfere or block the UI thread. The ISR requires the method it calls to be effectively static, meaning that you are not able to interact with the UI at all as all UI objects are not static. Converting it to a signal lets us notify the mainwindow that something has happened, which in turn gives us access to the UI as slots are not static. The setup of this button happens at the beginning of mainwindow.cpp, which has comments explaining why we are doing each call. 

### about.h and about.cpp
This is an example of a second window, which really only has the functionality to show and hide itself. 

### mainwindow.h and mainwindow.cpp
This is our main window class. There are examples in here of toggling an led with a button, setting up an ISR, and creating custom slots and signals to allow the ISR to interact with the UI. 