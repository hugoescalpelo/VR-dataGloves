//Left Hand

#include <SoftwareSerial.h>

SoftwareSerial slave (7, 8);

const byte SAMPLE_READ = 15 ;
const byte LIST_LENGTH = 16;
const int pin [] = {A3,A0,A1,A2,A5,A4,A6};// Inverse 
//{A3,A0,A6,A4,A5,A1,A2}
//{A6, A2, A1, A0, A5, A4, A3}--{A3,A0,A4,A1,A5,A6,A2}
//{A3, A4, A5, A0, A1, A2, A6}

String slaveee;
int i_s;

int data [7][LIST_LENGTH];
long timeNow, timeRead;
int i_length = 0;
long dataAvg [] = {0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin (57600);
  Serial.println ("start");

  slave.begin (57600);

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

  

  if (slave.available ())
  {
    slaveee = slave.readStringUntil ('\n');

    for (int i_avg = 0; i_avg < 7; i_avg++) {
      int buffDataAvg = 0;
      for (int i_list = 0; i_list < LIST_LENGTH; i_list++) {
        buffDataAvg += data [i_avg][i_list];
      }
      dataAvg [i_avg] = buffDataAvg / LIST_LENGTH;
    }
    String slaveeee;
    for (int i_append = 0; i_append < 7; i_append++) {
      slaveeee += dataAvg [i_append];
      slaveeee += ',';
    }

    slaveee.trim ();
    // slave.end ();

    //it was here
    int lngth = slaveee.length ();
    bool snd = 0;
    for (i_s = 0; i_s < lngth; i_s++)
    {
      char buffChar = slaveee.charAt (i_s);
      if (buffChar != 44 && buffChar != 48 && buffChar != 49 && buffChar != 50 && buffChar != 51 && buffChar != 52 && buffChar != 53 && buffChar != 54 && buffChar != 55 && buffChar != 56 && buffChar != 57 && buffChar != 13)
      {
        snd = 1;
      }
    }
    
    if (snd == 0)
    {
      Serial.print (slaveeee);
      Serial.println (slaveee);
    }
    
    //slave.begin (115200);
    delay (2);
  }
}
