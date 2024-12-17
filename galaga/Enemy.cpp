#include "Enemy.h"
#include "2D_graphics.h"
#include <iostream>
#include <windows.h>
using namespace std;
//10 stage design // 1, b and f// 2, downward // 3, swirl// 4, zig zag // 5 , I dont even know
//stage 1 tutorial like, passive enemies :black1 black2 x 5 enemies going back and forth
//stage 2 enemies start moving downwards to attack / black1, black2, g1, g2 with some going downwards at every X time
//stage 3 enemies start flying a little bit of swirl / g1,g2,g3 
//stage 4 same but faster // r1, r2, r3
//stage 5  blue1, blue2, blue 3, blue 4
//stage 6 r3, r4, bu4, bl3, bl4
//stage 7 g4, r4, bu4, bl4, gr2, r2, bu2, bl2,
//stage 8 g4, r4, bu4, bl4, gr2, r2, bu2, bl2, g5, r5,
//stage 9 bl1, bl2, bl3, bl4, bl5, bu1, bu2, bu3, bu4, bu5
//stage 10 All enemies go everywhere very chaotic, very hard to actually win, practically impossible




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
	if (movingRight) {
		this->xPosition++;
		if (this->xPosition >= 1000) {
			movingRight = false;
			return;
		}
		return;
	}
		else {
		this->xPosition--;
			if (this->xPosition <= 200) {
				movingRight = true;
				return;
			}
			return;
		}
}


