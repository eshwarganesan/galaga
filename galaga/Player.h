#pragma once
#include <string>

class Player
{
public:
	Player(char *filename);
	void draw();
	void move(float dx);
	void shoot();
	int player_id;
private:
	double xPosition, yPosition;
	double scale, angle;
};

