#pragma once
class Bullet
{
public:
	Bullet(char* filename, double xPosition, double yPosition, double speed);

	void draw();
private:
	double x, y, v;
	int id;
};

