/*This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License. 
To view a copy of this license, visit https://creativecommons.org/licenses/by-sa/4.0/deed.en */

#ifndef WAVES_H
#define WAVES_H
#include "Arduino.h"

enum waveform
{
  SINE, //Sinus
  RECT, //Triangle
  TRI,  //Rectangle
  PAUSE //Internal, do not use
};
#define MAX_VOLUME 32

namespace Waves
{
void init(uint8_t waveform = SINE, uint8_t duty_cycle = 50, uint8_t *envelope = NULL);
void play(uint16_t freq, uint16_t duration);

//Returns true while note is playing
boolean isPlaying();
} // namespace Waves

#endif
