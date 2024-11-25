#pragma once
#include "../setup/modules.h"


/**
 * @brief Adds a timestamp to a line on the SD card.
 * 
 */
void printTimeToSD() {
    myFile = SD.open(SENSOR_DATA_FILENAME, FILE_WRITE);
    if (myFile) {
      myFile.print(myRTC.getYear(), DEC);
      myFile.print("-");
      myFile.print(myRTC.getMonth(century), DEC);
      myFile.print("-");
      myFile.print(myRTC.getDate(), DEC);
      myFile.print(" ");
      myFile.print(myRTC.getHour(h12Flag, pmFlag), DEC); //24-hr
      myFile.print(":");
      myFile.print(myRTC.getMinute(), DEC);
      myFile.print(": ");
      myFile.print(myRTC.getSecond(), DEC);
      myFile.print(" ; ");
    } else {
      COM_DEBUG.println("Error at opening SD file for adding RTC time.");
    }
    myFile.close();
}


/*----------------------------------------------------------------------------------------------------*/
/*                                                                                                    */
/*          FUNCTIONS TO SET TIME ON RTC. NOT USED IN PROJECT. LEFT FOR FUTURE USE.                   */  
/*                                                                                                    */
/*----------------------------------------------------------------------------------------------------*/

/**
 * @brief Shows the settings configuring the time. Used in combination with inputDateFromSerial().
 * This function is written by Eric Ayars, who made the library used ("DS3231.h")
 * 
 */
void showRTCTimeSettings(){
  // Request the time correction on the Serial
  delay(1000);
  COM_DEBUG.println("Format YYMMDDwhhmmssx");
  COM_DEBUG.println("Where YY = Year (ex. 20 for 2020)");
  COM_DEBUG.println("      MM = Month (ex. 04 for April)");
  COM_DEBUG.println("      DD = Day of month (ex. 09 for 9th)");
  COM_DEBUG.println("      w  = Day of week from 1 to 7, 1 = Sunday (ex. 5 for Thursday)");
  COM_DEBUG.println("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  COM_DEBUG.println("      mm = minutes (ex. 02)");
  COM_DEBUG.println("      ss = seconds (ex. 42)");
  COM_DEBUG.println("Example for input : 2004095090242x");
  COM_DEBUG.println("-----------------------------------------------------------------------------");
  COM_DEBUG.println("Please enter the current time to set on DS3231 ended by 'x':");
}

/**
 * @brief Sets time from the Serial monitor.
 * This function is written by Eric Ayars, who made the library used ("DS3231.h").
 * 
 */
void setRTCTimeFromSerialInput() {
  // If something is coming in on the serial line, it's
  // a time correction so set the clock accordingly.
  if (COM_DEBUG.available()) {
    inputDateFromSerial();

    myRTC.setClockMode(false);  // set to 24h

    myRTC.setYear(year);
    myRTC.setMonth(month);
    myRTC.setDate(date);
    myRTC.setDoW(dow);
    myRTC.setHour(hour);
    myRTC.setMinute(minute);
    myRTC.setSecond(second);

    // Give time at next five seconds
    for (uint8_t i = 0; i < 5; i++){
        delay(1000);
        COM_DEBUG.print(myRTC.getYear(), DEC);
        COM_DEBUG.print("-");
        COM_DEBUG.print(myRTC.getMonth(century), DEC);
        COM_DEBUG.print("-");
        COM_DEBUG.print(myRTC.getDate(), DEC);
        COM_DEBUG.print(" ");
        COM_DEBUG.print(myRTC.getHour(h12Flag, pmFlag), DEC); //24-hr
        COM_DEBUG.print(":");
        COM_DEBUG.print(myRTC.getMinute(), DEC);
        COM_DEBUG.print(":");
        COM_DEBUG.println(myRTC.getSecond(), DEC);
    }

    // Notify that we are ready for the next input
    COM_DEBUG.println("Please enter the current time to set on DS3231 ended by 'x':");
  }
  delay(1000);
}

/**
 * @brief Configures the time. Used in combination with showRTCTimeSettings().
 * This function is written by Eric Ayars, who made the library used ("DS3231.h")
 * 
 */
void inputDateFromSerial() {
	// Call this if you notice something coming in on
	// the serial port. The stuff coming in should be in
	// the order YYMMDDwHHMMSS, with an 'x' at the end.
	boolean isStrComplete = false;
	char inputChar;
	byte temp1, temp2;
	char inputStr[20];

	uint8_t currentPos = 0;
	while (!isStrComplete) {
		if (COM_DEBUG.available()) {
			inputChar = COM_DEBUG.read();
			inputStr[currentPos] = inputChar;
			currentPos += 1;

      // Check if string complete (end with "x")
			if (inputChar == 'x') {
				isStrComplete = true;
			}
		}
	}
	COM_DEBUG.println(inputStr);

  // Find the end of char "x"
  int posX = -1;
  for(uint8_t i = 0; i < 20; i++) {
    if(inputStr[i] == 'x') {
      posX = i;
      break;
    }
  }

  // Consider 0 character in ASCII
  uint8_t zeroAscii = '0';

	// Read Year first
	temp1 = (byte)inputStr[posX - 13] - zeroAscii;
	temp2 = (byte)inputStr[posX - 12] - zeroAscii;
	year = temp1 * 10 + temp2;

	// now month
	temp1 = (byte)inputStr[posX - 11] - zeroAscii;
	temp2 = (byte)inputStr[posX - 10] - zeroAscii;
	month = temp1 * 10 + temp2;

	// now date
	temp1 = (byte)inputStr[posX - 9] - zeroAscii;
	temp2 = (byte)inputStr[posX - 8] - zeroAscii;
	date = temp1 * 10 + temp2;

	// now Day of Week
	dow = (byte)inputStr[posX - 7] - zeroAscii;

	// now Hour
	temp1 = (byte)inputStr[posX - 6] - zeroAscii;
	temp2 = (byte)inputStr[posX - 5] - zeroAscii;
	hour = temp1 * 10 + temp2;

	// now Minute
	temp1 = (byte)inputStr[posX - 4] - zeroAscii;
	temp2 = (byte)inputStr[posX - 3] - zeroAscii;
	minute = temp1 * 10 + temp2;

	// now Second
	temp1 = (byte)inputStr[posX - 2] - zeroAscii;
	temp2 = (byte)inputStr[posX - 1] - zeroAscii;
	second = temp1 * 10 + temp2;
}