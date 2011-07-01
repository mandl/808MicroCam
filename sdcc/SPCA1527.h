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

#include <stdint.h>

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))



// This information is from the SPCA 533 Datasheet

xdata at 0X2000 uint8_t Cammode;

xdata at 0X2002 uint8_t SoftReset;

#define SWUSBRst 3

xdata at 0X2005 uint8_t IntTrxEn;  //Internal USB transceiver enable.

xdata at 0X2010 uint8_t Clk48mEn;    //The 48MHz Clock

//[0]: CDSP module
//[1]: DMA module
//[2]: FM module
//[3]: USB module
//[4]: Audio module
//[5]: SDRAM module
//[6]: JPEG module
//[7]: TVEnc module

xdata at 0X2011 UclkEn;  //The uclk Clock (12MHz)

//[0]: USB module
//[1]: Audio module

xdata at 0x2024 uint8_t CPUfreq;
//0: 32 MHz
//1: 24 MHz
//2: 12 MHz (default)
//3: 6 MHz
//4: 3 MHz
//5: 1.5 MHz
//6: 750KHz
//7: 375KHz

xdata at 0x2038 uint8_t Gpiooe7_0;
xdata at 0x2030 uint8_t Gpioo7_0;

xdata at 0X2040 uint8_t Gpioi7_0;       //General purpose IO input values
xdata at 0X2041 uint8_t Gpioi15_8;
xdata at 0X2042 uint8_t Gpioi23_16;
xdata at 0X2043 uint8_t Gpioi31_24;
xdata at 0X2044 uint8_t Gpioi39_32;
xdata at 0X2045 uint8_t Gpioi41_40;


// RTC
xdata at  0X2067 uint8_t UnknownRTC;

xdata at  0X2069 uint8_t RTC;

xdata at 0X206a uint8_t RTCRdy;   //When one, it indicates the previous cycle of accessing RTC have been complete.

xdata at 0X20C0 uint8_t UIInt;		// UI resume interrupt

xdata at 0X20eb uint8_t UnknownInt;

xdata at  0X206b uint8_t RTCAddr;   // The address of RTC register will be accessed.

xdata at 0X206c uint8_t RTCWData;    //The data of RTC register will be written.
xdata at 0X206d uint8_t RTCRData;    // The data of RTC register has been read.

// DMA

xdata at  0X23D0 uint8_t DMAInt;

// Flash

xdata at  0X24d0 uint8_t  CompactFlashInt;

// USB
xdata at 0X2500 uint8_t Ep0BufData; 	//The data port for the USB ep0 buffer.

xdata at 0X25D0 uint8_t USBInt0;
xdata at 0X25D1 uint8_t USBInt1;
xdata at 0X25D2 uint8_t USBInt2;


// Serial Interface Control Registers

xdata at 0x2901 uint8_t Transmode;

// 00: Synchronous Serial Normal mode
// 01: Synchronous Serial Burst mode
// 10: Using Three wire interface
// 11: Using Three wire interface by manual control
//

xdata at  0x2904 uint8_t SerialFreq;
//3’b000: CPUCLK div 2048
//3’b001: CPUCLK div 1024
//3’b010: CPUCLK div 512
//3’b011: CPUCLK div 256
//3’b100: CPUCLK div 128
//3’b101: CPUCLK div 64
//3’b110: CPUCLK div 32
//3’b111: CPUCLK div 16

xdata at 0x2905 uint8_t  Wrcount;  // Decide how many byte to write (Used in SSC mode)
//Decide how many byte to write (Used in SSC mode)
//4’h0: 16 Bytes
//4’h1: 1 Bytes
//.
//.
//4’hF: 15 Bytes

xdata at 0x2911 uint8_t  Data0;  //The data buffer0

xdata at 0x29B0 uint8_t Rstsif; // Write 1 to this bit will reset the serial interface

xdata at 0X27D0 uint8_t DRAMinten;

xdata at 0X2C00 uint8_t LSRAM4Ken;

// 0 r/w LSRAM4Ken Low bank (0x0000–0x0FFF) SRAM4K access enable
// 0: disable
// 1: enable

// 1 r/w HSRAM4Ken High bank (0x1000–0x1FFF) SRAM4K access enable
// 0: disable
// 1: enable

// 2 r/w Rampageen
// 0: Normal 8051 addressing method
// 1: Redirect unused RAM space to ROM space

//3 r/w Rompageen
// 0: 64K ROM space
// 1: 256 K ROM space

//4 r/w Shadowen
// 0: execute the program from the external ROM.
// 1: execute the program from the shadow memory if the address hit the
//shadow area.
//The shadow memory is the low 4K bytes of embedded 8K SRAM.

xdata at 0X2C03 uint8_t P3oeSel5_0;   // Port 3 output enable mode selection

xdata at 0X2C04 uint8_t Interrupt;    //Int0_n : active low if any interrupt happends

