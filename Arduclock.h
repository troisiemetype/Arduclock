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

#ifndef ARDUCLOCK_H
#define ARDUCLOCK_H

//Counter top should be 52500, byt can vary following your board.
#define COUNTER_TOP	 			62470

class Arduclock{
public:
	Arduclock();

	void begin();
	bool update();

	unsigned char getSecond();
	unsigned char getMinute();
	unsigned char getHour();

protected:
	void setTimer();

	void updateSecond(unsigned char second);
	void updateMinute(unsigned char minute);
	void updateHour(unsigned char hour);

private:
	unsigned long _prevTick;
	volatile unsigned long _tick;

	unsigned char _second, _minute, _hour;
};

#endif