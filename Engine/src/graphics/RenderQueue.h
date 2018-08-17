//------------------------------------------------------------------------------
// RenderQueue.h
//
// holds object to be rendered
//
// Author: Sommerauer Christian
// Created: 02.08.18
// Changed: 02.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <Components\Renderable3D.h>
#include <common\types.h>

using namespace engine::component;

namespace engine { namespace graphics {
	
	struct RenderItem
	{
		const Renderable3D* renderable;
		U32 distance;
	};

	class RenderQueue
	{
	private:
		RenderItem* m_Head;
		U32 m_Count;
		U32 m_MaxItems;
		U32 m_Current;
	public:
		// Cstr
		RenderQueue(void* ptr, U32 count);

		~RenderQueue();

		// Deleted Cstr
		RenderQueue() = delete;
		RenderQueue(const RenderQueue&) = delete;
		RenderQueue(RenderQueue&&) = delete;
		RenderQueue& operator=(const RenderQueue&) = delete;
		RenderQueue& operator=(RenderQueue&&) = delete;

		// Add Items
		void pushItem(const RenderItem& item);
		RenderItem* getLastItem() const;

		RenderItem* next();

		void reset();
	};
}}
