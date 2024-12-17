
#include <iostream>
#include <cstdio>
#include <cmath>
#include "Bullet.h"
#include <vector>
#include "timer.h"
#include "Enemy.h"

#include <Windows.h> // also needed for the 2D graphics library
#include "Player.h"
#include "World.h"
#include "2D_graphics.h" // use the 2D graphics library

#include "timer.h" // use the time / clock reading function

using namespace std;


int main()
{
	/*const char* directXWindow = "..\\DirectX_Window\\DirectX_window.exe";
    
    STARTUPINFOA startupInfo = { sizeof(startupInfo) };
    PROCESS_INFORMATION processInfo = {};

    if (CreateProcessA(directXWindow, nullptr, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &startupInfo, &processInfo)) {
        std::cout << "\nDirectX window open";

    }
    else {
        std::cerr << "\nFailed to open DirectX window \n" << GetLastError();
    }
    */
    initialize_graphics();
	Player* spaceship = new Player("Player_Spaceship.png");
    Enemy* enemy1 = new Enemy("enemyBlack1.png",500);
    Enemy* enemy2 = new Enemy("enemyBlack2.png",600);
    Enemy* enemy3 = new Enemy("enemyBlack3.png",200);
    Enemy* enemy4 = new Enemy("enemyBlack4.png",300);
    Enemy* enemy5 = new Enemy("enemyBlack5.png",400);
    std::vector<Bullet> bullets;
	
    update();

    double lastTime = high_resolution_time();
    double lastFire = high_resolution_time();
 

    while (true) {
        clear();
        double currentTime = high_resolution_time();
        double delta = currentTime - lastTime;
        double fireDelay = currentTime - lastFire;
        lastTime = currentTime;
        spaceship->draw();
        enemy1->draw();
        //enemy2->draw(); 
        //enemy3->draw();
        enemy4->draw();
        //enemy5->draw();
        enemy1->move();
        Sleep(200);
        //enemy2->move(1000);
        //enemy3->move(2000);
        enemy4->move();
        //enemy5->move(4000);

        for (auto& bullet : bullets) {
            bullet.draw();
        }
        if (KEY('A')) {
            spaceship->move(-1, delta);
        }
        if (KEY('D')) {
            spaceship->move(1, delta);
        }
        if (KEY('L') && fireDelay > 1) {
            spaceship->shoot(bullets);
            lastFire = currentTime;
        }
        if (KEY('P')) {
            break;
        }
        for (auto& bullet : bullets) {
            bullet.update(delta);
            if (bullet.outOfScreen()) {
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
            }
        }
 
        update();
    }

    delete spaceship;
	return 0;
}

void explosion(std::vector<Bullet> bullets, Player* player) {
    clear();
    for (auto& bullet : bullets) {
        bullet.draw();
    }
    //player->death();
}