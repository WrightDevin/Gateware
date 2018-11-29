#ifndef GCONTROLLERINPUTDEFINES_H
#define GCONTROLLERINPUTDEFINES_H

/*!
File: GControllerCodes.h
Purpose: The Gateware controller input codes
Author: Devin Wright
Contributors: N/A
Last Modified: 11/29/2018
Copyright: 7thGate Software LLC.
License: MIT
*/

// Example input code: 0XFF01112 FF(Reserved for future use) 01(controler id) 1(Axis || Button) 12(input code)

// Controller IDs
#define G_GENERAL_CONTROLLER			0x00000
#define G_XBOX_CONTROLLER				0x01000
#define G_PS4_CONTROLLER				0x02000

// General Controller
#define G_GENERAL_SOUTH_BTN				((G_GENERAL_CONTROLLER) | 0xFF00000)
#define G_GENERAL_EAST_BTN				((G_GENERAL_CONTROLLER) | 0xFF00001)
#define G_GENERAL_NORTH_BTN				((G_GENERAL_CONTROLLER) | 0xFF00002)
#define G_GENERAL_WEST_BTN				((G_GENERAL_CONTROLLER) | 0xFF00003)
#define G_GENERAL_LEFT_SHOULDER_BTN		((G_GENERAL_CONTROLLER) | 0xFF00004)
#define G_GENERAL_RIGHT_SHOULDER_BTN    ((G_GENERAL_CONTROLLER) | 0xFF00005)
#define G_GENERAL_LEFT_TRIGGER_AXIS	    ((G_GENERAL_CONTROLLER) | 0xFF00106)
#define G_GENERAL_RIGHT_TRIGGER_AXIS    ((G_GENERAL_CONTROLLER) | 0xFF00107)
#define G_GENERAL_DPAD_LEFT_BTN			((G_GENERAL_CONTROLLER) | 0xFF00008)
#define G_GENERAL_DPAD_RIGHT_BTN		((G_GENERAL_CONTROLLER) | 0xFF00009)
#define G_GENERAL_DPAD_UP_BTN			((G_GENERAL_CONTROLLER) | 0xFF0000A)
#define G_GENERAL_DPAD_DOWN_BTN			((G_GENERAL_CONTROLLER) | 0xFF0000B)
#define G_GENERAL_LEFT_THUMB_BTN		((G_GENERAL_CONTROLLER) | 0xFF0000C)
#define G_GENERAL_RIGHT_THUMB_BTN		((G_GENERAL_CONTROLLER) | 0xFF0000D)
#define G_GENERAL_START_BTN				((G_GENERAL_CONTROLLER) | 0xFF0000E)
#define G_GENERAL_SELECT_BTN			((G_GENERAL_CONTROLLER) | 0xFF0000F)
#define G_GENERAL_LX_AXIS				((G_GENERAL_CONTROLLER) | 0xFF00110)
#define G_GENERAL_LY_AXIS				((G_GENERAL_CONTROLLER) | 0xFF00111)
#define G_GENERAL_RX_AXIS				((G_GENERAL_CONTROLLER) | 0xFF00112)
#define G_GENERAL_RY_AXIS				((G_GENERAL_CONTROLLER) | 0xFF00113)

// Xbox Controller
#define G_XBOX_A_BTN					((G_XBOX_CONTROLLER) | 0xFF00000)
#define G_XBOX_B_BTN					((G_XBOX_CONTROLLER) | 0xFF00001)
#define G_XBOX_Y_BTN					((G_XBOX_CONTROLLER) | 0xFF00002)
#define G_XBOX_X_BTN					((G_XBOX_CONTROLLER) | 0xFF00003)
#define G_XBOX_LEFT_SHOULDER_BTN		((G_XBOX_CONTROLLER) | 0xFF00004)
#define G_XBOX_RIGHT_SHOULDER_BTN		((G_XBOX_CONTROLLER) | 0xFF00005)
#define G_XBOX_LEFT_TRIGGER_AXIS		((G_XBOX_CONTROLLER) | 0xFF00106)
#define G_XBOX_RIGHT_TRIGGER_AXIS		((G_XBOX_CONTROLLER) | 0xFF00107)
#define G_XBOX_DPAD_LEFT_BTN			((G_XBOX_CONTROLLER) | 0xFF00008)
#define G_XBOX_DPAD_RIGHT_BTN			((G_XBOX_CONTROLLER) | 0xFF00009)
#define G_XBOX_DPAD_UP_BTN				((G_XBOX_CONTROLLER) | 0xFF0000A)
#define G_XBOX_DPAD_DOWN_BTN			((G_XBOX_CONTROLLER) | 0xFF0000B)
#define G_XBOX_LEFT_THUMB_BTN			((G_XBOX_CONTROLLER) | 0xFF0000C)
#define G_XBOX_RIGHT_THUMB_BTN			((G_XBOX_CONTROLLER) | 0xFF0000D)
#define G_XBOX_START_BTN				((G_XBOX_CONTROLLER) | 0xFF0000E)
#define G_XBOX_BACK_BTN					((G_XBOX_CONTROLLER) | 0xFF0000F)
#define G_XBOX_LX_AXIS					((G_XBOX_CONTROLLER) | 0xFF00110)
#define G_XBOX_LY_AXIS					((G_XBOX_CONTROLLER) | 0xFF00111)
#define G_XBOX_RX_AXIS					((G_XBOX_CONTROLLER) | 0xFF00112)
#define G_XBOX_RY_AXIS					((G_XBOX_CONTROLLER) | 0xFF00113)

// PS4 Controller
#define G_PS4_X_BTN						((G_PS4_CONTROLLER) | 0xFF00000) 
#define G_PS4_CIRCLE_BTN				((G_PS4_CONTROLLER) | 0xFF00001)
#define G_PS4_TRIANGLE_BTN				((G_PS4_CONTROLLER) | 0xFF00002)
#define G_PS4_SQUARE_BTN				((G_PS4_CONTROLLER) | 0xFF00003)
#define G_PS4_LEFT_SHOULDER_BTN			((G_PS4_CONTROLLER) | 0xFF00004)
#define G_PS4_RIGHT_SHOULDER_BTN	    ((G_PS4_CONTROLLER) | 0xFF00005)
#define G_PS4_LEFT_TRIGGER_AXIS			((G_PS4_CONTROLLER) | 0xFF00106)
#define G_PS4_RIGHT_TRIGGER_AXIS		((G_PS4_CONTROLLER) | 0xFF00107)
#define G_PS4_DPAD_LEFT_BTN				((G_PS4_CONTROLLER) | 0xFF00008)
#define G_PS4_DPAD_RIGHT_BTN			((G_PS4_CONTROLLER) | 0xFF00009)
#define G_PS4_DPAD_UP_BTN				((G_PS4_CONTROLLER) | 0xFF0000A)
#define G_PS4_DPAD_DOWN_BTN				((G_PS4_CONTROLLER) | 0xFF0000B)
#define G_PS4_LEFT_THUMB_BTN			((G_PS4_CONTROLLER) | 0xFF0000C)
#define G_PS4_RIGHT_THUMB_BTN			((G_PS4_CONTROLLER) | 0xFF0000D)
#define G_PS4_START_BTN					((G_PS4_CONTROLLER) | 0xFF0000E)
#define G_PS4_BACK_BTN					((G_PS4_CONTROLLER) | 0xFF0000F)
#define G_PS4_LX_AXIS					((G_PS4_CONTROLLER) | 0xFF00110)
#define G_PS4_LY_AXIS					((G_PS4_CONTROLLER) | 0xFF00111)
#define G_PS4_RX_AXIS					((G_PS4_CONTROLLER) | 0xFF00112)
#define G_PS4_RY_AXIS					((G_PS4_CONTROLLER) | 0xFF00113)

#endif 