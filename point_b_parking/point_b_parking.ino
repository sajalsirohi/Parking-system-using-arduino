//remove jumper behind the sensor
int trigPin = A0;  //D2   for arduino use any GPIO pin
int eP[8]={2,3,4,5,6,7,8,9};  
int i=0;
String data = "b";
String incoming,dataToSend;
char first_word;
bool do_reading = false;
long duration, distance;

void setup(){
 Serial.begin(9600);
 //Serial.println("Starting it");
 pinMode(trigPin, OUTPUT);   
 for(i=0;i<8;i++)      
  pinMode(eP[i], INPUT); 
 pinMode(10,OUTPUT);
}

void readSerialData(){
  while (Serial.available()>0){
    //Read the incoming byte
    incoming = Serial.readString();
    first_word = incoming.charAt(0);
    if(first_word == 'b')
    {
     do_reading = true;
     digitalWrite(10,HIGH);
    }
   else
   {
    do_reading = false;
    digitalWrite(10,LOW);   
   }
 }
}

String readDataFromSensor(){
  data = "b,";
  for (i=0;i<8;i++)  
 { digitalWrite(trigPin, HIGH);     
  delayMicroseconds (50);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(eP[i], HIGH);
  //Serial.print(duration);
  distance = duration / 58.2;
  data += String(distance);
  data += ","; 
  delay(50);
 }
 return data;
}

void loop(){
  if (Serial.available() > 0){
  readSerialData();
 }
 
 if (do_reading){
  dataToSend = readDataFromSensor();
  Serial.println(dataToSend);
  Serial.flush();
  //Serial.write(dataToSend);
 }
 
 // Serial.println(" No command to read Data " );
 // dataToSend = "nothing";
 //}
// Serial.println(dataToSend);
 do_reading = false;
 digitalWrite(10,LOW);
 delay(2000);
}


  
