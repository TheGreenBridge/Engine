#pragma once

// Hier kommen alle Definitionen (.h-Dateien) der Engine hin


#include <GLFW\glfw3.h>
#include <cmath>
///PLATFORM
#include "..\src\platform\windows\window.h"
#include "..\src\platform\windows\InputManager.h"
#include "..\src\systems\AnimationManager.h"
#include "..\src\platform\windows\Console.h"

#include "..\src\entity\Camera.h"
#include "..\src\entity\Entity.h" // MESH MODEL MATERIAL(TEXTURE) ANIMATION(TRANSFORM)
#include "..\src\entity\FollowCamera.h"


#include "..\src\entity\mesh\plane.h"
///RENDER




#include "..\src\entity\Light.h"
#include "..\src\entity\Terrain.h"

///ANIMATION
//#include "src\graphics\animation\skinning\SkinnedMesh.h"
#include "..\src\graphics\animation\Animation.h"
#include "..\src\graphics\animation\skinning\RenderableSkin.h"
#include "..\src\graphics\animation\AnimationHandle.h"
#include "..\src\graphics\animation\interpolation.h"

///COLLISION
#include "..\src\collision\AABB.h"
#include "..\src\systems\CollisionManager.h"


///MEMORY

///UTILS
#include "..\src\math\maths.h"
#include "..\src\utils\Time.h"
#include "..\src\utils\Log.h"
#include "..\src\utils\fileutils.h"

///
#include "..\src\systems\messageing\Event.h"
#include "..\src\systems\messageing\types\KeyPressedEvent.h"
#include "..\src\systems\messageing\types\AnimationEvent.h"

#include "..\src\systems\SystemManager.h"
#include <AntTweakBar.h>
#include <random>