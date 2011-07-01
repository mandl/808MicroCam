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


void main()
{

	EX0 = 0;   // Disable EX0 Interrupt
	EA = 0;    // Disable Global Interrupt Flag

	CPUfreq = 0;   // 32 Mhz

	//LSRAM4Ken = 0x17;

	BIT_SET(Gpiooe7_0,4);

	while (1) {

		BIT_SET(Gpioo7_0,4);   // Led off

		delay_1s();

		BIT_CLEAR(Gpioo7_0,4); // Led on

		delay_1s();

	}


}


