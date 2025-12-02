#include "Collision.h"

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

	bool pointLine(Vector2 point, Vector2 lineStart, Vector2 lineEnd)
	{
		Vector2 distanceStart = lineStart - point;
		float lengthStart = sqrtf(distanceStart.x * distanceStart.x + distanceStart.y * distanceStart.y);

		Vector2 distanceEnd = lineEnd - point;
		float lengthEnd = sqrtf(distanceEnd.x * distanceEnd.x + distanceEnd.y * distanceEnd.y);

		Vector2 distance = lineStart - lineEnd;
		float length = sqrtf(distance.x * distance.x + distance.y * distance.y);


		float buffer = 0.01f;

		return lengthStart + lengthEnd >= length - buffer && lengthStart + lengthEnd <= length + buffer;
	}

	bool circleLine(Vector2 center, float radius, Vector2 lineStart, Vector2 lineEnd)
	{
		Vector2 distance = lineEnd - lineStart;
		float lengthSq = distance.x * distance.x + distance.y * distance.y;

		Vector2 lineStartCircle = center - lineStart;

		float dot = (lineStartCircle.x * distance.x + lineStartCircle.y * distance.y) / lengthSq;

		Vector2 closest = lineStart + (Vector2Scale(lineEnd - lineStart, dot));

		if (!pointLine(closest, lineStart, lineEnd))
			return false;

		Vector2 distCircle = closest - center;
		float distVector = distCircle.x * distCircle.x + distCircle.y * distCircle.y;

		return distVector <= radius * radius;
	}
}