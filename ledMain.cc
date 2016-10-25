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
int currentR = 0;
int currentG = 0;
int currentB = 0;
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
	while(true) {
		sleep(10000);
			input = USB::get();
			switch(input) {
				case 49:
				if(currentR<100)
				currentR+=1;
				break;
				case 50:
				if(currentR>1)
				currentR-=1;
				break;
				case 51:
				if(currentG<100)
				currentG+=1;
				break;
				case 52:
				if(currentG>1)
				currentG-=1;
				break;
				case 53:
				if(currentB<100)
				currentB+=1;
				break;
				case 54:
				if(currentB>1)
				currentB-=1;
				break;
				case 55:
				for (currentR=0; currentR<=500; currentR++) {
					Thread::yield();
					sleep(10000);
				}
				for (currentR=500; currentR>=0; currentR--) {
					Thread::yield();
					sleep(10000);
				}
				break;
				case 56:
				for (currentG=0; currentG<=500; currentG++) {
					Thread::yield();
					sleep(10000);
				}
				for (currentG=500; currentG>=0; currentG--) {
					Thread::yield();
					sleep(10000);
				}
				break;
				case 57:
				for (currentB=0; currentB<=500; currentB++) {
					Thread::yield();
					sleep(10000);
				}
				for (currentB=500; currentB>=0; currentB--) {
					Thread::yield();
					sleep(10000);
				}
				break;
				default:
				currentR=0;
				currentG=0;
				currentB=0;
				break;
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
