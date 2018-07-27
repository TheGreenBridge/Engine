#pragma once

#include "ISystem.h"
#include "../graphics/animation/skinning/RenderableSkin.h"
#include "../math/mat4.h"

namespace engine {
	// forward declaration
	namespace animation {
		struct AnimationClip;
		struct AnimationSample;
		struct Joint;
		struct Skeleton;
		struct JointPose;
		struct AnimationHandle;
		struct RenderableSkin;
		
		struct Animatable;
	}
	
	struct Event;
	
	using namespace engine::animation;

	class AnimationManager : public ISystem{
	private:

		

		// Data
		Animatable* m_aComponents;
		AnimationHandle *m_aHandles;
		AnimationClip *m_aClips;
		AnimationSample *m_aSamples;
		JointPose *m_aJointPoses;

		Skeleton *m_aSkeletons;
		Joint *m_aJoints;
		
		mat4 *m_aBones;

		RenderableSkin *m_aRenderSkin;


		//Sections
		//Section sHandles;
		
		unsigned int numClips = 0, numSkeletons = 0, numHandles = 0,
			numJoints = 0, numBones = 0, numComponents = 0, 
			numSamples = 0, numJointPoses = 0, numRenderSkins = 0;
		//Animatable *cAnimateable;
		//AnimationHandle *cHandles;
		//AnimationClip *cClips;


	public:
	
		AnimationManager();
		~AnimationManager();	

		// System specifics
		void free(void *location, size_t size);
		void logStates() const;

		void loadAnimations();

		AnimationHandle *getHandle();
		RenderableSkin *getRenderable();
		mat4 *getBones();
		
		void requestNewComponent(Animatable *&component);

		// System Interface
		void update(const float dTime);
		void onEvent(Event *e);
		void startUp();
		void shutDown();
	};
}
