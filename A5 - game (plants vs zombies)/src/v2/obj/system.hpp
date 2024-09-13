#pragma once

#include "global.hpp"

enum State {
    IN_GAME,
    PAUSE_MENU,
    MAIN_MENU,
    LEVEL_SELECT,
    VICTORY_SCREEN,
    GAMEOVER_SCREEN,
    CREDITS,
    EXIT
};

class System {
public:
    System(int width, int height);
    void run();
    ~System();
    RenderWindow window;

private:
    State state;
    void update();
    void render();
    void handle_events();
    void handle_key_up(Keyboard::Key key);
    void handle_key_down(Keyboard::Key key);
    void handle_mouse_press(Event ev);
    void handle_mouse_release(Event ev);

    Vector2i circlePos = {200, 100};
    int circleR = 50;

    bool drag = 0;
};