#pragma once
#include <raylib.h>
#include <raymath.h>

namespace collision
{
	bool lineLine(Vector2 start1, Vector2 end1, Vector2 start2, Vector2 end2, Vector2* collisionPoint);
	bool pointLine(Vector2 point, Vector2 lineStart, Vector2 lineEnd);
	bool circleLine(Vector2 center, float radius, Vector2 lineStart, Vector2 lineEnd);
}