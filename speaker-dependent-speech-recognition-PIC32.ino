#include <Wire.h>

#define disk1 0x50    //Address of 24LC1025 eeprom chip

/****************************************************************************** 
 * Implementation of the write_eep_page function. This function will write a  *
 * page of data (up to 128 bytes). This is basically a buffer write mode.     *
 * This is better for the EEPROM as the number of write transactions an       *
 * EEPROM process is severely limited (i.e, writes damage the device).        *
 ******************************************************************************/
byte write_eep_page(int i2c_addr, unsigned long page_addr, byte* data, int length)
{
  /**************************************************************************** 
   * To make sure that we can access the second 512 kbits of the ROM,         *
   * we have to increase the device address by shifting to the left one bit.  *
   * The device has a boundary after 64 kilobytes of address space, or 65536  *
   * addresses. This effectively makes the address 0x54 instead of 0x50.      *
   ****************************************************************************/ 
  if(page_addr > 0xFFFF)
    i2c_addr |= 0x08;
  
  // We also need to right-shift the address one place because the Wire library
  // does an internal shift to the left that screws up addressing otherwise.
  i2c_addr >>= 1;

  // Start I2C bus and begin transmission to EEPROM
  Wire.beginTransmission(i2c_addr);

  // Write read/write bit. 0 indicates a write
  Wire.write(0x00);

  // Send the Most Significant Bit of the target address
  Wire.write((int) (page_addr >> 8));

  // Send the LSB of the target address
  Wire.write((int) (page_addr & 0xFF));

  // The send loop. Send the data byte by byte
  for(int i = 0; i < length; i++)
  {
    Wire.write(data[i]);
  }

  // We are done transmitting
  byte ret = Wire.endTransmission();

  // Add another small delay to make sure the communication settles
  delay(5);

 return ret;
}

byte write_eep_byte(int i2c_addr, unsigned int byte_addr, byte data)
{

  /**************************************************************************** 
   * To make sure that we can access the second 512 kbits of the ROM,         *
   * we have to increase the device address by shifting to the left one bit.  *
   * The device has a boundary after 64 kilobytes of address space, or 65536  *
   * addresses. This effectively makes the address 0x54 instead of 0x50.      *
   ****************************************************************************/ 
  if(byte_addr > 0xFFFF)
    i2c_addr |= 0x08;
    
  Wire.beginTransmission(i2c_addr);
  Wire.write((int)(byte_addr >> 8)); // MSB
  Wire.write((int)(byte_addr & 0xFF)); // LSB
  Wire.write(data);
  
  byte ret = Wire.endTransmission();
  
  delay(5);
  return ret;
}

// Read a byte of data from the EEPROM. 
byte read_eep_byte(int i2c_addr, unsigned int byte_addr)
{
  // Variable for recevied byte.
  byte data = 0xFF;

  // Start I2C bus and begin transmission to EEPROM
   Wire.beginTransmission(i2c_addr);

  // Send the Most Significant Bit of the target address
  Wire.write((int) (byte_addr >> 8));

  // Send the LSB of the target address
  Wire.write((int) (byte_addr & 0xFF));

  // We are done with address information to EEPROM
  Wire.endTransmission();

  // Transmission delay as discussed in write_eep_page.
  delay(5);

  // Now we read one byte from the specified device.
  Wire.requestFrom(i2c_addr, 1);
  
  // If the I2C device is available, receive one byte from the EEPROM.
  if(Wire.available()) 
    data = Wire.read();
  
  // Return received data.
  return data;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();  
  
  write_eep_byte(disk1, 10, 0);
  write_eep_byte(disk1, 11, 1);
  write_eep_byte(disk1, 32768, 2);
  write_eep_byte(disk1, 80000, 3);
  Serial.println(read_eep_byte(disk1, 10), DEC);
  Serial.println(read_eep_byte(disk1, 32768), DEC);
  Serial.println(read_eep_byte(disk1, 80000), DEC);
  Serial.println(read_eep_byte(disk1, 11), DEC);
}

void loop(){}
