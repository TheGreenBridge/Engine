#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "skinning\AnimationClip.h"
#include "skinning\RenderableSkin.h"

#include "AnimationLoader.h"
#include <utils/Log.h>
#include <graphics\api\Loader.h>


#include <vector>
#include <map>

#define VBO_SLOTS	5

#define VBO_VERTEX	0
#define VBO_NORMAL	1
#define VBO_UV		2
#define VBO_JOINT	3
#define VBO_WEIGHT	4

#define ATT_VERTEX	0
#define ATT_NORMAL	1
#define ATT_UV		2
#define ATT_JOINT	3
#define ATT_WEIGHT	4

#define JOINTS_PER_VERTEX 4

#define LIMIT_BONES	30

namespace engine {
	namespace animation{
	// Protoypes
	aiNodeAnim *findNodeAnim(const aiAnimation *pAnimation, const aiString &nodeName);
	void readBoneHierarchy(AnimationClip* clip, const aiAnimation *pAnimation, const aiNode *pNode, const int parentIndex);
	mat4 aiMatToMat4(const aiMatrix4x4 &mat);
	void testloadSkinnedMesh(unsigned int *vao, unsigned int *vbo, const float *vertices, const float *normals, const float *uvs, const int *joints, const float *weights,
		const unsigned int vertSize);


	//using namespace engine::animation;

	// REMOVE THIS SHIT
	std::map<std::string, int> boneMapping;
	std::map<std::string, mat4> invBindPoses;

	bool loadAnimation(const char* filePath, AnimationClip *clip, RenderableSkin *mesh) {
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(filePath,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_SortByPType |
			aiProcess_LimitBoneWeights);

		if (!scene) return false;

		

		aiMesh *aimesh = scene->mMeshes[0];

		//*****************************************************

		aiNode *rootBone = scene->mRootNode->FindNode("Steuerbone");
		aiAnimation *pAnimation = scene->mAnimations[0];
		unsigned int numBones = aimesh->mNumBones;
		unsigned int numKeys = pAnimation->mChannels[0]->mNumPositionKeys;

		unsigned int numChannels = pAnimation->mNumChannels;
		// AnimationInfo
		LOG("Root Bone", aimesh->mBones[0]->mName.C_Str());
		LOG("Number of Bones", numBones);
		LOG("Channels", numChannels);
		LOG("Keys", numKeys);
		LOG("Duration", std::to_string(pAnimation->mDuration).c_str());
		LOG("TicksPerSecond", std::to_string(pAnimation->mTicksPerSecond).c_str());

		LOG("sizeof Skeleton", sizeof(Skeleton));
		LOG("sizeof Joint", sizeof(Joint));
		LOG("sizeof AnimationSample", sizeof(AnimationSample));
		LOG("sizeof JointPose", sizeof(JointPose));

		clip->m_duration = (float)pAnimation->mDuration / (float)pAnimation->mTicksPerSecond;
		clip->m_pSkeleton->m_jointCount = numChannels;
		clip->m_frameCount = numKeys;

		JointPose *&pose = clip->m_aSample->m_aJointPose;

		// Setup structure
		for (unsigned int i = 0; i < numKeys; i++) {
			clip->m_aSample[i].m_aJointPose = &pose[i*numChannels];
		}


		for (unsigned int i = 0; i < aimesh->mNumBones; i++) {
			aiBone *tBone = aimesh->mBones[i];
			invBindPoses.insert(std::pair<std::string, mat4>(tBone->mName.C_Str(), aiMatToMat4(tBone->mOffsetMatrix.Transpose())));
		}

		readBoneHierarchy(clip, pAnimation, rootBone, -1);

		//*****************************************************
		// DATA PART

		// Mesh and Boneinformation
		int numVerts = aimesh->mNumFaces * 3;
		float *aVertices = new float[numVerts * 3];
		float *aNormals = new float[numVerts * 3];
		float *aUVs = new float[numVerts * 2];
		int *aBoneIds = new int[numVerts * 4];
		float *aBoneWeights = new float[numVerts * 4];

		// POSITIONS, NORMALS, UVS
		for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
			const aiFace& face = aimesh->mFaces[i];

			for (int j = 0; j < 3; j++) {
				/*if (aimesh->HasTextureCoords(1)) std::cout << "No Texture Coordinates!" << std::endl;
				else {

				std::cout << "Has Texture Coordinats!" << std::endl;
				aiVector3D uv = aimesh->mTextureCoords[0][face.mIndices[j]];
				memcpy(uvArray, &uv, sizeof(float) * 2);
				uvArray += 2;
				}*/

				aiVector3D normal = aimesh->mNormals[face.mIndices[j]];
				memcpy(aNormals, &normal, sizeof(float) * 3);
				aNormals += 3;

				aiVector3D pos = aimesh->mVertices[face.mIndices[j]];
				memcpy(aVertices, &pos, sizeof(float) * 3);
				aVertices += 3;
			}
		}
		// CREATE WEIGHTS
		std::vector<aiVertexWeight> * vTempWeightsPerVertex = new std::vector<aiVertexWeight>[numVerts];
		for (unsigned int i = 0; i < aimesh->mNumBones; i++) {
			const aiBone *pBone = aimesh->mBones[i];

			// Create all Weights for the vertices
			unsigned int tmp_index = boneMapping.find(pBone->mName.C_Str())->second;
			for (unsigned int a = 0; a < pBone->mNumWeights; a++) {
				// SAME INDEX!

				vTempWeightsPerVertex[pBone->mWeights[a].mVertexId].push_back(aiVertexWeight(tmp_index, pBone->mWeights[a].mWeight));
			}
		}
		// ASSIGN WEIGHTS
		for (int j = 0; j < numVerts; j++) {
			/*aBoneIds[j * 4 + 0] = 0;
			aBoneIds[j * 4 + 1] = 0;
			aBoneIds[j * 4 + 2] = 0;
			aBoneIds[j * 4 + 3] = 0;

			aBoneWeights[j * 4 + 0] = 0.0f;
			aBoneWeights[j * 4 + 1] = 0.0f;
			aBoneWeights[j * 4 + 2] = 0.0f;
			aBoneWeights[j * 4 + 3] = 0.0f;*/
			// RESET ALL WEIGHTS
			for (int b = 0; b < 3; b++) {
				aBoneWeights[j * 4 + b] = 0.0f;
				aBoneIds[j * 4 + b] = 0;
			}
			// ERROR CHECKING
			if (aimesh->HasBones()) {
				if (vTempWeightsPerVertex[j].size() > 4) {
					// Cerror
					//LOG_ERROR("The model has invalid bone weights and is not loaded.");
					return false;
				}
				// REAL ASSIGNING
				for (unsigned int k = 0; k < vTempWeightsPerVertex[j].size(); k++) {
					aBoneIds[j * 4 + k] = vTempWeightsPerVertex[j][k].mVertexId;
					aBoneWeights[j * 4 + k] = /*(GLfloat)*/vTempWeightsPerVertex[j][k].mWeight;
				}
			}
		}
		// DELETE TEMP VECTOR
		if (vTempWeightsPerVertex != NULL) {
			delete[] vTempWeightsPerVertex;
			vTempWeightsPerVertex = NULL;
		}
		//uvArray -= numVerts * 2;
		aNormals -= numVerts * 3;
		aVertices -= numVerts * 3;
		// SEND DATA TO GPU
		
		testloadSkinnedMesh(&mesh->vao, mesh->vbo, aVertices, aNormals, aUVs, aBoneIds, aBoneWeights, numVerts);

		//this->numVerts = aimesh->mNumFaces * 3;

		mesh->numVerts = aimesh->mNumFaces * 3;

		// DELETE DYNAMIC MEMORY
		delete[] aVertices;
		delete[] aNormals;
		delete[] aUVs;
		delete[] aBoneIds;
		delete[] aBoneWeights;

		// ************************************************************

		//typedef std::map<std::string, int>::const_iterator MapIterator;
		//for (MapIterator iter = boneMapping.begin(); iter != boneMapping.end(); iter++)
		//{
			//LOG("Key", iter->first);
			//LOG("Value", iter->second);
		//}
		return true;
	}

	//int channelIndex = 0;

	void readBoneHierarchy(AnimationClip *clip, const aiAnimation *pAnimation, const aiNode *pNode, const int parentIndex) {
		static int channelIndex = 0;
		// Save all Animationdata in Memory
		//if (pNode->mName.C_Str() == nullptr) LOG("THIS NODE IS NULLPTR!!!");
		std::string nodeName(pNode->mName.C_Str());
		const aiNodeAnim *pNodeAnim = findNodeAnim(pAnimation, pNode->mName);
		// relation -> joint name to index in array
		boneMapping.insert(std::pair<std::string, int>(nodeName, channelIndex));
		// checking for errors
		if (pNodeAnim != nullptr) {
			// all samples
			
			for (int kf = 0; kf < clip->m_frameCount; kf++) {
				aiQuaternion rot_temp = pNodeAnim->mRotationKeys[kf].mValue;
				aiVector3D pos_temp = pNodeAnim->mPositionKeys[kf].mValue;

				// LOCAL POSE
				JointPose nodeTransform;
				nodeTransform.m_rot = Quaternion(rot_temp.x, rot_temp.y, rot_temp.z, rot_temp.w);
				nodeTransform.m_trans = Vec3(pos_temp.x, pos_temp.y, pos_temp.z);
				nodeTransform.m_scale = 1.0f;
				// save pose
				clip->m_aSample[kf].m_aJointPose[channelIndex] = nodeTransform;
				
				// get overwritten all the time!!!
				//if(channelIndex == 5)
				if (channelIndex == 0) {
					clip->m_aSample[kf].m_timeStamp = (float)pNodeAnim->mPositionKeys[kf].mTime;
				}
				
			}
			// SKELETON
			clip->m_pSkeleton->m_aJoint[channelIndex].m_iParent = parentIndex;
			// search if a invBindPose exists for this joint, if not, set it to Identity Matrix 
			if (invBindPoses.find(nodeName) == invBindPoses.end())
				clip->m_pSkeleton->m_aJoint[channelIndex].m_invBindPose = mat4(1.0f);
			else clip->m_pSkeleton->m_aJoint[channelIndex].m_invBindPose = invBindPoses.find(nodeName)->second;
			// next index in the array
			channelIndex++;
			// recursion through all children
			for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
				readBoneHierarchy(clip, pAnimation, pNode->mChildren[i], boneMapping.find(nodeName.c_str())->second);
			}
		}
	}

	aiNodeAnim *findNodeAnim(const aiAnimation *pAnimation, const aiString &nodeName) {

		//LOG("Search for:", nodeName.C_Str());
		for (U32 i = 0; i < pAnimation->mNumChannels; i++) {
			//LOG("Channels:", pAnimation->mChannels[i]->mNodeName.data);
			if (pAnimation->mChannels[i]->mNodeName == nodeName) {

				//LOG("HIT DETECTETD!");

				return pAnimation->mChannels[i];
			}
		}
		return nullptr;
	}



	mat4 aiMatToMat4(const aiMatrix4x4 &mat) {
		/*mat4 result(	mat.a1, mat.b1,mat.c1, mat.d1,
		mat.a2, mat.b2, mat.c2,mat.d2,
		mat.a3, mat.b3, mat.c3, mat.d3,
		mat.a4, mat.b4, mat.c4, mat.d4);
		return result;*/

		mat4 result(mat.a1, mat.a2, mat.a3, mat.a4,
			mat.b1, mat.b2, mat.b3, mat.b4,
			mat.c1, mat.c2, mat.c3, mat.c4,
			mat.d1, mat.d2, mat.d3, mat.d4);
		return result;
	}

	void testloadSkinnedMesh(unsigned int *vao, unsigned int *vbo, const float *vertices, const float *normals, const float *uvs, const int *joints, const float *weights,
		const unsigned int vertSize) {

		Loader::testloadSkinnedMesh(vao, vbo, vertices, normals, uvs, joints, weights, vertSize);
	}
}
}