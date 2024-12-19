
#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include "Bullet.h"
#include <vector>
#include "timer.h"
#include "Enemy.h"

#include <Windows.h> // also needed for the 2D graphics library
#include "Player.h"
#include "World.h"
#include "2D_graphics.h" // use the 2D graphics library
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#include "timer.h" // use the time / clock reading function

using namespace std;

bool checkCollision(std::vector<Vector2>& hitbox1, std::vector<Vector2>& hitbox2);
std::pair<double, double> project(const std::vector<Vector2>& shape, const Vector2& axis);
bool overlap(double minA, double maxA, double minB, double maxB);
void play_sound(char* filename);

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
    //background sprite
    int background_id;
    //create_sprite("/sprites/Backgrounds/black.png", background_id);
    create_sprite("/sprites/Background3.png", background_id);
    Player* spaceship = new Player("/sprites/PNG/playerShip3_red.png");
    Enemy* enemy1 = new Enemy("enemyBlack1.png", 500,500);
    Enemy* enemy4 = new Enemy("enemyBlack4.png", 300,700);
    Enemy* enemy2 = new Enemy("enemyBlack2.png", 300, 600);
    Enemy* enemy3 = new Enemy("enemyBlack3.png", 400, 400);

    std::vector<Bullet> player_bullets;
    std::vector<Bullet> enemy_bullets;
    std::vector<Enemy> enemies;
	
    update();

    double lastTime = high_resolution_time();
    double lastFire = high_resolution_time();
    std::cout << "\nEnemy Hitbox: ";
    for (const auto& vertex : enemy1->getVertices()) {
        std::cout << "(" << vertex.x << ", " << vertex.y << ") ";
    }

    while (true) {
        clear();
        //background
        draw_sprite(background_id, 640, 360, 0, 5);
        double currentTime = high_resolution_time();
        double delta = currentTime - lastTime;
        double fireDelay = currentTime - lastFire;
        lastTime = currentTime;
        spaceship->draw();
        enemy1->draw();
        enemy4->draw();
        enemy2->draw();
        enemy3->draw();
     //   enemy1->attack(1, currentTime);
      //  enemy4->move(5);
        enemy2->swirl(1,currentTime,600,300); // use ufo PNG
      //  enemy3->zigzag(1, currentTime);
        
        /*
        for (auto& bullet : enemy_bullets) {
            bullet.draw();
        }
        for (auto& bullet : enemy_bullets) {
            bullet.update(delta);
            if (bullet.outOfScreen()) {
                cout << "\nBullet hit the top edge";
                enemy_bullets.erase(std::remove(enemy_bullets.begin(), enemy_bullets.end(), bullet), enemy_bullets.end());
            }
        }
        enemy4->shoot(enemy_bullets, 2000);
        */

        for (auto& bullet : player_bullets) {
            bullet.draw();
        }
        if (KEY('O')) {
            //enemy1->shoot(enemy_bullets);
        }
        if (KEY('A')) {
            spaceship->move(-1, delta);
        }
        if (KEY('D')) {
            spaceship->move(1, delta);
        }
        if (KEY('L') && fireDelay > 0.5) {
            spaceship->shoot(player_bullets);
            play_sound("Bullet_Shooting.wav");
            lastFire = currentTime;
        }
        if (KEY('P')) {
            spaceship->death_animation();
        }
        //check collision of player bullets
        for (auto& bullet : player_bullets) {
            bullet.update(delta);
            if (bullet.outOfScreen()) {
                cout << "\nBullet hit the top edge";
                player_bullets.erase(std::remove(player_bullets.begin(), player_bullets.end(), bullet), player_bullets.end());
            }
            if (checkCollision(bullet.getVertices(), enemy1->getVertices())) {
                cout << "\nCollision with enemy detected";
            }
        }
        //check collision of enemy bullets

        //check collision of enemies with players
        
        
        update();
        if (spaceship->alive == false) {
            break;
        }
    }
    
    delete spaceship;
    delete enemy1;
    delete enemy2;
    delete enemy3;
    delete enemy4;
	return 0;
}

bool checkCollision(std::vector<Vector2>& hitbox1, std::vector<Vector2>& hitbox2) {
    // Combine edges from both hitboxes
    std::vector<Vector2> axes;

    for (size_t i = 0; i < hitbox1.size(); ++i) {
        Vector2 edge = { hitbox1[(i + 1) % hitbox1.size()].x - hitbox1[i].x,
                         hitbox1[(i + 1) % hitbox1.size()].y - hitbox1[i].y };
        axes.push_back({ -edge.y, edge.x });  // Perpendicular normal
    }

    for (size_t i = 0; i < hitbox2.size(); ++i) {
        Vector2 edge = { hitbox2[(i + 1) % hitbox2.size()].x - hitbox2[i].x,
                         hitbox2[(i + 1) % hitbox2.size()].y - hitbox2[i].y };
        axes.push_back({ -edge.y, edge.x });
    }

    // Project both hitboxes onto each axis and check for overlap
    for (const auto& axis : axes) {
        auto resultA = project(hitbox1, axis);
        auto resultB = project(hitbox2, axis);

        double minA = resultA.first;
        double maxA = resultA.second;
        double minB = resultB.first;
        double maxB = resultB.second;

        if (!overlap(minA, maxA, minB, maxB)) {
            return false;  // No collision
        }
    }

    return true;  // Collision detected
}

std::pair<double, double> project(const std::vector<Vector2>& shape, const Vector2& axis) {
    double min = shape[0].x * axis.x + shape[0].y * axis.y;
    double max = min;

    for (const auto& vertex : shape) {
        double projection = vertex.x * axis.x + vertex.y * axis.y;
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }

    return std::make_pair(min, max);
}

bool overlap(double minA, double maxA, double minB, double maxB) {
    return !(minA > maxB || minB > maxA);
}

void play_sound(char *filename) {

    char* p_buffer{};
    int N_buffer{};

    char* p_data{};
    int N_data{};

    ifstream fin;
    fin.open(filename, ios::binary);

    if (!fin) {
        cout << "\nfile open error";
        return;
    }

    fin.seekg(0, ios::end);

    N_buffer = fin.tellg();

    fin.seekg(0, ios::beg);

    p_buffer = new char[N_buffer];

    if (p_buffer == NULL) {
        cout << "\ndynamic memory allocation error";
        return;
    }

    fin.read(p_buffer, N_buffer);

    fin.close();


    PlaySoundA(p_buffer, NULL, SND_MEMORY | SND_ASYNC);

    delete p_buffer;

}