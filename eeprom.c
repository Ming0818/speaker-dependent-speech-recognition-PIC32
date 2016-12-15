/******************************************************************************
 * 				E E P R O M  F U N C T I O N  D E F I N I T I O N S									*
 *																																						*
 * Description: The definitions for the read/write functions for the EEPROM.	*
 ******************************************************************************/

// EEPROM declarations
#include "eeprom.h"

// Include the Arduino Wire library to provide I2C functionality
#include <Wire.h>

/****************************************************************************** 
 * Implementation of the write_eep_page function. This function will write a	*
 * page of data (up to 128 bytes). This is basically a buffer write mode.			*
 * This is better for the EEPROM as the number of write transactions an				*
 * EEPROM process is severely limited (i.e, writes damage the device).				*
 ******************************************************************************/ 
void 
write_eep_page(int i2c_addr, unsigned int page_addr, byte* data, int length)
{
	// Start I2C bus and begin transmission to EEPROM
  Wire.beginTransmission(i2c_addr);

  // Send the Most Significant Bit of the target address
  Wire.send((int) (page_addr >> 8));

  // Send the LSB of the target address
  Wire.send((int) (page_addr & 0xFF));

  // The send loop. Send the data byte by byte
  for(int i = 0; i < length; i++)
	{
    Wire.send(data[i]);
		
		// This delay has been reported to be necessary to write correctly. 
		delay(5);
	}

  // We are done transmitting
  Wire.endTransmission(true);

	// Add another small delay to make sure the communication settles
	delay(5);
}

// Read a page of data from the EEPROM. 
// The page can be any size smaller than 128 bytes.
void 
read_eep_page(int i2c_addr, unsigned int page_addr, byte* buffer, int length)
{
  // This code is identical to writing. This is the transaction init code.
   // Start I2C bus and begin transmission to EEPROM
  Wire.beginTransmission(i2c_addr);

  // Send the Most Significant Bit of the target address
  Wire.send((int) (page_addr >> 8));

  // Send the LSB of the target address
  Wire.send((int) (page_addr & 0xFF));

  // We are done with address information to EEPROM
  Wire.endTransmission();

	// Transmission delay as discussed in write_eep_page.
	delay(5);

  // Now we read
  Wire.requestFrom(i2c_addr, length);

  // Fill buffer with bytes from EEPROM
  for (int i = 0; i < length; i++)
  {
    // Grab EEPROM info only if it is online
    if (Wire.available()) 
      buffer[i] = Wire.receive();
  }
}

// vim:set ts=2 bs=2 sw=2:
