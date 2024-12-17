#include "Player.h"
#include "2D_graphics.h"
#include <iostream>


using namespace std;


Player::Player(char *filename) {
	xPosition = 640;
	yPosition = 30;
	scale = 0.7;
	angle = 0;
	speed = 500.0;

	height = 65 * scale;
	width = 98 * scale;

	create_sprite(filename, player_id);
}

void Player::draw() {
	draw_sprite(player_id, xPosition, yPosition, angle, scale);
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

void Player::death(int frame) {
	draw_sprite(explosion_id[frame], xPosition, yPosition, angle, scale);
}

std::vector<Vector2> Player::getVertices() {
	std::vector<Vector2> vertices;

	// Assume ship points upward and is equilateral for simplicity
	vertices.push_back({ xPosition, yPosition + height / 2 });      // Top vertex
	vertices.push_back({ xPosition - width / 2, yPosition - height / 2 }); // Bottom left
	vertices.push_back({ xPosition + width / 2, yPosition - height / 2 }); // Bottom right

	return vertices;
}