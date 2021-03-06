/**
  ******************************************************************************
  * @file    cc1101.h
  * @author  phoenix
  * @version V1.0.0
  * @date    20-October-2017
  * @brief   This module contains the low level operations for CC1101
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "cc1101.h"


//10, 7, 5, 0, -5, -10, -15, -20, dbm output power, 0x12 == -30dbm
uint8_t PaTabel[]={0xc0, 0xC8, 0x84, 0x60, 0x68, 0x34, 0x1D, 0x0E};

uint8_t temp1;//for debug

// Sync word qualifier mode = 30/32 sync word bits detected 
// CRC autoflush = false 
// Channel spacing = 199.951172 
// Data format = Normal mode 
// Data rate = 2.00224 
// RX filter BW = 58.035714 
// PA ramping = false 
// Preamble count = 4 
// Whitening = false 
// Address config = No address check 
// Carrier frequency = 400.199890 
// Device address = 0 
// TX power = 10 
// Manchester enable = false 
// CRC enable = true 
// Deviation = 5.157471 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Packet length = 255 
// Modulation format = GFSK 
// Base frequency = 399.999939 
// Modulated = true 
// Channel number = 1 
// PA table 
//#define PA_TABLE {0xc2,0x00,0x00,0x00,0x00,0x00,0x00,0x00}

//static const uint8_t CC1101InitData[23][2]= 
//{
//  {CC1101_IOCFG0,      0x06},
//  {CC1101_FIFOTHR,     0x47},
//	{CC1101_PKTCTRL1,    0x07},
//  {CC1101_PKTCTRL0,    0x05},
//  {CC1101_CHANNR,      0x00},
//  {CC1101_FSCTRL1,     0x06},
//  {CC1101_FREQ2,       0x0F},
//  {CC1101_FREQ1,       0x62},
//  {CC1101_FREQ0,       0x76},
//  {CC1101_MDMCFG4,     0xF6},
//  {CC1101_MDMCFG3,     0x43},
//  {CC1101_MDMCFG2,     0x13},
//  {CC1101_DEVIATN,     0x15},
//  {CC1101_MCSM0,       0x18},
//  {CC1101_FOCCFG,      0x16},
//  {CC1101_WORCTRL,     0xFB},
//  {CC1101_FSCAL3,      0xE9},
//  {CC1101_FSCAL2,      0x2A},
//  {CC1101_FSCAL1,      0x00},
//  {CC1101_FSCAL0,      0x1F},
//  {CC1101_TEST2,       0x81},
//  {CC1101_TEST1,       0x35},
//  {CC1101_MCSM1,       0x3B},
//};

// Sync word qualifier mode = 30/32 sync word bits detected 
// CRC autoflush = false 
// Channel spacing = 199.951172 
// Data format = Normal mode 
// Data rate = 76.767
// RX filter BW = 232.142857
// PA ramping = false 
// Preamble count = 4 
// Whitening = ture 
// Address config = Address check and 0 (0x00) and 255 (0xFF) broadcast
// Carrier frequency = 432.999817
// Device address = 5 
// TX power = 10 
// Manchester enable = ture 
// CRC enable = true 
// Deviation = 31.738281
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Packet length = 255 
// Modulation format = 2-FSK
// Base frequency = 432.999817
// Modulated = true 
// Channel number = 0 
// PA table 
#define PA_TABLE {0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00}

static const uint8_t CC1101InitData[][2]= 
{/*
  {CC1101_IOCFG0,        0x06},
  {CC1101_FIFOTHR,       0x47},
  {CC1101_PKTLEN,        0x0A},
  {CC1101_PKTCTRL1,      0x04},
  {CC1101_PKTCTRL0,      0x05},
  {CC1101_CHANNR,        0x00},
  {CC1101_FSCTRL1,       0x04},
  {CC1101_FREQ2,         0x10},
  {CC1101_FREQ1,         0xAF},
  {CC1101_FREQ0,         0xC1},
  {CC1101_MDMCFG4,       0xF7},
  {CC1101_MDMCFG3,       0x83},
  {CC1101_MDMCFG2,       0x33},
  {CC1101_DEVIATN,       0x15},
  {CC1101_MCSM1,         0x30},
  {CC1101_MCSM0,         0x18},
  {CC1101_FOCCFG,        0x16},
  {CC1101_BSCFG,	 0x1C},
  {CC1101_AGCCTRL2,      0x03},
  {CC1101_AGCCTRL1,      0x40},
  {CC1101_AGCCTRL0,  	 0x91},
  {CC1101_WORCTRL,       0xFB},
  {CC1101_FREND1,        0x56},
  {CC1101_FREND0,        0x11},
  {CC1101_FSCAL3,        0xE9},
  {CC1101_FSCAL2,        0x2A},
  {CC1101_FSCAL1,        0x00},
  {CC1101_FSCAL0,        0x1F},
  {CC1101_TEST2,         0x81},
  {CC1101_TEST1,         0x35},
  {CC1101_TEST0,         0x09},
  {CC1101_VERSION,       0x14},
  {CC1101_LQI,           0x7F},
  {CC1101_RSSI,          0x80},
  {CC1101_MARCSTATE,     0x01},
  {CC1101_VCO_VC_DAC,    0x94},
*/
  {CC1101_IOCFG0,      0x06},
  {CC1101_FIFOTHR,     0x47},
  {CC1101_PKTCTRL0,    0x05},
  {CC1101_FSCTRL1,     0x06},
  {CC1101_FREQ2,       0x10},
  {CC1101_FREQ1,       0xAF},
  {CC1101_FREQ0,       0xC1},
  {CC1101_MDMCFG4,     0xF7},
  {CC1101_MDMCFG3,     0x0A},
  {CC1101_MDMCFG2,     0x30},
  {CC1101_DEVIATN,     0x15},
  {CC1101_MCSM0,       0x18},
  {CC1101_FOCCFG,      0x16},
  {CC1101_WORCTRL,     0xFB},
  {CC1101_FREND0,      0x11},
  {CC1101_FSCAL3,      0xE9},
  {CC1101_FSCAL2,      0x2A},
  {CC1101_FSCAL1,      0x00},
  {CC1101_FSCAL0,      0x1F},
  {CC1101_TEST2,       0x81},
  {CC1101_TEST1,       0x35},
  {CC1101_TEST0,       0x09},
  {CC1101_VERSION,       0x14},
  {CC1101_LQI,           0x7F},
  {CC1101_RSSI,          0x80},
  {CC1101_MARCSTATE,     0x01},
  {CC1101_VCO_VC_DAC,    0x94},
};

/*
================================================================================
Function : CC1101WORInit()
    Initialize the WOR function of CC1101
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101WORInit(void)
{
    CC1101WriteReg(CC1101_MCSM0, 0x18);
    CC1101WriteReg(CC1101_WORCTRL, 0x78); //EVENT1 = 7,RC_CAL = 1,WOR_RES = 0
																					//tEvent1 = 750/fXOSC * 7 = 48*750/(26*10^6) = 1.385ms
    CC1101WriteReg(CC1101_MCSM2, 0x00);		//RX_TIME = 0,Duty cycle = 12.5%
																					//tRXtimeout = tEvent0 * Duty cycle = 129.75ms
    CC1101WriteReg(CC1101_WOREVT1, 0x8C);
		CC1101WriteReg(CC1101_WOREVT0, 0xA0);	//EVENT0 = 0d36000
																					//tEvent0 = 750/fXOSC * EVENT0 * 2^(5*WOR_RES)
																					//tEvent0 = 750/(26*10^6) * 36000 * 2^0 = 1.038s
}

//??????tEvent0 = 60.495s??tRXtimeout = 1.18s??????RX??????????17.72mA??SLEEP??????????0.3uA
//void CC1101WORInit(void)
//{
//    CC1101WriteReg(CC1101_MCSM0, 0x18);
//    CC1101WriteReg(CC1101_WORCTRL, 0x79); //EVENT1 = 7,RC_CAL = 1,WOR_RES = 1
//																					//tEvent1 = 750/fXOSC * 7 = 48*750/(26*10^6) = 1.385ms
//    CC1101WriteReg(CC1101_MCSM2, 0x00);		//RX_TIME = 0,Duty cycle = 1.95%
//																					//tRXtimeout = tEvent0 * Duty cycle = 1.18s
//		CC1101WriteReg(CC1101_WOREVT1, 0xFF);
//		CC1101WriteReg(CC1101_WOREVT0, 0xFF);	//EVENT0 = 0d65535
//																					//tEvent0 = 750/fXOSC * EVENT0 * 2^(5*WOR_RES)
//																					//tEvent0 = 750/(26*10^6) * 65535 * 2^5 = 60.495s
//}
/*
================================================================================
Function : CC1101SetWORMode()
    set the WOR function of CC1101,include configure IOCFG0,IOCFG2
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101SetWORMode(void)
{
		CC1101WriteReg(CC1101_IOCFG0, 0x46);
		CC1101WriteReg(CC1101_IOCFG2, 0x64);	//Event0 monitor
		CC1101WriteCmd(CC1101_SWORRST);
		CC1101WriteCmd(CC1101_SWOR);
}
/*
================================================================================
Function : CC1101ReadReg()
    read a byte from the specified register
INPUT    : addr, The address of the register
OUTPUT   : the byte read from the rigister
================================================================================
*/
uint8_t CC1101ReadReg(uint8_t addr)
{
    uint8_t i;
    CC1101_CSN_LOW();
    SPI_ExchangeByte(  addr | READ_SINGLE);
    i = SPI_ExchangeByte(  0xFF );
    CC1101_CSN_HIGH();
    return i;
}
/*
================================================================================
Function : CC1101ReadMultiReg()
    Read some bytes from the rigisters continously
INPUT    : addr, The address of the register
           buff, The buffer stores the data
           size, How many bytes should be read
OUTPUT   : None
================================================================================
*/
void CC1101ReadMultiReg(uint8_t addr, uint8_t *buff, uint8_t size)
{
    uint8_t i, j;
    CC1101_CSN_LOW();
    SPI_ExchangeByte(  addr | READ_BURST);
    for(i=0; i<size; i++)
    {
        for(j=0; j<20; j++);
        *(buff+i)=SPI_ExchangeByte(  0xFF);
    }
    CC1101_CSN_HIGH();
}
/*
================================================================================
Function : CC1101ReadStatus()
    Read a status register
INPUT    : addr, The address of the register
OUTPUT   : the value read from the status register
================================================================================
*/
uint8_t CC1101ReadStatus(uint8_t addr)
{
    uint8_t i;
    CC1101_CSN_LOW();
    SPI_ExchangeByte(  addr | READ_BURST);
    i = SPI_ExchangeByte(  0xFF );
    CC1101_CSN_HIGH();
    return i;
}
/*
================================================================================
Function : CC1101SetTRMode()
    Set the device as TX mode or RX mode
INPUT    : mode selection
OUTPUT   : None
================================================================================
*/
void CC1101SetTRMode(TRMODE mode)
{
    if(mode == TX_MODE)
    {
        CC1101WriteReg(CC1101_IOCFG0, 0x46);
        CC1101WriteCmd(CC1101_STX);  
    }
    else if(mode == RX_MODE)
    {
        CC1101WriteReg(CC1101_IOCFG0, 0x46);
        CC1101WriteCmd(CC1101_SRX);
    }
}
/*
================================================================================
Function : CC1101WriteReg()
    Write a byte to the specified register
INPUT    : addr, The address of the register
           value, the byte you want to write
OUTPUT   : None
================================================================================
*/
void CC1101WriteReg(uint8_t addr, uint8_t value)
{
    CC1101_CSN_LOW();
    for(int i=0; i<1000; i++);
    SPI_ExchangeByte(  addr);
    SPI_ExchangeByte(  value);
    for(int i=0; i<1000; i++);
    CC1101_CSN_HIGH();
}
/*
================================================================================
Function : CC1101WriteMultiReg()
    Write some bytes to the specified register
INPUT    : addr, The address of the register
           buff, a buffer stores the values
           size, How many byte should be written
OUTPUT   : None
================================================================================
*/
void CC1101WriteMultiReg(uint8_t addr, uint8_t *buff, uint8_t size)
{
    uint8_t i;
    CC1101_CSN_LOW();
    SPI_ExchangeByte(  addr | WRITE_BURST);
    for(i=0; i<size; i++)
    {
        SPI_ExchangeByte( *(buff+i));
    }
    CC1101_CSN_HIGH();
}
/*
================================================================================
Function : CC1101WriteCmd()
    Write a command byte to the device
INPUT    : command, the byte you want to write
OUTPUT   : None
================================================================================
*/
void CC1101WriteCmd(uint8_t command)
{
    CC1101_CSN_HIGH();
    CC1101_CSN_LOW();
    SPI_ExchangeByte(  command);
    CC1101_CSN_HIGH();
}
/*
================================================================================
Function : CC1101Reset()
    Reset the CC1101 device
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101Reset(void)
{
    uint16_t x;

    CC1101_CSN_HIGH();
    CC1101_CSN_LOW();
    CC1101_CSN_HIGH();
    for(x=0; x<1000; x++);
    CC1101WriteCmd(CC1101_SRES);
    for(x=0; x<1000; x++);
}
/*
================================================================================
Function : CC1101SetIdle()
    Set the CC1101 into IDLE mode
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101SetIdle(void)
{
    CC1101WriteCmd(CC1101_SIDLE);
}
/*
================================================================================
Function : CC1101ClrTXBuff()
    Flush the TX buffer of CC1101
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101ClrTXBuff(void)
{
    CC1101SetIdle();//MUST BE IDLE MODE
    CC1101WriteCmd(CC1101_SFTX);
}
/*
================================================================================
Function : CC1101ClrRXBuff()
    Flush the RX buffer of CC1101
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101ClrRXBuff(void)
{
    CC1101SetIdle();//MUST BE IDLE MODE
    CC1101WriteCmd(CC1101_SFRX);
}
/*
================================================================================
Function : CC1101SendPacket()
    Send a packet
INPUT    : txbuffer, The buffer stores data to be sent
           size, How many bytes should be sent
           mode, Broadcast or address check packet
OUTPUT   : None
================================================================================
*/
void CC1101SendPacket(uint8_t *txbuffer, uint8_t size, TX_DATA_MODE mode)
{
    uint8_t address;
    volatile uint8_t i;
    uint32_t time;
    
    if(mode == BROADCAST)             {address=0;}
    else if(mode == ADDRESS_CHECK)    {address=CC1101ReadReg(CC1101_ADDR);}
    CC1101ClrTXBuff();

    CC1101WriteReg(CC1101_TXFIFO, 255);
    CC1101_CSN_LOW();
    SPI_ExchangeByte(  CC1101_TXFIFO | WRITE_BURST);
    for(i=0; i<size; i++)
    {
        SPI_ExchangeByte( *(txbuffer+i));
    }
    CC1101_CSN_HIGH();
    
    
   // CC1101WriteReg(CC1101_TXFIFO, size);
    //CC1101WriteMultiReg(CC1101_TXFIFO, txbuffer, size);
    
    //CC1101WriteCmd(CC1101_SIDLE); 	//**********************????????????????????????????????**********************
    CC1101WriteCmd(CC1101_STX);
    /////CC1101SetTRMode(TX_MODE);
    //i = CC1101ReadStatus( CC1101_TXBYTES );//for test, TX status
    while(GPIO_ReadInputDataBit(CC1101_IRQ_GPIO_PORT, CC1101_IRQ_PIN) != 0)
    {
      time++;
      nop();
      if(time>1000000) break;
    };
    time=0; 
    while(GPIO_ReadInputDataBit(CC1101_IRQ_GPIO_PORT, CC1101_IRQ_PIN) == 0)
    {
      time++;
      nop();
      if(time>1000000) break;
    };
    //i = CC1101ReadStatus( CC1101_TXBYTES );//for test, TX status
    //CC1101WriteCmd(CC1101_SIDLE);
    CC1101WriteCmd(CC1101_SFTX);
    //CC1101ClrTXBuff();
}
/*
================================================================================
Function : CC1101GetRXCnt()
    Get received count of CC1101
INPUT    : None
OUTPUT   : How many bytes hae been received
================================================================================
*/
uint8_t CC1101GetRXCnt(void)
{
    return (CC1101ReadStatus(CC1101_RXBYTES) & BYTES_IN_RXFIFO);
}
/*
================================================================================
Function : CC1101SetAddress()
    Set the address and address mode of the CC1101
INPUT    : address, The address byte
           AddressMode, the address check mode
OUTPUT   : None
================================================================================
*/
void CC1101SetAddress(uint8_t address, ADDR_MODE AddressMode)
{
    uint8_t btmp=CC1101ReadReg(CC1101_PKTCTRL1) & ~0x03;
    CC1101WriteReg(CC1101_ADDR, address);
    if(AddressMode == BROAD_ALL)        {}
    else if(AddressMode == BROAD_NO)    {btmp |= 0x01;}
    else if(AddressMode == BROAD_0)     {btmp |= 0x02;}
    else if(AddressMode == BROAD_0AND255)   {btmp |= 0x03;}  
}
/*
================================================================================
Function : CC1101SetSYNC()
    Set the SYNC bytes of the CC1101
INPUT    : sync, 16bit sync 
OUTPUT   : None
================================================================================
*/
void CC1101SetSYNC(uint16_t sync)
{
    //CC1101WriteReg(CC1101_SYNC1, 0xFF & (sync>>8));
    //CC1101WriteReg(CC1101_SYNC0, 0xFF & sync);
    CC1101WriteReg(CC1101_SYNC1, 0xD3);
    CC1101WriteReg(CC1101_SYNC0, 0x91);
}
/*
================================================================================
Function : CC1101RecPacket()
    Receive a packet
INPUT    : rxBuffer, A buffer store the received data
OUTPUT   : 1:received count, 0:no data
================================================================================
*/
uint8_t CC1101RecPacket(uint8_t *rxBuffer, uint8_t *addr, uint8_t *rssi)
{
    uint8_t status[2];
    uint8_t pktLen;

    if (CC1101GetRXCnt() != 0)
    {
        pktLen=CC1101ReadReg(CC1101_RXFIFO);                    // Read length byte
        if((CC1101ReadReg(CC1101_PKTCTRL1) & ~0x03) != 0)
        {
            *addr = CC1101ReadReg(CC1101_RXFIFO);
        }
        if(pktLen == 0) {return 0;}
        else    {pktLen--;}
        CC1101ReadMultiReg(CC1101_RXFIFO, rxBuffer, pktLen);    // Pull data
        CC1101ReadMultiReg(CC1101_RXFIFO, status, 2);           // Read status bytes
				*rssi = status[0];

        CC1101ClrRXBuff();

        if(status[1] & CRC_OK)  {return pktLen;}
        else    {return 0;}
    }
    else    {return 0;}                                       // Error
}
/*
================================================================================
Function : CC1101Init()
    Initialize the CC1101, User can modify it
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101Init(uint8_t addr, uint16_t sync)
{
    volatile uint8_t i, j;
    SPI_Initial();
    CC1101Reset();    
    
    for(i=0; i<sizeof(CC1101InitData)/2; i++)
    {
        CC1101WriteReg(CC1101InitData[i][0], CC1101InitData[i][1]);
    }
    CC1101SetAddress(addr, BROAD_0AND255);
    CC1101SetSYNC(sync);
    //CC1101WriteReg(CC1101_MDMCFG1, 0x02); //Modem Configuration

    CC1101WriteMultiReg(CC1101_PATABLE, PaTabel, 8);

    i = CC1101ReadStatus(CC1101_PARTNUM);//for test, must be 0x00
    i = CC1101ReadStatus(CC1101_VERSION);//for test, refer to the datasheet,must be 0x14
}
/*
================================================================================
Function : int16_t CC1101ReadRSSI(void)
    Read the RSSI value of the CC1101
INPUT    : RSSI, 8bit 
OUTPUT   : rssi_dBm
================================================================================
*/
int16_t CC1101ReadRSSI(void)
{
	uint8_t rssi_dec;
	int16_t rssi_dBm;
	uint8_t	rssi_offset = 74;
	
	rssi_dec = CC1101ReadStatus(CC1101_RSSI);
	if(rssi_dec >= 128)
		rssi_dBm = (int16_t)((int16_t)(rssi_dec - 256)/2) - rssi_offset;
	else
		rssi_dBm = (rssi_dec/2) - rssi_offset;
	return rssi_dBm;
}
/*
================================================================================
Function : int16_t CC1101CalcRSSI_dBm(uint8_t)
    Calc the RSSI value to RSSI dBm
INPUT    : RSSI, 8bit 
OUTPUT   : rssi_dBm
================================================================================
*/
int16_t CC1101CalcRSSI_dBm(uint8_t rssi_dec)
{
	int16_t rssi_dBm;
	uint8_t	rssi_offset = 74;
	
	if(rssi_dec >= 128)
		rssi_dBm = (int16_t)((int16_t)(rssi_dec - 256)/2) - rssi_offset;
	else
		rssi_dBm = (rssi_dec/2) - rssi_offset;
	return rssi_dBm;
}
/*
================================================================================
------------------------------------THE END-------------------------------------
================================================================================
*/
