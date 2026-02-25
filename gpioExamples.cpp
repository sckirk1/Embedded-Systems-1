#include <wiringPi.h>
#include <softPwm.h>

#include <iostream>
#include <unistd.h>

void pollingExample() {
	int pinNum = 29; //This pin number is using the wiringPi numbering scheme. This is GPIO pin 21.
	
	wiringPiSetup(); //If you want to use the GPIO numberings instead, change this call to wiringPiSetupGpio();
	pinMode(pinNum, INPUT);
	
	
	while (true) {
		int pinRead = digitalRead(pinNum);
		if (pinRead == 0) {
			std::cout<< "Button not Pressed" << std::endl;
		} else {
			std::cout<< "YOU PRESSED IT" << std::endl;
		}
		sleep(1);
	}
	
}

void onInterrupt() {
	std::cout<< "YOU PRESSED IT" << std::endl;
}

void interruptExample() {
	int pinNum = 21;
	
	wiringPiSetup();
	wiringPiISR(pinNum, INT_EDGE_RISING, &onInterrupt);
	pinMode(pinNum, INPUT);
	
}

void blinkExample() {
	int pinNum = 29;
	
	wiringPiSetup();
	pinMode(pinNum, OUTPUT);
	
	int currentVal = 0;
	while (true) {
		currentVal = ((currentVal + 1) % 2);
		digitalWrite(pinNum, currentVal);
		sleep(1);
	}
}

void pwmExample() {
	int pin = 29;
	wiringPiSetup();
	
	softPwmCreate(pin, 0, 100);
	softPwmWrite(pin, 30);

}


int main() {
  // Uncomment the example you would like to run, otherwise it won't do anything
  
	//blinkExample();
	//pollingExample();
	//interruptExample();
	
	//pwmExample();
	
	while(true) {
		sleep(1);
		
	}
	
	return 0;
}
