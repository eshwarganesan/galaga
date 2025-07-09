#include "Enemy.h"
#include "2D_graphics.h"
#include <iostream>
#include <windows.h>
#include "timer.h" // use the time / clock reading function
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






Enemy::Enemy(char* file_name, double xPosition1, double yPosition1) {
	yPosition = yPosition1;
	xPosition = xPosition1;
	scale = 0.90;
	angle = 0;
	speed = 500.0;
	height = 86 * scale;
	width = 86 * scale;

	create_sprite(file_name, enemy_id);
}

void Enemy::draw() {
	draw_sprite(enemy_id, xPosition, yPosition, angle, scale);
}
void Enemy::spawn(float xPosition) {
	if (yPosition <= 300) {
		return;
	}
	this->yPosition -= 1;
	return;

}
void Enemy::move(float speed) { // range of speed should be between 1 to 10
	if (movingRight) {
		this->xPosition = xPosition + speed;
		if (this->xPosition >= 1000) {
			movingRight = false;
			return;
		}
		return;
	}
	else {
		this->xPosition = xPosition - speed;
		if (this->xPosition <= 200) {
			movingRight = true;
			return;
		}
		return;
	}
}
//Make start attack on a cycle like every 10s 
void Enemy::attack(float speed, float deltaTime) {


	if (attacking) {
		this->yPosition = yPosition + speed;
		if (this->yPosition >= 690) {
			attacking = false;
			return;
		}
		return;
	}
	else {
		this->yPosition = yPosition - speed;
		if (this->yPosition <= 50) {
			attacking = true;
			return;
		}
		return;
	}

}

void Enemy::swirl(float speed, float deltaTime, float x, float y) {
	static double angle = 0.0; // Angle for swirl movement
	double radius = 100.0;    // Swirl radius
	static float z = 680;     // Vertical reset position
	float start_time = deltaTime;
	yPosition = y;
	angle += 0.05;
	if (attacking) {
		// Increment angle for swirling


		// Update position with swirl pattern
		this->xPosition = x + radius * sin(angle);
		this->yPosition -= 25 * speed * deltaTime;

		// If the enemy reaches the top boundary, stop attacking
		if (this->yPosition <= 50) {
			yPosition = y;// Switch to moving upward
			attacking = false;
			return;
		}
	}

	else {

		//	this->yPosition += 50 * speed;
		this->xPosition = x + radius * sin(angle);


	}
}

void Enemy::circle(float speed, float deltaTime, float x, float y) {
	double radius = 100;
	for (int i = 1; i <= 360; i++) {
		angle += 2.0 * i * 10e-8;
		if (attacking) {
			//cout << "patrick says bye\n";


			this->xPosition = x + radius * sin(angle * speed);
			this->yPosition = y + radius * cos(angle * speed) - 20 * speed * deltaTime;
			//cout << "Patrick is tired\n " << z << ":\t" <<i;
			if (this->yPosition <= 50) {
				attacking = false;
				this->yPosition += 100;
				this->yPosition += 100;
				this->yPosition += 100;
				return;
			}
		}

		else {
			if (this->yPosition >= 690) {
				attacking = true;
			}
			this->xPosition = x + radius * sin(angle * speed);
			this->yPosition = y + radius * cos(angle * speed);
			this->yPosition = yPosition + 5 * speed;

		}
	}

}



/* Use this for it to go straight up and come back down for some reason
else {
	this->yPosition = yPosition + 20 * speed;
	if (this->yPosition >= 690) {
	for (int i = 1; i <= 360; i++) {
		angle += 2.0 * i * 10e-8;
		this->xPosition = x + radius * sin(angle * speed);
		this->yPosition = yPosition*2 - radius * cos(angle * speed) - 20 * speed * this_time;
		attacking = true;
		return;
	}
}
*/



void Enemy::zigzag(float speed, float deltaTime) {
	if (movingRight && attacking) {
		this->xPosition = xPosition + speed;
		this->yPosition = yPosition - speed;
		if (this->xPosition >= 1000) {
			movingRight = false;
			return;
		}
		if (this->yPosition <= 50) {
			attacking = false;
			return;
		}
		return;
	}
	if (attacking == false) {
		this->yPosition = yPosition + speed;
		if (this->yPosition >= 690) {
			attacking = true;
			return;
		}
		return;
	}
	if (movingRight == false) {
		this->xPosition = xPosition - speed;
		if (this->xPosition <= 200) {
			movingRight = true;
			return;
		}
		return;
	}

}


void Enemy::shoot(std::vector<Bullet>& bullets) {
	bullets.push_back(Bullet("/sprites/PNG/Lasers/laserRed14.png", xPosition, yPosition - 40, -500.0));
}

std::vector<Vector2> Enemy::getVertices() {
	std::vector<Vector2> vertices;

	// Assume ship points upward and is equilateral for simplicity
	vertices.push_back({ xPosition - width / 2, yPosition + height / 2 });      // Top left vertex
	vertices.push_back({ xPosition + width / 2, yPosition + height / 2 }); // Top right 
	vertices.push_back({ xPosition + width / 2, yPosition - height / 2 }); // Bottom right
	vertices.push_back({ xPosition - width / 2, yPosition - height / 2 });      // bot left vertex
	return vertices;
}

bool Enemy::operator==(const Enemy& other) const {
	return this->xPosition == other.xPosition && this->yPosition == other.yPosition;
}