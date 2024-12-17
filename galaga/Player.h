#pragma once
#include <string>
#include <vector>
#include "Bullet.h"
#include "Vector2D.h"

class Bullet;

class Player
{
public:
	Player(char *filename);
	void draw();
	void move(double direction, double deltaTime);
	void shoot(std::vector<Bullet>& bullets);
	void death(int frame);
	std::vector<Vector2> getVertices();
	int player_id;
	int explosion_id[4];
private:
	double xPosition, yPosition;
	double scale, angle;
	double speed;
	double height, width;
};

