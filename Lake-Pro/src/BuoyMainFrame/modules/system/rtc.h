#pragma once
#include "../setup/modules.h"

// This function is written by Eric Ayars, who made the library used ("DS3231.h")
void showRTCTimeSettings(){
  // Request the time correction on the Serial
  delay(4000);
  Serial.println("Format YYMMDDwhhmmssx");
  Serial.println("Where YY = Year (ex. 20 for 2020)");
  Serial.println("      MM = Month (ex. 04 for April)");
  Serial.println("      DD = Day of month (ex. 09 for 9th)");
  Serial.println("      w  = Day of week from 1 to 7, 1 = Sunday (ex. 5 for Thursday)");
  Serial.println("      hh = hours in 24h format (ex. 09 for 9AM or 21 for 9PM)");
  Serial.println("      mm = minutes (ex. 02)");
  Serial.println("      ss = seconds (ex. 42)");
  Serial.println("Example for input : 2004095090242x");
  Serial.println("-----------------------------------------------------------------------------");
  Serial.println("Please enter the current time to set on DS3231 ended by 'x':");
}

// This function is written by Eric Ayars, who made the library used ("DS3231.h")
void setRTCTimeFromSerialInput() {
  // If something is coming in on the serial line, it's
  // a time correction so set the clock accordingly.
  if (Serial.available()) {
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
        Serial.print(myRTC.getYear(), DEC);
        Serial.print("-");
        Serial.print(myRTC.getMonth(century), DEC);
        Serial.print("-");
        Serial.print(myRTC.getDate(), DEC);
        Serial.print(" ");
        Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC); //24-hr
        Serial.print(":");
        Serial.print(myRTC.getMinute(), DEC);
        Serial.print(":");
        Serial.println(myRTC.getSecond(), DEC);
    }

    // Notify that we are ready for the next input
    Serial.println("Please enter the current time to set on DS3231 ended by 'x':");
  }
  delay(1000);
}

void printTime() {
    Serial.print(myRTC.getYear(), DEC);
    Serial.print("-");
    Serial.print(myRTC.getMonth(century), DEC);
    Serial.print("-");
    Serial.print(myRTC.getDate(), DEC);
    Serial.print(" ");
    Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC); //24-hr
    Serial.print(":");
    Serial.print(myRTC.getMinute(), DEC);
    Serial.print(":");
    Serial.println(myRTC.getSecond(), DEC);
}

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
      myFile.print(":");
      myFile.println(myRTC.getSecond(), DEC);
    }
    myFile.close();
}


// This function is written by Eric Ayars, who made the library used ("DS3231.h")
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
		if (Serial.available()) {
			inputChar = Serial.read();
			inputStr[currentPos] = inputChar;
			currentPos += 1;

      // Check if string complete (end with "x")
			if (inputChar == 'x') {
				isStrComplete = true;
			}
		}
	}
	Serial.println(inputStr);

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