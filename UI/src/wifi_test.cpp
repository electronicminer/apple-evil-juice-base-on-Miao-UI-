#include "Arduino.h"
#include "wifi.h"
#include "HAL_Display.h"
#include "indev/indevDriver.h"
#include "ui_conf.h"
void wifi_init() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("wifi Setup done");
}

char wifiInfo[1000] = ""; // 创建一个空字符串用于存储WiFi信息

void wifi_scan(ui_t* ui) {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    strcpy(wifiInfo, "No networks found");
  } else {
    while(1)
    {
      if(indevScan() == UI_ACTION_ENTER)return;
      for (int i = 0; i < n; ++i) {
      char buffer[100];
    //   sprintf(buffer, "Network: %s, RSSI: %d, Encryption: %s\n", WiFi.SSID(i).c_str(), WiFi.RSSI(i), (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured");
      sprintf(buffer, " %- %ddB\n", WiFi.SSID(i).c_str(), WiFi.RSSI(i));
      strcat(wifiInfo, buffer);
      delay(1000);
      strcpy(wifiInfo, ""); // 清空字符串以便下一次扫描
    }
    
    }
  }
  Serial.print(wifiInfo); // 打印所有WiFi信息
//   delay(1000); // 延迟5秒后再次扫描
  
}
