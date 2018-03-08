#pragma once

struct SkinnedVertex {
	float m_position[3];
	float m_normal[3];
	float m_u, m_v;
	short m_jointIndex[4];
	float m_jointWeight[3];
};