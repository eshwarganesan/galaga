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
	Enemy(char* file_name, double xPosition1, double yPosition1,int type);
	~Enemy();
	bool down = true;
	bool movingRight = true;
	bool attacking = true;
	void draw();
	void spawn(float xPosition);
	void move(float speed,float deltaTime);
	void attack(float speed,float deltaTime);
	void swirl(float speed, float deltaTime, float x, float y);
	void circle(float speed, float deltaTime, float x, float y);
	void zigzag(float speed, float deltaTime);
	std::vector<Vector2> getVertices();
	void shoot(std::vector<Bullet>& bullets);
	void death(int frame);
	bool operator==(const Enemy& other) const;
	int enemy_id;
	int explosion_id[4];
	void sim_step(double dt);
	float x, y;
	float z=0;
	float last_time = 0;
	int type;
private:
	float speed;
	double xPosition, yPosition;
	double scale, angle;
	double height, width;
	
};

void SpawnEnemies();
void UpdateEnemies(float deltaTime);
