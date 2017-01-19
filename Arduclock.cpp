//Arduclock

/*
 * This class is for a self-sufficient clock, based on the Atmega 328P Timer 1.
 * Copyright (C) 2016  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduclock.h"

ISR(TIMER1_COMPA_vect){
	_tick++;
}

//public methods

//setup the library
void Arduclock::begin(){
	setupTimer();
}

//update method. To be called from main loop.
bool Arduclock::update(){
	if( _tick != _prevTick){
		_prevTick = _tick;
		updateSecond();
		return true;
	}
	return false;
}

//Setters for second, minute and hour
void Arduclock::setSecond(unsigned char second){
	_second = second % 60;
}

void Arduclock::setMinute(unsigned char minute){
	_minute = minute % 60;
}

void Arduclock::setHour(unsigned char hour){
	_hour = hour % 24;
}

//getters for second, minute and hour
unsigned char Arduclock::getSecond(){
	return _second;
}

unsigned char Arduclock::getMinute(){
	return _minute;
}

unsigned char Arduclock::getHour(){
	return _hour;
}



//protected methods

void Arduclock::updateSecond(){
	_second++;
	if(_second >= 60){
		updateMinute();
		_second = 0;
	}
}

void Arduclock::updateMinute(){
	_minute++;
	if(_minute >= 60){
		updateHour();
		_minute = 0;
	}
}

void Arduclock::updateHour(){
	_hour++;
	if(_hour >=24){
		_hour = 0;
	}
}

void Arduclock::setupTimer(){
  cli();
  TCNT1 = 0;
  //initialisation du compteur 1
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  //Set the max count of the timer
  OCR1A = COUNTER_TOP;
  //Timer mode = CTC ; prescaler 256
  TCCR1B |= (1 << WGM12) | (1 << CS12);
  //Set compare match A
  TIMSK1 |= (1 << OCIE1A);
  sei();
}