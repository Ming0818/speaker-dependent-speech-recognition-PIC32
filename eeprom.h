/******************************************************************************
 *               E E P R O M  F U N C T I O N  H E A D E R										*
 *																																						*
 * Author: 					Alex Brinister																						*
 * Derived from: 		Arduino Playground page on I2C EEPROMS										*
 * 									http://playground.arduino.cc/Code/I2CEEPROM  							*
 * Project: 				Speaker-dependent Speech Recognizer												*
 * License: 				GPL 3.0																										*
 *																																						*
 * Purpose: These functions are for working with the 24LC1025 I2C EEPROM			*
 *																																						*
 * Description: The speech recognizer will use an EEPROM to store speaker			*
 * 							data. This data will be read during normal device operation.	*
 * 							Only when the speaker-dependent training data needs						*
 * 							alteration will the EEPROM be written to. In general, EEPROMS *
 * 							do not like being written, making them perfect for holding		*
 * 							static data. In this application, the speech training set 		*
 * 							will almost never change after the first write. This may			*
 * 							change if this project is expanded.														*
 *****************************************************************************/

#ifndef EEPROM_H
#define EEPROM_H

/******************************************************************************
 * write_eep_page																															*
 *																																						*
 * Description: Write a page (64 bytes) of data to the EEPROM.								*
 * Params:																																		*
 * 	i2c_addr:		The address of the EEPROM on the I2C bus.											*
 * 	page_addr:	The starting address where to write the bytes to.							*
 *	data:				A byte array of the data to send to the EEPROM.								*
 *	length:			The length of the byte array.																	*
 *****************************************************************************/ 
void 
write_eep_page(int i2c_addr, unsigned int page_addr, byte* data, int length);

/******************************************************************************
 * read_eep_page																															*
 *																																						*
 * Description: Read a page (64 bytes) of data to the EEPROM.									*
 * Params:																																		*
 * 	i2c_addr:		The address of the EEPROM on the I2C bus.											*
 * 	page_addr:	The starting address where to write the bytes to.							*
 *	buffer:			A byte array of the buffer to hold data from the EEPROM.			*
 *	length:			The length of the byte array.																	*
 *****************************************************************************/ 
void
read_eep_page(int i2c_addr, unsigned int page_addr, byte* buffer, int length)

#endif /* end of eeprom.h */
