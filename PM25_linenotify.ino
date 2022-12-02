#include <PMS.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <TridentTD_LineNotify.h>

#define pmsErr 0
int pmsValue;
String pmsDataLine;
String result1;
#define SSID        "-"
#define PASSWORD    "-"
#define LINE_TOKEN  "-"

PMS pms(Serial);
PMS::DATA data;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

void getStatus(){
  if(pmsValue>300){
      lcd.setCursor(0,1);
      lcd.print("HAZARDOUS!");
      }else if(pmsValue<=300&&pmsValue>200){
      lcd.setCursor(0,1);
      lcd.print("Very Unhealty");
     }else if(pmsValue<=200&&pmsValue>150){
      lcd.setCursor(0,1);
      lcd.print("Unhealty");
     }else if(pmsValue<=150&&pmsValue>100){
      lcd.setCursor(0,1);
      lcd.print("Unhealty sensitive");
      }else if(pmsValue<=100&&pmsValue>0){
      lcd.setCursor(0,1);
      lcd.print("Good");
     }else{
      lcd.setCursor(0,1);
      lcd.print("Waiting");
     }
}
void loop()
{
  if (pms.read(data))
  {
    //delay(2000);
    pmsValue = data.PM_AE_UG_2_5 - pmsErr;
    lcd.begin();
    lcd.setCursor(0,0); 
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(pmsValue);
    lcd.print("PM2.5 : ");
    lcd.print(pmsValue);
    lcd.print(" ug/m3");

    lcd.setCursor(0,1);
    lcd.print(" ");
    getStatus();
    String value1 = String(pmsValue);
    getStatus();
 
    String pmsDataLine = String("PM 2.5 : "+value1+ " ug/m3 ");
     LINE.notify(pmsDataLine);
    //getStatus()
  }
 }
