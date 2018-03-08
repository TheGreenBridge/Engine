#pragma once


namespace engine {	namespace animation {
	// forward declaration
	struct AnimationClip;
	struct RenderableSkin;

	bool loadAnimation(const char* path, AnimationClip *clipStorage, RenderableSkin *mesh);
}}
