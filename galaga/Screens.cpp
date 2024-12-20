
#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <Windows.h>

#include "2D_graphics.h"

#include "timer.h"
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")

using namespace std;
//Question 2.1
int main()
{
	int id_projectile, id_turret, world_id, GameOver_id, Victory_id, intro_id;
	initialize_graphics();
	clear();
	create_sprite("Gameover_screen.JPG", GameOver_id);
	create_sprite("Victory_screen.JPG", Victory_id);
	create_sprite("Intro_screen.png", intro_id);
	double x, y, q, scale;

	x = 0.0;
	y = 0.0;
	q = 0.0;
	scale = -1.0;

	//Instruction background
	draw_sprite(intro_id, x, y, q, scale);
	//Instruction text
	x = 440;
	y = 550;
	scale = 1;

	text("GALAGA - SPACESHOOTER", x, y, scale);

	y -= 60;

	text("To move, you can use the 'A' and 'D' keys to move left and right", x, y, scale);

	y -= 60;

	text(Use 'L' to shoot bullets, x, y, scale);

	y -= 60;

	text("Many different types of enemies will attack you in different waves", x, y, scale);

	y -= 30;
	text("Beware as different enemies have different abilities and movement", x, y, scale);

	y -= 60;

	text("You're given three lives to complete all waves", x, y, scale);

	y -= 60;

	text("Press any button to begin", x, y, scale);

	y -= 60;

	text("Goodluck!", x, y, scale);

	update();

	while (1) {
		getchar();
		break;
		clear();
	}
	/*
	x = 0;
	y = 0;
	draw_sprite(Victory_id, x, y, q, scale);
	update();
		while (1) {
			getchar();
			break;
			clear();
		}
		draw_sprite(GameOver_id, x, y, q, scale);
		update();
		while (1) {
			getchar();
			break;
		}
		*/
}
