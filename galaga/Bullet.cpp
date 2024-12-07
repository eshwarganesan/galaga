#include "Bullet.h"
#include "2D_graphics.h"

Bullet::Bullet(char* filename, double xPosition, double yPosition, double speed) {
	x = xPosition;
	y = yPosition;
	v = speed;

	create_sprite(filename, id);
}