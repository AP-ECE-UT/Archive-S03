#include "plant.h"

#include "animation.h"

char* plantPngFilePath[PLANT_ANIM_CNT] = {"assets/sunflower/idle.png"};
int plantFrameCnt[PLANT_ANIM_CNT] = {6};
int plantTimesPlayedPerSecond[PLANT_ANIM_CNT] = {2};
Animation plantAnim[PLANT_ANIM_CNT] = {0};

void initPlantVariables() {
    for (int i = 0; i < PLANT_ANIM_CNT; i++) {
        initAnimation(&plantAnim[i], plantPngFilePath[i], plantFrameCnt[i],
                      plantTimesPlayedPerSecond[i]);
    }
}

void exitPlantVariables() {
    for (int i = 0; i < PLANT_ANIM_CNT; i++) {
        exitAnimation(&plantAnim[i]);
    }
}
