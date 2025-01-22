#include "HAL_Button.h"
#include "Arduino.h"
#define   TOUCH_BUTTON1 10
#define   TOUCH_BUTTON2 14
#define   TOUCH_BUTTON3 1

int current_time=0;
int last_time=0;

int touch_value1 = 0;
int touch_value2 = 0;
int touch_value3 = 0;
char button1_state = 0;
char button2_state = 0;
char button3_state = 0;
int touch_test = 28000;
void key_init(void)
{
    pinMode(TOUCH_BUTTON1, INPUT_PULLUP);
    pinMode(TOUCH_BUTTON2, INPUT_PULLUP);
    pinMode(TOUCH_BUTTON3, INPUT_PULLUP);
}
uint8_t touch_button_scan(void)
{
     current_time = millis();
  if (current_time - last_time > 200)
   {
    last_time = current_time;
    touch_value1 = touchRead(TOUCH_BUTTON1);
    touch_value2 = touchRead(TOUCH_BUTTON2);
    touch_value3 = digitalRead(TOUCH_BUTTON3);
    if (touch_value1 > touch_test) {
      button1_state=1;
      return 1;
    }
    if (touch_value2 > touch_test) {
      button2_state=1;
      return 2;
    }
    if (touch_value3==HIGH) {
      button3_state=1;
        return 3;
    }
    
  }
  return 0;
}
uint8_t touch_button_scan_2(void)
{
     current_time = millis();
  // if (current_time - last_time > 200)
   {
    last_time = current_time;
    touch_value1 = touchRead(TOUCH_BUTTON1);
    touch_value2 = touchRead(TOUCH_BUTTON2);
    touch_value3 = digitalRead(TOUCH_BUTTON3);
    if (touch_value1 > touch_test) {
      button1_state=1;
      return 1;
    }
    if (touch_value2 > touch_test) {
      button2_state=1;
      return 2;
    }
    if (touch_value3 ==0) {
      button3_state=1;
        return 3;
    }
    
  }
  return 0;
}
uint8_t key_scan(void)
{
    uint8_t key;
    // if(Serial.available())
    // Serial.readBytes(&key, 1);
    // else key = 0;
    key = touch_button_scan();
    switch (key)
    {
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    case 3:
        return 3;
        break;
    default:
        break;
    }
    return 0;
    
    
}