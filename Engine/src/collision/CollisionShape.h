#pragma once

enum class CShapeType
{
	SHAPE_SPHERE,
	SHAPE_AABB3D,
	SHAPE_AABB2D,
	SHAPE_OBB,
	SHAPE_SOUP
};

class CollisionShape {
private:
	CShapeType m_eType;
public:
	CollisionShape() {}
	~CollisionShape() {}

	CShapeType getType() { return m_eType; }

};