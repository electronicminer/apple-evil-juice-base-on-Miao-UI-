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
#ifndef __HAL_BUTTON_H__
#define __HAL_BUTTON_H__


#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
void key_init(void);
uint8_t touch_button_scan(void);
uint8_t touch_button_scan_2(void);
uint8_t key_scan(void);

#ifdef __cplusplus
}
#endif

#endif
