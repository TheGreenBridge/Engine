//------------------------------------------------------------------------------
// RenderQueue.cpp
//
// Implementation of the render queue
//
// Author: Sommerauer Christian
// Created: 02.08.18
// Changed: 02.08.18
//------------------------------------------------------------------------------
//

#include <graphics\RenderQueue.h>

namespace engine{ namespace graphics {

	//--------------------------------------------------------------------------
	RenderQueue::RenderQueue(void* ptr, U32 count) :
		m_Head(static_cast<RenderItem*>(ptr)), m_Count(0), 
		m_MaxItems(count), m_Current(0)
	{

	}

	//--------------------------------------------------------------------------
	RenderQueue::~RenderQueue()
	{

	}

	//--------------------------------------------------------------------------
	void RenderQueue::pushItem(const RenderItem& item)
	{
		if (m_Count < m_MaxItems)
		{
			memcpy(static_cast<void*>(m_Head + m_Count), &item, sizeof(RenderItem));
			m_Count++;
		}
	}

	RenderItem * RenderQueue::getLastItem() const
	{
		return m_Count != 0 ? (m_Head + (m_Count - 1)) : nullptr;
	}

	//--------------------------------------------------------------------------
	RenderItem* RenderQueue::next()
	{
		if (m_Current >= m_Count)
		{
			m_Current = 0;
			return nullptr;
		}
		else
		{
			return (m_Head + m_Current++);
		}
	}

	//--------------------------------------------------------------------------
	void RenderQueue::reset()
	{
		m_Count = 0;
		m_Current = 0;
	}

} }
