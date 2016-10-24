//Simple LED thread for reading usb and turning LEDs out

#include <utility/ostream.h>
#include <gpio.h>
#include <alarm.h>
#include <usb.h>

void sleep(unsigned long);

using namespace EPOS;

GPIO ledR('C', 3, EPOS::GPIO::OUTPUT);
GPIO ledG('C', 1, EPOS::GPIO::OUTPUT);
GPIO ledB('C', 0, EPOS::GPIO::OUTPUT);
OStream cout;
int main(int argc, char** argv) {
    while(true) {
    	cout<< "Waiting for input\n";
    	unsigned long a = USB::get();
    	/*
    	//Turn off all LEDs
    	case 48:
    	ledR.set(false);
    	ledG.set(false);
    	ledB.set(false);
    	break;
    	//Turn on all LEDs
    	case 49:
    	ledR.set(true);
    	ledG.set(true);
    	ledB.set(true);
    	break;
    	//Invert all LEDs values
    	case 50:
    	ledR.set(!ledR.get());
    	ledG.set(!ledG.get());
    	ledB.set(!ledB.get());
    	break;
    	//Try to simulate (software) PWM on all LEDs
    	case 51:
    	unsigned long period = 1;
    	while(period <= 1000) {
    	ledR.set(!ledR.get());
    	ledG.set(!ledG.get());
    	ledB.set(!ledB.get());
    	sleep(1);
    	period++;
    	}
    	break;
    	//Turn on R, G, then B for 100ms each
    	case 52:
    	ledR.set(false);
    	ledG.set(false);
    	ledB.set(false);
    	ledR.set(true);
    	sleep(100);
    	ledR.set(false);
    	ledG.set(true);
    	sleep(100);
    	ledG.set(false);
    	ledB.set(true);
    	sleep(100);
    	ledB.set(false);
    	//Turn on B, G, then R for 100ms each
    	case 53:
        ledR.set(false);
    	ledG.set(false);
    	ledB.set(false);
    	ledB.set(true);
    	sleep(100);
    	ledB.set(false);
    	ledG.set(true);
    	sleep(100);
    	ledG.set(false);
    	ledR.set(true);
    	sleep(100);
    	ledR.set(false);
    	*/
    	switch (a) {
            case 48:
            ledR.set(false);
            cout<< a;
            break;
			case 49:
			ledG.set(false);
			cout<< a;
			break;
			case 50:
			ledB.set(false);
			cout<< a;
			break;
			default:
			cout<< a;
			break;
		}
        sleep(1000);
    }
}

void sleep(unsigned long ms) {
    EPOS::Delay(ms * 1000); //Maintains current LEDs state for -+ms+- milliseconds
}
