#include <Arduino.h>
#include "HAL_Button.h"
#include "display/dispDriver.h"
#include "HAL_Display.h"
#include "core/ui.h"
#include "ui_conf.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <applejuice.h> // �Զ����
#include "wifi_test.h"
ui_t ui;
int Wave_TestData;

uint8_t global_flag=0;
int device_num=-1;
// ������
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

// ����1��������ʾ
void Task1(void *pvParameters) {
  for (;;) {
    Wave_TestData = rand() % 600;
    ui_loop(&ui);
    // vTaskDelay(pdMS_TO_TICKS(100)); // ��ʱ100����
  }
}

// ����2��attack
void Task2(void *pvParameters) {
  for (;;) {
    extern uint8_t global_flag;
    extern int device_num;
    Serial.println(global_flag);
    Serial.println(device_num);
    Serial.println("\n");
    if (global_flag==1) {
      if (device_num==-1) {
        attack();
      }else
      {
        attack_by_device(device_num);
      }
      
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup start");

  // ��ʼ����ʾ��UI
  dispInit();
  MiaoUi_Setup(&ui);
  applejuice_init();
  wifi_init();
  // ��������
  BaseType_t result1 = xTaskCreate(Task1, "Task1", 8192, NULL, 1, &Task1Handle);
  BaseType_t result2 = xTaskCreate(Task2, "Task2", 8192, NULL, 1, &Task2Handle);

  // ������񴴽����
  if (result1 != pdPASS) {
    Serial.println("Task1 creation failed");
  }
  if (result2 != pdPASS) {
    Serial.println("Task2 creation failed");
  }

  Serial.println("Scheduler started");
}

void loop() {
  delay(2000);
  // delay();
}
