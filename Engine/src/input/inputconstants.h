#pragma once

#include <common/types.h>

///<summary>
///	defines all actions, states and ranges
/// IS GAME DEPENDEND
///</summary>

enum class STATE : U8 {
	player_up,
	player_down,
	player_left,
	player_right,


	// DEBUG
	camera_up,
	camera_down,
	camera_right,
	camera_left,
	camera_forward,
	camera_backward,
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