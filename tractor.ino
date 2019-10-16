#include <esp_now.h>
#include <WiFi.h>
#include <IBusBM.h>

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1
esp_now_peer_info_t slave;
uint8_t trailerMac[] = {0x3C, 0x71, 0xBF, 0x6E, 0xF9, 0x55};
#define maxDataFrameSize 200
const esp_now_peer_info_t *peer = &slave;
uint8_t dataToSend[maxDataFrameSize];
uint8_t RCdata[10];
byte cnt=0;

IBusBM IBusServo;
IBusBM IBusSensor;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\n");
  IBusServo.begin(Serial1, 1, 21, 22);
  IBusSensor.begin(Serial2);
  WiFi.mode(WIFI_STA);
  Serial.println( WiFi.softAPmacAddress() );
  WiFi.disconnect();
  if(esp_now_init() == ESP_OK)
  {
    Serial.println("ESP NOW INIT!");
  }
  else
  {
    Serial.println("ESP NOW INIT FAILED....");
  }
  
  
  memcpy( &slave.peer_addr, &trailerMac, 6 );
  slave.channel = WIFI_CHANNEL;
  slave.encrypt = 0;
  if( esp_now_add_peer(peer) == ESP_OK)
  {
    Serial.println("Added Peer!");
  }

  esp_now_register_send_cb(OnDataSent);
}

void loop()
{
    for (int i=0; i<10 ; i++) {
      RCdata[i]=IBusServo.readChannel(i)  ;
  //  Serial.print(RCdata[i]);
  //  Serial.print(" ");
  }
  RCdata[1] = 1500;
  sprintf((char*)dataToSend,"RC %lld",RCdata[1]);
  /*
  %+05d %+05d %+05d %+05d %+05d %+05d %+05d %+05d %+05d",
  RCdata[1],RCdata[2],RCdata[3],RCdata[4],RCdata[5],RCdata[6],RCdata[7],RCdata[8],RCdata[9],RCdata[10]);*/
  Serial.print("Data to send: ");
  Serial.println(*dataToSend);
  if( esp_now_send(slave.peer_addr, dataToSend, maxDataFrameSize) == ESP_OK)
  {
    Serial.printf("\r\nSuccess Sent Value->\t%d", dataToSend[0]);
  }
  else
  {
    Serial.printf("\r\nDID NOT SEND....");
  }
  delay(1250);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
