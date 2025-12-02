#pragma once
#include <raylib.h>
#include <raymath.h>

namespace collision
{
	bool lineLine(Vector2 start1, Vector2 end1, Vector2 start2, Vector2 end2, Vector2* collisionPoint)
	{
		Vector2 a = start1;
		Vector2 b = end1;
		Vector2 c = start2;
		Vector2 d = end2;

		Vector2 ab = b - a;
		Vector2 cd = d - c;
		Vector2 ca = a - c;

		float det = (cd.y * ab.x - cd.x * ab.y);

		float uA = (cd.x * ca.y - cd.y * ca.x) / det;
		float uB = (ab.x * ca.y - ab.y * ca.x) / det;

		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
			*collisionPoint = a + (Vector2Scale(b - a, uA));
			return true;
		}
		return false;
	}
}