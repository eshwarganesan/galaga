#include "Player.h"
#include "2D_graphics.h"
#include <iostream>
#include "timer.h"


using namespace std;


Player::Player(char *filename) {
	xPosition = 640;
	yPosition = 30;
	scale = 0.7;
	angle = 0;
	speed = 500.0;
	exploding = false;
	alive = true;
	animationStartTime = 0;
	height = 65 * scale;
	width = 98 * scale;

	create_sprite(filename, player_id);
	create_sprite("/sprites/player_Explosion3.png", explosion_id[0]);
	create_sprite("/sprites/player_Explosion4.png", explosion_id[1]);
}

void Player::draw() {
	if (exploding) {
		double elapsedTime = high_resolution_time() - animationStartTime;
		if (elapsedTime < 0.0333) {
			draw_sprite(explosion_id[0], xPosition, yPosition, angle, 1);
		}
		else if (elapsedTime < 0.0666) {
			draw_sprite(explosion_id[1], xPosition, yPosition, angle, 1);
		}
		else {
			this->alive = false;
		}
	}
	else {
		draw_sprite(player_id, xPosition, yPosition, angle, scale);
	}
	
}

void Player::move(double direction, double deltaTime) {
	double dx = speed * direction * deltaTime;

	if (this->xPosition + dx <= 35) {
		this->xPosition = 35;
		cout << "\nMoving player - X: " << this->xPosition;
		return;
	}
	if (this->xPosition + dx >= 1245) {
		this->xPosition = 1245;
		cout << "\nMoving player - X: " << this->xPosition;
		return;
	}
	
	this->xPosition += dx;
	cout << "\nMoving player - X: " << this->xPosition;

}

void Player::shoot(std::vector<Bullet>& bullets) {
	bullets.push_back(Bullet("/sprites/PNG/Lasers/laserRed14.png", xPosition, yPosition + 20, 500.0));
}

void Player::death_animation() {
	this->exploding = true;
	this->animationStartTime = high_resolution_time();
}

std::vector<Vector2> Player::getVertices() {
	std::vector<Vector2> vertices;

	// Assume ship points upward and is equilateral for simplicity
	vertices.push_back({ xPosition, yPosition + height / 2 });      // Top vertex
	vertices.push_back({ xPosition - width / 2, yPosition - height / 2 }); // Bottom left
	vertices.push_back({ xPosition + width / 2, yPosition - height / 2 }); // Bottom right

	return vertices;
}