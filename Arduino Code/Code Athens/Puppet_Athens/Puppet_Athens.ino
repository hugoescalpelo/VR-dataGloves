//Right Hand

#include <SoftwareSerial.h>

SoftwareSerial mySerial (7, 8);

const byte LIST_LENGTH = 16;
const int pin [] = {A1,A5,A6,A7,A2,A3,A4};
//{A1,A7,A6,A3,A4,A2,A5}
//Inverse {A4, A7, A6, A5, A2, A3, A1}
//{A1, A3, A2, A5, A6, A7, A4}

const byte SAMPLE_TIME = 75;
const byte SAMPLE_READ = 15;
int data [7][LIST_LENGTH];
byte i_length = 0;
long timeNow, timeStep, timeRead;
long dataAvg [] = {0, 0, 0, 0, 0, 0, 0};

void setup() {
  //Serial.begin (57600);
  //Serial.println ("Start");

  mySerial.begin (57600);

  timeStep = millis () + SAMPLE_TIME;
  timeRead = millis () + SAMPLE_READ;
}

void loop() {

  timeNow = millis ();

  if (timeNow > timeRead) {
    for (int i_read = 0; i_read < 7; i_read++) {
      data [i_read][i_length] = analogRead (pin [i_read]);
    }
    i_length++;
    i_length = i_length % LIST_LENGTH;
    timeRead = timeNow + SAMPLE_READ;
  }


  if (timeNow > timeStep) {

    for (int i_avg = 0; i_avg < 7; i_avg++) {
      int buffDataAvg = 0;
      for (int i_list = 0; i_list < LIST_LENGTH; i_list++) {
        buffDataAvg += data [i_avg][i_list];
      }
      dataAvg [i_avg] = buffDataAvg / LIST_LENGTH;
    }

    mySerial.print (dataAvg [0]);
    mySerial.print (",");
    mySerial.print (dataAvg [1]);
    mySerial.print (",");
    mySerial.print (dataAvg [2]);
    mySerial.print (",");
    mySerial.print (dataAvg [3]);
    mySerial.print (",");
    mySerial.print (dataAvg [4]);
    mySerial.print (",");
    mySerial.print (dataAvg [5]);
    mySerial.print (",");
    mySerial.print (dataAvg [6]);
    mySerial.println ();
    
    

//    for (int i_send = 0; i_send < 7; i_send++) {
//      Serial.print (dataAvg [i_send]);
//      Serial.print (",");
//    }
//    Serial.println ();

    timeStep = timeNow + SAMPLE_TIME;
  }
  delay (2);
}
