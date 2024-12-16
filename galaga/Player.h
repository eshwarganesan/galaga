#pragma once
#include <string>
#include <vector>
#include "Bullet.h"

class Bullet;

class Player
{
public:
	Player(char *filename);
	void draw();
	void move(double direction, double deltaTime);
	void shoot(std::vector<Bullet>& bullets);
	void death();
	int player_id;
	int explosion_id;
private:
	double xPosition, yPosition;
	double scale, angle;
	double speed;
};

