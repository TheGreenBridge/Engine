#pragma once

#include <common/types.h>

///<summary>
/// Defines all types of raw inputs
///</summary>

enum class INPUTMETA : U8{
	NO_CODE,
	key_pressed,
	key_released,
};

enum class INPUTBUTTON : U32 {
	NO_CODE,
	l_mouse_button = 0x01,
	r_mouse_button = 0x02,

	enter = 0x0D,
	shift = 0x10,
	control = 0x11,
	alt = 0x12,
	pause = 0x13,
	esc = 0x18,
	space = 0x20,
	arrow_left = 0x107, // OFFICIAL 0x25
	arrow_up = 0x109, // OFFICIAL 0x26
	arrow_right = 0x106, // OFFICIAL 0x27
	arrow_down = 0x108, // OFFICIAL 0x28

	key_0 = 0x30,
	key_1 = 0x31,
	key_2 = 0x32,
	key_3 = 0x33,
	key_4 = 0x34,
	key_5 = 0x35,
	key_6 = 0x36,
	key_7 = 0x37,
	key_8 = 0x38,
	key_9 = 0x39,

	a = 0x41,
	b = 0x42,
	c = 0x43,
	d = 0x44,
	e = 0x45,
	f = 0x46,
	g = 0x47,
	h = 0x48,
	i = 0x49,
	j = 0x4A,
	k = 0x4B,
	l = 0x4C,
	m = 0x4D,
	n = 0x4E,
	o = 0x4F,
	p = 0x50,
	q = 0x51,
	r = 0x52,
	s = 0x53,
	t = 0x54,
	u = 0x55,
	v = 0x56,
	w = 0x57,
	x = 0x58,
	y = 0x59,
	z = 0x5A,

	num_key_0 = 0x60,
	num_key_1 = 0x61,
	num_key_2 = 0x62,
	num_key_3 = 0x63,
	num_key_4 = 0x64,
	num_key_5 = 0x65,
	num_key_6 = 0x66,
	num_key_7 = 0x67,
	num_key_8 = 0x68,
	num_key_9 = 0x69,

	multiply = 0x6A,
	add = 0x6B,

	subtract = 0x6D,
	divide = 0x6F,

	// temporary test
	new_SDL_W = 0x77,
	SDL_DOWN = 1073741905,
	SDL_UP = 1073741906,
	SDL_LEFT = 1073741904,
	SDL_RIGHT = 1073741903,
};

enum class INPUTAXIS : U8 {
	NO_CODE,
	mouse_x,
	mouse_y,
};



enum class RAWINPUT : U8 {
	// ####
	// BUTTONS 
	// ####

	// BUTTONS : KEYBOARD
	// alphabet
	input_key_a,
	input_key_b,
	input_key_c,
	input_key_d,
	input_key_e,
	input_key_f,
	input_key_g,
	input_key_h,
	input_key_i,
	input_key_j,
	input_key_k,
	input_key_l,
	input_key_m,
	input_key_n,
	input_key_o,
	input_key_p,
	input_key_r,
	input_key_s,
	input_key_t,
	input_key_u,
	input_key_v,
	input_key_w,
	input_key_x,
	input_key_y,
	input_key_z,
	
	// special keys 
	input_key_space,
	input_key_shift,
	input_key_control,
	input_key_enter,
	input_key_return,
	input_key_escape,

	input_key_f1,
	input_key_f2,
	input_key_f3,
	input_key_f4,
	input_key_f5,
	input_key_f6,
	input_key_f7,
	input_key_f8,
	input_key_f9,
	input_key_f10,
	input_key_f11,
	input_key_f12,
	
	input_key_up,
	input_key_down,
	input_key_left,
	input_key_right,

	// BUTTONS: CONTROLLER - XBOX
	/*
		ls=left stick ; rs = rigt stick ; lt = left trigger ; rt = right trigger ; lb = left bumper ;
		rb = right bumper ; direct = directional
	*/
	input_xbox_a,
	input_xbox_b,
	input_xbox_x,
	input_xbox_y,
	input_xbox_start,
	input_xbox_back,
	input_xbox_up,
	input_xbox_down,
	input_xbox_left,
	input_xbox_right,
	input_xbox_ls_down,
	input_xbox_rs_down,
	input_xbox_lb,
	input_xbox_rb,

	
	// ####
	// AXES
	// ####
	
	// AXES : KEYBOARD
	input_mouse_x = 100,
	input_mousey,

	// AXES : TOUCH
	input_touch_x ,
	input_touch_y,

	// AXES : CONTROLLER - XBOX
	/* 
		ls=left stick ; rs = rigt stick ; lt = left trigger ; rt = right trigger ; lb = left bumper ; 
		rb = right bumper ; direct = directional 
	*/
	input_xbox_ls_x,
	input_xbox_ls_y,
	input_xbox_rs_x,
	input_xbox_rs_y,

	input_xbox_lt,
	input_xbox_rt,
};

// Link to the list of virtual keys
/* https://msdn.microsoft.com/de-de/library/windows/desktop/dd375731(v=vs.85).aspx */

enum class RAWINPUT_WIN : U8 {
	l_mouse_button = 0x01,
	r_mouse_button = 0x02,

	enter = 0x0D,
	shift = 0x10,
	control = 0x11,
	alt = 0x12,
	pause = 0x13,
	esc = 0x18,
	space = 0x20,
	arrow_left = 0x25,
	arrow_up = 0x26,
	arrow_right = 0x27,
	arrow_down = 0x28,

	key_0 = 0x30,
	key_1 = 0x31,
	key_2 = 0x32,
	key_3 = 0x33,
	key_4 = 0x34,
	key_5 = 0x35,
	key_6 = 0x36,
	key_7 = 0x37,
	key_8 = 0x38,
	key_9 = 0x39,

	a = 0x41,
	b = 0x42,
	c = 0x43,
	d = 0x44,
	e = 0x45,
	f = 0x46,
	g = 0x47,
	h = 0x48,
	i = 0x49,
	j = 0x4A,
	k = 0x4B,
	l = 0x4C,
	m = 0x4D,
	n = 0x4E,
	o = 0x4F,
	p = 0x50,
	q = 0x51,
	r = 0x52,
	s = 0x53,
	t = 0x54,
	u = 0x55,
	v = 0x56,
	w = 0x57,
	x = 0x58,
	y = 0x59,
	z = 0x5A,

	num_key_0 = 0x60,
	num_key_1 = 0x61,
	num_key_2 = 0x62,
	num_key_3 = 0x63,
	num_key_4 = 0x64,
	num_key_5 = 0x65,
	num_key_6 = 0x66,
	num_key_7 = 0x67,
	num_key_8 = 0x68,
	num_key_9 = 0x69,

	multiply = 0x6A,
	add = 0x6B,

	subtract = 0x6D,
	divide = 0x6F,
};