#pragma once
#include <string>
#include <vector>
#include "Bullet.h"

class Bullet;

class Enemy
{
public:
public:
	Enemy(char* filename);
	void draw();
	void move(double direction, double deltaTime);
	void shoot(std::vector<Bullet>& bullets);
	void death(int frame);
	int player_id;
	int explosion_id[4];
private:
	double xPosition, yPosition;
	double scale, angle;
	double speed;
};

};

