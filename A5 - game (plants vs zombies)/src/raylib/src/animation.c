#include "animation.h"

void initAnimation(Animation* anim, char* filename, int frameCount,
                   int timesPlayedPerSecond) {
    anim->texture = LoadTexture(filename);
    anim->frameRec = (Rectangle*)malloc(frameCount * sizeof(Rectangle));
    for (int i = 0; i < frameCount; i++) {
        anim->frameRec[i] = (Rectangle){(float)i * anim->texture.width / frameCount,
                                        0, (float)anim->texture.width / frameCount,
                                        anim->texture.height};
        /* anim->frameRec[i] = GetSpriteBounds(anim->texture, anim->frameRec[i]); */
    }
    anim->frameCount = frameCount;
    anim->timesPlayedPerSecond = timesPlayedPerSecond;
}

void exitAnimation(Animation* anim) {
    UnloadTexture(anim->texture);
    free(anim->frameRec);
}

void updateAnimation(Animation* anim, float* currentFrame) {
    (*currentFrame) +=
        anim->timesPlayedPerSecond * anim->frameCount * GetFrameTime();
    if (*currentFrame >= anim->frameCount) {
        *currentFrame = 0;
    }
}

void drawAnimationPro(Animation* anim, float currentFrame, Vector2 position,
                      float rotation, float scale, Color tint) {
    DrawTexturePro(
        anim->texture, anim->frameRec[(size_t)floor(currentFrame)],
        (Rectangle){position.x, position.y,
                    anim->frameRec[(size_t)floor(currentFrame)].width * scale,
                    anim->frameRec[(size_t)floor(currentFrame)].height * scale},
        (Vector2){anim->frameRec[(size_t)floor(currentFrame)].width * scale / 2,
                  anim->frameRec[(size_t)floor(currentFrame)].height * scale / 2},
        rotation, tint);
}

void drawAnimation(Animation* anim, float currentFrame, Vector2 position) {
    drawAnimationPro(anim, currentFrame, position, 0, 1, WHITE);
}

void drawMovableObjectFromAnimation(movableObject* obj, int animIndex) {
    drawAnimationPro(obj->anim + animIndex, obj->currentFrame, obj->position,
                     obj->rotation, obj->scale, WHITE);
}

void updateMovableObjectFromAnimation(movableObject* obj, int animIndex) {
    updateAnimation(obj->anim + animIndex, &obj->currentFrame);
}
