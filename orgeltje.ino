/*This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 
To view a copy of this license, visit https://creativecommons.org/licenses/by-sa/4.0/deed.en */
#include <Arduino.h>
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

bool isPlayingHere = false;
uint8_t instrument = 0;

unsigned long lastDebounceTime = 0;
//
//Sum of ADSR values must not exceed 100%
uint8_t envelope0[] = {
        20,  //attack[%]
        19, //decay[%]
        41,  //sustain[%]
        20, //release[%]
        16  //Sustain Level 1..32
};

//Sum of ADSR values must not exceed 100%
uint8_t envelope1[] = {
        0,  //attack[%]
        20, //decay[%]
        1,  //sustain[%]
        79, //release[%]
        16  //Sustain Level 1..32
};

int *freqs;

int freqs0[] = {
        131,
        147,
        165,
        175,
        196,
        220,
        247,
        262
};

int freqs1[] = {
        98,
        110,
        131,
        147,
        165,
        196,
        220,
        262
};
int time0 = 300;
int time1 = 150;
int timeToUse = 300;


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
            envelope0);
    freqs = freqs0;
}

void loop() {
    int reading =
            digitalRead(2) && digitalRead(3) && digitalRead(4) && digitalRead(5) && digitalRead(6) && digitalRead(7) &&
            digitalRead(8) && digitalRead(9) && digitalRead(10);
    unsigned long now = millis();
    if (reading == 1) {
        lastDebounceTime = now;
    }
    if (reading == 0 && !isPlayingHere) {
        Serial.println("Will start playing");
        if (now - lastDebounceTime > 50 && now - lastDebounceTime < 500) {
            lastDebounceTime = 0;
            uint8_t volume = 32;
            int freq = 0;
            if (digitalRead(BTN1) == 0) {
                freq = freqs[0];
            } else if (digitalRead(BTN2) == 0) {
                freq = freqs[1];
            } else if (digitalRead(BTN3) == 0) {
                freq = freqs[2];
            } else if (digitalRead(BTN4) == 0) {
                freq = freqs[3];
            } else if (digitalRead(BTN5) == 0) {
                freq = freqs[4];
            } else if (digitalRead(BTN6) == 0) {
                freq = freqs[5];
            } else if (digitalRead(BTN7) == 0) {
                freq = freqs[6];
            } else if (digitalRead(BTN8) == 0) {
                freq = freqs[7];
            }
            if (freq != 0) {
                play(freq, timeToUse, volume);
                isPlayingHere = true;
            }
            if (digitalRead(BTNMOD) == 0) {
                isPlayingHere = true;
                if (instrument == 0) {
                    freqs = freqs1;
                    timeToUse = time1;
                    instrument = 1;
                    reinit(
                            TRI, //TRI: Triangle, RECT: Rectangle
                            20,  //duty cycle 0..100%, only matters for Triangle and Rectangle
                            envelope1);
                } else {
                    freqs = freqs0;
                    timeToUse = time0;
                    instrument = 0;
                    reinit(
                            TRI, //TRI: Triangle, RECT: Rectangle
                            50,  //duty cycle 0..100%, only matters for Triangle and Rectangle
                            envelope0);
                }
            }
        }
    }
    if (reading == 1 && isPlayingHere) {
        Serial.println("Will stop playing");
        stop();
        isPlayingHere = false;
    }
}
