#pragma once

#include <common/types.h>

///<summary>
///	defines all actions, states and ranges
/// IS GAME DEPENDEND
///</summary>

enum class STATE : U8 {
	player_up = 0,
	player_down = 1,
	player_left = 2,
	player_right = 3,


	// DEBUG
	camera_up = 4,
	camera_down = 5,
	camera_right = 6,
	camera_left = 7,
	camera_forward = 8,
	camera_backward = 9,
};

enum class ACTION : U8 {
	change_camera_debug,
	change_camera_3rdperson,
	test,
	_,
};

enum class RANGE : U8 {
	camera_x,
	camera_y,
};