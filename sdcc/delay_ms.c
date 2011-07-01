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


void delay_ms()
{
	_asm
		mov	r5,#0x0a
00011$:	mov	r6,#0x64
00012$:	nop
		nop
		nop
		djnz	r6,00012$
		djnz	r5,00011$
		ret
		_endasm;
}


void delay_1s()
{
	_asm
		mov	r4,#0x64
00021$:	mov	r5,#0x64
00022$:	mov	r6,#0x64
00023$:	nop
		nop
		nop
	    djnz	r6,00023$
		djnz	r5,00022$
		djnz	r4,00021$
		ret
	_endasm;
}


