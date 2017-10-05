 /*This example sketch converts an RN-42 bluetooth module to
 communicate at 9600 bps (from 115200), and passes any serial
 data between Serial Monitor and bluetooth module.
 */
#include <SoftwareSerial.h>  

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
char valeur[2];
int temp=0;
int count=0;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
}

void loop()
{ 
  count=0;
  while(count!=2)
  {
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
   
    valeur[count]=(char)bluetooth.read();  
      if(count==1)
       {
        temp=(valeur[0]-48)*10+valeur[1]-48; 
        Serial.print(temp);
      
        digitalWrite(temp,HIGH);
        delay(2000);
       }
    count++;
    //Serial.print((char)bluetooth.read());
    digitalWrite(13,HIGH);
 }
 }  
  digitalWrite(temp,LOW);
  valeur[0]=0;
  valeur[1]=0;
  
    
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
    digitalWrite(13,HIGH);
  }
  // and loop forever and ever!
}
