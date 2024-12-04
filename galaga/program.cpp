
#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h> // also needed for the 2D graphics library
#include "Player.h"
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
	
    update();

    while (true) {
        clear();
        spaceship->draw();
        if (KEY('A')) {
            spaceship->move(-2);
        }
        if (KEY('D')) {
            spaceship->move(2);
        }

    }

	return 0;
}

