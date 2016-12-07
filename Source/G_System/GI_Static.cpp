#include "../../Interface/G_System/GKeyDefines.h"
#include <map>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#elif __APPPLE__

#endif

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define TURNON_BIT(var,pos) ((var) |=  (1<<(pos)))
#define TURNOFF_BIT(var,pos) ((var) &= ~(1<<(pos)))
#define TOGGLE_BIT(var, pos) (CHECK_BIT(var, pos) ? (TURNOFF_BIT(var,pos)) : (TURNON_BIT(var,pos)))

static const unsigned int Keycodes[][2] = {
	//Windows Scancodes		//Linux Other
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, // 0
	{ G_KEY_ESCAPE,			G_KEY_UNKNOWN }, // 1
	{ G_KEY_1,				G_KEY_UNKNOWN }, // 2
	{ G_KEY_2,				G_KEY_UNKNOWN }, // 3
	{ G_KEY_3,				G_KEY_UNKNOWN }, // 4
	{ G_KEY_4,				G_KEY_UNKNOWN }, // 5
	{ G_KEY_5,				G_KEY_UNKNOWN }, // 6
	{ G_KEY_6,				G_KEY_UNKNOWN }, // 7
	{ G_KEY_7,				G_KEY_UNKNOWN }, // 8
	{ G_KEY_8,				G_KEY_ESCAPE }, // 9
	{ G_KEY_9,				G_KEY_1 }, // 10
	{ G_KEY_0,				G_KEY_2 }, // 11
	{ G_KEY_MINUS,			G_KEY_3 }, // 12
	{ G_KEY_EQUALS,			G_KEY_4 }, // 13
	{ G_KEY_BACKSPACE,		G_KEY_5 }, // 14
	{ G_KEY_TAB,			G_KEY_6 }, // 15
	{ G_KEY_Q,				G_KEY_7 }, // 16
	{ G_KEY_W,				G_KEY_8 }, // 17
	{ G_KEY_E,				G_KEY_9 }, // 18
	{ G_KEY_R,				G_KEY_0 }, // 19
	{ G_KEY_T,				G_KEY_MINUS }, // 20
	{ G_KEY_Y,				G_KEY_EQUALS }, // 21
	{ G_KEY_U,				G_KEY_BACKSPACE }, // 22
	{ G_KEY_I,				G_KEY_TAB }, // 23
	{ G_KEY_O,				G_KEY_Q }, // 24
	{ G_KEY_P,				G_KEY_W }, // 25
	{ G_KEY_BRACKET_OPEN,	G_KEY_E }, // 26
	{ G_KEY_BRACKET_CLOSE,	G_KEY_R }, // 27
	{ G_KEY_ENTER,			G_KEY_T }, // 28
	{ G_KEY_CONTROL,		G_KEY_Y }, // 29
	{ G_KEY_A,				G_KEY_U }, // 30
	{ G_KEY_S,				G_KEY_I }, // 31
	{ G_KEY_D,				G_KEY_O }, // 32
	{ G_KEY_F,				G_KEY_P }, // 33
	{ G_KEY_G,				G_KEY_BRACKET_OPEN  }, // 34
	{ G_KEY_H,				G_KEY_BRACKET_CLOSE }, // 35
	{ G_KEY_J,				G_KEY_ENTER }, // 36
	{ G_KEY_K,				G_KEY_CONTROL }, // 37
	{ G_KEY_L,				G_KEY_A }, // 38
	{ G_KEY_COLON,			G_KEY_S }, // 39
	{ G_KEY_QUOTE,			G_KEY_D }, // 40
	{ G_KEY_TILDE,			G_KEY_F }, // 41
	{ G_KEY_LEFTSHIFT,		G_KEY_G }, // 42
	{ G_KEY_BACKSLASH,		G_KEY_H }, // 43
	{ G_KEY_Z,				G_KEY_J }, // 44
	{ G_KEY_X,				G_KEY_K }, // 45
	{ G_KEY_C,				G_KEY_L }, // 46
	{ G_KEY_V,				G_KEY_COLON }, // 47
	{ G_KEY_B,				G_KEY_QUOTE }, // 48
	{ G_KEY_N,				G_KEY_TILDE }, // 49
	{ G_KEY_M,				G_KEY_LEFTSHIFT }, // 50
	{ G_KEY_COMMA,			G_KEY_BACKSLASH }, // 51
	{ G_KEY_PERIOD,			G_KEY_Z }, // 52
	{ G_KEY_FOWARDSLASH,	G_KEY_X }, // 53
	{ G_KEY_RIGHTSHIFT,		G_KEY_C }, // 54
	{ G_KEY_PRINTSCREEN,	G_KEY_V }, // 55
	{ G_KEY_LEFTALT,		G_KEY_B }, // 56
	{ G_KEY_SPACE,			G_KEY_N }, // 57
	{ G_KEY_CAPSLOCK,		G_KEY_M }, // 58
	{ G_KEY_F1,				G_KEY_COMMA }, // 59
	{ G_KEY_F2,				G_KEY_PERIOD }, // 60
	{ G_KEY_F3,				G_KEY_FOWARDSLASH }, // 61
	{ G_KEY_F4,				G_KEY_RIGHTSHIFT }, // 62
	{ G_KEY_F5,				G_KEY_MULTIPLY }, // 63
	{ G_KEY_F6,				G_KEY_LEFTALT }, // 64
	{ G_KEY_F7,				G_KEY_SPACE }, // 65
	{ G_KEY_F8,				G_KEY_UNKNOWN }, // 66
	{ G_KEY_F9,				G_KEY_F1 }, // 67
	{ G_KEY_F10,			G_KEY_F2 }, // 68
	{ G_KEY_NUMLOCK,		G_KEY_F3 }, // 69
	{ G_KEY_SCROLL_LOCK,	G_KEY_F4 }, // 70
	{ G_KEY_HOME,			G_KEY_F5 }, // 71
	{ G_KEY_UP,				G_KEY_F6 }, // 72
	{ G_KEY_PAGEUP,			G_KEY_F7 }, // 73
	{ G_KEY_NUMPAD_MINUS,	G_KEY_F8 }, // 74
	{ G_KEY_LEFT,			G_KEY_F9 }, // 75
	{ G_KEY_CENTER,			G_KEY_F10 }, // 76
	{ G_KEY_RIGHT,			G_KEY_NUMLOCK }, // 77
	{ G_KEY_NUMPAD_PLUS,	G_KEY_UNKNOWN }, // 78
	{ G_KEY_END,			G_KEY_HOME }, // 79
	{ G_KEY_DOWN,			G_KEY_UP }, // 80
	{ G_KEY_PAGEDOWN,		G_KEY_PAGEUP }, // 81
	{ G_KEY_INSERT,			G_KEY_MINUS }, // 82
	{ G_KEY_DELETE,			G_KEY_LEFT }, // 83
	{ G_KEY_UNKNOWN,		G_KEY_CENTER }, // 84
	{ G_KEY_UNKNOWN,		G_KEY_RIGHT }, // 85
	{ G_KEY_UNKNOWN,		G_KEY_ADD }, // 86
	{ G_KEY_F12,			G_KEY_END }, //87
	{ G_KEY_F12,			G_KEY_DOWN }, //88
	{ G_KEY_UNKNOWN,		G_KEY_PAGEDOWN }, //89
	{ G_KEY_UNKNOWN,		G_KEY_INSERT }, //90
	{ G_KEY_UNKNOWN,		G_KEY_PERIOD }, //91
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //92
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //93
	{ G_KEY_UNKNOWN,		G_KEY_F11 }, //94
	{ G_KEY_UNKNOWN,		G_KEY_F12 }, //95
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //96
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //97
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //98
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //99
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //100
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //101
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //102
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //103
	{ G_KEY_UNKNOWN,		G_KEY_ENTER }, //104
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //105
	{ G_KEY_UNKNOWN,		G_KEY_DIVIDE }, //106
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //107
	{ G_KEY_UNKNOWN,		G_KEY_RIGHTALT }, //108
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //109
	{ G_KEY_UNKNOWN,		G_KEY_HOME }, //110
	{ G_KEY_UNKNOWN,		G_KEY_UP }, //111
	{ G_KEY_UNKNOWN,		G_KEY_PAGEUP }, //112
	{ G_KEY_UNKNOWN,		G_KEY_LEFT }, //113
	{ G_KEY_UNKNOWN,		G_KEY_RIGHT }, //114
	{ G_KEY_UNKNOWN,		G_KEY_END }, //115
	{ G_KEY_UNKNOWN,		G_KEY_DOWN }, //116
	{ G_KEY_UNKNOWN,		G_KEY_PAGEDOWN }, //117
	{ G_KEY_UNKNOWN,		G_KEY_SCROLL_LOCK }, //118
	{ G_KEY_UNKNOWN,		G_KEY_DELETE }, //119
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //120
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //121
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //122
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //123
	{ G_KEY_UNKNOWN,		G_KEY_UNKNOWN }, //124
};


