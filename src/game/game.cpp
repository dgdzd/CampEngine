#include <game/game.h>

Game::Game(GLFWwindow* window, Screen* activeScreen, Level* activeLevel, GameStatus status) {
    // Init libs
    init_libs();
    
    // Init each var
    TextRenderer::common = new TextRenderer(&ft.lib);
    this->tr = TextRenderer::common;
    
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
    this->actions = ActionMapper();
    
    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCharCallback(window, char_callback);
    glfwSetKeyCallback(window, key_callback);
    
    pp = *rm.getPostProcessor("basic");
    
    activeGame = this;
}

int Game::initialize() {
    if(init_libs() != 0) return 0;
    
    /* Create a window and it's OpenGL context */
    GLFWwindow* window = glfwCreateWindow(CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT, CE_WINDOW_TITLE, glfwGetPrimaryMonitor(), NULL);
    if (!window) {
        glfwTerminate();
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Checks if GLAD loaded well */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::CampEngine.error("Failed to initialize GLAD");
        return 0;
    }
    
    return 1;
}

int Game::init_libs() {
    ft = { FT_Library() };
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_DECORATED, false);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    if (FT_Init_FreeType(&ft.lib)) {
        Logger::CampEngine.error("Failed to initialize FreeType Library");
        return -1;
    }

    return 0;
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
        MouseMoveEvent event;
        event.mouseX = xpos;
        event.mouseY = ypos;
        SEND_EVENT(event);
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
                MouseClickEvent event;
                event.mouseX = activeGame->mouse.xpos;
                event.mouseY = activeGame->mouse.ypos;
                event.mouseButton = button;
                SEND_EVENT(event);
            }
            case GLFW_RELEASE: {
                if(Game::activeGame->mouse.releaseState) {
                    MouseReleaseEvent event_;
                    event_.mouseX = activeGame->mouse.xpos;
                    event_.mouseY = activeGame->mouse.ypos;
                    event_.mouseButton = button;
                    SEND_EVENT(event_);
                }
                inputs->erase(std::find(inputs->begin(), inputs->end(), button));
                Game::activeGame->mouse.releaseState = !Game::activeGame->mouse.releaseState;
            }
        }
    }
}

void Game::char_callback(GLFWwindow* window, unsigned int codepoint) {
    CharacterInputEvent event;
    event.codepoint = codepoint;
    SEND_EVENT(event);
}

void Game::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS || action == GLFW_REPEAT) {
        KeyPressEvent event;
        event.key = key;
        event.scancode = scancode;
        event.action = action;
        event.mods = mods;
        SEND_EVENT(event);
    }
}

Game* Game::activeGame;
