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
#define SLEEP_FOR_NEXT_INPUT 20000
#define MAXIMUM_BRIGHTNESS 0 //Max. and min. represent the efficient range of the PWM algorithm 
#define MINIMUM_BRIGHTNESS 30
#define PWM_SCALE 700 //Sleep scaling for the PWM polling
#define INCREASE_BRIGHTNESS 1
#define DECREASE_BRIGHTNESS 1

GPIO ledR('C', 3, GPIO::OUTPUT);
GPIO ledG('C', 1, GPIO::OUTPUT);
GPIO ledB('C', 0, GPIO::OUTPUT);
Thread * cbR;
Thread * cbG;
Thread * cbB;
Thread * usbIn;
int input;
int currentR = MAXIMUM_BRIGHTNESS;
int currentG = MAXIMUM_BRIGHTNESS;
int currentB = MAXIMUM_BRIGHTNESS;
OStream cout;

int main(int argc, char** argv) {
	cbR = new Thread(changeBrightnessR);
	cbG = new Thread(changeBrightnessG);
	cbB = new Thread(changeBrightnessB);
	usbIn = new Thread(inputIntensity);
	usbIn->join();
}

void sleep(unsigned long ms) {
    EPOS::Delay(ms *1); //Holds for -+ms+- microseconds
}

int inputIntensity() {
	while(true) {
		sleep(SLEEP_FOR_NEXT_INPUT);
			input = USB::get();
			Thread::yield();
			switch(input) {
				case 49:
				if(currentR<MINIMUM_BRIGHTNESS)
				currentR+=INCREASE_BRIGHTNESS;
				break;
				case 50:
				if(currentR>MAXIMUM_BRIGHTNESS+1)
				currentR-=DECREASE_BRIGHTNESS;
				break;
				case 51:
				if(currentG<MINIMUM_BRIGHTNESS)
				currentG+=INCREASE_BRIGHTNESS;
				break;
				case 52:
				if(currentG>MAXIMUM_BRIGHTNESS+1)
				currentG-=DECREASE_BRIGHTNESS;
				break;
				case 53:
				if(currentB<MINIMUM_BRIGHTNESS)
				currentB+=INCREASE_BRIGHTNESS;
				break;
				case 54:
				if(currentB>MAXIMUM_BRIGHTNESS+1)
				currentB-=DECREASE_BRIGHTNESS;
				break;
				case 55:
				for (currentR=MINIMUM_BRIGHTNESS; currentR>MAXIMUM_BRIGHTNESS; currentR--) {
					Thread::yield();
					sleep(150000);
				}
				for (currentR=MAXIMUM_BRIGHTNESS; currentR<MINIMUM_BRIGHTNESS; currentR++) {
					Thread::yield();
					sleep(150000);
				}
				break;
				case 56:
				for (currentG=MINIMUM_BRIGHTNESS; currentG>MAXIMUM_BRIGHTNESS; currentG--) {
					Thread::yield();
					sleep(150000);
				}
				for (currentG=MAXIMUM_BRIGHTNESS; currentG<MINIMUM_BRIGHTNESS; currentG++) {
					Thread::yield();
					sleep(150000);
				}
				break;
				case 57:
				for (currentB=MINIMUM_BRIGHTNESS; currentB>MAXIMUM_BRIGHTNESS; currentB--) {
					Thread::yield();
					sleep(150000);
				}
				for (currentB=MAXIMUM_BRIGHTNESS; currentB<MINIMUM_BRIGHTNESS; currentB++) {
					Thread::yield();
					sleep(150000);
				}
				break;
				default:
				currentR=MAXIMUM_BRIGHTNESS;
				currentG=MAXIMUM_BRIGHTNESS;
				currentB=MAXIMUM_BRIGHTNESS;
				break;
			}
		sleep(SLEEP_FOR_NEXT_INPUT);			
		Thread::yield();	
	}
	return input;
}

int changeBrightnessR() {
	while (true) {
		if(currentR != MINIMUM_BRIGHTNESS)
    	ledR.set(true);
    	// Loop over duty cycle
    	for (int x = MAXIMUM_BRIGHTNESS; x < currentR; x++)
    	{   
        	// Set LED off when it's on
        	 if (x > ledR.get())
               	ledR.set(false);
        sleep(PWM_SCALE);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessG() {
	while (true) {
		if(currentG != MINIMUM_BRIGHTNESS)
    	ledG.set(true);
    	// Loop over duty cycle
    	for (int x = MAXIMUM_BRIGHTNESS; x < currentG; x++)
    	{   
        	// Set LED off when it's on
        	 if (x > ledG.get())
               	ledG.set(false);
        sleep(PWM_SCALE);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessB() {
	while (true) {
		if(currentB != MINIMUM_BRIGHTNESS)
    	ledB.set(true);
    	// Loop over duty cycle
    	for (int x = MAXIMUM_BRIGHTNESS; x < currentB; x++)
    	{   
        	// Set LED off when it's on
        	 if (x > ledB.get())
	           	ledB.set(false);
        sleep(PWM_SCALE);
    	}
    	Thread::yield();
    }
    return 0;
}
