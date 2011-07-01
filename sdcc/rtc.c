/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (either version 2 or
 * version 3) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <8052.h>
#include "delay_ms.h"
#include "SPCA1527.h"

void ext0_isr (void) __interrupt (0)
{
	BIT_CLEAR(Gpioo7_0,4); // Led on
}

void timer_isr (void) __interrupt (1)
{

}

void timer_isr2 (void) __interrupt (2)
{

}

void timer_isr3 (void) __interrupt (3)
{

}

void timer_isr4 (void) __interrupt (4)
{

}

void timer_isr5 (void) __interrupt (5)
{

}

void timer_isr6 (void) __interrupt (6)
{

}

void WriteRTCData(uint8_t addr, uint8_t mdata);
void WriteRTCCounter();

void WriteRTCAlarm();

void EnableRTCAlarmInter();


void main()
{



	CPUfreq = 0;   // 32 Mhz

	//LSRAM4Ken = 0x17;

	BIT_SET(Gpiooe7_0,4);

	BIT_SET(Gpioo7_0,4);   // Led off

	WriteRTCCounter();

	//delay_1s();

	//delay_1s();


	//BIT_CLEAR(Gpioo7_0,4); // Led on

	EX0 = 1;   // Disable EX0 Interrupt
	EA = 1;    // Disable Global Interrupt Flag

	WriteRTCAlarm();

	EnableRTCAlarmInter();

	while (1);


}

void WriteRTCAlarm()
{
	WriteRTCData(0x20,0xFF);
	WriteRTCData(0x21,0xFF);
	WriteRTCData(0x22,0x2);
	WriteRTCData(0x23,0);
	WriteRTCData(0x24,0);
	WriteRTCData(0x25,0);

}

void WriteRTCCounter()
{

	WriteRTCData(2,0x5A);

	WriteRTCData(0xd0,0);

	WriteRTCData(0xc0,0);

	WriteRTCData(0,0x0f);

	WriteRTCData(3,1);

	WriteRTCData(0,0x0d);

	WriteRTCData(0x0c,0);

	WriteRTCData(0x0d,2);


	// Write 48 bit
	WriteRTCData(0x10, 0);  // the bit [7:0] of load count of RTC timer
	WriteRTCData(0x11, 0);
	WriteRTCData(0x12, 0);
	WriteRTCData(0x13, 0);
	WriteRTCData(0x14, 0);
	WriteRTCData(0x15, 0);

	// Write Load
	WriteRTCData(0xb0, 1);


}

void EnableRTCAlarmInter()
{

	WriteRTCData(0xc0,0);

	WriteRTCData(0xd0,2); // The interrupt of alarm data match enable

	UnknownInt = UnknownInt | 0x01;


}

void WriteRTCData(uint8_t addr, uint8_t mdata)
{

	UnknownRTC = 1;

	RTCAddr = addr;

	RTCWData = mdata;

	RTC = 1;

	while ( BIT_CHECK(RTCRdy,0) != 1);  // Wait for ready

	//delay_ms();

	UnknownRTC = 0;
}


