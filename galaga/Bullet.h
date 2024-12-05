#pragma once
class Bullet
{
public:
	Bullet(double xPosition, double yPosition, double speed, bool enemy);
	void draw();
private:
	double x, y;
};

