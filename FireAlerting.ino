#include <SoftwareSerial.h>
SoftwareSerial gprsSerial(9, 10);
#include <String.h>
int flag = 0;
void setup()
{
 pinMode(8, OUTPUT);
 pinMode(7, INPUT);
 gprsSerial.begin(9600);
 Serial.begin(9600);
 Module_Init();
}
void loop()
{
 if (gprsSerial.available())
 Serial.write(gprsSerial.read());
 int fire = digitalRead(7);
 if (fire == 0)
 {
 digitalWrite(8, HIGH);
 Serial.println("Fire is Detected");
 gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");
 delay(600);
 ShowSerialData();
 gprsSerial.println("AT+CIPSEND");
 delay(400);
 ShowSerialData();
 String str = "GET https://api.thingspeak.com/update?api_key=BP3LZ6KES8B54DIZ&field1=" + String(1);
 Serial.println(str);
 gprsSerial.println(str);
 delay(400);
 ShowSerialData();
 digitalWrite(8, LOW);
 gprsSerial.println((char)26);
 delay(500);
 gprsSerial.println();
 ShowSerialData();
 gprsSerial.println("AT+CIPSHUT");
 delay(10);
 ShowSerialData();
 flag = 0;
 }
 else
 {
 digitalWrite(8, LOW);
 if (flag == 0)
 {
 flag = 1;
 Serial.println("No Fire is Detected");
 gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
 delay(600);
 ShowSerialData();
 gprsSerial.println("AT+CIPSEND");
 delay(400);
 ShowSerialData();
 String str = "GET https://api.thingspeak.com/update?api_key=BP3LZ6KES8B54DIZ&field1=" + String(0);
 Serial.println(str);
 gprsSerial.println(str);
 delay(400);
 ShowSerialData();
 digitalWrite(8, LOW);
 gprsSerial.println((char)26);
 delay(500);
 gprsSerial.println();
 ShowSerialData();
 gprsSerial.println("AT+CIPSHUT");
 delay(10);
 ShowSerialData();
 }
 }
}
void ShowSerialData()
{
 while (gprsSerial.available() != 0)
 Serial.write(gprsSerial.read());
 delay(500);
}
void Module_Init()
{
 gprsSerial.println("AT");
 delay(100);
 gprsSerial.println("AT+CPIN?");
 delay(100);
 gprsSerial.println("AT+CREG?");
 delay(100);
 gprsSerial.println("AT+CGATT?");
 delay(100);
 gprsSerial.println("AT+CIPSHUT");
 delay(100);
 gprsSerial.println("AT+CIPSTATUS");
 delay(200);
 gprsSerial.println("AT+CIPMUX=0");
 delay(200);
 ShowSerialData();
 gprsSerial.println("AT+CSTT=\"www\"");
 delay(100);
 ShowSerialData();
 gprsSerial.println("AT+CIICR");
 delay(300);
 ShowSerialData();
 gprsSerial.println("AT+CIFSR");
 delay(200);
 ShowSerialData();
 gprsSerial.println("AT+CIPSPRT=0");
 delay(300);
 ShowSerialData();
}
