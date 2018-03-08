#include "../entity/component/Animatable.h"
#include "messageing\Event.h"
#include "AnimationManager.h"

#include "../graphics/animation/skinning/AnimationSample.h"
#include "../graphics/animation/skinning/Joint.h"
#include "../graphics/animation/skinning/JointPose.h"
#include "../graphics/animation/skinning/AnimationClip.h"
#include "../graphics/animation/skinning/AnimationSample.h"
#include "../graphics/animation/skinning/JointPose.h"
#include "../graphics/animation/skinning/skeleton.h"

#include "../graphics/animation/skinning/RenderableSkin.h"

#include "../systems/messageing/types/AnimationEvent.h"

#include "../graphics/animation/AnimationHandle.h"
#include "../graphics/animation/interpolation.h"

#include "../graphics/animation/AnimationLoader.h"
#include <iostream>



#include "../importAnimations.h"

#include "SystemManager.h"

#include "../utils/Log.h"

#define SYSTEM_TITLE "AnimationManager"

// Summary
/// <summary>
/// This system is for animation only
/// </summary>
/// <remarks>
/// Tasks
/// # store Skeletons
/// # store animationdata
/// # play animation
/// </remarks>

/*
THOUGHTS

Skeletons



*/




namespace engine{

	// Storage size in Byte: 10KB
	#define STORAGE_SIZE 1024*10*10
	#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
	//#define ALLOCATE(type)    allocate<TypeAndCount<type>::Type>(arena, TypeAndCount<type>::Count, __FILENAME__, __LINE__)
	
	#define SKELETON_COUNT 2
	#define JOINT_COUNT 30
	#define CLIP_COUNT 5

	#define MAX_SKELETONS 5
	#define MAX_CLIPS 5
	#define MAX_HANDLES 5
	#define MAX_BONES 30*10
	#define MAX_SAMPLES 10 
	#define MAX_JOINTS 30*10
	#define MAX_JOINT_POSES 30*10
	#define MAX_COMPONENTS 5
	#define MAX_RENDERABLES 5

	// STORAGE in Bytes
	#define STORAGE_HANDLES		sizeof(AnimationHandle) * MAX_HANDLES
	#define STORAGE_SKELETONS	sizeof(Skeleton) * MAX_SKELETONS
	#define STORAGE_CLIPS		sizeof(AnimationClip) * MAX_CLIPS		
	#define STORAGE_SAMPLES		sizeof(AnimationSample) * MAX_SAMPLES
	#define STORAGE_JOINTS		sizeof(Joint) * MAX_JOINTS
	#define STORAGE_JOINT_POSES	sizeof(JointPose) * MAX_JOINT_POSES

	#define STORAGE_TOTAL_ANIMATION STORAGE_HANDLES+STORAGE_SKELETONS+STORAGE_CLIPS+STORAGE_SAMPLES+STORAGE_JOINTS+STORAGE_JOINT_POSES

	// Prototypes
	mat4 convertPoseToMat(const JointPose &pose);

	struct Section {
		Section(void *storage, size_t size): start(storage), current(start), 
			limit(static_cast<char *>(storage)+size), size(size){}
		void *start;
		void *current;
		void *limit;
		size_t size;
	};

	struct SectionDynamic {
		void *head;
		void *data;
		void *limit;
	};
	
	AnimationManager::AnimationManager() {
		LOG("AnimationSystem total Size", STORAGE_TOTAL_ANIMATION);
	}

	AnimationManager::~AnimationManager() {

	}

	void AnimationManager::update(const F32 dTime) {	
		for (U32 i = 0; i < numComponents; i++) {
			
			AnimationHandle &handle = *m_aComponents[i].m_pHandle;
			if (handle.isAnimating) {

				U32 &clipID = handle.currentClip;
				AnimationClip *clip = &m_aClips[clipID];
				AnimationSample *&samples = clip->m_aSample;
				Skeleton *&skeleton = m_aClips[clipID].m_pSkeleton;
				Joint *&joint = m_aClips[clipID].m_pSkeleton->m_aJoint;

				// Time Managment
				handle.localTime += dTime*handle.playbackRate;

				U32 fromSample = 0, toSample = 1;
				F32 oldTimeStamp = 0, newTimeStamp = 0;;

				
				if (handle.localTime >= clip->m_duration || handle.localTime <= -clip->m_duration) {
					handle.localTime = 0;
				}

				if (handle.localTime < 0) {
					handle.localTime = 0.02f;
				}

				for (I32 kf = 0; kf < clip->m_frameCount; kf++) {
					if (handle.localTime < clip->m_aSample[kf].m_timeStamp) {
						if (kf != 0) {
							if (kf == clip->m_frameCount-1) {
								fromSample = kf-1;
								toSample = 0;

								oldTimeStamp = clip->m_aSample[kf - 1].m_timeStamp;
								newTimeStamp = clip->m_aSample[kf].m_timeStamp;
							}
							else {
								fromSample = kf - 1;
								toSample = kf;

								oldTimeStamp = clip->m_aSample[kf-1].m_timeStamp;
								newTimeStamp = clip->m_aSample[kf].m_timeStamp;
							}
						}  else {
							handle.isAnimating = false;
						}
						break;
					}
				}

				F32 normalizedLocalTime = (handle.localTime - oldTimeStamp) / (newTimeStamp - oldTimeStamp);

				for (U32 a = 0; a < skeleton->m_jointCount; a++) {
					
					
					
					I32 &parentIndex = joint[a].m_iParent;

					JointPose pose1 = samples[fromSample].m_aJointPose[a];
					JointPose pose2 = samples[toSample].m_aJointPose[a];

					JointPose finalPose = ani_lerp(pose1, pose2, normalizedLocalTime);
					U32 boneIndex = /*30 * bonesID +*/ a;
					if (parentIndex == -1) 
						m_aBones[boneIndex] = joint[a].m_globalTransform = convertPoseToMat(finalPose);
					else {
						joint[a].m_globalTransform = joint[parentIndex].m_globalTransform * convertPoseToMat(finalPose);
						m_aBones[boneIndex] = joint[a].m_globalTransform * joint[a].m_invBindPose;
					}
				}
			}
		}
	}

	void AnimationManager::onEvent(engine::Event *e) {
		switch (e->getType()) {
		case EventType::EVENT_ANIMATION:
			{AnimationEvent *ae = static_cast<AnimationEvent*> (e);
			m_aHandles[ae->getID()].isAnimating = ae->getState(); }	
			break;
		}
	}

	void AnimationManager::free(void *location, size_t size) {
// (SUMI) NOT IMPLEMENTED
		//m_pAllocator->free(location, size);
	}

	void AnimationManager::logStates() const {
		
	}

	void AnimationManager::startUp() {	
		if (!isInitialized) {
			isInitialized = true;

			//Section sHandles(requestMemory(sizeof(AnimationHandle) * 10), 10);
			

			// Skeletons
			m_aSkeletons = REQUEST_MEMORY(Skeleton, MAX_SKELETONS);
			m_aJoints = REQUEST_MEMORY(Joint, MAX_JOINTS);

			// Clips
			m_aClips = REQUEST_MEMORY(AnimationClip, MAX_CLIPS);
			m_aSamples = REQUEST_MEMORY(AnimationSample, MAX_SAMPLES);
			m_aJointPoses = REQUEST_MEMORY(JointPose, MAX_JOINT_POSES);
			
			// Handles
			m_aHandles = REQUEST_MEMORY(AnimationHandle, MAX_HANDLES);
			
			// Bones
			m_aBones = REQUEST_MEMORY(mat4, MAX_BONES);

			// Components
			m_aComponents = REQUEST_MEMORY(Animatable, MAX_COMPONENTS);

			// Renderable SKins
			m_aRenderSkin = REQUEST_MEMORY(RenderableSkin, MAX_RENDERABLES);

			// Connections
			//m_aSkeletons->m_aJoint = m_aJoints;
			//m_aSamples->m_aJointPose = m_aJointPoses;

			m_aClips->m_aSample = m_aSamples;
			m_aClips->m_aSample->m_aJointPose = m_aJointPoses;
			//m_aClips->m_aSample[1].m_aJointPose = &m_aJointPoses[30];
			//m_aClips->m_aSample[2].m_aJointPose = &m_aJointPoses[30*2];
			//m_aClips->m_aSample[3].m_aJointPose = &m_aJointPoses[30*3];
			//m_aClips->m_aSample[4].m_aJointPose = &m_aJointPoses[30*4];
			//m_aClips->m_aSample[5].m_aJointPose = &m_aJointPoses[30*5];
			//m_aClips->m_aSample[6].m_aJointPose = &m_aJointPoses[30*6];


			m_aClips->m_pSkeleton = m_aSkeletons;
			m_aClips->m_pSkeleton->m_aJoint = m_aJoints;

			for (U32 i = 0; i < MAX_BONES; i++) m_aBones[i] = mat4(1.0f);

			U32 totalAllocation =
				sizeof(AnimationClip)*MAX_CLIPS +
				sizeof(Skeleton) * MAX_SKELETONS +
				sizeof(AnimationHandle) * MAX_HANDLES +
				sizeof(mat4) * MAX_BONES +
				sizeof(AnimationSample) * MAX_SAMPLES +
				sizeof(Joint) * MAX_JOINTS +
				sizeof(JointPose) * MAX_JOINT_POSES;

			LOG("Allocation Size in Bytes", totalAllocation);
		}
		
	}

	void AnimationManager::shutDown() {

	}

	RenderableSkin *AnimationManager::getRenderable() {
		return m_aRenderSkin;
	}

	AnimationHandle *AnimationManager::getHandle() {
		return m_aHandles;
	}

	mat4 *AnimationManager::getBones() {
		return m_aBones;
	}

	void AnimationManager::requestNewComponent(Animatable *&component) {	
		U32 index = 0;
		// create handle
		m_aHandles[index].globalTime = 0.0f;
		m_aHandles[index].localTime = 0.0f;
		m_aHandles[index].currentClip = 0;
		m_aHandles[index].nextClip = 0;
		m_aHandles[index].playbackRate = 2.0f;
		m_aHandles[index].isAnimating = true;

		m_aComponents[numComponents].m_pBones = &m_aBones[0];
		m_aComponents[numComponents].m_pSkin = &m_aRenderSkin[0];
		m_aComponents[numComponents].m_pHandle = &m_aHandles[index];
		component = &m_aComponents[numComponents];
		
		numComponents++;
	}

	void AnimationManager::loadAnimations() {
		loadAnimation(ANIM_PLAYER_RUN, &m_aClips[numClips], &m_aRenderSkin[numRenderSkins]);
	}


	// HELPER
	mat4 convertPoseToMat(const JointPose &pose) {
		mat4 transM(1.0f);
		transM.elements[12] = pose.m_trans.x;
		transM.elements[13] = pose.m_trans.y;
		transM.elements[14] = pose.m_trans.z;
		Quaternion rotation = pose.m_rot;
		mat4 rotM = rotation.toMatrix();
		return transM * rotM;
	}

}
