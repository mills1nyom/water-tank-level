//  #define uS_TO_S_FACTOR 1000000ULL
//  #define TIME_TO_SLEEP  5     


#include <LiquidCrystal_I2C.h>

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Arduino.h>

#include <WiFiMulti.h>
 #include <HTTPClient.h>
WiFiMulti wifiMulti;


//RTC_DATA_ATTR int bootCount = 0;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display



#include "motor.h";

const char* ssid = "Millz";
const char* password = "nanayaw2022";

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701 

WebServer server(80);

const int led = 2;
const int motor = 13;
const int trigPin = 5;
const int echoPin = 18;
int value = 0;
int tankID = 1;



float WaterLevel;
long duration;
float distanceCm;
float distanceInch;

unsigned long prevTime_T1 = millis();
long interval_T1 = 1000;
unsigned long prevTime_T2 = millis();
long interval_T2 = 1000;
unsigned long prevTime_T3 = millis();
long interval_T3 = 1000;
unsigned long prevTime_T4 = millis();
long interval_T4 = 1000;

 void handleRoot() {
 
 String s=MAIN_page;
 server.send(200, "text/html", s);

 }

void getTank1(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  WaterLevel=distanceCm;

  String getT1 = String(distanceCm);
  server.send(200, "text/plane", getT1);  // Print a message on both lines of the LCD.
 

  //delay(1000);


}

//  void print_wakeup_reason(){
//   esp_sleep_wakeup_cause_t wakeup_reason;

//   wakeup_reason = esp_sleep_get_wakeup_cause();

//   switch(wakeup_reason)
//   {
//     case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
//     case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
//     case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
//     case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
//     case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
//     default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
//   }
// }




// void lcdPrintValues() {
// float Tank1;
// long duration;
// float distanceCm;

//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   duration = pulseIn(echoPin, HIGH);
  
//   // Calculate the distance
//   distanceCm = duration * SOUND_SPEED/2;
//   Tank1=distanceCm;

//   String lcdprint = "Tanks values are : \n";
//   lcdprint += "Tank1 =";
//   lcdprint += Tank1;
//   server.send(200, "text/plain", lcdprint);
// }

// void handleNotFound() {
//   digitalWrite(led, 1);
//   String message = "File Not Found\n\n";
//   message += "URI: ";
//   message += server.uri();
//   message += "\nMethod: ";
//   message += (server.method() == HTTP_GET) ? "GET" : "POST";
//   message += "\nArguments: ";
//   message += server.args();
//   message += "\n";
//   for (uint8_t i = 0; i < server.args(); i++) {
//     message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//   }
//   server.send(404, "text/plain", message);
//   digitalWrite(led, 0);
// }

void MS(){
 value=2;
  //if(value == 1) {
  // digitalWrite(led,HIGH);
  // digitalWrite(motor,LOW);
  //  server.send(200, "text/plane");
  
  // }
}
void MSt(){
  value=1;
  //if(value == 1){
  //    digitalWrite(led,LOW);
  // digitalWrite(motor,HIGH);
  //   server.send(200, "text/plane");
  //}
  }
 

void A(){

  value= 0;

  // if(distanceCm<=15){
  // digitalWrite(led,HIGH);
  // digitalWrite(motor,LOW);
  //  server.send(200, "text/plane");
 
  // }

  // else if(distanceCm>35){
  //  digitalWrite(led,LOW);
  // digitalWrite(motor,HIGH);
  // server.send(200, "text/plane");
    
  // }
  



  //server.send(200, "text/plane");

}

void setup(void) {

  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(led, OUTPUT); // Sets the led as an Output
  pinMode(motor, OUTPUT); // Sets the motor as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

 
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  Serial.println();
  Serial.println();
  Serial.println();

  // for (uint8_t t = 4; t > 0; t--) {
  //   Serial.printf("[SETUP] WAIT %d...\n", t);
  //   Serial.flush();
  //   delay(1000);
  // }

 WiFi.mode(WIFI_STA);
 wifiMulti.addAP("Millz", "nanayaw2022");
//   // Wait for connection
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
//   Serial.println("");
//   Serial.print("Connected to ");
//   Serial.println(ssid);
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());

  // if (MDNS.begin("esp32")) {
  //   Serial.println("MDNS responder started");
  // }

  // server.on("/", handleRoot);
  
  // server.on("/lcd", lcdPrintValues);

  // server.on("/inline", []() {
  //   server.send(200, "text/plain", "this works as well");
  // });

  // server.onNotFound(handleNotFound);
 server.on("/", handleRoot); 
 server.on("/MS", MS);     
 server.on("/MSt", MSt);
 server.on("/readTank1", getTank1);
 server.on("/A", A);
server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  unsigned long currentTime = millis();
  if(currentTime - prevTime_T3 > interval_T3){
  getTank1();
  prevTime_T3 = currentTime;

}
 
// if(currentTime - prevTime_T4 > interval_T4){
 if(value==0){
     if(distanceCm<=15){
  digitalWrite(led,HIGH);
  digitalWrite(motor,HIGH);
   server.send(200, "text/plane");
 
  }

  else if(distanceCm>35){
   digitalWrite(led,LOW);
  digitalWrite(motor,LOW);
  server.send(200, "text/plane");
 }
 }
 else if(value==1){
       digitalWrite(led,LOW);
  digitalWrite(motor,LOW);
    server.send(200, "text/plane"); 
 }
 else if(value==2){
     digitalWrite(led,HIGH);
  digitalWrite(motor,HIGH);
   server.send(200, "text/plane");
 }

//    prevTime_T4 = currentTime;

// }

  if(currentTime - prevTime_T2 > interval_T2){
    // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Distance is");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print(distanceCm);

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  prevTime_T2 = currentTime;

}

  server.handleClient();
//  delay(1000);



if(currentTime - prevTime_T1 > interval_T1){
  // wait for WiFi connection
  if ((wifiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://192.168.123.129/IOTLAB5/Lab5.php?WaterLevel=" +String(WaterLevel)+ "&tankID="+String(tankID))) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();

     // Sleep

     //delay(1000);

  //    //Increment boot number and print it every reboot
  //  ++bootCount;
  //  Serial.println("Boot number: " + String(bootCount));

  // //Print the wakeup reason for ESP32
  // print_wakeup_reason();

  // /*
  // First we configure the wake up source
  // We set our ESP32 to wake up every 5 seconds
  // */
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  // " Seconds");

  // // /*
  // Next we decide what all peripherals to shut down/keep on
  // By default, ESP32 will automatically power down the peripherals
  // not needed by the wakeup source, but if you want to be a poweruser
  // this is for you. Read in detail at the API docs
  // http://esp-idf.readthedocs.io/en/latest/api-reference/system/deep_sleep.html
  // Left the line commented as an example of how to configure peripherals.
  // The line below turns off all RTC peripherals in deep sleep.
  // */
  //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  //Serial.println("Configured all RTC Peripherals to be powered down in sleep");

  /*
  Now that we have setup a wake cause and if needed setup the
  peripherals state in deep sleep, we can now start going to
  deep sleep.
  In the case that no wake up sources were provided but deep
  sleep was started, it will sleep forever unless hardware
  reset occurs.
  */
 // Serial.println("Going to sleep now");
// Serial.flush(); 
// esp_deep_sleep_start();
//  Serial.println("This will never be printed");
  
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  prevTime_T1 = currentTime;
 
}
}

   //allow the cp