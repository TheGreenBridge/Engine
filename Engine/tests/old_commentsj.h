// Pool Allocator


//#pragma once
//#include <memory>
//#include <common\types.h>
//
//namespace engine {
//	namespace memory {
//
//		template <typename T>
//		union PoolChunk {
//			T value;
//			PoolChunk<T> *nextPoolChunk;
//
//			PoolChunk() {};
//			~PoolChunk() {};
//		};
//
//		template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
//		class PoolAllocator
//		{
//		private:
//			static const size_t POOLALLOCATORDEFAULTSIZE = 1024;
//			size_t m_OpenAllocations = 0;
//
//			size_t m_Size = 0;
//
//			PoolChunk<T> *m_Data = nullptr;
//			PoolChunk<T> *m_Head = nullptr;
//
//			Allocator* m_ParentAllocator = nullptr;
//			bool m_needsToDeleteParentAllocator = false;
//
//		public:
//			explicit PoolAllocator(size_t size = POOLALLOCATORDEFAULTSIZE, Allocator *parentAllocator = nullptr);
//
//			PoolAllocator(const PoolAllocator &other) = delete; // Copy Cstr
//			PoolAllocator(const PoolAllocator &&other) = delete; // Move Cstr
//			PoolAllocator& operator= (const PoolAllocator &other) = delete; // Copy Assignment
//			PoolAllocator& operator= (const PoolAllocator &&other) = delete; // Move Assignment
//
//			~PoolAllocator();
//
//			template <typename... arguments>
//			T* allocate(arguments&&... args);
//
//			void deallocate(T* data);
//
//			U32 getSize() const;
//		};
//
//	}
//}
//
//// IMPLEMENTATION
//
//namespace engine {
//	namespace memory {
//
//		template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
//		PoolAllocator<T, Allocator>::PoolAllocator(size_t size = POOLALLOCATORDEFAULTSIZE, Allocator *parentAllocator = nullptr)
//			: m_Size(size), m_ParentAllocator(parentAllocator)
//		{
//			if (parentAllocator == nullptr) {
//				m_ParentAllocator = new Allocator();
//				m_needsToDeleteParentAllocator = true;
//			}
//
//			m_Data = m_ParentAllocator->allocate(m_Size);// new PoolChunk<T>[size];
//			m_Head = m_Data;
//
//			for (size_t i = 0; i < m_Size - 1; ++i)
//			{
//				m_Data[i].nextPoolChunk = std::addressof(m_Data[i + 1]);
//			}
//			m_Data[m_Size - 1].nextPoolChunk = nullptr;
//		}
//
//
//		template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
//		PoolAllocator<T, Allocator>::~PoolAllocator()
//		{
//			if (m_OpenAllocations != 0) {
//				// Error
//			}
//
//			m_ParentAllocator->deallocate(m_Data, m_Size);
//			if (m_needsToDeleteParentAllocator)
//			{
//				delete m_ParentAllocator;
//			}
//			m_Data = nullptr;
//			m_Head = nullptr;
//		}
//
//		template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
//		template <typename... arguments>
//		T* PoolAllocator<T, Allocator>::allocate(arguments&&... args)
//		{
//			if (m_Head == nullptr)
//				return nullptr;
//
//			m_OpenAllocations++;
//
//			PoolChunk<T> *poolChunk = m_Head;
//			m_Head = m_Head->nextPoolChunk;
//			T* retVal = new (std::addressof(poolChunk->value)) T(std::forward<arguments>(args)...);
//			return retVal;
//		}
//
//		template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
//		void PoolAllocator<T, Allocator>::deallocate(T* data)
//		{
//			if (data == nullptr)
//			{
//				return;
//			}
//			data->~T();
//			m_OpenAllocations--;
//			PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
//			poolChunk->nextPoolChunk = m_Head;
//			m_Head = poolChunk;
//		}
//
//		template <typename T, typename Allocator = std::allocator<PoolChunk<T>>>
//		U32 PoolAllocator<T, Allocator>::getSize() const {
//			return m_Size;
//		}
//	}
//}
















//#include "tests\EngineTest.h"
//
//int main() {
//
//	EngineTest test;
//	test.init();
//	test.run();
//
//	return 0;
//}

//int xPosition = 0, yPosition = 0;
//
//void cursor_position_callback(GLFWwindow* commingWindow, double xpos, double ypos)
//{
//	TwEventMousePosGLFW3(commingWindow, xpos, ypos);
//	int dx = (int)xpos - xPosition;
//	int dy = (int)ypos - yPosition;
//
//	float sens = 0.01f;
//	float ry = -dy * sens;
//	float rx = -dx * sens;
//
//	xPosition = (int)xpos;
//	yPosition = (int)ypos;
//
//	camera.Rotate(Vec3(1, 0, 0), -ry);
//	camera.Rotate(Vec3(0, 1, 0), -rx);
//}
//
//float angle = 0;
//Transform fromTrans(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f);
//Transform toTrans(Vec3(0, 0, 0), Quaternion(1, 0, 0, 1), 1.0f);
//float countering = 0;
//bool cameraState = false;
//void updateInput() {
//	// Translation
//	if (gInputManager.KEYS[GLFW_KEY_W]) camera.Translate(Vec3(0, 0, 1));
//	if (gInputManager.KEYS[GLFW_KEY_S]) camera.Translate(Vec3(0, 0, -1));
//	if (gInputManager.KEYS[GLFW_KEY_A]) camera.Translate(Vec3(1, 0, 0));
//	if (gInputManager.KEYS[GLFW_KEY_D]) camera.Translate(Vec3(-1, 0, 0));
//	if (gInputManager.KEYS[GLFW_KEY_SPACE]) camera.Translate(Vec3(0, -1, 0));
// 	if (gInputManager.KEYS[GLFW_KEY_C]) camera.Translate(Vec3(0, 1, 0));
//
//	// Inits
//	if (gInputManager.KEYS[GLFW_KEY_L]) sun.setPosition(Vec3(0, 5, 0));
//
//	// Camera: UP - DOWN - FRONT - BACK- RIGHT - LEFT
//	if (gInputManager.KEYS[GLFW_KEY_8]) { camera.setRotation(Vec3(1, 0, 0), (float)(PI / 2)); camera.setPosition(Vec3(0, -10, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_2]) { camera.setRotation(Vec3(-1, 0, 0), (float)(PI / 2)); camera.setPosition(Vec3(0, 10, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_5]) { camera.setRotation(Vec3(0, 0, 0), 1); camera.setPosition(Vec3(0, 0, -10)); }
//	if (gInputManager.KEYS[GLFW_KEY_0]) { camera.setRotation(Vec3(0, 0, 1), (float)(PI / 2)); camera.setPosition(Vec3(0, 0, -10)); }
//	if (gInputManager.KEYS[GLFW_KEY_6]) { camera.setRotation(Vec3(0, 0, 1), (float)(PI / 2)); camera.setPosition(Vec3(-10, 0, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_4]) { camera.setRotation(Vec3(0, 0, -1), (float)(PI / 2)); camera.setPosition(Vec3(10, 0, 0)); }
//
//	//Rotation
//	if (gInputManager.KEYS[GLFW_KEY_Q]) camera.Rotate(Vec3(0, 0, 1), 0.1f);
//
//	// Special
//	if (gInputManager.KEYS[GLFW_KEY_ENTER]) camera.printInfo();
//	if (gInputManager.KEYS[GLFW_KEY_U]) { camera.setRotation(Vec3(1, 0, 0), (float)(PI / 2));	camera.setPosition(Vec3(0, -10, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_V]) checkConsole();
//
//	if (gInputManager.KEYS[GLFW_KEY_X]) camera.m_Speed = 0.1f;
//	if (gInputManager.KEYS[GLFW_KEY_B]) camera.m_Speed = 0.01f;
//
//	if (gInputManager.KEYS[GLFW_KEY_P]) {
//		/*if (beta < 1)*/ beta += 0.01f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_O]) {
//		/*if (beta > 0)*/ beta -= 0.01f;
//	}
//
//	if (gInputManager.KEYS[GLFW_KEY_K]) {
//		//if(entity.animatable->m_pHandle->playbackRate < 3.0f)	entity.animatable->m_pHandle->playbackRate += 0.02f;
//		//LOG("PlaybackRate", entity.animatable->m_pHandle->playbackRate);
//
//		gAnimationManager.update(0.005f);
//		//selectAnimation = 0;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_J]) {
//		//if(entity.animatable->m_pHandle->playbackRate > -1.02) entity.animatable->m_pHandle->playbackRate -= 0.02f;
//		//LOG("PlaybackRate", entity.animatable->m_pHandle->playbackRate);
//		gAnimationManager.update(-0.005f);
//		//selectAnimation = 1.0f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_UP]) {
//		eentity.transform.position.y += 0.1f;
//		eentity.collidable->max.y += 0.1f;
//		eentity.collidable->min.y += 0.1f;
//		//AnimationEvent e(0, true);
//		//gAnimationManager.onEvent(&e);
//	}
//	else {
//		//AnimationEvent e(0, false);
//		//gAnimationManager.onEvent(&e);
//	}
//
//	if (gInputManager.KEYS[GLFW_KEY_DOWN]) {
//		eentity.transform.position.y -= 0.1f;
//		eentity.collidable->max.y -= 0.1f;
//		eentity.collidable->min.y -= 0.1f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_RIGHT]) {
//		eentity.transform.position.x += 0.1f;
//		eentity.collidable->max.x += 0.1f;
//		eentity.collidable->min.x += 0.1f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_LEFT]) {
//		eentity.transform.position.x -= 0.1f;
//		eentity.collidable->max.x -= 0.1f;
//		eentity.collidable->min.x -= 0.1f;
//	}
//
//	if (gInputManager.KEYS[GLFW_KEY_H]) {
//		if(countering < 1)countering += 0.001f;
//		eentity.transform = ani_transform(fromTrans, toTrans, countering);
//	}
//	
//	if (gInputManager.KEYS[GLFW_KEY_M]) {			
//		renderer.setCamera(&followCam);
//	}
//	if (gInputManager.KEYS[GLFW_KEY_N]) {
//		renderer.setCamera(&camera);
//	}
//}
//
//
//
//void key_callback(GLFWwindow* commingWindow, int key, int scancode, int action, int mods){	
//	TwEventKeyGLFW3(commingWindow, key, scancode, action, mods);
//	
//	if (action == GLFW_PRESS) {
//		gInputManager.KEYS[key] = true;
//		KeyPressedEvent ke(key);
//		engine::Event *e = &ke;
//		gInputManager.onEvent(e);
//	}
//	else if (action == GLFW_RELEASE) {
//		gInputManager.KEYS[key] = false;
//		engine::Event e(EventType::EVENT_KEY_RELEASED);
//		gInputManager.onEvent(&e);
//	}
//}