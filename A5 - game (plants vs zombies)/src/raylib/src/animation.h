#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "general.h"
#include "sprite.h"

typedef struct Animation {
    Texture2D texture;
    Rectangle* frameRec;
    int frameCount;
    int timesPlayedPerSecond;
} Animation;

void initAnimation(Animation* anim, char* filename, int frameCount,
                   int timesPlayedPerSecond);

void exitAnimation(Animation* anim);

void generateFrameRecFromTexture(Texture2D texture, Rectangle* frameRec,
                                 int frameCount);

void updateAnimation(Animation* anim, float* currentFrame);

void drawAnimationPro(Animation* anim, float currentFrame, Vector2 position,
                      float rotation, float scale, Color tint);

void drawAnimation(Animation* anim, float currentFrame, Vector2 position);

typedef struct movableObject {
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float scale;
    float currentFrame;
    int animCount;
    Animation* anim;
} movableObject;

void drawMovableObjectFromAnimation(movableObject* obj, int animIndex);

void updateMovableObjectFromAnimation(movableObject* obj, int animIndex);

#endif // ANIMATION_H_
