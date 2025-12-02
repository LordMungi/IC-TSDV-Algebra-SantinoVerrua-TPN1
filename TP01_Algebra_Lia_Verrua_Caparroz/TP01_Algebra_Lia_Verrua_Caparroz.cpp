#include <iostream>
#include "raylib.h"
#include "Polygon.h"
#include "Point.h"
#include "Collision.h"

//------------------------------------------------------------------------------------
//							Instrucciones
// 
// 
// Utilizando el mouse se pueden crear y mover poligonos.
// Si hay una interseccion esta se marcara con un punto magenta
// al ser sobrepuestas, se mostraran las intersecciones con un punto de color
// si un poligono no permite terminarse o no se puede seguir dibujando, usar la tecla Borrar
// 
// 
//							Controles
// 
//	Click izquierdo				->		poner punto para el poligono actual
//	Mantener clic izquierdo		->		hacer curvas
//	Click derecho				->		seleccionar poligono
//	Enter						->		terminar el poligono actual
//	Borrar (sin seleccion)		->		eliminar el ultimo punto puesto (mantener para eliminar varios)
//	Borrar (con seleccion)		->		elimina el poligono seleccionado
//
//------------------------------------------------------------------------------------

void main()
{

	int screenWidth = 1600;
	int screenHeight = 900;
	int fps = 60;

	float deltaTime = 0.0f;

	float holdThreshold = 0.2f;
	float heldTime = 0;

	int pointsCreated = 0;

	InitWindow(screenWidth, screenHeight, "Main");
	SetTargetFPS(fps);

	std::vector<Polygon> polygons;
	Polygon currentPolygon;

	Polygon* selectedPolygon = nullptr;

	Vector2 mouse;
	Vector2 lastPos = { 0,0 };
	Vector2 mouseDelta = { 0,0 };

	std::vector <Vector2> points;

	std::vector <Point> collisions;
	Vector2* collision = new Vector2();
	Color collisionColor = RED;

	Color currentColor;
	currentColor.a = 255;

	while (WindowShouldClose() == false)
	{
		deltaTime = GetFrameTime();

		mouseDelta = GetMouseDelta();
		mouse = GetMousePosition();

		if (IsKeyDown(KEY_SPACE)) {
			if (selectedPolygon != nullptr) {
				selectedPolygon = nullptr;
			}
			else if (currentPolygon.addPoint(mouse)) {
				lastPos = mouse;
			}
		}

		if (IsMouseButtonDown(0)) {

			heldTime += deltaTime;

			if (heldTime >= holdThreshold) {
				if (selectedPolygon != nullptr) {
					selectedPolygon = nullptr;
				}
				else if (currentPolygon.addPoint(mouse)) {
					pointsCreated++;
					std::cout << "New Point: " << pointsCreated << std::endl;
					lastPos = mouse;
				}
				heldTime -= deltaTime * 1.5f;
			}
		}
		else if (IsMouseButtonReleased(0) && heldTime < holdThreshold) {
			heldTime = 0.0f;

			if (selectedPolygon != nullptr) {
				selectedPolygon = nullptr;
			}
			else if (currentPolygon.addPoint(mouse)) {
				lastPos = mouse;
			}

		}
		else {
			pointsCreated = 0;
		}

		if (IsMouseButtonPressed(1)) {

			DrawCircleV(mouse, 15, RAYWHITE);
			if (selectedPolygon == nullptr) {
				for (int i = 0; i < polygons.size();i++) {

					for (int j = 0; j < polygons[i].getPoints().size() - 1; j++) {

						if (CheckCollisionCircleLine(mouse, 15, polygons[i].getPoints()[j], polygons[i].getPoints()[j + 1])) {

							selectedPolygon = &polygons[i];
							std::cout << "Id: " << selectedPolygon->getId() << std::endl;
							std::cout << "size: " << selectedPolygon->size() << std::endl;
						}
					}
				}

			}
		}
		else if(IsMouseButtonReleased(1)){
			std::cout << "nullptr" << std::endl;
			selectedPolygon = nullptr;
		}

		if (IsKeyPressed(KEY_ENTER)) {

			if (currentPolygon.size() > 2) {

				if (currentPolygon.addPoint(currentPolygon.getPoints()[0])) {

					currentColor.r = rand() % 255;
					currentColor.g = rand() % 255;
					currentColor.b = rand() % 255;

					currentPolygon.addId();

					currentPolygon.setColor(currentColor);
					polygons.push_back(currentPolygon);

					currentPolygon.Clear();
				}
			}
		}

		if (IsKeyDown(KEY_BACKSPACE)) {

			heldTime += deltaTime;

			if (heldTime >= holdThreshold) {
				if (selectedPolygon == nullptr) {
					currentPolygon.deletePoint();
					if (currentPolygon.size() > 1) {
						lastPos = currentPolygon.getPoints()[currentPolygon.size() - 1];
					}
					else {
						lastPos = { -100,-100 };
					}
				}
				heldTime -= deltaTime * 2.0f;
			}
		}
		else if (IsKeyReleased(KEY_BACKSPACE)) {
			heldTime = 0.0f;
		}

		if (IsKeyPressed(KEY_BACKSPACE)) {

			if (selectedPolygon == nullptr) {
				currentPolygon.deletePoint();
				if (currentPolygon.size() > 1) {
					lastPos = currentPolygon.getPoints()[currentPolygon.size() - 1];
				}
				else {
					lastPos = { -100,-100 };
				}
			}
			else {

				for (int i = 0; i < polygons.size(); i++)
				{
					std::cout << "Trying to delete: " << i << std::endl;
					if ((*selectedPolygon).getId() == polygons[i].getId()) {
						polygons.erase(polygons.begin() + i);
						selectedPolygon = nullptr;
						std::cout << "Delete complete" << std::endl;
						i = polygons.size();
					}
				}
			}
		}

		if (selectedPolygon != nullptr) {
			selectedPolygon->offsetPoints(mouseDelta);
		}


		BeginDrawing();
		ClearBackground(BLACK);

		if (!currentPolygon.getPoints().empty()) {
			DrawCircleV(lastPos, 10, RED);
			currentPolygon.Draw(WHITE);
		}

		for (Polygon polygon : polygons)
		{
			polygon.Draw();
		}

		collisions.clear();

		for (Polygon currentPolygon : polygons)
		{
			for (Polygon polygon : polygons) {

				if (polygon.getId() != currentPolygon.getId() && polygons.size() > 1) {

					for (int i = 0; i < currentPolygon.size() - 1; i++)
					{
						for (int j = 0; j < polygon.size() - 1; j++) {

							if (collision::lineLine(polygon.getPoints()[j], polygon.getPoints()[j + 1], currentPolygon.getPoints()[i], currentPolygon.getPoints()[i + 1], collision)) {

								collisionColor.r = (currentPolygon.getColor().r / 2) + (polygon.getColor().r / 2);
								collisionColor.g = (currentPolygon.getColor().g / 2) + (polygon.getColor().g / 2);
								collisionColor.b = (currentPolygon.getColor().b / 2) + (polygon.getColor().b / 2);

								collisions.push_back({ (*collision), collisionColor });;

							}
						}
					}
				}
			}
		}

		for (Point point : collisions)
		{
			DrawCircleV(point.pos, 10, point.color);
		}

		EndDrawing();
	}
	delete collision;
	CloseWindow();
}