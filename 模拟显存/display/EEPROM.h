#ifndef EEPROM_h
#define EEPROM_h

#include <inttypes.h>

#define	e2pReset()	do { ECCR |= 0x20; } while(0)
#define	e2pSWMON()	do { ECCR = 0x80; ECCR |= 0x10; } while(0);
#define	e2pSWMOFF()	do { ECCR = 0x80; ECCR &= 0xEF; } while(0);

class EEPROMClass
{
  public:
	EEPROMClass() { ECCR = 0x80; ECCR = 0x4C; };

	uint8_t read(uint16_t);
	void write(uint16_t, uint8_t);
	void read_block(uint8_t *, uint16_t, uint8_t);
	void write_block(uint8_t *, uint16_t, uint8_t);
	uint32_t read32(uint16_t);
	void write32(uint16_t, uint32_t);
	void writeSWM(uint16_t, uint32_t *, uint8_t);
	void readSWM(uint16_t, uint32_t *, uint8_t);
};

extern EEPROMClass EEPROM;

#endif

