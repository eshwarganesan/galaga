#include "Bullet.h"
#include "2D_graphics.h"
#include <iostream>

using namespace std;

Bullet::Bullet(char* filename, double xPosition, double yPosition, double speed) {
	x = xPosition;
	y = yPosition;
	v = speed;
	scale = 0.3;

	create_sprite(filename, id);
	cout << "Bullet created at X: " << x << ", Y: " << y << "\n";
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
	return y > 780;
}

bool Bullet::operator==(const Bullet& other) {
	return (x == other.x && y == other.y);
}
