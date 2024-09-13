#ifndef PLANT_H_
#define PLANT_H_

#include "animation.h"
#include "general.h"

#define PLANT_ANIM_CNT 1
enum PLANT_ENUM {
    PLANT_IDLE,
};

extern char* plantPngFilePath[PLANT_ANIM_CNT];
extern int plantFrameCnt[PLANT_ANIM_CNT];
extern int plantTimesPlayedPerSecond[PLANT_ANIM_CNT];
extern Animation plantAnim[PLANT_ANIM_CNT];

void initPlantVariables();
void exitPlantVariables();
#endif // PLANT_H_
