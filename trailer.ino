//cc:50:e3:af:e2:14

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1
uint8_t localCustomMac[] = {0xCC, 0x50, 0xE3, 0xAF, 0xE2, 0x14};
const byte maxDataFrameSize = 200;
byte cnt=0;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\n");
  WiFi.mode(WIFI_AP); 
  Serial.println( WiFi.softAPmacAddress() );
  WiFi.disconnect();
  if(esp_now_init() == ESP_OK)
  {
    Serial.println("ESPNow Init Success!");
  }
  else
  {
    Serial.println("ESPNow Init Failed....");
  }
  esp_now_register_recv_cb(OnDataRecv);
  
}

void loop()
{
 yield();
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  Serial.printf("\r\nReceived\t%d Bytes\t%d", data_len, *data);
}
