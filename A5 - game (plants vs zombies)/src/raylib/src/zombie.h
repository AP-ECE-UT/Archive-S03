#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "animation.h"
#include "general.h"

#define ZOMBIE_ANIM_CNT 6
enum ZOMBIE_ENUM {
    ZOMBIE_IDLE,
    ZOMBIE_EAT,
    ZOMBIE_WALK,
    ZOMBIE_HURT_WALK,
    ZOMBIE_HURT_EAT,
    ZOMBIE_DIE
};

extern char* zombiePngFilePath[ZOMBIE_ANIM_CNT];
extern int zombieFrameCnt[ZOMBIE_ANIM_CNT];
extern int zombieTimesPlayedPerSecond[ZOMBIE_ANIM_CNT];
extern Animation zombieAnim[ZOMBIE_ANIM_CNT];

void initZombieVariables();
void exitZombieVariables();

#endif // ZOMBIE_H_
