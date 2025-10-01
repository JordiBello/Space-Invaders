#include <raylib.h>
#include "ship.h"
#include "enemy_cylon.h"
#include "enemy_xenomorph.h"
#include <vector>
#include <set>
#include <memory>
#define MIN(a, b) ((a)<(b)? (a):(b))

#define VIRTUAL_WIDTH 1980
#define VIRTUAL_HEIGHT 1080

#define FACTORY_INDEX_ENEMY [Cylon, Xenomorph]

void drawEnemies(const std::vector<std::unique_ptr<Enemy>> &enemies);
void checkCollisionEnemies(const std::vector<std::unique_ptr<Enemy>> &enemies, Enemy &enemy);
void moveEnemies(std::vector<std::unique_ptr<Enemy>> &enemies);
void checkEnemyStatus(std::vector<std::unique_ptr<Enemy>> &enemies);
std::unique_ptr<Enemy> createEnemy(const std::vector<std::unique_ptr<Enemy>> &enemies, const Texture2D &enemy_texture);

int main() 
{
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Space Invaders COPY :D");
    InitAudioDevice();

    SetTargetFPS(60);

    Ship ship = Ship();

    RenderTexture2D target = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT); // evita blur

    std::vector<std::unique_ptr<Enemy>> enemies;
    Image enemy_image = LoadImage("assets/enemy-1.png");
    Texture2D enemy_texture = LoadTextureFromImage(enemy_image);
    SetTextureFilter(enemy_texture, TEXTURE_FILTER_POINT);
    float enemy_timer = 1.0f;

    Font font = LoadFont("assets/fonts/Nowadays Italic.ttf");

    while (!WindowShouldClose())
    {
        // ------------------ ENEMY UPDATES -----------------------------
        checkEnemyStatus(enemies);

        // Enemy creation every second
        float dt = GetFrameTime();
        enemy_timer += dt;
        if(enemy_timer >= ENEMY_COOLDOWN_SPAWN){
            auto enemy = createEnemy(enemies, enemy_texture);
            
            
            checkCollisionEnemies(enemies, *enemy);
            enemies.push_back(std::move(enemy));
            enemy_timer = 0.0f;
        }
        moveEnemies(enemies);


        // ----------------- PLAYER'S SHIP UPDATE ---------------------------
        ship.moveShip();
        ship.shootLaser(enemies);


        
        // ----------------- DRAWING ----------------------------------------
        BeginTextureMode(target);
            ClearBackground(BLACK);
            ship.drawShip();
            ship.drawLasers();
            drawEnemies(enemies);
            //ship.drawPoints(font);
            DrawTextEx(font, "PRUEBA TEXTO 12345", {200, 200}, 56, 2, YELLOW);
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


std::unique_ptr<Enemy> createEnemy(const std::vector<std::unique_ptr<Enemy>> &enemies, const Texture2D &enemy_texture){
    
    // Random type of enemy generation
    switch (GetRandomValue(0, 4))
    {
    case 0 || 1 || 2 || 3:
        return std::make_unique<Cylon>(enemy_texture);    
    case 4:
        return std::make_unique<Xenomorph>(enemy_texture);
    default:
        return nullptr;
    }
}


void drawEnemies(const std::vector<std::unique_ptr<Enemy>> &enemies){
    
    for (unsigned long long i = 0; i < enemies.size(); i++){
        enemies[i]->drawEnemy();
    }
}

void checkCollisionEnemies(const std::vector<std::unique_ptr<Enemy>> &enemies, Enemy &enemy){
    
    bool collision;
    do {
        collision = false;
        for (size_t i = 0; i < enemies.size(); i++) {
            if (CheckCollisionRecs(enemy.getEnemyBox(), enemies[i]->getEnemyBox())) {
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

void moveEnemies(std::vector<std::unique_ptr<Enemy>> &enemies){
    for (size_t i = 0; i < enemies.size(); i++){
        enemies[i]->moveEnemy();
    }
}

void checkEnemyStatus(std::vector<std::unique_ptr<Enemy>> &enemies){
    for (size_t i = 0; i < enemies.size(); i++){
        if (enemies[i]->needDestroy()){
            enemies[i] = std::move(enemies.back());
            enemies.pop_back();
            i--;
        }
    }
}