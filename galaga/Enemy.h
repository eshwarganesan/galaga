#pragma once
#include <string>
#include <vector>
#include "Bullet.h"
#include "timer.h" // use the time / clock reading function
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
	Enemy(char* file_name, double yPosition1, double xPosition1);
	bool movingRight = true;
	bool attacking = true;
	void draw();
	void move(float speed);
	void attack(float speed,float deltaTime);
	void swirl(float speed, float deltaTime);
	void zigzag(float speed, float deltaTime);
	std::vector<Vector2> getVertices();
	void shoot(std::vector<Bullet>& bullets, double interval);
	void death(int frame);
	int enemy_id;
	int explosion_id[4];
	void sim_step(double dt);
	float x, y;
private:
	float speed;
	double xPosition, yPosition;
	double scale, angle;
	double height, width;
	
};

void SpawnEnemies();
void UpdateEnemies(float deltaTime);
