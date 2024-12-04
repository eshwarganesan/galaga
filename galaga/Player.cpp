#include "Player.h"
#include "2D_graphics.h"
#include <iostream>

using namespace std;

Player::Player(char *filename) {
	xPosition = 1780;
	yPosition = 100;
	scale = 0.2;
	angle = 0;

	create_sprite(filename, player_id);

}

void Player::draw() {
	draw_sprite(player_id, xPosition, yPosition, angle, scale);
	update();
}

void Player::move(float dx) {
	this->xPosition += dx;
	cout << "\nMoving player - X: " << this->xPosition;
}