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
    	ledR.set(true);
    	ledG.set(true);
    	ledB.set(true);
    	cout<< "All LEDs on, waiting for input\n";
    	unsigned long a = USB::get();
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
