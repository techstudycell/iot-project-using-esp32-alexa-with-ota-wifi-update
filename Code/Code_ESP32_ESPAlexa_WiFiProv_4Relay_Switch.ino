/**********************************************************************************
 *  TITLE: ESPAlexa + IR + Switch control 4 Relays using ESP32 (Real time feedback + no WiFi control + WiFi Provision)
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/xTcsIIKROI4
 *  Related Blog : https://iotcircuithub.com/esp32-projects/
 *  
 *  This code is provided free for project purpose and fair use only.
 *  Please do mail us to techstudycell@gmail.com if you want to use it commercially.
 *  Copyrighted © by Tech StudyCell
 *  
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board ESP32 (2.0.11) : https://github.com/espressif/arduino-esp32
 *
 *  Download the libraries 
 *  Espalexa Library (2.7.0):  https://github.com/Aircoookie/Espalexa
 *  IRremote Library (3.6.1): https://github.com/Arduino-IRremote/Arduino-IRremote
 *  AceButton Library (1.9.2): https://github.com/bxparks/AceButton
 **********************************************************************************/


// #define USE_SOFT_AP // Uncomment if you want to enforce using Soft AP method instead of BLE

const char * pop = "abcd1234"; // Proof of possession - otherwise called a PIN - string provided by the device, entered by user in the phone app
const char * service_name = "PROV_123"; // Name of your device (the Espressif apps expects by default device name starting with "Prov_")
const char * service_key = NULL; // Password used for SofAP method (NULL = no password needed)
bool reset_provisioned = false; // When true the library will automatically delete previously provisioned data.


// device names
String Device_1_Name = "Night Lamp";
String Device_2_Name = "Room Light";
String Device_3_Name = "Studio Light";
String Device_4_Name = "Toilet Light";


//Update the HEX code of IR Remote buttons 0x<HEX CODE>
#define IR_Button_1   0x1FEE01F
#define IR_Button_2   0x1FE10EF
#define IR_Button_3   0x1FE906F
#define IR_Button_4   0x1FE50AF
#define IR_All_On     0x1FE807F
#define IR_All_Off    0x1FE48B7

#include <WiFi.h>
#include "WiFiProv.h"
#include <Espalexa.h>
#include <IRremote.h>
#include <AceButton.h>
using namespace ace_button;

Espalexa espalexa;

// define the GPIO connected with Relays and switches
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19

#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27


#define wifiLed   2   //D2
#define IR_RECV_PIN   35 // D35 (IR receiver pin)

#define WiFiResetButton 0  //BOOT button


// Relay State
bool toggleState_1 = LOW; //Define integer to remember the toggle state for relay 1
bool toggleState_2 = LOW; //Define integer to remember the toggle state for relay 2
bool toggleState_3 = LOW; //Define integer to remember the toggle state for relay 3
bool toggleState_4 = LOW; //Define integer to remember the toggle state for relay 4


ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);

int wifiFlag = 0;

IRrecv irrecv(IR_RECV_PIN);
decode_results results;

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);


boolean wifiConnected = false;
boolean addDevicesFlag = false;

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness == 255)
    {
      digitalWrite(RelayPin1, LOW);
      Serial.println("Device1 ON");
      toggleState_1 = 1;
    }
  else
  {
    digitalWrite(RelayPin1, HIGH);
    Serial.println("Device1 OFF");
    toggleState_1 = 0;
  }
}

void secondLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin2, LOW);
      Serial.println("Device2 ON");
      toggleState_2 = 1;
    }
  else
  {
    digitalWrite(RelayPin2, HIGH);
    Serial.println("Device2 OFF");
    toggleState_2 = 0;
  }
}

void thirdLightChanged(uint8_t brightness)
{
  //Control the device  
  if (brightness == 255)
    {
      digitalWrite(RelayPin3, LOW);
      Serial.println("Device3 ON");
      toggleState_3 = 1;
    }
  else
  {
    digitalWrite(RelayPin3, HIGH);
    Serial.println("Device3 OFF");
    toggleState_3 = 0;
  }
}

void fourthLightChanged(uint8_t brightness)
{
  //Control the device 
  if (brightness == 255)
    {
      digitalWrite(RelayPin4, LOW);
      Serial.println("Device4 ON");
      toggleState_4 = 1;
    }
  else
  {
    digitalWrite(RelayPin4, HIGH);
    Serial.println("Device4 OFF");
    toggleState_4 = 0;
  }
}



void addDevices(){
  // Define your devices here.
  espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
  espalexa.addDevice(Device_2_Name, secondLightChanged);
  espalexa.addDevice(Device_3_Name, thirdLightChanged);
  espalexa.addDevice(Device_4_Name, fourthLightChanged);

  espalexa.begin();
}

void sendFeedback(int relay, int value){
  EspalexaDevice* d = espalexa.getDevice(relay); //the index is zero-based
  if(relay == 4){
    d->setPercent(map(value, 0, 4, 0, 100)); //set value "brightness" in percent
  }
  else{
    d->setPercent(value);
  }
}

void ir_remote(){
  if (irrecv.decode(&results)) {
    switch(results.value){
        case IR_Button_1:  
          digitalWrite(RelayPin1, toggleState_1);
          toggleState_1 = !toggleState_1;
          (toggleState_1 == false) ? sendFeedback(0, 0) : sendFeedback(0, 100);
          delay(100);            
          break;
        case IR_Button_2:  
          digitalWrite(RelayPin2, toggleState_2);
          toggleState_2 = !toggleState_2;
          (toggleState_2 == false) ? sendFeedback(1, 0) : sendFeedback(1, 100);
          delay(100);            
          break;
        case IR_Button_3:  
          digitalWrite(RelayPin3, toggleState_3);
          toggleState_3 = !toggleState_3;
          (toggleState_3 == false) ? sendFeedback(2, 0) : sendFeedback(2, 100);
          delay(100);            
          break;
        case IR_Button_4:  
          digitalWrite(RelayPin4, toggleState_4);
          toggleState_4 = !toggleState_4;
          (toggleState_4 == false) ? sendFeedback(3, 0) : sendFeedback(3, 100);
          delay(100);            
          break;
        case IR_All_Off:
          all_SwitchOff();  
          break;
        case IR_All_On:
          all_SwitchOn();  
          break;
        default : break;         
      }   
      //Serial.println(results.value, HEX);    
      irrecv.resume();   
  } 
}

void all_SwitchOn(){
  toggleState_1 = 1; digitalWrite(RelayPin1, LOW); sendFeedback(0, 100); delay(100);
  toggleState_2 = 1; digitalWrite(RelayPin2, LOW); sendFeedback(1, 100); delay(100);
  toggleState_3 = 1; digitalWrite(RelayPin3, LOW); sendFeedback(2, 100); delay(100);
  toggleState_4 = 1; digitalWrite(RelayPin4, LOW); sendFeedback(3, 100); delay(100);
}

void all_SwitchOff(){
  toggleState_1 = 0; digitalWrite(RelayPin1, HIGH); sendFeedback(0, 0); delay(100);
  toggleState_2 = 0; digitalWrite(RelayPin2, HIGH); sendFeedback(1, 0); delay(100);
  toggleState_3 = 0; digitalWrite(RelayPin3, HIGH); sendFeedback(2, 0); delay(100);
  toggleState_4 = 0; digitalWrite(RelayPin4, HIGH); sendFeedback(3, 0); delay(100);
}

void SysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        Serial.print("\nConnected IP address : ");
        Serial.println(IPAddress(sys_event->event_info.got_ip.ip_info.ip.addr));
        wifiConnected = 1;
        break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        Serial.println("\nDisconnected. Connecting to the AP again... ");
        wifiConnected = 0;
        break;
    case ARDUINO_EVENT_PROV_START:
        Serial.println("\nProvisioning started\nGive Credentials of your access point using smartphone app");
        break;
    case ARDUINO_EVENT_PROV_CRED_RECV: {
        Serial.println("\nReceived Wi-Fi credentials");
        Serial.print("\tSSID : ");
        Serial.println((const char *) sys_event->event_info.prov_cred_recv.ssid);
        Serial.print("\tPassword : ");
        Serial.println((char const *) sys_event->event_info.prov_cred_recv.password);
        break;
    }
    case ARDUINO_EVENT_PROV_CRED_FAIL: {
        Serial.println("\nProvisioning failed!\nPlease reset to factory and retry provisioning\n");
        if(sys_event->event_info.prov_fail_reason == WIFI_PROV_STA_AUTH_ERROR)
            Serial.println("\nWi-Fi AP password incorrect");
        else
            Serial.println("\nWi-Fi AP not found....Add API \" nvs_flash_erase() \" before beginProvision()");
        break;
    }
    case ARDUINO_EVENT_PROV_CRED_SUCCESS:
        Serial.println("\nProvisioning Successful");
        break;
    case ARDUINO_EVENT_PROV_END:
        Serial.println("\nProvisioning Ends");
        break;
    default:
        break;
    }
}

void wifiReset(){
  if (digitalRead(WiFiResetButton) == LOW)
    {
      Serial.println("Reset Button Pressed");
      delay(5000);
  
      if (digitalRead(WiFiResetButton) == LOW) {
        Serial.println("Resetting");
        wifi_prov_mgr_reset_provisioning();
        ESP.restart();
      }
    }
}

void setup()
{
  Serial.begin(115200);
  
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  pinMode(WiFiResetButton, INPUT);


  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);
  digitalWrite(RelayPin3, !toggleState_3);
  digitalWrite(RelayPin4, !toggleState_4);

  digitalWrite(wifiLed, LOW);

  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);

  button1.init(SwitchPin1);
  button2.init(SwitchPin2);
  button3.init(SwitchPin3);
  button4.init(SwitchPin4);

  irrecv.enableIRIn(); // Enabling IR sensor

   WiFi.onEvent(SysProvEvent);

#if CONFIG_IDF_TARGET_ESP32 && CONFIG_BLUEDROID_ENABLED && not USE_SOFT_AP
    Serial.println("Begin Provisioning using BLE");
    // Sample uuid that user can pass during provisioning using BLE
    uint8_t uuid[16] = {0xb4, 0xdf, 0x5a, 0x1c, 0x3f, 0x6b, 0xf4, 0xbf,
                        0xea, 0x4a, 0x82, 0x03, 0x04, 0x90, 0x1a, 0x02 };
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name, service_key, uuid, reset_provisioned);
#else
    Serial.println("Begin Provisioning using Soft AP");
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name, service_key);
#endif

  #if CONFIG_BLUEDROID_ENABLED && not USE_SOFT_AP
    log_d("ble qr");
    WiFiProv.printQR(service_name, pop, "ble");
  #else
    log_d("wifi qr");
    WiFiProv.printQR(service_name, pop, "softap");
  #endif

  delay(500);
}

void loop()
{  
  if (!wifiConnected)
  {
    //Serial.println("WiFi Not Connected ");
    digitalWrite(wifiLed, LOW); //Turn off WiFi LED
  }
  else
  {
    //Serial.print("WiFi Connected  ");
    digitalWrite(wifiLed, HIGH);
    if(!addDevicesFlag){
      delay(200);
      addDevices();
      Serial.println("Devices added... ");
      addDevicesFlag = true;
      delay(500);
    }
    espalexa.loop();
    delay(1);
  }
  
  wifiReset(); //to reset wifi details
  
  //Control Switches Manualy
  button1.check();
  button2.check();
  button3.check();
  button4.check();

  ir_remote(); //IR remote Control
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT1");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_1 = 1;
      digitalWrite(RelayPin1, LOW);
      sendFeedback(0, 100);
      break;
    case AceButton::kEventReleased:
      toggleState_1 = 0;
      digitalWrite(RelayPin1, HIGH);
      sendFeedback(0, 0);
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT2");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_2 = 1;
      digitalWrite(RelayPin2, LOW);
      sendFeedback(1, 100);
      break;
    case AceButton::kEventReleased:
      toggleState_2 = 0;
      digitalWrite(RelayPin2, HIGH);
      sendFeedback(1, 0);
      break;
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT3");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_3 = 1;
      digitalWrite(RelayPin3, LOW);
      sendFeedback(2, 100);
      break;
    case AceButton::kEventReleased:
      toggleState_3 = 0;
      digitalWrite(RelayPin3, HIGH);
      sendFeedback(2, 0);
      break;
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println("EVENT4");
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_4 = 1;
      digitalWrite(RelayPin4, LOW);
      sendFeedback(3, 100);
      break;
    case AceButton::kEventReleased:
      toggleState_4 = 0;
      digitalWrite(RelayPin4, HIGH);
      sendFeedback(3, 0);
      break;
  }
}
