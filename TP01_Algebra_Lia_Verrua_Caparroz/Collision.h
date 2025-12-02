#pragma once
#include <raylib.h>
#include <raymath.h>

namespace collision
{
	bool lineLine(Vector2 start1, Vector2 end1, Vector2 start2, Vector2 end2, Vector2* collisionPoint);
}