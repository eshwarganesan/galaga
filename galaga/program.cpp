
#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>
#include "Bullet.h"
#include <vector>
#include "timer.h"
#include "Enemy.h"
#include "ran.h"
#include <Windows.h> // also needed for the 2D graphics library
#include "Player.h"

#include "2D_graphics.h" // use the 2D graphics library
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#include "timer.h" // use the time / clock reading function

using namespace std;

bool checkCollision(std::vector<Vector2>& hitbox1, std::vector<Vector2>& hitbox2);
std::pair<double, double> project(const std::vector<Vector2>& shape, const Vector2& axis);
bool overlap(double minA, double maxA, double minB, double maxB);
void play_sound(char* filename);
void spawnWave(std::vector<Enemy>& enemies, long int wave);

//Eshwar and Patrick
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
    clear();
    //background sprite
    int background_id, intro_id;
    create_sprite("Intro_screen.png", intro_id);
    //create_sprite("/sprites/Backgrounds/black.png", background_id);
    create_sprite("/sprites/Background3.png", background_id);
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

    text("Use 'L' to shoot bullets", x, y, scale);

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
    Player* spaceship = new Player("/sprites/PNG/playerShip3_red.png");

    std::vector<Bullet> player_bullets;
    std::vector<Bullet> enemy_bullets;
    std::vector<Enemy> enemies;

    double lives = 3;
    double score = 0;
    long int wave = 1;
    update();

    double lastTime = high_resolution_time();
    double lastFire = high_resolution_time();
    
    spawnWave(enemies, wave);

    double fps = 0.0;
    while (true) {
        clear();
        //background
        draw_sprite(background_id, 640, 360, 0, 5);
        text("Lives: ", 10, 700, 0.4);
        text(lives, 80, 700, 0.4);
        text("Score: ", 10, 680, 0.4);
        text(score, 90, 680, 0.4);
        text("Wave: ", 10, 660, 0.4);
        text(wave, 90, 660, 0.4);
        double currentTime = high_resolution_time();
        double delta = currentTime - lastTime;
        double fireDelay = currentTime - lastFire;
        lastTime = currentTime;
        spaceship->draw();
        
        /*
        if (delta > 0) {
            fps = 1.0 / delta;
        }

        cout << "\nFPS: " << fps << "\r";

        for (auto& enemy : enemies) {
            enemy.draw();
        }
        */

        if (enemies.size() == 0) {
            if (wave < 5) {
                wave += 1;
                spawnWave(enemies, wave);
                player_bullets.clear();
                enemy_bullets.clear();
                Sleep(4000);
                spaceship->respawn();
            }
            else {
                player_bullets.clear();
                enemy_bullets.clear();
                Sleep(4000);
                break;
            }
        }

        for (auto& enemy : enemies) {
            enemy.draw();
        }

        for (auto& bullet : player_bullets) {
            bullet.draw();
        }
        for (auto& enemy_bullet : enemy_bullets) {
            enemy_bullet.draw();
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
        //check collision of player bullets
        for (auto it = player_bullets.begin(); it != player_bullets.end(); ) {
            it->update(delta);

            if (it->outOfScreen()) {
                it = player_bullets.erase(it); // Safe erase
            }
            else {
                bool collided = false;
                for (auto enemy_it = enemies.begin(); enemy_it != enemies.end(); ) {
                    if (checkCollision(it->getVertices(), enemy_it->getVertices())) {
                        enemy_it = enemies.erase(enemy_it);
                        collided = true;
                        score += 1;
                    }
                    else {
                        ++enemy_it;
                    }
                }
                if (collided) {
                    it = player_bullets.erase(it); // Remove the bullet only once
                }
                else {
                    ++it;
                }
            }
        }
        //check collision of enemy bullets
        for (auto& enemy_bullet : enemy_bullets) {
            enemy_bullet.update(delta);
            if (enemy_bullet.outOfScreen()) {
                enemy_bullets.erase(std::remove(enemy_bullets.begin(), enemy_bullets.end(), enemy_bullet), enemy_bullets.end());
            }
            if (checkCollision(spaceship->getVertices(), enemy_bullet.getVertices()) && spaceship->exploding == false) {
                spaceship->death_animation();
                lives--;
                break;
            }
        }
        //check collision of enemies with players
        for (auto& enemy : enemies) {
            if (checkCollision(spaceship->getVertices(), enemy.getVertices()) && spaceship->exploding == false) {
                spaceship->death_animation();
                lives--;
                break;
            }
        }
        
        update();
        if (spaceship->alive == false) {
            if (lives > 0) {
                spaceship->respawn();
                Sleep(3000);
            }
            else {
                break;
            }
        }
    }
    
    delete spaceship;
	return 0;
}
//Eshwar
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
//Eshwar
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
//Eshwar
bool overlap(double minA, double maxA, double minB, double maxB) {
    return !(minA > maxB || minB > maxA);
}
//Eshwar
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

//Eshwar and Patrick
void spawnWave(std::vector<Enemy>& enemies, long int wave) {

    switch (wave) {
    case 1:
        //5 stationary enemies
        for (int i = 0; i < 5; ++i) {
            enemies.push_back(Enemy("enemyBlack1.png", 200 + i * 100, 400)); // Spread out horizontally
        }
        break;
    case 2:
        //8 stationary enemies
        for (int i = 0; i < 8; ++i) {
            int row = i < 4 ? 0 : 1;
            enemies.push_back(Enemy("enemyBlack1.png", 150 + (i % 5) * 100, 100 + row * 50)); // Spread out horizontally
        }
        break;
    case 3:
        //3 swirling enemies
        for (int i = 0; i < 3; ++i) {
            enemies.push_back(Enemy("enemyBlack3.png", 300 + i * 200, 600));
        }
        break;
    case 4:
        //6 enemies, 2 moving side to side and 4 swirling
        for (int i = 0; i < 6; ++i) {
            enemies.push_back(Enemy("enemyBlack3.png", 150 + i * 200, 600));
        }
        break;
    case 5:
        //4 enemies moving in circles, 1 moving side to side
        for (int i = 0; i < 4; ++i) {
            enemies.push_back(Enemy("enemyBlack3.png", 300 + i * 200, 600));
        }
        break;
    }
}

void gameover() {
    initialize_graphics();
    int GameOver_id;
    clear();
    create_sprite("Gameover_screen.JPG", GameOver_id);
    double x, y, q, scale;

    x = 0.0;
    y = 0.0;
    q = 0.0;
    scale = -1.0;
    draw_sprite(GameOver_id, x, y, q, scale);
    update();
    while (1) {
        getchar();
        break;
    }
}

void Victory() {
    initialize_graphics();
    int Victory_id;
    clear();
    create_sprite("Victory_screen.JPG", Victory_id);
    double x, y, q, scale;

    x = 0.0;
    y = 0.0;
    q = 0.0;
    scale = -1.0;
    draw_sprite(Victory_id, x, y, q, scale);
    update();
    while (1) {
        getchar();
        break;
    }
}
void wave_number_png(int wave) {
    initialize_graphics();
    int wave_id[5];
    clear();
    create_sprite("Wave1.png", wave_id[0]);
    create_sprite("Wave2.png", wave_id[1]);
    create_sprite("Wave3.png", wave_id[2]);
    create_sprite("Wave4.png", wave_id[3]);
    create_sprite("Wave5.png", wave_id[4]);

    /*
    create_sprite("Wave6.png", wave_id[0]);
    create_sprite("Wave7.png", wave_id[0]);
    create_sprite("Wave8.png", wave_id[0]);
    create_sprite("Wave9.png", wave_id[0]);
    create_sprite("Wave10.png", wave_id[0]);
    */

    double x, y, q, scale;
    x = 0.0;
    y = 0.0;
    q = 0.0;
    scale = 1.0;
    draw_sprite(wave_id[wave], x, y, q, scale);
    update();
    while (1) {
        getchar();
        break;
    }
}