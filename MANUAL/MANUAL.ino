

#include <OneWire.h>              // Include the libraries we need
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Adjust the address if necessary, common addresses are 0x27 and 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);


OneWire oneWire(2); // Sets Pin 2 for reading temperature sensor oneWire
DallasTemperature sensor2(&oneWire); // The temperature reading from Pin 2 will be called sensor2

int CHECK = 0; //Creates a check variable that changes when an operation has been preformed
int MODE = 1; //Starts up the first mode
// 1 --> Kitchen/Bathroom Blinds  2 --> Door Blind  3 --> Windows  4 --> Fan

//sets motor/fan pins
const int DB1 = 3;
const int DB2 = 4;
const int W1 = 5;
const int W2 = 6;
const int KB1 = 9;
const int KB2 = 10;
const int F1 = 7;
const int F2 = 8;
//end

//sets button pins
const int BU = 11;
const int BD = 13;
const int sel = 12; //SELECT MOTOR BUTTON
const int mod = A0; //SELECT MODE BUTTON
//end

//sets LED pins
const int LED1 = SDA;
const int LED2 = SCL;
//end



void setup() {
  // put your setup code here, to run once:

   sensor2.begin(); // Start Sensor 2

   //Sets up all relay pins
   pinMode(KB1, OUTPUT);
   pinMode(KB2, OUTPUT);
   pinMode(DB1, OUTPUT);
   pinMode(DB2, OUTPUT);
   pinMode(W1, OUTPUT);
   pinMode(W2, OUTPUT);
   pinMode(F1, OUTPUT);
   pinMode(F2, OUTPUT);
   //end

   //Turns all motors and fan off to start  // low low pos, high low pos, high high = off, low high off
   digitalWrite(F1, LOW);
   digitalWrite(F2, HIGH);
   digitalWrite(DB1, LOW);
   digitalWrite(DB2, LOW);
   digitalWrite(W1, LOW);
   digitalWrite(W2, LOW);
   digitalWrite(KB1, LOW);
   digitalWrite(KB2, LOW);
   //end

   //starts buttons
   pinMode(BU, INPUT);
   pinMode(BD, INPUT);
   pinMode(sel, INPUT);
   //end

  // Initialize the LCD connected to the I2C bus
  lcd.init();
  // Turn on the backlight
  lcd.backlight();
  // Print a message to the LCD
  lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
  lcd.print("Manual Mode");
  lcd.setCursor(0, 1); // Set the cursor to column 0, line 0
  lcd.print("Temp: ");

   
 

   
   
}



void loop() { // lopp start
  // put your main code here, to run repeatedly:

sensor2.requestTemperatures(); // Recieves temperature
float temp = sensor2.getTempCByIndex(0)*9/5 + 32; //converts temp to Farenheight for display
lcd.setCursor(6, 1); // Set the cursor to column 0, line 0
lcd.print(temp); //Prints temperature

//Rotates through modes when button is pressed
if (digitalRead(sel) == HIGH)
  {MODE = MODE + 1;}
//end

if (MODE == 5)
  {MODE = 1;}
//end

// Statements for LCD Modes to display
if (MODE == 1){
// Open Kitchen + Bathroom Blinds
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Fan                    ");
//end
}

if (MODE == 2){
// Open Front Door Blinds
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Door Blinds            ");
//end
}

if (MODE == 3){
// Opens Windows
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Windows              ");
//end
}

if (MODE == 4){
// Turns off fan
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Kit/Bat Blinds                  ");
}
//end

if (MODE == 5)
  {MODE = 1;}
//end

if((digitalRead(BU))== HIGH && (CHECK == 0))         // If Up button is pressed
{
// Open blinds, Close Windows, Turn off Fan
CHECK = 1; //Updates check

if (MODE == 1){
// Turns fan on
digitalWrite(F1, HIGH);
digitalWrite(F2, LOW); 
//end
}

if (MODE == 2){
// Close Front Door Blinds
digitalWrite(DB1, LOW);
digitalWrite(DB2, HIGH); 
delay(78000); //Time needed for Front door blind to open
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 
//end
}

if (MODE == 3){
// Opens Windows
digitalWrite(W1, LOW);
digitalWrite(W2, HIGH); 
delay(16000); //Time needed for windows to close
digitalWrite(W1, LOW);
digitalWrite(W2, LOW); 
//end
}


if (MODE == 4){
// Open Kitchen + Bathroom Blinds
digitalWrite(KB1, LOW);
digitalWrite(KB2, HIGH); 
delay(29000); //Time needed for windows to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW); 
//end
}

CHECK = 1;

} // end of UP statement


if((digitalRead(BD))== HIGH && (CHECK == 1))         // If Up button is pressed
{
// Open blinds, Close Windows, Turn off Fan
CHECK = 0;

if (MODE == 1){
// Turns Fan off
digitalWrite(F1, LOW);
digitalWrite(F2, HIGH); 
//end
}

if (MODE == 2){
// Open Front Door Blinds
digitalWrite(DB1, HIGH);
digitalWrite(DB2, LOW); 
delay(78000); //Time needed for Front door blind to open
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 
//end
}

if (MODE == 3){
// Opens Windows
digitalWrite(W1, HIGH);
digitalWrite(W2, LOW); 
delay(15000); //Time needed for windows to close
digitalWrite(W1, LOW);
digitalWrite(W2, LOW); 
//end
}


if (MODE == 4){
// Open Kitchen + Bathroom Blinds
digitalWrite(KB1, LOW);
digitalWrite(KB2, HIGH); 
delay(29000); //Time needed for windows to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW); 
//end
}

CHECK = 0;

} // end of DOWN statement
  

} // loop end
