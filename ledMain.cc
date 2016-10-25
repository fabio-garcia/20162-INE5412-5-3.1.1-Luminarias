//Simple LED thread for reading usb and turning LEDs out

#include <utility/ostream.h>
#include <gpio.h>
#include <alarm.h>
#include <usb.h>
#include <thread.h>

void sleep(unsigned long);
int changeBrightness(int intensity);
int changeBrightnessR(int intensity);
int changeBrightnessG(int intensity);
int changeBrightnessB(int intensity);
int inputIntensity(int input);

using namespace EPOS;

GPIO ledR('C', 3, EPOS::GPIO::OUTPUT);
GPIO ledG('C', 1, EPOS::GPIO::OUTPUT);
GPIO ledB('C', 0, EPOS::GPIO::OUTPUT);
Thread * cbR;
Thread * cbG;
Thread * cbB;
Thread * usbIn;
int current = 200;
int input;
OStream cout;
int main(int argc, char** argv) {
	usbIn = new Thread(inputIntensity, input);
	cbR = new Thread(changeBrightnessR, 0);
	cbG = new Thread(changeBrightnessG, 50);
	cbB = new Thread(changeBrightnessB, 100);
	while (true) {
		usbIn->join();
		cbR->join();
		cbG->join();
		cbB->join();
	}
	
}

void sleep(unsigned long ms) {
    EPOS::Delay(ms *1); //Holds for -+ms+- microseconds
}

int inputIntensity(int input) {
	while(true) {
	sleep(1000);
	input = USB::get();
	cout << input;
	
	}
	return input;
}

int changeBrightnessR(int intensity) {
	while (true) {
    	ledR.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < intensity; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledR.get())
        		{
                	ledR.set(false);
            	}
        sleep(intensity);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessG(int intensity) {
	while (true) {
    	ledG.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < intensity; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledG.get())
        		{
                	ledG.set(false);
            	}
        sleep(intensity);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessB(int intensity) {
	while (true) {
    	ledB.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < intensity; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledB.get())
        		{
                	ledB.set(false);
            	}
        sleep(intensity);
    	}
    	Thread::yield();
    }
    return 0;
}

int changeBrightnessAll(int intensity) {
	while (true) {
	// Set all LEDs on
    	ledR.set(true);
    	ledG.set(true);
    	ledB.set(true);
    	// Loop over duty cycle
    	for (int x = 0; x < intensity; x++)
    	{   
        	// Set LEDs off when they're on
        	 if (x > ledR.get())
        		{
                	ledR.set(false);
    				ledG.set(false);
    				ledB.set(false);
            	}
        sleep(intensity);
    	}
    }
    return 0;
}