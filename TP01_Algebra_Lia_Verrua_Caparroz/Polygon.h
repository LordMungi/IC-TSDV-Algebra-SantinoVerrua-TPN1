#pragma once
#include "raylib.h"
#include <Vector>

struct Line {

	Vector2 start;
	Vector2 end;

};

class Polygon
{
private:
	int id = 0;
	std::vector <Vector2> points;
	Color color = MAGENTA;

public:

	Polygon();

	int getId();
	void setId(int id);
	void addId();

	void setPoints(std::vector <Vector2> points);
	bool addPoint(Vector2 point, bool force = false);
	void offsetPoints(Vector2 offset);
	void deletePoint();
	void setColor(Color color);
	Color getColor();

	void Clear();

	int size();

	std::vector<Vector2> getPoints();

	void Draw(Color color);
	void Draw();

};

