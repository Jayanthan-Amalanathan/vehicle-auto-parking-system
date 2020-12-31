#include <Servo.h> //
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

void p1slot1(); 
  void p1slot2();
    void SendMessage();
      void entrnce_servo();

SoftwareSerial SIM900A(10,11); // RX | TX
Servo myservoEntrance;
Servo myservoExit;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


int pos = 0;

int Entrance_IR=2;
  int Exit_IR=3;
    int Slot_01=4;
      int Slot_02=5;
          int free_slot=2;

String Msg; 
String Msg1;
String Msg2;



void setup() {

//Entrance Servo
  myservoEntrance.attach(12);
//Exit Servo
  myservoExit.attach(13);
  
   pinMode(Entrance_IR,INPUT);
   pinMode(Exit_IR,INPUT);
   pinMode(Slot_01,INPUT);
   pinMode(Slot_02,INPUT);
   
   
  SIM900A.begin(9600);   // Setting the baud rate of GSM Module 
  Serial.begin(9600); 
  Serial.println ("SIM900A Ready");

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  
}

void loop() {
  
  int Status_Entrnce= digitalRead(Entrance_IR);
  int Status_Exit= digitalRead(Exit_IR);
  int Status_Slot_01= digitalRead(Slot_01);
  int Status_Slot_02= digitalRead(Slot_02);
  

  if(Status_Entrnce==0){
  entrnce_servo();
  p1slot1(); 
  p1slot2();
  free_slot--;   
  Serial.println ("Message is ="+Msg1+Msg2);
  lcd.setCursor(0,0);
  lcd.print(Msg1);
  lcd.setCursor(0,1);
  lcd.print(Msg2);
  delay(1000);
  SendMessage();
  }

  if(Status_Exit==0){
  exit_servo();
  p1slot1(); 
  p1slot2();
  free_slot++;   
  Serial.println ("Message is ="+Msg1+Msg2);
  lcd.setCursor(0,0);
  lcd.print(Msg1);
  lcd.setCursor(0,1);
  lcd.print(Msg2);
  delay(1000);
  SendMessage();
  }
  }
        
///////////// Functions
 void SendMessage()

{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+94766646404\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Message is ="+Msg1+Msg2);// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS Selesai dikirim");
}

void p1slot1() // parkng 1 slot1

{
  int Status_Slot_01= digitalRead(Slot_01);
  if( Status_Slot_01 == 1 ) 
  {
  Msg1=("Slot 01 free    "); // parking1 slot1 
  
 delay(200); 
  } 
if(Status_Slot_01== 0)
{
  Msg1=("Slot 01 not free");  
 delay(200);  
}
}
 
void p1slot2() // parking 1 slot2

{
  int Status_Slot_02= digitalRead(Slot_02);
  if( Status_Slot_02 == 1 ) 
  {
  Msg2=("Slot 02 free    "); 
  delay(200); 
  }
if( Status_Slot_02 == 0 )  
  {
  Msg2=("Slot 02 not free");
 delay(200);
  } 
}

void entrnce_servo()

{
if(free_slot>=1){
    int pos;
    //open entrance servo
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservoEntrance.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
      }
  //delay to close the door
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservoEntrance.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
}
void exit_servo()

{
if(free_slot>=1){
    int pos;
    //open entrance servo
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservoExit.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
      }
  //delay to close the door
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservoExit.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
}
