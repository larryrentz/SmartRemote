// This #include statement was automatically added by the Particle IDE.
#include <IRremote.h>

//CLEAN CODE WHEN PROTOTYPE IS FINISHED

// This #include statement was automatically added by the Particle IDE.
//#include <IRTransmitter.h>

// This #include statement was automatically added by the Particle IDE.
#include "IRremote.h"

//#include <array>

#include <map>

//#include <iostream>

//#include <string>
//using namespace std;

#include <iterator>

int ledPin = D7;

int RECV_PIN = D0;

IRrecv irrecv(RECV_PIN);

decode_results results;


bool remote_setup = false; // boolean for whether a remote is being setup or not
/*
-replacement for bool remote_setup
-used as a counter in loop() to count how many IR signals have been received
-set to 0 when setup button on UI is pressed
*/
int buttonCounter = 0; 

//#define ARRAYSIZE 67; //Used for Samsung remote IR signals

/*
Made 2 maps because pairs are inserted in random order so there's
no efficient way to pair correct IR value to correct buttonName
w/o another sub-function/hard-coding
*/

//map for button commands
//std::map<String, int> irControls;

//std::map<String, unsigned long> irControls;
//change size of array
std::map<String, unsigned int(*)[67]> irControls;

//map for IR codes
//std::map<int, long> irSignals;

IRsend irsend; //Pin A5; Refer to line 488 in IRremoteInt.h
//change size of array
int rawIRsetup(std::map<String, unsigned int(*)[67]> &irControls);
//int IRsetup(std::map<String,unsigned long> &irControls);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver, Way to turn receiver off when not in use?
  //test
  Serial.println("Testing");
  //Serial.println("Larry");

  pinMode(ledPin, OUTPUT);
  
  Spark.function("send", sendIR);
  //Spark.function("receive", receiveIR);
  
  //IRsetup(irControls);
  rawIRsetup(irControls);
  
  //test
  /*
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin,  LOW);
  */

}

/*
void loop() 
{ }  
*/
//NO LOOPS IN loop()

/*
int receiveIR(String command)
{
    //bug that sets buttonCounter to 1 after doing a second setup; not very important but keep in mind
     if (command.equalsIgnoreCase("setup"))
        buttonCounter = 0;
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin,  LOW);
    
    //change back to 1
    int i = 0;
    while(remote_setup)
    {
        //test
        //digitalWrite(ledPin, HIGH);
        
        //if statement not executing
        if (irrecv.decode(&results))
        {
            //test
            digitalWrite(ledPin, HIGH);
            delay(1000);
            digitalWrite(ledPin, LOW);

            Serial.println(results.value, HEX);
            
            //Check for duplicates
            
            //adds value to irCode map
            irSignals.insert(std::pair<int, long>(i, results.value));

            //Serial.println(results.value, HEX);
            i++;
        }
        //array doesnt have size so create var for num of buttons
        //if(i == numOfButtons + 1)
        if(i == 2)
        {
          remote_setup = false;
          
          //test
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
          delay(500);
          digitalWrite(ledPin, HIGH);
          delay(500);
          digitalWrite(ledPin, LOW);
        }  
        irrecv.resume(); // Receive the next value
    }
    
    return 1;
}
*/

//Sends IR signals to TV when user selects a button
int sendIR(String command)
{
    //std::map<String, unsigned long>::iterator itr;
    //change size of array
    std::map<String, unsigned int(*)[67]>::iterator itr;


    for(itr = irControls.begin(); itr != irControls.end(); itr++)
    {
        if(command.equalsIgnoreCase(itr -> first))
        {
            //irsend.sendNEC(irSignals.find(itr -> second) -> second, 32);
            //irsend.sendSony(itr -> second, 32);
            //irsend.sendSAMSUNG(itr -> second, 32);
            //irsend.sendRaw(itr -> second, sizeof(itr -> second) / sizeof((itr -> second)[0]), 38); //not sendIR function for Samsung in particle IRremote library
            //void sendRaw(unsigned int buf[], int len, int hz);
            irsend.sendRaw(*(itr -> second), 67, 38); //not sendIR function for Samsung in particle IRremote library

            //testing
            digitalWrite(ledPin, HIGH);
            delay(500);
            digitalWrite(ledPin, LOW);
        }

    }

    return 1;
}

//setup for remotes with IRsend functions
int IRsetup(std::map<String, unsigned long> &irControls)
{
    //hard code in IRsignals
   //buttons 0-9
  irControls.insert(std::pair<String, unsigned long>("but1", 3772784863)); 
  irControls.insert(std::pair<String, unsigned long>("but2", 3772817503));
  irControls.insert(std::pair<String, unsigned long>("but3", 3772801183));
  irControls.insert(std::pair<String, unsigned long>("but4", 3772780783));
  irControls.insert(std::pair<String, unsigned long>("but5", 3772813423));
  irControls.insert(std::pair<String, unsigned long>("but6", 3772797103));
  irControls.insert(std::pair<String, unsigned long>("but7", 3772788943));
  irControls.insert(std::pair<String, unsigned long>("but8", 3772821583));
  irControls.insert(std::pair<String, unsigned long>("but9", 3772805263));
  irControls.insert(std::pair<String, unsigned long>("but0", 3772811383));

  //power button
  //change "power" value back to 11
  irControls.insert(std::pair<String, unsigned long>("power", 3772793023)); //change to home tv for testing

  //channel buttons
  irControls.insert(std::pair<String, unsigned long>("channel_up", 3772795063));
  irControls.insert(std::pair<String, unsigned long>("channel_down", 3772778743));

  //volume buttons
  irControls.insert(std::pair<String, unsigned long>("volume_up", 3772833823)); //change to home tv for testing
  irControls.insert(std::pair<String, unsigned long>("volume_down", 3772829743)); //change to home tv for testing

  //settings button
  irControls.insert(std::pair<String, unsigned long>("settings", 3772799143));

  //arrow buttons
  irControls.insert(std::pair<String, unsigned long>("up", 3772778233));
  irControls.insert(std::pair<String, unsigned long>("down", 3772810873));
  irControls.insert(std::pair<String, unsigned long>("left", 3772810873));
  irControls.insert(std::pair<String, unsigned long>("right", 3772794553));

  //select/ok button
  irControls.insert(std::pair<String, unsigned long>("select", 3772782313));
  
  return 1;
}

//setup for remotes without IRsend functions

/* 1) store array of IRsignals in var; make new var everytime
-will have to change size of array
   2) pass var in by reference in value of map
*/
//change size of array
int rawIRsetup(std::map<String, unsigned int(*)[67]> &irControls)
{
    //hard code in IRsignals
   //buttons 0-9
   unsigned int rawData[67] = {4550,4400, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,500, 600,1600, 600,1650, 600,1600, 650,500, 600,500, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,500, 600,500, 650,500, 600,500, 600,500, 600,1650, 600,1600, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 600,1650, 600};// SAMSUNG E0E020DF 020DF
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but1", &rawData));
  
  unsigned int rawData2[67] = {4550,4400, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,500, 600,1600, 600,550, 600,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 650,1600, 600};  // SAMSUNG E0E0A05F
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but2", &rawData2));
  
  unsigned int rawData3[67] = {4550,4450, 600,1600, 650,1600, 600,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 650,1600, 600,1600, 650,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,500, 600,1600, 600,550, 550,550, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600}; // SAMSUNG E0E0609F
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but3", &rawData3));
  
  unsigned int rawData4[67] = {4550,4450, 550,1650, 600,1650, 600,1600, 600,500, 600,550, 550,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,500, 600,550, 550,550, 600,500, 600,500, 600,1650, 600,1600, 600,550, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600}; // SAMSUNG E0E020DF
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but4", &rawData4));
  
  unsigned int rawData5[67] = {4550,4450, 600,1600, 600,1650, 600,1600, 600,500, 650,500, 600,500, 600,500, 600,500, 600,1650, 600,1600, 650,1600, 600,500, 650,450, 650,500, 600,500, 600,500, 650,1600, 600,500, 600,500, 600,1650, 600,500, 650,450, 650,500, 600,500, 600,500, 600,1650, 600,1600, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E0906F
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but5", &rawData5));
  
  unsigned int rawData6[67] = {4550,4400, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 550,550, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 550,550, 600,1600, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,500, 600,1650, 600,500, 600,1600, 600,1650, 600,1600, 600,1650, 600};  // SAMSUNG E0E050AF
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but6", &rawData6));
  
  unsigned int rawData7[67] = {4550,4450, 600,1600, 650,1600, 600,1600, 650,500, 600,500, 600,500, 650,500, 550,550, 600,1600, 600,1650, 600,1600, 650,500, 600,500, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 550,1650, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,500, 600,550, 600,1600, 600,1650, 550,1650, 600,1650, 600};  // SAMSUNG E0E030CF
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but7", &rawData7));
  
  unsigned int rawData8[67] = {4550,4450, 600,1600, 600,1650, 600,1600, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,500, 600,1650, 600,1600, 600,500, 650,500, 600,500, 600,500, 600,500, 650,1600, 600,500, 600,500, 650,1600, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E0B04F
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but8", &rawData8));
  
  unsigned int rawData9[67] = {4600,4400, 600,1600, 600,1650, 600,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 650,450, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,1600, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E0708F
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but9", &rawData9));
  
  unsigned int rawData10[67] = {4550,4400, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 650,500, 550,550, 600,1600, 600,550, 550,550, 600,500, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 600,500, 600,1650, 600,1600, 600,1650, 600};  // SAMSUNG E0E08877
  irControls.insert(std::pair<String, unsigned int(*)[67]>("but0", &rawData10));
  
  //power button
  unsigned int rawData11[67] = {4550,4400, 600,1650, 600,1600, 650,1600, 600,500, 600,500, 600,550, 600,500, 600,500, 650,1600, 600,1600, 600,1650, 600,500, 600,500, 650,450, 650,500, 600,500, 600,500, 650,1600, 600,500, 600,500, 650,450, 650,500, 600,500, 650,450, 650,1600, 600,500, 600,1600, 650,1600, 600,1600, 650,1600, 650,1550, 650,1600, 600};  // SAMSUNG E0E040BF
  irControls.insert(std::pair<String, unsigned int(*)[67]>("power", &rawData11));
  
  //channel buttons
  unsigned int rawData12[67] = {4550,4400, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,500, 600,500, 600,1650, 600,500, 600,500, 650,450, 600,1650, 600,500, 600,1650, 600,1600, 600,500, 600,1650, 600,1600, 650,1600, 600};  // SAMSUNG E0E048B7
  irControls.insert(std::pair<String, unsigned int(*)[67]>("channel_up", &rawData12));
  
  unsigned int rawData13[67] = {4600,4400, 600,1600, 600,1650, 600,1600, 650,450, 650,500, 600,500, 600,500, 650,500, 600,1600, 600,1650, 600,1600, 650,450, 650,500, 600,500, 600,500, 650,450, 600,550, 600,500, 600,500, 650,450, 650,1600, 600,500, 650,450, 600,550, 600,1600, 650,1600, 600,1600, 650,1600, 600,500, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E008F7
  irControls.insert(std::pair<String, unsigned int(*)[67]>("channel_down", &rawData13));
  
   //volume buttons
   unsigned int rawData14[67] = {4550,4450, 600,1600, 600,1650, 600,1600, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 650,450, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,500, 600,550, 600,500, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E0E01F
   irControls.insert(std::pair<String, unsigned int(*)[67]>("volume_up", &rawData14));
 
   unsigned int rawData15[67] = {4550,4450, 600,1600, 600,1650, 600,1600, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 650,450, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,500, 600,550, 600,500, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E0E01F
   irControls.insert(std::pair<String, unsigned int(*)[67]>("volume_down", &rawData15));
   
    //settings button
   unsigned int rawData16[67] = {4550,4450, 600,1600, 600,1650, 600,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,500, 600,1650, 600,1600, 650,450, 600,550, 600,500, 600,1600, 650,500, 600,1600, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 600};  // SAMSUNG E0E058A7
   irControls.insert(std::pair<String, unsigned int(*)[67]>("settings", &rawData16));
    
    //arrow buttons
   unsigned int rawData17[67] = {4550,4400, 650,1600, 600,1650, 600,1600, 600,500, 600,550, 600,500, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,500, 650,500, 600,500, 600,500, 600,500, 600,1650, 600,1600, 650,500, 600,1600, 600,1600, 650,1600, 600,1600, 650,1600, 600,500, 600,500, 650,1600, 600};  // SAMSUNG E0E006F9
   irControls.insert(std::pair<String, unsigned int(*)[67]>("up", &rawData17));
    
    unsigned int rawData18[67] = {4550,4450, 600,1600, 650,1600, 600,1600, 600,550, 600,500, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 600,500, 600,550, 600,500, 600,500, 650,450, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,1600, 650,1600, 600,500, 600,500, 600,1650, 600,1600, 650,1600, 600,1600, 600,550, 600,500, 600,1600, 650};  // SAMSUNG E0E08679
    irControls.insert(std::pair<String, unsigned int(*)[67]>("down", &rawData18));
    
    unsigned int rawData19[67] = {4550,4400, 650,1600, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 650,500, 600,500, 600,1650, 600,500, 600,1600, 600,550, 600,500, 600,1600, 600,1650, 600,500, 600,500, 600,1650, 600,500, 600,1600, 600,1650, 600,500, 600,500, 650,1600, 600};  // SAMSUNG E0E0A659
    irControls.insert(std::pair<String, unsigned int(*)[67]>("left", &rawData19));
    
    unsigned int rawData20[67] = {4550,4400, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,500, 600,500, 600,500, 650,1600, 600,1600, 600,550, 600,1600, 600,500, 650,1600, 600,1600, 600,1650, 600,500, 600,500, 600,1650, 600};  // SAMSUNG E0E046B9
    irControls.insert(std::pair<String, unsigned int(*)[67]>("right", &rawData20));
    
    
    //select/ok button
    unsigned int rawData21[67] = {4550,4400, 600,1650, 600,1600, 650,1600, 600,500, 600,500, 600,500, 650,500, 600,500, 600,1600, 650,1600, 600,1600, 600,550, 600,500, 600,500, 650,450, 600,550, 600,500, 600,500, 650,450, 650,1600, 600,500, 600,1650, 600,1600, 600,500, 600,1650, 600,1600, 650,1600, 600,500, 600,1650, 600,500, 600,500, 600,1650, 600};  // SAMSUNG E0E016E9
    irControls.insert(std::pair<String, unsigned int(*)[67]>("select", &rawData21));

  return 1;
}

