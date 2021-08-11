#include <TM1638.h>
 
// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);
 
void setup() {
    // display a hexadecimal number and set  dots
    module.setDisplayToHexNumber(0x0001234, 0x80);
}
 
void loop() {
}
