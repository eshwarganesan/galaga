#include "Player.h"
#include "2D_graphics.h"
#include <iostream>

using namespace std;


Player::Player(char *filename) {
	xPosition = 1280;
	yPosition = 100;
	scale = 0.2;
	angle = 0;
	speed = 500.0;

	create_sprite(filename, player_id);
}

void Player::draw() {
	draw_sprite(player_id, xPosition, yPosition, angle, scale);
}

void Player::move(double direction, double deltaTime) {
	double dx = speed * direction * deltaTime;

	if (this->xPosition + dx <= 60) {
		this->xPosition = 60;
		cout << "\nMoving player - X: " << this->xPosition;
		return;
	}
	if (this->xPosition + dx >= 1280) {
		this->xPosition = 1280;
		cout << "\nMoving player - X: " << this->xPosition;
		return;
	}
	
	this->xPosition += dx;
	cout << "\nMoving player - X: " << this->xPosition;

}

void Player::shoot(std::vector<Bullet>& bullets) {
	bullets.push_back(Bullet("spaceship.png", xPosition, yPosition, 500.0));
}

void Player::death(int frame) {
	draw_sprite(explosion_id[frame], xPosition, yPosition, angle, scale);
}