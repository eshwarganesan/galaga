#include "Enemy.h"
#include "2D_graphics.h"
#include <iostream>
#include <windows.h>
#include "timer.h" // use the time / clock reading function
using namespace std;





 Enemy::Enemy(char *file_name, double xPosition1, double yPosition1,int type) {
	yPosition = yPosition1;
	xPosition = xPosition1;
	scale = 0.90;
	angle = 0;
	speed = 500.0;
	height = 86*scale;
	width = 86*scale;
	this->type = type;
	exploding = false;
	alive = true;
	create_sprite(file_name, enemy_id);
	create_sprite("/sprites/player_Explosion3.png", explosion_id[0]);
	create_sprite("/sprites/player_Explosion4.png", explosion_id[1]);
}

void Enemy::draw() {
	if (exploding) {
		double elapsedTime = high_resolution_time() - animationStartTime;
		if (elapsedTime < 0.0333) {
			draw_sprite(explosion_id[0], xPosition, yPosition, angle, 1);
		}
		else if (elapsedTime < 0.0666) {
			draw_sprite(explosion_id[1], xPosition, yPosition, angle, 1);
		}
		else {
			alive = false;
		}
	}
	else if (alive) {
		draw_sprite(enemy_id, xPosition, yPosition, angle, scale);
	}
	
}
/*
void Enemy::spawn(float xPosition) {
	if (yPosition <= 300) {
		return;
	}
	this->yPosition -= 1;
	return;

}
*/
void Enemy::move(float speed, float deltaTime) { // range of speed should be between 1 to 10
	//5 different movement methods so 5 different types
	//1 - left and right
	//2 - up and down
	//3 - zigzag downwards - comes back at initial position
	//4 - zigzag laterally
	//5 - circle swirl downwards - comes back at initial position
	//6 - no movement
	if(type==1){ 
		if (movingRight) {
			this->xPosition = xPosition + speed;
			if (this->xPosition >= 1200) {
				movingRight = false;
				return;
			}
			return;
		}
		else {
			this->xPosition = xPosition - speed;
			if (this->xPosition <= 50) {
				movingRight = true;
				return;
			}
			return;
		}
	}
	else if (type == 2) {
		if (attacking) {
			yPosition = yPosition + speed;
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
	else if (type == 3) {
		static double angle = 0.0; 
		double radius = 100.0;    
		yPosition = yPosition;
		angle += 0.05;
		if (attacking) {
			this->xPosition = xPosition + radius * sin(angle);
			this->yPosition -= 25 * speed * deltaTime;
			if (this->yPosition <= 50) {
				yPosition = y;
				attacking = false;
				return;
			}
		}
		else {
			this->xPosition = xPosition + radius * sin(angle);
		}
	}
	else if (type ==4){
		if (movingRight && attacking) {
			this->xPosition = xPosition + speed;
			this->yPosition = yPosition - speed;
			if (this->xPosition >= 1200) {
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
			if (this->xPosition <= 50) {
				movingRight = true;
				return;
			}
			return;
		}
	}
	else if (type == 5) {
		double radius = 100;
		for (int i = 1; i <= 360; i++) {
			angle += 2.0 * i * 10e-8;
			if (attacking) {
				this->xPosition = xPosition + radius * sin(angle * speed);
				this->yPosition = yPosition + radius * cos(angle * speed) - 20 * speed * deltaTime;
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
	else if (type == 6) {
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

Enemy::~Enemy() {
	cout << "\nDestroying Enemy";
	return;
}

void Enemy::death_animation() {
	this->exploding = true;
	this->animationStartTime = high_resolution_time();
}