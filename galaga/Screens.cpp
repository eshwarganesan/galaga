
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
	x = 50;
	y = 550;
	scale = 0.5;

	text("Welcome to the game!", x, y, scale);

	y -= 60;

	text("Use 'A' and 'D' to move left and right", x, y, scale);

	y -= 60;

	text("Tap Space to jump, Shift to dash, and Control to roll", x, y, scale);

	y -= 60;

	text("You can leap through the orange platforms", x, y, scale);

	y -= 30;
	text("and tap 'S' to fall through them", x, y, scale);

	y -= 60;

	text("Make your way past the enemies and reach the golden coin!", x, y, scale);

	y -= 60;

	text("Press Enter when you're ready to begin", x, y, scale);

	y -= 60;

	text("p.s. the walls are sticky", x, y, scale);

	update();

	while (1) {
		getchar();
		break;
		clear();
	}
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
}
