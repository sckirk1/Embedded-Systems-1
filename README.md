# Overview

You will be creating an Car Dashboard Infotainment System, which will allow users to interact with a car. This can control the lights, volume, horn, fuel gauge, or any other systems you think would be nice to have controlled through a dashboard. The dashboard itself is going to be created and run using the QT framework, which should run through QT Creator on your raspberry pi to allow connetivity to the Pi's GPIO pins. The UI should in some way interact with a circuit which will mock our Car. This circuit can have LEDs to represent headlights and break lights, buttons to represent horns, or other components to represent other mechanical features of the car that you think would be cool to control. These don't have to be exact models of those systems, just some representation of them. We don't want you to rebuild a car from scratch (Unless you have the time in which case go for it!).

Your project should include at least three features, ideally more, that showcase your ability to have hardware and software communicate. Your dashboard should be styled an laid out in some way you think the end users would find useful. Think about how a user would actually interact with them and where it makes sense to place them. Also give it your own pizzazz, this should be something you think would look cool in a car!

### gpioExamples.cpp
This file contains an examples of how to use wiringPi in different ways to change the state of the circuit. 

### QT-Example
This contains example QT files that show how we have used wiringPi in tandem with QT framework. `QT-README.md` contains more information on this part of the examples.

