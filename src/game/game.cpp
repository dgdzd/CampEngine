#include <game/game.h>

Game::Game(GLFWwindow* window, Screen* activeScreen, Level* activeLevel, GameStatus status) {
    srand((unsigned) time(NULL));
    this->status = status;
    this->activeScreen = activeScreen;
    this->window = window;
    this->activeLevel = activeLevel;
    this->frame = {
        CE_WINDOW_WIDTH,
        CE_WINDOW_HEIGHT
    };
    this->projection = glm::ortho(0.0f, static_cast<float>(CE_WINDOW_WIDTH), 0.0f, static_cast<float>(CE_WINDOW_HEIGHT), -1.0f, 1.0f);
    
    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCharCallback(window, char_callback);
    glfwSetKeyCallback(window, key_callback);
    
    pp = *rm.getPostProcessor("basic");
    
    activeGame = this;
}

void Game::update() {
    /* Rendering functions here */
    pp.start();

    if(status == GAME_PLAYING) {
        /* Render the entire level */
        activeLevel->update(projection);
    } else if(status == GAME_MENU) {
        /* Render the screen */
        activeScreen->render(projection);
    }
    pp.end();
    pp.render();
    
    tr->projection = projection;

    /* Events and buffer swap */
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::setActiveScreen(Screen* screen) {
    this->activeScreen = screen;
}

void Game::pause() {
    this->activeGame->status = GAME_PAUSED;
}

void Game::resume() {
    this->activeGame->status = GAME_PLAYING;
}

void Game::quit() {
    glfwSetWindowShouldClose(this->window, 1);
}

void Game::mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if(activeGame->mouse.xpos != xpos || activeGame->mouse.ypos != ypos) {
        class MouseMoveEvent event;
        event.mouseX = xpos;
        event.mouseY = ypos;
        SEND_MOUSE_EVENT(event);
    }
    activeGame->mouse.xpos = xpos;
    activeGame->mouse.ypos = ypos;
}

void Game::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    std::vector<int>* inputs = &activeGame->mouse.inputs;
    std::vector<int>* actions = &activeGame->mouse.actions;
    if(std::find(inputs->begin(), inputs->end(), button) == inputs->end()) {
        inputs->push_back(button);
        
        if(std::find(actions->begin(), actions->end(), action) == actions->end()) {
            actions->push_back(action);
        }
        
        switch(action) {
            case GLFW_PRESS: {
                std::cout << "click\n";
                class MouseClickEvent event;
                event.mouseX = activeGame->mouse.xpos;
                event.mouseY = activeGame->mouse.ypos;
                event.mouseButton = button;
                SEND_MOUSE_EVENT(event);
            }
            case GLFW_RELEASE: {
                if(Game::activeGame->mouse.releaseState) {
                    std::cout << "release\n";
                    class MouseReleaseEvent event_;
                    event_.mouseX = activeGame->mouse.xpos;
                    event_.mouseY = activeGame->mouse.ypos;
                    event_.mouseButton = button;
                    SEND_MOUSE_EVENT(event_);
                }
                inputs->erase(std::find(inputs->begin(), inputs->end(), button));
                Game::activeGame->mouse.releaseState = !Game::activeGame->mouse.releaseState;
            }
        }
    }
}

void Game::char_callback(GLFWwindow* window, unsigned int codepoint) {
    class CharacterInputEvent event;
    event.codepoint = codepoint;
    SEND_KEYBOARD_EVENT(event);
}

void Game::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS || action == GLFW_REPEAT) {
        class KeyPressEvent event;
        event.key = key;
        event.scancode = scancode;
        event.action = action;
        event.mods = mods;
        SEND_KEYBOARD_EVENT(event);
    }
}

Game* Game::activeGame;
