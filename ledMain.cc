#include <utility/ostream.h>
#include <gpio.h>
#include <alarm.h>
#include <usb.h>
#include <thread.h>

void sleep(unsigned long);
int changeBrightnessR();
int changeBrightnessG();
int changeBrightnessB();
int inputIntensity();

using namespace EPOS;

GPIO ledR('C', 3, GPIO::OUTPUT);
GPIO ledG('C', 1, GPIO::OUTPUT);
GPIO ledB('C', 0, GPIO::OUTPUT);
Thread * cbR;
Thread * cbG;
Thread * cbB;
Thread * usbIn;
int input;
int currentR = 10;
int currentG = 20;
int currentB = 30;
OStream cout;

int main(int argc, char** argv) {
	cbR = new Thread(changeBrightnessR);
	cbG = new Thread(changeBrightnessG);
	cbB = new Thread(changeBrightnessB);
	usbIn = new Thread(inputIntensity);
	//while (true) {
		usbIn->join();
		//tentar dar join em um só
		//cbR->join();
		//cbG->join();
		//cbB->join();
	//}
	
}

void sleep(unsigned long ms) {
    EPOS::Delay(ms *1); //Holds for -+ms+- microseconds
}

int inputIntensity() {
	unsigned int counter = 0;
	while(true) {
		counter++;
		if (counter > 2000) {
			input = USB::get();
			switch(input) {
				case 49: 
				currentR+=10;
				break;
				case 50:
				currentR-=10;
				break;
				case 51:
				currentG+=10;
				break;
				case 52:
				currentG-=10;
				break;
				case 53:
				currentB+=10;
				break;
				case 54:
				currentB-=10;
				case 55:
				for (int i=0; i<=100; i++) {
					currentR = i;
					sleep(100);
				}
				for (int i=100; i>=0; i--) {
					currentR = i;
					sleep(100);
				}
				break;
				default:
				currentR=0;
				currentG=0;
				currentB=0;
				break;
			}
			counter = 0;
				
		}
		Thread::yield();	
	}
	return input;
}

int changeBrightnessR() {
	while (true) {
    	ledR.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < currentR; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledR.get())
               	ledR.set(false);
        sleep(currentR);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessG() {
	while (true) {
    	ledG.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < currentG; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledG.get())
               	ledG.set(false);
        sleep(currentG);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessB() {
	while (true) {
    	ledB.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < currentB; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledB.get())
	           	ledB.set(false);
        sleep(currentB);
    	}
    	Thread::yield();
    }
    return 0;
}
