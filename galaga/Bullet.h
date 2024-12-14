#pragma once
class Bullet
{
public:
	Bullet(char* filename, double xPosition, double yPosition, double speed);

	void draw();

	void update(double deltaTime);

	bool outOfScreen();

	bool operator==(const Bullet& other);

private:
	double x, y, v, scale;
	int id;
};

