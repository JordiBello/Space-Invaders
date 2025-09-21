#include <raylib.h>
#include "ship.h"
#include "enemy.h"
#include <vector>
#include <set>

#define MIN(a, b) ((a)<(b)? (a):(b))

#define VIRTUAL_WIDTH 1980
#define VIRTUAL_HEIGHT 1080



void drawEnemies(std::vector<Enemy> enemies);
void checkCollisionEnemies(const std::vector<Enemy> &enemies, Enemy &enemy);
void moveEnemies(std::vector<Enemy> &enemies);
void checkEnemyStatus(std::vector<Enemy> &enemies);

int main() 
{
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Space Invaders COPY :D");
    InitAudioDevice();

    SetTargetFPS(60);

    Ship ship = Ship();

    RenderTexture2D target = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT); // evita blur

    std::vector<Enemy> enemies;
    Image enemy_image = LoadImage("assets/enemy-1.png");
    Texture2D enemy_texture = LoadTextureFromImage(enemy_image);
    SetTextureFilter(enemy_texture, TEXTURE_FILTER_POINT);
    float enemy_timer = 1.0f;


    while (!WindowShouldClose())
    {
        checkEnemyStatus(enemies);
        float dt = GetFrameTime();
        enemy_timer += dt;
        if(enemy_timer >= ENEMY_COOLDOWN_SPAWN){
            Enemy enemy = Enemy(enemy_texture);
            checkCollisionEnemies(enemies, enemy);
            enemies.push_back(enemy);
            enemy_timer = 0.0f;
        }

        ship.moveShip();
        ship.shootLaser(enemies);
        
        moveEnemies(enemies);

        BeginTextureMode(target);
            ClearBackground(BLACK);
            ship.drawShip();
            ship.drawLasers();
            drawEnemies(enemies);

        EndTextureMode();

                // --- Escalar a la ventana real ---
        BeginDrawing();
            ClearBackground(BLACK);

            float scale = MIN(
                (float)GetScreenWidth()/VIRTUAL_WIDTH,
                (float)GetScreenHeight()/VIRTUAL_HEIGHT
            );


            Rectangle src = { 0, 0, (float)target.texture.width, -(float)target.texture.height };
            Rectangle dest = {
                (GetScreenWidth() - VIRTUAL_WIDTH*scale)/2,
                (GetScreenHeight() - VIRTUAL_HEIGHT*scale)/2,
                VIRTUAL_WIDTH*scale,
                VIRTUAL_HEIGHT*scale
            };

            DrawTexturePro(target.texture, src, dest, {0,0}, 0.0f, WHITE);

        EndDrawing();
    }
    
    // Liberar recursos
    UnloadRenderTexture(target);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}


void drawEnemies(std::vector<Enemy> enemies){
    
    for (unsigned long long i = 0; i < enemies.size(); i++){
        enemies[i].drawEnemy();
    }
}

void checkCollisionEnemies(const std::vector<Enemy> &enemies, Enemy &enemy){
    
    bool collision;
    do {
        collision = false;
        for (size_t i = 0; i < enemies.size(); i++) {
            if (CheckCollisionRecs(enemy.getEnemyBox(), enemies[i].getEnemyBox())) {
                // Recolocar y volver a comprobar
                enemy.setPosition({
                    (float)GetRandomValue(0, VIRTUAL_WIDTH - enemy.getWidth()),
                    enemy.getPosition().y
                });
                collision = true;
                break; // salir del for y volver a comprobar
            }
        }
    } while (collision);
}

void moveEnemies(std::vector<Enemy> &enemies){
    for (size_t i = 0; i < enemies.size(); i++){
        enemies[i].moveEnemy();
    }
}

void checkEnemyStatus(std::vector<Enemy> &enemies){
    for (size_t i = 0; i < enemies.size(); i++){
        if (enemies[i].needDestroy()){
            enemies[i] = enemies.back();
            enemies.pop_back();
            i--;
        }
    }
}