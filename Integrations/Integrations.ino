

#include <OneWire.h>              // Include the libraries we need
#include <DallasTemperature.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Adjust the address if necessary, common addresses are 0x27 and 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);


OneWire oneWire(2); // Sets Pin 2 for reading temperature sensor oneWire
DallasTemperature sensor2(&oneWire); // The temperature reading from Pin 2 will be called sensor2

//Creates a check variable that changes when an operation has been preformed
int CHECK = 0;
int CHECK_DB = 0; 
int CHECK_W = 0; 
int CHECK_KB = 0;
int CHECK_F = 0;

int MODE = 1; //Starts up the first mode
int SYSTEM = 1; //Starts up the first system which is manual
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
const int BU = 11; //BUTTON UP
const int BD = 13; //BUTTON DOWN
const int sel = 12; //SELECT MODE BUTTON
const int sys = 14; //SELECT AUTOMATION/MANUAL/SYNC BUTTON
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
   pinMode(sys, INPUT);
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



void loop() { // loop start
  // put your main code here, to run repeatedly:

sensor2.requestTemperatures(); // Recieves temperature
float temp = sensor2.getTempCByIndex(0)*9/5 + 32; //converts temp to Farenheight for display
lcd.setCursor(6, 1); // Set the cursor to column 0, line 0
lcd.print(temp); //Prints temperature


//Rotates through SYSTEMS when button is pressed
if (digitalRead(sys) == HIGH)
  {SYSTEM = SYSTEM + 1;}
//end


//Rotates through modes when button is pressed
if (digitalRead(sel) == HIGH)
  {MODE = MODE + 1;}
//end

//Ensures the modes loop
if (MODE == 5)
  {MODE = 1;}
//end

//Ensures the Systems loop
if (SYSTEM == 4)
  {SYSTEM = 1;}
//end



//DEFAULTING STATEMENT --- makes everything go to default position when changing in between systems to ensure that there is no issue.
//Default positions (Heating) Fan off, Blinds Open, Windows Closed
if (digitalRead(sys) == HIGH){

// Turns fan off
if (CHECK_F == 0){
digitalWrite(F1, LOW);
digitalWrite(F2, LOW); 
CHECK_F = 1; 
}

// Open Front Door Blinds
if (CHECK_DB == 0){
digitalWrite(DB1, HIGH);
digitalWrite(DB2, LOW); 
delay(10000); //Time needed for Front door blind to open
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 
CHECK_DB = 1; 
}

// Close Windows
if (CHECK_W == 0){
digitalWrite(W1, LOW);
digitalWrite(W2, HIGH); 
delay(10000); //Time needed for windows to close
digitalWrite(W1, LOW);
digitalWrite(W2, LOW);
CHECK_W = 1; 
} 

// Open Kitchen + Bathroom Blinds
if (CHECK_KB == 0){
digitalWrite(KB1, HIGH);
digitalWrite(KB2, LOW); 
delay(10000); //Time needed for blinds to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW);
CHECK_KB = 1;  
}

}// ------ END OF DEFAULTING STATEMENT -------






// ------- BEGINNING OF LED STATEMENTS -------
// If MANUAL MODE
if (SYSTEM ==1) {
 
// Statements for LCD Modes to display
if (MODE == 1){
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Fan                    ");
//end
}

if (MODE == 2){
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Door Blinds            ");
//end
}

if (MODE == 3){
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Windows              ");
//end
}

if (MODE == 4){
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Kit/Bat Blinds                  ");
}
//end

}
//end

//LCD Reads Mode you are in
if (SYSTEM == 2){
// Automation Mode
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Automation Mode                    ");
}//end

//LCD Reads Mode you are in
if (SYSTEM == 3){
// Sync Mode
lcd.setCursor(0, 0); // Set the cursor to column 0, line 0
lcd.print("Sync Mode                    ");
}//end

// ------- END OF LED STATEMENTS -------






//Ensures the modes loop
if (MODE == 5)
  {MODE = 1;}
//end

//Ensures the Systems loop
if (SYSTEM == 4)
  {SYSTEM = 1;}
//end







// ---------------------- IN MANUAL MODE ---------------------- 
if (SYSTEM == 1){

if((digitalRead(BU))== HIGH && (CHECK == 0))         // If Up button is pressed
{
// Open blinds, Close Windows, Turn off Fan
CHECK = 1; //Updates check

if ((MODE == 1) && (CHECK_F == 0)){
// Turns fan off
digitalWrite(F1, LOW);
digitalWrite(F2, LOW); 
CHECK_F = 1; //Updates Check
//end
}

if ((MODE == 2) && (CHECK_DB == 0)){
// Open Front Door Blinds
digitalWrite(DB1, HIGH);
digitalWrite(DB2, LOW); 
delay(10000); //Time needed for Front door blind to open
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 
CHECK_DB == 1; //Updates Check
//end
}

if ((MODE == 3) && (CHECK_W == 0)){
// Close Windows
digitalWrite(W1, LOW);
digitalWrite(W2, HIGH); 
delay(10000); //Time needed for windows to close
digitalWrite(W1, LOW);
digitalWrite(W2, LOW); 
CHECK_W == 1; //Updates Check
//end
}


if ((MODE == 4) && (CHECK_KB == 0)){
// Open Kitchen + Bathroom Blinds
digitalWrite(KB1, HIGH);
digitalWrite(KB2, LOW); 
delay(10000); //Time needed for windows to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW); 
CHECK_KB == 1; //Updates Check
//end
}

CHECK = 1;

} // end of UP statement


if((digitalRead(BD))== HIGH && (CHECK == 1))         // If Up button is pressed
{
// Close blinds, Open Windows, Turn Fan on
CHECK = 0;

if ((MODE == 1) && (CHECK_F == 1)){
// Turns Fan off
digitalWrite(F1, LOW);
digitalWrite(F2, HIGH); 
CHECK_F = 0; //Updates Check
//end
}

if ((MODE == 2) && (CHECK_DB == 1)){
// Close Front Door Blinds
digitalWrite(DB1, LOW);
digitalWrite(DB2, HIGH); 
delay(10000); //Time needed for Front door blind to open
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 
CHECK_DB = 0; //Updates Check
//end
}

if ((MODE == 3) && (CHECK_W == 1)){
// Opens Windows
digitalWrite(W1, HIGH);
digitalWrite(W2, LOW); 
delay(10000); //Time needed for windows to close
digitalWrite(W1, LOW);
digitalWrite(W2, LOW); 
CHECK_W = 0; //Updates Check
//end
}


if ((MODE == 4) && (CHECK_KB == 1)){
// Close Kitchen + Bathroom Blinds
digitalWrite(KB1, LOW);
digitalWrite(KB2, HIGH); 
delay(10000); //Time needed for windows to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW); 
CHECK_KB = 0; //Updates Check
//end
}

CHECK = 0;

} // end of DOWN statement

} // ---------------------- END OF MANUAL MODE ---------------------- 











// ---------------------- IN AUTOMATION MODE ---------------------- 
if (SYSTEM == 1){

if((temp < 68) && (CHECK == 0))         // If temperature is less than 68 degrees farenheight
{
// Open blinds, Close Windows, Turn off Fan

//Updates check
CHECK = 1; 
CHECK = 1;
CHECK_F = 1;
CHECK_DB = 1;
CHECK_W = 1;
CHECK_KB = 1;

// Turns fan off
digitalWrite(F1, LOW);
digitalWrite(F2, LOW); 

// Open Front Door Blinds
digitalWrite(DB1, HIGH);
digitalWrite(DB2, LOW); 
delay(10000); //Time needed for Front door blind to open
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 

// Close Windows
digitalWrite(W1, HIGH);
digitalWrite(W2, LOW); 
delay(10000); //Time needed for windows to close
digitalWrite(W1, LOW);
digitalWrite(W2, LOW); 

// Open Kitchen + Bathroom Blinds
digitalWrite(KB1, HIGH);
digitalWrite(KB2, LOW); 
delay(10000); //Time needed for blinds to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW); 


} // end of COLD Statement


if((temp > 72) && (CHECK == 1))         // If temperature is greater than 72 degrees farenheight
{
// Close blinds, Open Windows, Turn on Fan

//Updates Check
CHECK = 0;
CHECK_F = 0;
CHECK_DB = 0;
CHECK_W = 0;
CHECK_KB = 0;

// Turns Fan on
digitalWrite(F1, LOW);
digitalWrite(F2, HIGH); 

// Open Front Door Blinds
digitalWrite(DB1, LOW);
digitalWrite(DB2, HIGH); 
delay(10000); //Time needed for Front door blind to close
digitalWrite(DB1, LOW);
digitalWrite(DB2, LOW); 

// Opens Windows
digitalWrite(W1, LOW);
digitalWrite(W2, HIGH); 
delay(10000); //Time needed for windows to open
digitalWrite(W1, LOW);
digitalWrite(W2, LOW); 

// Close Kitchen + Bathroom Blinds
digitalWrite(KB1, LOW);
digitalWrite(KB2, HIGH); 
delay(10000); //Time needed for blinds to close
digitalWrite(KB1, LOW);
digitalWrite(KB2, LOW); 

CHECK = 0;

} // end of HOT statement

} // ---------------------- END OF AUTOMATION MODE ---------------------- 
  





} // xxxxxxxxxxxxxxxxxxxxxxxx END OF LOOP xxxxxxxxxxxxxxxxxxxxxxxx
