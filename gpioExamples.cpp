#include <wiringPi.h>
#include <softPwm.h>

#include <iostream>
#include <unistd.h>

void pollingExample() {
	int pinNum = 29; //This pin number is using the wiringPi numbering scheme. This is GPIO pin 21.
	
	wiringPiSetup(); //If you want to use the GPIO numberings instead, change this call to wiringPiSetupGpio();
	pinMode(pinNum, INPUT);
	
	// Repeatedly read the pin to check if the button was pressed (HIGH value) or not (LOW value)
	while (true) {
		int pinRead = digitalRead(pinNum);
		if (pinRead == 0) { // Button was not pressed
			std::cout<< "Button not Pressed" << std::endl;
		} else { // Button was pressed
			std::cout<< "YOU PRESSED IT" << std::endl;
		}
		sleep(1); // Sleep for a second so we don't constantly read
	}
	
}

void onInterrupt() { 
	// This method is called when the ISR detects a rising edge
	std::cout<< "YOU PRESSED IT" << std::endl;
}

void interruptExample() {
	int pinNum = 21;
	
	wiringPiSetup();
	
	// Create an ISR on the pin, which will call the onInterrupt method when it detects a rising edge
	wiringPiISR(pinNum, INT_EDGE_RISING, &onInterrupt);
	pinMode(pinNum, INPUT); // Technically don't need this call I believe, but it doesn't hurt
	
}

void blinkExample() {
	int pinNum = 29;
	
	wiringPiSetup();
	pinMode(pinNum, OUTPUT);
	
	int currentVal = 0;
	while (true) {
		currentVal = ((currentVal + 1) % 2); // Toggle the value between 0 and 1
		digitalWrite(pinNum, currentVal);
		sleep(1);
	}
}

void pwmExample() {
	int pin = 29;
	wiringPiSetup();
	
	softPwmCreate(pin, 0, 100); // Create a PWM that ranges from 0 to 100 on pin 29
	softPwmWrite(pin, 30); // Set the PWM to 30, which is a 30% duty cycle in our case. This creates a dim effect

}


int main() {
  // Uncomment the example you would like to run, otherwise it won't do anything
  
	//blinkExample();
	//pollingExample();
	//interruptExample();
	
	//pwmExample();
	
	while(true) { // Keeps the program running for the examples that do not have a while loop of their own
		sleep(1); 
	}
	
	return 0;
}
