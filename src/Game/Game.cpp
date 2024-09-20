#include <CampEngine/Game/Game.h>

#include <CampEngine/Game/Constants.h>
#include <CampEngine/Game/Events/Categories/KeyboardEvents.h>
#include <CampEngine/Game/Events/Categories/MouseEvents.h>
#include <CampEngine/Game/Events/Categories/WindowEvents.h>
#include <CampEngine/Graphics/Screens/DebugScreen.h>
#include <CampEngine/Graphics/Widgets/TextBox.h>
#include <CampEngine/Initialize.h>
#include <CampEngine/Physics/CollisionsHandler.h>
#include <CampEngine/Utils/Conversions.h>

#include <string>


Game::Game() = default;

int Game::initialize() {
    if(init_libs() != 0) return 0;
    
    /* Create a window and it's OpenGL context */
    this->window = glfwCreateWindow(CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT, CE_WINDOW_TITLE, NULL, NULL);
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
    
    /* Initializes the viewport */
    glViewport(0, 0, CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);
    
    /* Loading font */
    TextRenderer::common = new TextRenderer(&ft.lib);
    this->tr = TextRenderer::common;
    tr->loadFont(GET_RESOURCE(fonts/helveticaLight.ttf), 48);

    /* Loading shaders */
    ResourceManager &rm = ResourceManager::standard;
    if(CampEngine::CREATE_RESOURCE_FILE) {
        rm.loadShader("unlitShader", GET_RESOURCE(shaders/unlitShader.vs), GET_RESOURCE(shaders/unlitShader.fs));
        rm.loadShader("litShader", GET_RESOURCE(shaders/lit/defaultLitShader.vs), GET_RESOURCE(shaders/lit/defaultLitShader.fs));
        rm.loadShader("text", GET_RESOURCE(shaders/text.vs), GET_RESOURCE(shaders/text.fs));
        rm.loadShader("widget", GET_RESOURCE(shaders/widget/widget.vs), GET_RESOURCE(shaders/widget/widget.fs));
        rm.loadShader("rectangle", GET_RESOURCE(shaders/shapes/rectangle.vs), GET_RESOURCE(shaders/shapes/rectangle.fs));
        rm.loadShader("circle", GET_RESOURCE(shaders/shapes/circle.vs), GET_RESOURCE(shaders/shapes/circle.fs));

        /* Loading post-processing effect shaders */
        rm.loadShader("pp.none", GET_RESOURCE(shaders/screen/screen.vs), GET_RESOURCE(shaders/screen/screen.fs));
        rm.loadShader("pp.reverse_colors", GET_RESOURCE(shaders/screen/screen.vs), GET_RESOURCE(shaders/screen/post_processing/reverse_colors.fs));
        rm.loadShader("pp.grayscale", GET_RESOURCE(shaders/screen/screen.vs), GET_RESOURCE(shaders/screen/post_processing/grayscale.fs));

        rm.loadPostProcessor("basic", *rm.getShader("pp.none"), CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);
        rm.loadPostProcessor("reverse_colors", *rm.getShader("pp.reverse_colors"), CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);
        rm.loadPostProcessor("grayscale", *rm.getShader("pp.grayscale"), CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);

        rm.startEmbedding(GET_RESOURCE(data/resources.dat));
        rm.embedShader("unlitShader");
        rm.embedShader("litShader");
        rm.embedShader("text");
        rm.embedShader("widget");
        rm.embedShader("rectangle");
        rm.embedShader("circle");
        rm.embedShader("pp.none");
        rm.embedShader("pp.reverse_colors");
        rm.embedShader("pp.grayscale");
        rm.embedPostProcessor("basic");
        rm.embedPostProcessor("reverse_colors");
        rm.embedPostProcessor("grayscale");
        rm.stopEmbedding();
    } else {
        rm.loadEmbeddedData(GET_RESOURCE(data/resources.dat));
    }

    this->status = GAME_MENU;
    this->frame = { CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT };
    this->pp = *rm.getPostProcessor("basic");
    this->projection = glm::ortho(0.0f, static_cast<float>(CE_WINDOW_WIDTH), 0.0f, static_cast<float>(CE_WINDOW_HEIGHT), 0.0f, -128.0f);
    this->actions = new ActionMapper();
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, char_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetWindowCloseCallback(window, window_close_callback);
    
    activeGame = this;

    glDepthFunc(GL_LESS);
    
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
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, false);
    glfwWindowHint(GLFW_DECORATED, false);
    glfwWindowHint(GLFW_SAMPLES, 4);

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
    /* Update game infos */
    const double time = glfwGetTime();
    gameInfos.deltaTime = time - gameInfos.time;
    gameInfos.time = time;
    glEnable(GL_DEPTH_TEST);

    actions->update();
    CollisionsHandler::step();
    
    /* Rendering functions here */
    pp.start();


    if(activeLevel) activeLevel->update(projection);
    if(activeScreen) activeScreen->render(projection);
    if(auto ds = dynamic_cast<DebugScreen*>(activeScreen)) {
        ds->textFPS->text = L"FPS: " + std::to_wstring((int)PhysicsEnvironment::getInstance()->fpsCount);
        ds->textDeltaTime->text = L"DeltaTime: " + std::to_wstring(PhysicsEnvironment::getInstance()->deltaTime);
        ds->textObjCount->text = L"Object count: " + std::to_wstring(activeLevel->objects.size());
    }

    pp.end();
    glDisable(GL_DEPTH_TEST);
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

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS || action == GLFW_REPEAT) {
        KeyPressEvent event;
        event.key = key;
        event.scancode = scancode;
        event.action = action;
        event.mods = mods;
        SEND_EVENT(event);
    } else if(action == GLFW_RELEASE) {
        KeyReleaseEvent event;
        event.key = key;
        event.scancode = scancode;
        event.action = action;
        event.mods = mods;
        SEND_EVENT(event);
    }
}

void Game::char_callback(GLFWwindow* window, unsigned int codepoint) {
    CharacterInputEvent event;
    event.codepoint = codepoint;
    SEND_EVENT(event);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Game::activeGame->projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), 0.0f, 128.0f);
    Game::activeGame->frame = {
        CE_WINDOW_WIDTH,
        CE_WINDOW_HEIGHT
    };

    FramebufferResizeEvent event;
    event.window = window;
    event.width = width;
    event.height = height;
    SEND_EVENT(event);
}

void Game::window_close_callback(GLFWwindow* window) {
    WindowShouldCloseEvent event;
    event.window = window;
    SEND_EVENT(event);
}

void Game::window_refresh_callback(GLFWwindow* window) {
    activeGame->update();
}


Game* Game::activeGame;
