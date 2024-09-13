#include "main.h"

#include "animation.h"
#include "plant.h"
#include "zombie.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "P v Z");

    initZombieVariables();
    initPlantVariables();
    movableObject zombie = {.position = {SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2},
                            .velocity = {0, 0},
                            .rotation = 0,
                            .scale = 4.0,
                            .currentFrame = 0,
                            .animCount = ZOMBIE_ANIM_CNT,
                            .anim = zombieAnim};

    movableObject plant = {.position = {SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT / 2},
                           .velocity = {0, 0},
                           .rotation = 0,
                           .scale = 4.0,
                           .currentFrame = 0,
                           .animCount = PLANT_ANIM_CNT,
                           .anim = plantAnim};

    int idx = 0;
    int idx2 = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_Q)) {
            break;
        }
        if (IsKeyPressed(KEY_J)) {
            idx = (idx + 1) % ZOMBIE_ANIM_CNT;
            idx2 = (idx2 + 1) % PLANT_ANIM_CNT;
        }
        if (IsKeyPressed(KEY_K)) {
            idx = (idx - 1 + ZOMBIE_ANIM_CNT) % ZOMBIE_ANIM_CNT;
            idx2 = (idx2 - 1 + PLANT_ANIM_CNT) % PLANT_ANIM_CNT;
        }
        // Update
        updateMovableObjectFromAnimation(&zombie, idx);
        updateMovableObjectFromAnimation(&plant, idx2);

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        drawMovableObjectFromAnimation(&zombie, idx);
        drawMovableObjectFromAnimation(&plant, idx2);

        EndDrawing();
    }
    exitZombieVariables();
    exitPlantVariables();

    CloseWindow();
    return 0;
}
