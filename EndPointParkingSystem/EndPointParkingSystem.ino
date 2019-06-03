#include <SoftwareSerial.h>

bool started = false;
bool ended = false;
bool read_from_a = false;
bool read_from_b = false;
String incoming;
String reading_from_a;
String reading_from_b;
char first_word;

SoftwareSerial Serialb(10, 11);
SoftwareSerial Seriala(8,9);


void setup() {
  Seriala.begin(9600);
  Serialb.begin(9600); 
  Serial.begin(9600);     
}

String readData(){
  while (Seriala.available()>0 || Serialb.available() > 0){
    //Read the incoming byte
    if (Seriala.available() > 0) { incoming = Seriala.readString();}
    if (Serialb.available() > 0) { incoming = Serialb.readString();}
    first_word = incoming.charAt(0);
    if(first_word == 'a')
    {
     started = true;
     read_from_a = true;
     read_from_b = false;
    }
    else if (first_word == 'b'){
     started = true;
     read_from_a = false;
     read_from_b = true;
    }

   else
   {
    Serial.print("Error ");
    Serial.print(incoming);
    started = false;
    read_from_a = false;
    read_from_b = false; 
    delay(1000);   
   }
 }
 return incoming;
}


void loop() {
  started=  false;
  Serial.println("A");
  Seriala.begin(9600);
  Seriala.println('a');
  delay(5000);
  reading_from_a = readData();
  if(read_from_a && started){
    Serial.print(" Data received from point A  : ");
    Serial.println(reading_from_a);
  }
  delay(5000);
  Seriala.end();
  Serial.println("B");
  Serialb.begin(9600);
  Serialb.println('b');
  delay(5000);
  reading_from_b = readData();
  if(read_from_b && started){
    Serial.print(" Data received from point B  : ");
    Serial.println(reading_from_b);
  }
 Serialb.end();
 delay(5000);
 
}
