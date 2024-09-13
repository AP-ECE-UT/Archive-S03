#include "zombie.h"

#include "animation.h"

char* zombiePngFilePath[ZOMBIE_ANIM_CNT] = {
    "assets/zombie/idle.png", "assets/zombie/eat.png",
    "assets/zombie/walk.png", "assets/zombie/hurt-walk.png",
    "assets/zombie/hurt-eat.png", "assets/zombie/die.png"};
int zombieFrameCnt[ZOMBIE_ANIM_CNT] = {5, 7, 7, 7, 5, 9};
int zombieTimesPlayedPerSecond[ZOMBIE_ANIM_CNT] = {2, 1, 1, 1, 1, 1};
Animation zombieAnim[ZOMBIE_ANIM_CNT] = {0};

void initZombieVariables() {
    for (int i = 0; i < ZOMBIE_ANIM_CNT; i++) {
        initAnimation(&zombieAnim[i], zombiePngFilePath[i], zombieFrameCnt[i],
                      zombieTimesPlayedPerSecond[i]);
    }
}

void exitZombieVariables() {
    for (int i = 0; i < ZOMBIE_ANIM_CNT; i++) {
        exitAnimation(&zombieAnim[i]);
    }
}
