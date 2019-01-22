 /*
 SparkfunSerialLCD.cpp - Library for controlling a SparkFun SparkfunSerialLCD
              module.
          Code written for firmware version 2.5

 Created by Cody B. Null, September 9, 2011
 Modified by Jordan Hochenbaum, Dec 5, 2011. (Version 1.5)
 Modified by Johan Korten, March 23, 2013. (Version 1.6)
 Modified by Florentin Salomez, June 18, 2016 (Version 1.7)


 Version 1.4 - This version wrote specifically for 16x2
               Display.
               More display support coming in later version.

 Version 1.5 - Since mid 2011 the Arduino IDE has implemented the NewSoftSerial 
                library updates in the standard SoftwareSerial library and so 
                using NewSoftSerial is no longer needed. SparkfunSerialLCD has been updated 
                to use the Standard SoftwareSerial library. Also, Arduino 1.0
                support has been added. Backwards compatible with previous versions.

 Version 1.6 - Added support for the setType special command.
                This will help using different LCD's (2x16, 2x20, 4x16, 4x20).  
              Added support for scrollLeft and scrollRight commands.

Version 1.7 - Completed the setType special command. 
                Now the setCursor function works correctly.
                Added keywords.txt and library.properties file.

 Note - This library requires NewSoftSerial library
 The latest version of NewSoftSerial library can 
 always be found at http://arduiniana.org. -> NO LONGER NECESSARY. See V1.5 notes above
*/

//#include <../NewSoftSerial/NewSoftSerial.h>

#include <SoftwareSerial.h>

#include "raat.h"

#include "sparkfun-serial-lcd.h"

//  PUBLIC FUNCTIONS

// Contstructor
SparkfunSerialLCD::SparkfunSerialLCD(int pin, DISPLAY_WIDTH eWidth, DISPLAY_LINES eLines) : SoftwareSerial(pin, pin){
    pinMode(pin, OUTPUT);
    begin(9600);
    this->setType(eWidth, eLines, false);
}

// Set brightness value range 1-30 1=OFF 30=FULL
void SparkfunSerialLCD::setBrightness(int val){
    if(val >= 1 && val <= 30){
        specialCommand(LCD_BACKLIGHT | (val - 1));
    }
}

// Clears screen and returns cursor to home position
void SparkfunSerialLCD::clear(){
    command(LCD_CLEARDISPLAY);
}

// Clears a single line by writing blank spaces then returning
// cursor to beginning of line
void SparkfunSerialLCD::clearLine(int num){
    if(num > 0 && num <= _numlines){
        setCursor(num, 1);
        print("                ");
        setCursor(num, 1);
    }
}

// Moves cursor to the beginning of selected line
void SparkfunSerialLCD::selectLine(int num){
    if(num > 0 && num <= _numlines){
        setCursor(num, 1);
    }
}

// Clears then sets a particular line
void SparkfunSerialLCD::setLine(int num, char * text){
    this->clearLine(num);
    this->print(text);
}

// returns cursor to home position
void SparkfunSerialLCD::home(){
    command(LCD_RETURNHOME);
}

// Saves first 2 lines of txt to splash screen memory
void SparkfunSerialLCD::setSplash(){
    specialCommand(LCD_SETSPLASHSCREEN);
}

// Toggles splashscreen on and off
void SparkfunSerialLCD::toggleSplash(){
    specialCommand(LCD_SPLASHTOGGLE);
}

//  This is for text that flows Left to Right
void SparkfunSerialLCD::leftToRight(){
    _displaymode |= LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void SparkfunSerialLCD::rightToLeft() {
    _displaymode &= ~LCD_ENTRYLEFT;
    command(LCD_ENTRYMODESET | _displaymode);
}

// Blinking cursor on/off
void SparkfunSerialLCD::blink(){
    _displaycontrol |= LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void SparkfunSerialLCD::noBlink(){
    _displaycontrol &= ~LCD_BLINKON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Underline cursor on/off
void SparkfunSerialLCD::cursor(){
    _displaycontrol |= LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void SparkfunSerialLCD::noCursor(){
    _displaycontrol &= ~LCD_CURSORON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Display on/off
void SparkfunSerialLCD::display(){
    _displaycontrol |= LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void SparkfunSerialLCD::noDisplay(){
    _displaycontrol &= ~LCD_DISPLAYON;
    command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Set cursor to specific row and col values start at 1 not 0
void SparkfunSerialLCD::setCursor(int row, int col){
    int row_offsets[2][4] = {
        { 0x00, 0x40, 0x10, 0x50 },
        { 0x00, 0x40, 0x14, 0x54 }
    };
    if((row > 0 && row < _numlines+1) && (col > 0 && col < _numchars+1)){
           command(LCD_SETDDRAMADDR | ((col - 1) + row_offsets[_rowoffset][(row - 1)]));
    }
}

// Creates custom characters 8 char limit
// Input values start with 1
void SparkfunSerialLCD::createChar(int location, uint8_t charmap[]){
    location -= 1;
    location &= 0x07;
  for (int i=0; i<8; i++){
    command(LCD_SETCGRAMADDR | (location << 3) | i);
    write(charmap[i]);
  }
}

// Prints custom character
// Input values start with 1
void SparkfunSerialLCD::printCustomChar(int num){
    write((num - 1));
}

// new in 1.6: sets the type of the LCD
void SparkfunSerialLCD::setType(DISPLAY_WIDTH eWidth, DISPLAY_LINES eLines, bool write_to_lcd=false){

    int width_type = 0;
    int height_type = 0;

    switch(eWidth)
    {
    case DISPLAY_WIDTH_16:
        _numchars = LCD_16CHAR;
        width_type = 4;
        break;
    case DISPLAY_WIDTH_20:
        _numchars = LCD_20CHAR;
        width_type = 3;
        break;
    }

    switch(eLines)
    {
    case DISPLAY_LINES_2:
        _numlines = LCD_2LINE;
        height_type = 6;
        _rowoffset = 0;
        break;
    case DISPLAY_LINES_4:
        _numlines = LCD_4LINE;
        height_type = 5;
        _rowoffset = 1;
        break;
    }

    if (write_to_lcd)
    {
        specialCommand(width_type);
        specialCommand(height_type);
    }
}

// new in 1.6: scrolls text to left with one position
void SparkfunSerialLCD::scrollLeft(){
  command(0x18);
}

// new in 1.6: scrolls text to right with one position
void SparkfunSerialLCD::scrollRight(){
    command(0x1C);
}

void SparkfunSerialLCD::setup(){
    this->clear();
}

void SparkfunSerialLCD::reset(){
    this->clear();
}

int SparkfunSerialLCD::command_handler(char const * const command, char * reply){
    if (command[0] == 'C')
    {
        return this->handle_config_command(&command[1], reply);
    }
    else if (command[0] == 'T')
    {
        return this->handle_text_command(&command[1], reply);
    }
    else
    {
        strcpy(reply, "CMD?");
    }
}

// PRIVATE FUNCTIONS

// Functions for sending the special command values

int SparkfunSerialLCD::handle_config_command(char const * const command, char * reply){

    int reply_length = 0;
    bool valid_command = true;

    if (command[0] == 'R')
    {
        this->reset();
    }
    else
    {
        valid_command = false;
    }

    if (valid_command)
    {
        strcpy(reply, "COK");
        reply_length = 3;
    }
    else
    {
        strcpy(reply, "C?");
        reply_length = 2;
    }
    
    return reply_length;
}

int SparkfunSerialLCD::handle_text_command(char const * const command, char * reply){
    print(command);
    strcpy(reply, "COK");
    return 3;
}

void SparkfunSerialLCD::command(uint8_t value){
    write(0xFE);
    write(value);
    delay(5);
}

void SparkfunSerialLCD::specialCommand(uint8_t value){
    write(0x7C);
    write(value);
    delay(5);
}

void SparkfunSerialLCD::tick() {}
