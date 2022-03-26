/*This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 
To view a copy of this license, visit https://creativecommons.org/licenses/by-sa/4.0/deed.en */

#include "waves.h"

using namespace Waves;

static const char BTN8 = 2;
static const char BTN7 = 3;
static const char BTN6 = 4;
static const char BTN4 = 5;
static const char BTN3 = 6;
static const char BTN2 = 7;
static const char BTN1 = 8;
static const char BTN5 = 9;
static const char BTNMOD = 10;

unsigned long lastDebounceTime = 0;

//Sum of ADSR values must not exceed 100%
uint8_t envelope[] = {
        20,  //attack[%]
        20, //decay[%]
        30,  //sustain[%]
        30, //release[%]
        16  //Sustain Level 1..32
};

void setup() {
    pinMode(BTN1, INPUT_PULLUP); //8
    pinMode(BTN2, INPUT_PULLUP); //7
    pinMode(BTN3, INPUT_PULLUP); //6
    pinMode(BTN4, INPUT_PULLUP); //4
    pinMode(BTN5, INPUT_PULLUP); //3
    pinMode(BTN6, INPUT_PULLUP); //2
    pinMode(BTN7, INPUT_PULLUP); // 1
    pinMode(BTN8, INPUT_PULLUP); // 5
    pinMode(BTNMOD, INPUT_PULLUP); // extra
    init(
            TRI, //TRI: Triangle, RECT: Rectangle
            50,  //duty cycle 0..100%, only matters for Triangle and Rectangle
            envelope);
}

void loop() {
    int reading =
            digitalRead(2) && digitalRead(3) && digitalRead(4) && digitalRead(5) && digitalRead(6) && digitalRead(7) &&
            digitalRead(8) && digitalRead(9) && digitalRead(10);
    unsigned long now = millis();
    if (reading == 1) {
        lastDebounceTime = now;
    }
    if (reading == 0) {
        if (now - lastDebounceTime > 50 && now - lastDebounceTime < 500) {
            lastDebounceTime = 0;
            int freq = 0;
            if (digitalRead(BTN1) == 0 ) {
                freq = 200;
            } else if(digitalRead(BTN2) == 0 ) {
                freq = 240;
            }  else if(digitalRead(BTN3) == 0 ) {
                freq = 280;
            }  else if(digitalRead(BTN4) == 0 ) {
                freq = 320;
            }  else if(digitalRead(BTN5) == 0 ) {
                freq = 360;
            }  else if(digitalRead(BTN6) == 0 ) {
                freq = 400;
            }  else if(digitalRead(BTN7) == 0 ) {
                freq = 440;
            }  else if(digitalRead(BTN8) == 0 ) {
                freq = 480;
            }
            Serial.println(freq);
            play(freq, 500);
            Serial.println("end play");
        }
    }

}
