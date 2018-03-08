#pragma once

#include "Skeleton.h"

#include "JointPose.h"
namespace engine {	namespace animation {
	
	struct SkeletonPose {
		Skeleton *m_pSkeleton; // Change to ID with Systems
		JointPose *m_aLocalPose;
		mat4 *m_aGlobalPose;
	};

}}