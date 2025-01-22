/**
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <2024>  <JianFeng>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "ui_conf.h"
#include "core/ui.h"
#include "display/dispDriver.h"
#include "images/image.h"
#include "widget/custom.h"
#include "version.h"

#include "wifi_test.h"
#include"Arduino.h"
//

//
/*Page*/
ui_page_t Home_Page, System_Page,Apple_juice_Page;
/*item */
ui_item_t HomeHead_Item, SystemHead_Item, System_Item, Image_Item, Github_Item, Bilibili_Item, Version_Item, Wave_Item,AppleJuice_Item,AppleJuiceHead_Item,Animation_Item;
ui_item_t Contrast_Item, Power_Item, MenuColor_Item, CursorAni_Item, Test_Item;
ui_item_t Attack_Item,Airpods_Item,Airpods_Pro_Item,Airpods_Max_Item,Airpods_Gen_3_Item,Airpods_Pro_Gen_2_Item,Power_Beats_Item,Power_Beats_Pro_Item,Beats_Solo_Pro_Item,Beats_Studio_Buds_Item,Beats_Flex_Item,Beats_X_Item,Beats_Solo_3_Item,Beats_Studio_3_Item,wifi_Item;
/**
 * 在此建立所需显示或更改的数据
 * 无参数
 * 无返回值
 */
//
extern uint8_t global_flag;
extern int device_num;
void flag_test()
{
    if(global_flag == 0)
    global_flag = 1;
    else
    global_flag = 0;
}

//
void device_choose0()
{
    if(device_num != 0)
    device_num = 0;
    else
    device_num = -1;
}
//
void device_choose1()
{
    if(device_num != 1)
    device_num = 1;
    else
    device_num = -1;
}
//
void device_choose2()
{
    if(device_num != 2)
    device_num = 2;
    else
    device_num = -1;
}
//
void device_choose3()
{
    if(device_num != 3)
    device_num = 3;
    else
    device_num = -1;
}
//
void device_choose4()
{
    if(device_num != 4)
    device_num = 4;
    else
    device_num = -1;
}
//
void device_choose5()
{
    if(device_num != 5)
    device_num = 5;
    else
    device_num = -1;
}
//
void device_choose6()
{
    if(device_num != 6)
    device_num = 6;
    else
    device_num = -1;
}
//
void device_choose7()
{
    if(device_num != 7)
    device_num = 7;
    else
    device_num = -1;
}
//
void device_choose8()
{
    if(device_num != 8)
    device_num = 8;
    else
    device_num = -1;
}
//
void device_choose9()
{
    if(device_num != 9)
    device_num = 9;
    else
    device_num = -1;
}
//
void device_choose10()
{
    if(device_num != 10)
    device_num = 10;
    else
    device_num = -1;
}
//
void device_choose11()
{
    if(device_num != 11)
    device_num = 11;
    else
    device_num = -1;
}
//
void device_choose12()
{
    if(device_num != 12)
    device_num = 12;
    else
    device_num = -1;
}
//
void Create_Parameter(ui_t *ui)
{
    static int Contrast = 255;
    static ui_data_t Contrast_data;
    Contrast_data.name = "Contrast";
    Contrast_data.ptr = &Contrast;
    Contrast_data.function = Disp_SetContrast;
    Contrast_data.functionType = UI_DATA_FUNCTION_STEP_EXECUTE;
    Contrast_data.dataType = UI_DATA_INT;
    Contrast_data.actionType = UI_DATA_ACTION_RW;
    Contrast_data.max = 255;
    Contrast_data.min = 0;
    Contrast_data.step = 5;
    static ui_element_t Contrast_element;
    Contrast_element.data = &Contrast_data;
    Create_element(&Contrast_Item, &Contrast_element);

    static uint8_t power_off = false;
    static ui_data_t Power_switch_data;
    Power_switch_data.ptr = &power_off;
    Power_switch_data.function = Disp_SetPowerSave;
    Power_switch_data.dataType = UI_DATA_SWITCH;
    Power_switch_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Power_element;
    Power_element.data = &Power_switch_data;
    Create_element(&Power_Item, &Power_element);

    extern int Wave_TestData;
    static ui_data_t Wave_data;
    Wave_data.name = "Wave";
    Wave_data.ptr = &Wave_TestData;
    Wave_data.dataType = UI_DATA_INT;
    Wave_data.max = 600;
    Wave_data.min = 0;
    static ui_element_t Wave_element;
    Wave_element.data = &Wave_data;
    Create_element(&Wave_Item, &Wave_element);


    static ui_data_t MenuColor_data;
    MenuColor_data.name = "MenuColor";
    MenuColor_data.ptr = &ui->bgColor;
    MenuColor_data.dataType = UI_DATA_SWITCH;
    MenuColor_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t MenuColor_element;
    MenuColor_element.data = &MenuColor_data;
    Create_element(&MenuColor_Item, &MenuColor_element);

    static ui_data_t CursorAni_data;
    CursorAni_data.name = "CursorAni";
    CursorAni_data.ptr = &ui->animation.cursor_ani.kp;
    CursorAni_data.dataType = UI_DATA_FLOAT;
    CursorAni_data.actionType = UI_DATA_ACTION_RW;
    CursorAni_data.min = 0;
    CursorAni_data.max = 10;
    CursorAni_data.step = 0.1;
    static ui_element_t CursorAni_element;
    CursorAni_element.data = &CursorAni_data;
    Create_element(&CursorAni_Item, &CursorAni_element);
    //
    static uint8_t attack1 = false;
    static ui_data_t attack_data;
    attack_data.ptr = &attack1;
    attack_data.function =  flag_test;
    attack_data.dataType = UI_DATA_SWITCH;
    attack_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t attack_element;
    attack_element.data = &attack_data;
    Create_element(&Attack_Item, &attack_element);
    //device
    static uint8_t Airpods = false;
    static ui_data_t Airpods_data;
    Airpods_data.ptr = &Airpods;
    Airpods_data.function =  device_choose0;
    Airpods_data.dataType = UI_DATA_SWITCH;
    Airpods_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Airpods_element;
    Airpods_element.data = &Airpods_data;
    Create_element(&Airpods_Item, &Airpods_element);

    static uint8_t Airpods_Pro = false;
    static ui_data_t Airpods_Pro_data;
    Airpods_Pro_data.ptr = &Airpods_Pro;
    Airpods_Pro_data.function =  device_choose1;
    Airpods_Pro_data.dataType = UI_DATA_SWITCH;
    Airpods_Pro_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Airpods_Pro_element;
    Airpods_Pro_element.data = &Airpods_Pro_data;
    Create_element(&Airpods_Pro_Item, &Airpods_Pro_element);

    static uint8_t Airpods_Max = false;
    static ui_data_t Airpods_Max_data;
    Airpods_Max_data.ptr = &Airpods_Max;
    Airpods_Max_data.function =  device_choose2;
    Airpods_Max_data.dataType = UI_DATA_SWITCH;
    Airpods_Max_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Airpods_Max_element;
    Airpods_Max_element.data = &Airpods_Max_data;
    Create_element(&Airpods_Max_Item, &Airpods_Max_element);

    static uint8_t Airpods_Gen_3 = false;
    static ui_data_t Airpods_Gen_3_data;
    Airpods_Gen_3_data.ptr = &Airpods_Gen_3;
    Airpods_Gen_3_data.function =  device_choose3;
    Airpods_Gen_3_data.dataType = UI_DATA_SWITCH;
    Airpods_Gen_3_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Airpods_Gen_3_element;
    Airpods_Gen_3_element.data = &Airpods_Gen_3_data;
    Create_element(&Airpods_Gen_3_Item, &Airpods_Gen_3_element);

    static uint8_t Airpods_Pro_Gen_2 = false;
    static ui_data_t Airpods_Pro_Gen_2_data;
    Airpods_Pro_Gen_2_data.ptr = &Airpods_Pro_Gen_2;
    Airpods_Pro_Gen_2_data.function =  device_choose4;
    Airpods_Pro_Gen_2_data.dataType = UI_DATA_SWITCH;
    Airpods_Pro_Gen_2_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Airpods_Pro_Gen_2_element;
    Airpods_Pro_Gen_2_element.data = &Airpods_Pro_Gen_2_data;
    Create_element(&Airpods_Pro_Gen_2_Item, &Airpods_Pro_Gen_2_element);

    static uint8_t Power_Beats = false;
    static ui_data_t Power_Beats_data;
    Power_Beats_data.ptr = &Power_Beats;
    Power_Beats_data.function =  device_choose5;
    Power_Beats_data.dataType = UI_DATA_SWITCH;
    Power_Beats_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Power_Beats_element;
    Power_Beats_element.data = &Power_Beats_data;
    Create_element(&Power_Beats_Item, &Power_Beats_element);

    static uint8_t Power_Beats_Pro = false;
    static ui_data_t Power_Beats_Pro_data;
    Power_Beats_Pro_data.ptr = &Power_Beats_Pro;
    Power_Beats_Pro_data.function =  device_choose6;
    Power_Beats_Pro_data.dataType = UI_DATA_SWITCH;
    Power_Beats_Pro_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Power_Beats_Pro_element;
    Power_Beats_Pro_element.data = &Power_Beats_Pro_data;
    Create_element(&Power_Beats_Pro_Item, &Power_Beats_Pro_element);

    static uint8_t Beats_Solo_Pro = false;
    static ui_data_t Beats_Solo_Pro_data;
    Beats_Solo_Pro_data.ptr = &Beats_Solo_Pro;
    Beats_Solo_Pro_data.function =  device_choose7;
    Beats_Solo_Pro_data.dataType = UI_DATA_SWITCH;
    Beats_Solo_Pro_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Beats_Solo_Pro_element;
    Beats_Solo_Pro_element.data = &Beats_Solo_Pro_data;
    Create_element(&Beats_Solo_Pro_Item, &Beats_Solo_Pro_element);
    
    static uint8_t Beats_Studio_Buds = false;
    static ui_data_t Beats_Studio_Buds_data;
    Beats_Studio_Buds_data.ptr = &Beats_Studio_Buds;
    Beats_Studio_Buds_data.function =  device_choose8;
    Beats_Studio_Buds_data.dataType = UI_DATA_SWITCH;
    Beats_Studio_Buds_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Beats_Studio_Buds_element;
    Beats_Studio_Buds_element.data = &Beats_Studio_Buds_data;
    Create_element(&Beats_Studio_Buds_Item, &Beats_Studio_Buds_element);

    static uint8_t Beats_Flex = false;
    static ui_data_t Beats_Flex_data;
    Beats_Flex_data.ptr = &Beats_Flex;
    Beats_Flex_data.function =  device_choose9;
    Beats_Flex_data.dataType = UI_DATA_SWITCH;
    Beats_Flex_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Beats_Flex_element;
    Beats_Flex_element.data = &Beats_Flex_data;
    Create_element(&Beats_Flex_Item, &Beats_Flex_element);

    static uint8_t Beats_X = false;
    static ui_data_t Beats_X_data;
    Beats_X_data.ptr = &Beats_X;
    Beats_X_data.function =  device_choose10;
    Beats_X_data.dataType = UI_DATA_SWITCH;
    Beats_X_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Beats_X_element;
    Beats_X_element.data = &Beats_X_data;   
    Create_element(&Beats_X_Item, &Beats_X_element);

    static uint8_t Beats_Solo_3 = false;
    static ui_data_t Beats_Solo_3_data;
    Beats_Solo_3_data.ptr = &Beats_Solo_3;
    Beats_Solo_3_data.function =  device_choose11;
    Beats_Solo_3_data.dataType = UI_DATA_SWITCH;
    Beats_Solo_3_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Beats_Solo_3_element;
    Beats_Solo_3_element.data = &Beats_Solo_3_data;
    Create_element(&Beats_Solo_3_Item, &Beats_Solo_3_element);

    static uint8_t Beats_Studio_3 = false;
    static ui_data_t Beats_Studio_3_data;
    Beats_Studio_3_data.ptr = &Beats_Studio_3;
    Beats_Studio_3_data.function =  device_choose12;
    Beats_Studio_3_data.dataType = UI_DATA_SWITCH;
    Beats_Studio_3_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Beats_Studio_3_element;
    Beats_Studio_3_element.data = &Beats_Studio_3_data;
    Create_element(&Beats_Studio_3_Item, &Beats_Studio_3_element);

}

/**
 * 在此建立所需显示或更改的文本
 * 无参数
 * 无返回值
 */                  
extern char wifiInfo[1000];             
void Create_Text(ui_t *ui)
{
    static ui_text_t github_text;
    github_text.font = UI_FONT;
    github_text.fontHight = UI_FONT_HIGHT;
    github_text.fontWidth = UI_FONT_WIDTH;
    github_text.ptr = VERSION_PROJECT_LINK;
    static ui_element_t github_element;
    github_element.text = &github_text;
    Create_element(&Github_Item, &github_element);

    static ui_text_t bilibili_text;
    bilibili_text.font = UI_FONT;
    bilibili_text.fontHight = UI_FONT_HIGHT;
    bilibili_text.fontWidth = UI_FONT_WIDTH;
    bilibili_text.ptr = "This is a testing program";
    static ui_element_t bilibili_element;
    bilibili_element.text = &bilibili_text;
    Create_element(&Bilibili_Item, &bilibili_element);

    static ui_text_t wifi_text;
    wifi_text.font = UI_FONT;
    wifi_text.fontHight = UI_FONT_HIGHT;
    wifi_text.fontWidth = UI_FONT_WIDTH;
    wifi_text.ptr = wifiInfo;
    static ui_element_t wifi_element;
    wifi_element.text = &wifi_text;
    Create_element(&wifi_Item, &wifi_element);
}

/*
 * 菜单构建函数
 * 该函数不接受参数，也不返回任何值。
 * 功能：静态地构建一个菜单系统。
 */

void Create_MenuTree(ui_t *ui)
{
    AddPage("[HomePage]", &Home_Page, UI_PAGE_ICON);
        // AddItem("[HomePage]", UI_ITEM_ONCE_FUNCTION, logo_allArray[0], &HomeHead_Item, &Home_Page, NULL, Show_StarAnimation);
        

        //
        AddItem("-Apple Juice", UI_ITEM_PARENTS, logo_allArray[4], &HomeHead_Item, &Home_Page, &Apple_juice_Page, NULL);
            AddPage("[System]", &Apple_juice_Page, UI_PAGE_TEXT);
                AddItem("[System]", UI_ITEM_RETURN, NULL, &AppleJuiceHead_Item, &Apple_juice_Page, &Home_Page, NULL);
                AddItem("-attack",UI_ITEM_DATA, NULL, &Attack_Item, &Apple_juice_Page, NULL, NULL);
                // AddItem(" -Menu Color", UI_ITEM_DATA, NULL, &MenuColor_Item, &Apple_juice_Page, NULL, NULL);   
                // AddItem(" -Cursor Ani", UI_ITEM_DATA, NULL, &CursorAni_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Airpods",UI_ITEM_DATA, NULL, &Airpods_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Airpods Pro",UI_ITEM_DATA, NULL, &Airpods_Pro_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Airpods Max",UI_ITEM_DATA, NULL, &Airpods_Max_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Airpods Gen 3",UI_ITEM_DATA, NULL, &Airpods_Gen_3_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Airpods Pro Gen 2",UI_ITEM_DATA, NULL, &Airpods_Pro_Gen_2_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Power Beats",UI_ITEM_DATA, NULL, &Power_Beats_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Power Beats Pro",UI_ITEM_DATA, NULL, &Power_Beats_Pro_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Beats Solo Pro",UI_ITEM_DATA, NULL, &Beats_Solo_Pro_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Beats Studio Buds",UI_ITEM_DATA, NULL, &Beats_Studio_Buds_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Beats Flex",UI_ITEM_DATA, NULL, &Beats_Flex_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Beats X",UI_ITEM_DATA, NULL, &Beats_X_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Beats Solo 3",UI_ITEM_DATA, NULL, &Beats_Solo_3_Item, &Apple_juice_Page, NULL, NULL);
                AddItem("-Beats Studio 3",UI_ITEM_DATA, NULL, &Beats_Studio_3_Item, &Apple_juice_Page, NULL, NULL);
        //

        AddItem(" +System", UI_ITEM_PARENTS, logo_allArray[1], &System_Item, &Home_Page, &System_Page, NULL);
            AddPage("[System]", &System_Page, UI_PAGE_TEXT);
                AddItem("[System]", UI_ITEM_RETURN, NULL, &SystemHead_Item, &System_Page, &Home_Page, NULL);
                AddItem(" -Contrast",    UI_ITEM_DATA, NULL, &Contrast_Item, &System_Page, NULL, NULL);
                AddItem(" -Power off", UI_ITEM_DATA, NULL, &Power_Item, &System_Page, NULL, NULL);   
                AddItem(" -This is a testing program", UI_ITEM_DATA, NULL, &Test_Item, &System_Page, NULL, NULL);
                AddItem(" -Menu Color", UI_ITEM_DATA, NULL, &MenuColor_Item, &System_Page, NULL, NULL);   
                AddItem(" -Cursor Ani", UI_ITEM_DATA, NULL, &CursorAni_Item, &System_Page, NULL, NULL);
        // AddItem(" -Image", UI_ITEM_LOOP_FUNCTION, logo_allArray[2], &Image_Item, &Home_Page, NULL, Show_Logo);
         AddItem(" -wifi scan", UI_ITEM_WORD, logo_allArray[3], &wifi_Item, &Home_Page, NULL, NULL);

        // AddItem(" -This is a testing program", UI_ITEM_WORD, logo_allArray[4], &Bilibili_Item, &Home_Page, NULL, NULL);
        // AddItem(" -Version", UI_ITEM_ONCE_FUNCTION, logo_allArray[5], &Version_Item, &Home_Page, NULL, Show_Version);
        AddItem(" -Wave", UI_ITEM_WAVE, logo_allArray[6], &Wave_Item, &Home_Page, NULL, NULL);
        AddItem("-Animation", UI_ITEM_ONCE_FUNCTION, logo_allArray[0], &Animation_Item, &Home_Page, NULL, Draw_Home);
}


void MiaoUi_Setup(ui_t *ui)
{
    Create_UI(ui, &HomeHead_Item); // 创建UI, 必须给定一个头项目
    // Draw_Home(ui);
    //原初始化界面
}

//

//
