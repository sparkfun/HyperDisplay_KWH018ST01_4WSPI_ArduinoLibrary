//
// KWH018ST03 Display Class    			  
//

#ifndef _HYPERDISPLAY_KWH018ST01_4WSPI_H_
#define _HYPERDISPLAY_KWH018ST01_4WSPI_H_

#include "HyperDisplay_ILI9163C.h"


#define KWH018ST01_WIDTH 	128
#define KWH018ST01_HEIGHT 	160
#define KWH018ST01_START_ROW	0
#define KWH018ST01_START_COL	0
#define KWH018ST01_STOP_ROW 	159
#define KWH018ST01_STOP_COL		127

class KWH018ST01_4WSPI : public ILI9163C_4WSPI{
private:
protected:
public:

	

	KWH018ST01_4WSPI();	// Constructor

	uint8_t _bl;

	ILI9163C_STAT_t begin(uint8_t dcPin, uint8_t csPin, uint8_t blPin, SPIClass &spiInterface = SPI, uint32_t spiFreq = ILI9163C_SPI_DEFAULT_FREQ);
	ILI9163C_STAT_t defaultConfigure( void ); // The reccomended settings from the datasheet
	void startup( void );		// The default startup for this particular display

	 void getCharInfo(uint8_t val, char_info_t  pchar);

	// Some specialized drawing frunctions
	void clearDisplay( void );

	// Special Functions
	void setWindowDefaults(wind_info_t*  pwindow); // Overrrides default implementation in hyperdisplay class
	void setBacklight(uint8_t b);
};

#endif /* _HYPERDISPLAY_KWH018ST01_4WSPI_H_ */