#include "Enemy.h"
#include "2D_graphics.h"
#include <iostream>
#include <windows.h>
using namespace std;
//10 stage design



std::vector<Waypoint> path = {
	{100, 0}, {150, 50}, {200, 100}, {250, 150}, {300, 200}
};

 Enemy::Enemy(char *file_name, double yPosition1) {
	yPosition = yPosition1;
	xPosition = 500;
	scale = 0.90;
	angle = 0;
	speed = 500.0;

	create_sprite(file_name, enemy_id);
}

void Enemy::draw() {
	draw_sprite(enemy_id, xPosition, yPosition, angle, scale);
}

void Enemy::move() {
	

	bool movingRight = true;
	if (movingRight) {
		xPosition++;
		return;
		if (yPosition >= 1280) {
			movingRight = false;
		}
		else {
			xPosition--;
			return;
			if (yPosition <= 0) {
				movingRight = true;
			}
		}
	}

}
