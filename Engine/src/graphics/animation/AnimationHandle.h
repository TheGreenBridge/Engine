#pragma once

#include <common/types.h>

/*
Represents a handle to the AnimationManager.
It holds: 
# the global Time of the Component, since it was created.
# the local Time of the current Clip
# the playbackRate - how fast the clip have to be played
# ID to the current Clip
# ID to the next Clip
# boolean, to start or stop the animation
*/
namespace engine {	namespace animation {
	struct AnimationHandle {
		F32 globalTime;	
		F32 localTime;	
		F32 playbackRate;	
		U32 currentClip;
		U32 nextClip;
		bool isAnimating;
	};
}}
