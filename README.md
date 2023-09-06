# IoT Project Using ESP32 Alexa With OTA WiFi Update
ESP32 Alexa Home Automation with OTA WiFi credentials update for FREE. (Circuit + Code)
In this IoT project, I have shown how to make IoT-based ESP32 Home Automation using Alexa, IR remote, and switches to control a 4-channel relay module with and without the internet. If the internet is unavailable, you can control the home appliances from IR remote & manual switches.
You can also update the WiFi credentials through OTA using the ESP BLE Provisioning app.
You don't need any third-party IoT applications to make this IoT project, you just need an echo device and ESP32.
During the article, I have shown all the steps to make this ESP32 Alexa home automation system.

## Tutorial Video on IoT Project using ESP32 & Alexa
https://youtu.be/xTcsIIKROI4

**This ESP32 control relay module has the following features:**

1. Update WiFi credentials to ESP32 through OTA using the ESP BLE Provisioning app.
2. Control home appliances with Alexa (voice control).
3. Control home appliances with an IR Remote.
4. Control home appliances with manual switches.
5. Monitor real-time feedback in the Amazon Alexa app
6. Control home appliances manually without internet from IR remote and switches.
   
If you don't want to use any PCB, you can also make this IoT project using a 4-channel relay module, ESP32, and IR receiver sensor.

## Required Components for the ESP32 Project

**Required Components (without PCB) for the ESP32 project.**
1. ESP32 DEV KIT V1
2. 4-channel 5V SPDT Relay Module
3. TSOP1838 IR receiver (with metallic casing)
4. Switches
5. Amazon Echo Dot

**Required Components (for PCB)**
1. ESP32 DEVKIT
2. TSOP1838 IR receiver
3. Relays 5v (SPDT) (4 no)
4. BC547 Transistors (4 no)
5. PC817 Optocuplors (4 no)
6. 510-ohm 0.25-watt Resistor (4 no) (R1 - R4)
7. 1k 0.25-watt Resistors (6 no) (R5 - R11)
8. LED 5-mm (6 no)
9. 1N4007 Diodes (4 no) (D1 - D4)
10. Push Buttons (4 no) or Switches
11. Terminal Connectors
12. Any Alexa devices like ECHO DOT

## Circuit Diagram of the ESP32 Projects

The circuit is very simple, I have used the GPIO pins **D23, D22, D21 & D19** to control the 4 relays.

The GPIO pins **D13, D12, D14 & D27** are connected with switches to control the relays manually.

I used the INPUT_PULLUP function in Arduino IDE instead of the pull-up resistors.

IR remote receiver (TSOP1838) connected with **D35.**

I have used a 5V mobile charger to supply the smart relay module.

Please take proper safety precautions while working with high voltage.

## Testing the Circuit Before Designing the PCB

Before designing the PCB, I made the complete circuit using ESP32, a 4-channel relay module, IR receiver, and manual switches.

As you can see, the relay can be controlled from the IR Remote, manual switches, and Amazon Alexa App.

In the following steps, I have explained the complete projects in detail and also shared the code and PCB Garber file.

##Design the PCB for ESP32 Home Automation System

To make the circuit compact and give it a professional look, I designed the PCB after testing all the features of the smart relay module.

You can download the PCB Gerber, BOM, and "pick and place" files of this ESP32 control relay PCB from the following link:

**Download PCB Gerber File:** https://github.com/techstudycell/iot-project-using-esp32-alexa-with-ota-wifi-update/tree/main/PCB_Gerber

For this project, you can also use the JLC SMT Service while ordering the PCB

## Why you should use JLC SMT Service?
On JLCPCB's one-stop online platform, customers enjoy low-cost & high-quality & fast SMT service at an $8.00 setup fee($0.0017 per joint).

$27 New User coupon & $24 SMT coupons every month.
Visit https://jlcpcb.com/RAB

JLCPCB SMT Parts Library 200k+ in-stock components (689 Basic components and 200k+ Extended components)

Parts Pre-Order service https://support.jlcpcb.com/article/164-what-is-jlcpcb-parts-pre-order-service

Build a Personal library Inventory, save parts for now or the future

Assembly will support 10M+ parts from Digikey, Mouser.

## Steps to Order the PCB Assembly from JLCPCB
1. Visit https://jlcpcb.com/RAB and **Sign in / Sign up.**
2. Click on the **QUOTE NOW** button.
3. Click on the "**Add your Gerber file**" button. Then browse and select the Gerber file you have downloaded.
4. Set the required parameters like **Quantity, PCB masking color**, etc.
5. Select the **Assemble side** and SMT Quantity.
6. Now upload the **BOM and PickAndPlace files**.
7. Now **confirm all the components** that you want to be soldered by SMT services.
8. Click on the "**SAVE TO CART** button.
9. Type the **Shipping Address**.
10. Select the **Shipping Method** suitable for you.
11. Submit the order and proceed with the **payment**.

You can also track your order from the JLCPCB.
My PCBs took 3 days to get manufactured and arrived within a week using the DHL delivery option.
PCBs were well packed and the quality was really good at this affordable price.

## Get the IR Codes (HEX Code) From the Remote
Now, to get the HEX codes from the remote, first, we have to connect the IR receiver output pin with GPIO D35.

And give the 5V across the VCC and GND. The IR receiver must have a metallic casing, otherwise, you may face issues.

Then follow the following steps to get the HEX codes

1. Install the IRremote library in Arduino IDE
2. Download the attached code, and upload it to ESP32.
3. Open Serial Monitor with Baud rate 9600.
4. Now, press the IR remote button.
5. The respective HEX code will populate in the serial monitor.
Save all the HEX codes in a text file.

## Program the ESP32 for This IoT Project
Please download the code for this IoT project.

First, you have to install the required libraries. I have shared all the links in the code.
**Download the libraries**
 1. Espalexa Library (2.7.0): https://github.com/Aircoookie/Espalexa
 2. IRremote Library (3.6.1): https://github.com/Arduino-IRremote/Arduino-IRremote
 3. AceButton Library (1.9.2): https://github.com/bxparks/AceButton

1. Then enter the Device Names for Alexa. (as per your requirement)
2. Update the HEX codes for IR Remote Buttons

In the code, I have used the **WiFiProv.h** library to reset the WiFi credentials from mobile using the ESP BLE Provisioning app.
After doing these changes, go to Tools and select the board as "**ESP32 Dev Module**", Partition Scheme as "**Huge APP (3MB...)**" and the proper PORT in Arduino IDE.

Then click on the **upload** button to program the ESP32 board.

## Generate the QR Code to Update WiFi Details
After uploading the code, open the serial monitor with Baud rate 115200. Then press the boot button of ESP32 for 5 seconds.
A QR code will appear in the serial monitor, then copy the QR code and paste in Notepad++ or any other IDE.

## Enter WiFi Credentials to ESP32 using ESP BLE Provisioning app
Download and install the ESP BLE Provisioning app from the Google Play Store or App Store.

Now turn on the Bluetooth and GPS on your mobile, then scan the QR code using the ESP BLE Provisioning app.
Enter the WiFi credentials (WiFi Name and Password) and submit.
The ESP BLE Provisioning app will send the WiFi credentials to ESP32 through BLE. The ESP32 will connect to that WiFi and the inbuilt blue LED will turn on.

## Configure the Alexa App for the Smart Home System
Open the Amazon Alexa App and follow the steps:

1. Tap on Devices. Then Tap on the "+" icon.
2. Tap on "**Light**", then select "**Others**".
3. Select **WiFi**.
4. Tap on "**DISCOVER DEVICES**".
5. Tap on "**Devices**", and tap on "Lights" to see all the devices.

Once the Alexa App finds all the devices, you can control those devices with voice commands using the Alexa Echo Dot.

## Control Relays With Alexa, IR Remote & Manual Switch
Now you can control the relays with voice commands using Alexa. Or if the WiFi is not available, you can control the relays with the IR remote and manual switches.

**After adding the devices to the Amazon Alexa app, only the Echo Dot and ESP32 must be connected with the same WiFi. Your mobile can be connected to any different network.

If the WiFi is available, you can also monitor the real-time feedback on the Amazon Alexa app.

I hope you have liked this Alexa home automation project. I have shared all the required information for this project. I will really appreciate it if you share your valuable feedback.

Also if you have any queries please write in the comment section. Thank you & Happy Learning.
