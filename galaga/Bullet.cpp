#include "Bullet.h"
#include "2D_graphics.h"
#include <iostream>

using namespace std;

Bullet::Bullet(char* filename, double xPosition, double yPosition, double speed) {
	x = xPosition;
	y = yPosition;
	v = speed;
	scale = 0.3;
	width = 13 * scale;
	height = 57 * scale;

	create_sprite(filename, id);
	cout << "\nBullet created at X: " << x << ", Y: " << y << "\n";
}

void Bullet::draw() {
	draw_sprite(id, x, y, 0, scale);
}

void Bullet::update(double deltaTime) {
	if (this->y < 1280) { // Move upward
		this->y += v * deltaTime;
	}
}

bool Bullet::outOfScreen() {
	return y > 780 || y < 0;
}

bool Bullet::operator==(const Bullet& other) {
	return (x == other.x && y == other.y);
}

std::vector<Vector2> Bullet::getVertices() {
	std::vector<Vector2> vertices;

	vertices.push_back({ x - width / 2, y - height / 2 });  // Top-left
	vertices.push_back({ x + width / 2, y - height / 2 });  // Top-right
	vertices.push_back({ x + width / 2, y + height / 2 });  // Bottom-right
	vertices.push_back({ x - width / 2, y + height / 2 });  // Bottom-left

	return vertices;
}