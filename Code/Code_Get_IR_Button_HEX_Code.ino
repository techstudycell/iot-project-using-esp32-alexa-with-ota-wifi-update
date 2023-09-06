 /**********************************************************************************
 *  TITLE: Get the Hex code from any IR remote.
 *  Click on the following links to learn more. 
 *  YouTube Video: 
 *  Related Blog : https://iotcircuithub.com/esp32-projects/
 *  by Tech StudyCell
 * 
 *  Download the Libraries:
 *  IRremote Library: https://github.com/Arduino-IRremote/Arduino-IRremote
 **********************************************************************************/

#include <IRremote.h>
 
int IR_RECV_PIN = 35;
 
IRrecv irrecv(IR_RECV_PIN);
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
 
void loop()
{
  if (irrecv.decode(&results))
  {
  Serial.print("0x");
  Serial.println(results.value, HEX); //print the HEX code
  irrecv.resume();
  }
}
