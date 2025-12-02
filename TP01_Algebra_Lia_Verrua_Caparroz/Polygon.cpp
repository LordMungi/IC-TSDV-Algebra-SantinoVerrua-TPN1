#include "Polygon.h"

Polygon::Polygon()
{
}

int Polygon::getId()
{
	return this->id;
}

void Polygon::setId(int id)
{
	this->id = id;
}

void Polygon::addId()
{
	this->id = id + 1;
}

void Polygon::setPoints(std::vector<Vector2> points)
{
	this->points = points;
}

bool Polygon::addPoint(Vector2 point, bool force)
{
	Vector2* collision = new Vector2();
	Line line;
	int collisions = 0;

	if (this->size() == 0 || force) {
		points.push_back(point);
		return true;
	}

	Line currentLine = { points[this->size() - 1], point };

	for (int i = 0; i < this->size() - 2; i++)
	{
		line = { this->points[i], this->points[i + 1] };

		if (CheckCollisionLines(currentLine.start, currentLine.end, line.start, line.end, collision)) {

			DrawCircleV(*collision, 10, MAGENTA);

			collisions++;
		}
	}

	if (collisions == 0) {
		points.push_back(point);
		delete collision;
		return true;
	}
	else if ((collisions == 1 && (*collision).x == points[0].x && (*collision).y == points[0].y)) {
		points.push_back(point);
		delete collision;
		return true;
	}
	else {
		delete collision;
		return false;
	}


}

void Polygon::offsetPoints(Vector2 offset)
{
	for (int i = 0; i < points.size(); i++)
	{
		points[i].x += offset.x;
		points[i].y += offset.y;
	}
}

void Polygon::deletePoint()
{
	if (this->points.size() > 1) {
		this->points.pop_back();
	}
}


void Polygon::setColor(Color color)
{
	this->color = color;
}

Color Polygon::getColor()
{
	return color;
}

void Polygon::Clear()
{
	this->points.clear();
	std::vector <Vector2> empty;
	this->setPoints(empty);
}

int Polygon::size()
{
	return this->getPoints().size();
}

std::vector<Vector2> Polygon::getPoints()
{
	return points;
}

void Polygon::Draw(Color color)
{
	Vector2 lastPos = points[0];

	for (Vector2 point : points) {

		DrawLineV(lastPos, point, color);
		lastPos = point;
	}
}

void Polygon::Draw()
{
	Draw(color);
}

