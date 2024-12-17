#pragma once
#include <string>
#include <vector>
#include "Bullet.h"

class Bullet;

struct Waypoint {
	float x, y;
};

enum class EnemyType {
	BASIC,
	SWIRL,
	ZIGZAG,
	BOSS
};

class Enemy
{
public:
	Enemy(char* filename, double xPosition1);

	void draw();
	void move();
	void shoot(std::vector<Bullet>& bullets);
	void death(int frame);
	int enemy_id;
	int explosion_id[4];
	
	float x, y;
private:
	float speed;
	double xPosition, yPosition;
	double scale, angle;
	
};
void SpawnEnemies();
void UpdateEnemies(float deltaTime);
