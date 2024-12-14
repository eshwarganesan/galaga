
#include <iostream>
#include <cstdio>
#include <cmath>
#include "Bullet.h"
#include <vector>
#include "timer.h"

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
	Player* spaceship = new Player("spaceship.png");
    std::vector<Bullet> bullets;
	
    update();

    double lastTime = high_resolution_time();

    while (true) {
        clear();
        double currentTime = high_resolution_time();
        double delta = currentTime - lastTime;
        lastTime = currentTime;
        spaceship->draw();
        for (auto& bullet : bullets) {
            bullet.draw();
        }
        if (KEY('A')) {
            spaceship->move(-1, delta);
        }
        if (KEY('D')) {
            spaceship->move(1, delta);
        }
        if (KEY('L')) {
            spaceship->shoot(bullets);
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

