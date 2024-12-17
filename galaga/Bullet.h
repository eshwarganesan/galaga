#pragma once
#include <vector>
#include "Vector2D.h"

class Bullet
{
public:
	Bullet(char* filename, double xPosition, double yPosition, double speed);

	void draw();

	void update(double deltaTime);

	bool outOfScreen();

	bool operator==(const Bullet& other);

	std::vector<Vector2> getVertices();

private:
	double x, y, v, scale;
	double width, height;
	int id;
};

