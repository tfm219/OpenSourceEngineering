//using the definitions in this library: https://github.com/Flydroid/ADS12xx-Library
#ifndef ADS1256_H
#define ADS1256_H

#include <SPI.h>
#include <Arduino.h>
#define SPI_SPEED 2500000


/* For information to the register and settings see manual page (p..) */

/* ADS1248 Register (see p42 for Register Map) */

#define   STATUS  (0x00) //Status Control Register 0
#define   MUX     (0x01) //Multiplexer Control Register 0
#define   ADCON   (0x02) //A/D Control Register 0
#define   DRATE   (0x03) //A/D Data Rate Control Register 0
#define   IO      (0X04) //GPIO Control Register 0
#define   OFC0    (0x05) //Offset Calibration Coefficient Register 1
#define   OFC1    (0x06) //Offset Calibration Coefficient Register 2
#define   OFC2    (0x07) //Offset Calibration Coefficient Register 2
#define   FSC0    (0x08) //Full scale Callibration Coefficient Register 0
#define   FSC1    (0x09) //Full scale Callibration Coefficient Register 1
#define   FSC2    (0x0A) //Full scale Callibration Coefficient REgister 2

/*STATUS - Status Control Register 0 ( see p30)*/
/* BIT7 - BIT6 -  BIT5   -  BIT4   -  BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* ID   - ID   -  ID     -  ID     -  ORDER  -  ACAL   -  BUFEN  -  DRDY */
#define STATUS_RESET (0x01) // Reset STATUS Register

/*Bits 7 - 4 ID3, ID2, ID1, ID0 Factory Programmed Identification Bits(Read Only)*/
/*ORDER1:0  Data Output Bit Order*/
#define ORDER_MSB (0x00) //B00000000 // Most significant Bit first (default)
#define ORDER_LSB (0x08) //B00001000//Least significant Bit first

/*Input data is always shifted in most significant byte and bit first. Output data is always shifted out most significant
byte first. The ORDER bit only controls the bit order of the output data within the byte.*/
/*ACAL1:0 Auto Calibration*/
#define ACAL_OFF (0x00) //B00000000 // Auto Calibration Disabled (default)
#define ACAL_ON  (0x04) //B00000100 // Auto Calibration Enabled

/*When Auto-Calibration is enabled, self-calibration begins at the completion of the WREG command that changes
the PGA (bits 0-2 of ADCON register), DR (bits 7-0 in the DRATE register) or BUFEN (bit 1 in the STATUS register)
values.*/
/*BUFEN1:0 Analog Input Buffer Enable*/
#define BUFEN_OFF (0x00) //B00000000 //Buffer Disabled (default)
#define BUFEN_ON  (0x02) //B00000010 //BUffer Enabled
/*DRDY1:0 Data Ready (Read Only) Duplicates the state of the DRDY pin*/

/* MUX - Multiplexer Control Register 0 (see p31 - bring together with bitwise OR | */
/* BIT7  - BIT6  -  BIT5   -  BIT4   -  BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* PSEL3 - PSEL2 -  PSEL1  -  PSEL0  -  NSEL3  -  NSEL2   - NSEL1   - NSEL0 */
#define MUX_RESET (0x01)      // Reset MUX0 Register

/* PSEL3:0 Input channel selection bits 
    If used: positive needs to be shifted << 4*/
#define AIN0   (0x00) //B00000000 //(default)
#define AIN1   (0x01) //B00000001 
#define AIN2   (0x02) //B00000010
#define AIN3   (0x03) //B00000011
#define AIN4   (0x04) //B00000100
#define AIN5   (0x05) //B00000101
#define AIN6   (0x06) //B00000110
#define AIN7   (0x07) //B00000111
#define AINCOM (0x08) //B00001000
/* PSEL3:0 Positive input channel selection bits */
#define P_AIN0   (0x00) //B00000000 //(default)
#define P_AIN1   (0x10) //B00010000
#define P_AIN2   (0x20) //B00100000
#define P_AIN3   (0x30) //B00110000
#define P_AIN4   (0x40) //B01000000
#define P_AIN5   (0x50) //B01010000
#define P_AIN6   (0x60) //B01100000
#define P_AIN7   (0x70) //B01110000
#define P_AINCOM (0x80) //B10000000
/* NSEL3:0 Negativ input channel selection bits */
#define N_AIN0   (0x00) //B00000000
#define N_AIN1   (0x01) //B00000001 //(default)
#define N_AIN2   (0x02) //B00000010
#define N_AIN3   (0x03) //B00000011
#define N_AIN4   (0x04) //B00000100
#define N_AIN5   (0x05) //B00000101
#define N_AIN6   (0x06) //B00000110
#define N_AIN7   (0x07) //B00000111
#define N_AINCOM (0x08) //B00001000

/*ADCON - A/D Control Register 0 ( see p31)*/
/* BIT7 - BIT6   -  BIT5   -  BIT4   -  BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* 0    - CLK1   -  CLK0   -  SDCS1  -  SDCS0  -  PGA2   -  PGA1   -  PAG0 */
#define ADCON_RESET (0x20) // Reset ADCON Register

/*CLK2:0 D0/CLKOUT Clock Out Rate Setting*/
#define CLK_OFF (0x00) //B00000000 //Clock Out off
#define CLK_1   (0x20) //B00100000 //Clock Out Frequency = fCLKIN (default)
#define CLK_2   (0x40) //B01000000 //Clock Out Frequency = fCLKIN/2
#define CLK_4   (0x60) //B01100000 //Clock Out Frequency = fCLKIN/4

/*When not using CLKOUT, it is recommended that it be turned off. These bits can only be reset using the RESET pin.*/
/*SDCS2:0 Sensor Detection Current Sources*/
#define SDCS_OFF (0x00) //B00000000//Sensor Detect Off (default)
#define SDCS_05  (0x80) //B00001000//Sensor Detect Current 0.5?A
#define SDCS_2   (0x10) //B00010000//Sensor Detect Current 2?A
#define SDCS_10  (0x18) //B00011000//Sensor Detect Current 10?A

/*The Sensor Detect Current Sources can be activated to verify the integrity of an external sensor supplying a signal to the
ADS1255/6. A shorted sensor produces a very small signal while an open-circuit sensor produces a very large signal.*/
/*PGA3:0 Programmable Gain Amplifier Setting*/
#define PGA_1  (0x20) //B00100000//(default)
#define PGA_2  (0x21) //B00100001
#define PGA_4  (0x22) //B00100010
#define PGA_8  (0x23) //B00100011
#define PGA_16 (0x24) //B00100100
#define PGA_32 (0x26) //B00100110
#define PGA_64 (0x27) //B00100111

/*DRATE - A/D Data Rate Register 0 ( see p32)*/
/* BIT7 - BIT6   -  BIT5   -  BIT4   -  BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* DR7  - DR6    -  DR5    -  DR4    -  DR3    -  DR2    -  DR1    -  DR0 */
#define DRATE_RESET 0xF0 // Reset DRATE Register

/*DR7:0 Data Rate Setting*/
#define DR_30000 (0xF0) //B11110000 //30.000 SPS (default)
#define DR_15000 (0xE0) //B11100000 //15.000 SPS
#define DR_7500  (0xD0) //B11010000 //7.500 SPS
#define DR_3750  (0xC0) //B11000000 //3.750 SPS
#define DR_2000  (0xB0) //B10110000 //2.000 SPS
#define DR_1000  (0xA1) //B10100001 //1.000 SPS
#define DR_500   (0x92) //B10010010 //500 SPS
#define DR_100   (0x82) //B10000010 //100 SPS
#define DR_60    (0x72) //B01110010 //60 SPS
#define DR_50    (0x63) //B01100011 //50 SPS
#define DR_30    (0x53) //B01010011 //30 SPS
#define DR_25    (0x43) //B01000011 //25 SPS
#define DR_15    (0x33) //B00110011 //15 SPS
#define DR_10    (0x23) //B00100011 //10 SPS
#define DR_5     (0x13) //B00010011 //5 SPS
#define DR2_5    (0x03) //B00000011 //2,5 SPS

/*IO - GPIO Control Register 0 ( see p32)*/
/* BIT7 - BIT6   -  BIT5   -  BIT4   -  BIT3   -  BIT2   -  BIT1   -  BIT0 */
/* DIR3 - DIR2   -  DIR1   -  DIR0   -  DIO3   -  DIO2   -  DIO1   -  DIO0 */
#define IO_RESET (0xE0) // Reset IO Register

/*DIR3 - Digital I/O Direction for Pin D3*/
#define DIR3_OUT (0x00) //B00000000 //D3 is an output
#define DIR_IN   (0x80) //B10000000 //D3 is an input (default)

/*DIR2 - Digital I/O Direction for Pin D3*/
#define DIR2_OUT (0x00) //B00000000 //D2 is an output
#define DIR2_IN  (0x40) //B01000000 //D2 is an input (default)

/*DIR1 - Digital I/O Direction for Pin D3*/
#define DIR1_OUT (0x00) //B00000000 //D1 is an output
#define DIR1_IN  (0x20) //B00100000 //D1 is an input (default)

/*DIR0 - Digital I/O Direction for Pin D3*/
#define DIR0_OUT (0x00) //B00000000 //D0/CLKOUT is an output
#define DIR0_IN  (0x10) //B00010000 //D0/CLKOUT is an input (default)
/*DIO3:0 Status of Digital I/O, Read Only*/

/* SPI COMMAND DEFINITIONS (p34) */
/*SYSTEM CONTROL */
#define   WAKEUP    (0x00)  //Exit Sleep Mode
#define   STANDBY   (0xFD)  //Enter Sleep Mode
#define   SYNC      (0xFC)  //Synchornize the A/D Conversion
#define   RESET     (0xFE)  //Reset To Power UP values
#define   NOP       (0xFF)  //No operation
/*DATA READ*/
#define   RDATA     (0x01)  //Read data once
#define   RDATAC    (0x03)  //Read data continously
#define   SDATAC    (0x0F)  //Stop reading data continously
/*READ REGISTER */
#define   RREG      (0x10)  //Read From Register
#define   WREG      (0x50)  //Write To Register
/*Calibration */
#define   SYSOCAL   (0xF3)  //System Offset Calibration
#define   SYSGCAL   (0xF2)  //System Gain Calibration
#define   SELFCAL   (0xF0)  //Self Offset and Gain Calibration
#define   SELFOCAL  (0xF1)  //Self Offset Calibration
#define   SELFGCAL  (0xF2)  //Self Offset and Gain Calibration

#define NOP1 "nop\n\t"
#define NOP2 "nop\n\t""nop\n\t"
#define NOP3 "nop\n\t""nop\n\t""nop\n\t"
#define NOP4 "nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP5 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP6 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP7 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP8 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP9 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP10 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP20 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP25 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP50 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP100 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"


#define pause4   __asm__ __volatile__(NOP50);
#define pause24  __asm__ __volatile__(NOP100 NOP100 NOP100);
#define pause50  __asm__ __volatile__(NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP25 NOP10);


#endif // ADS1256_H
