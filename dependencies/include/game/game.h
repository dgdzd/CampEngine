#ifndef CE_GAME_H
#define CE_GAME_H

#include <game/constants.h>

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <view/screens/screen.h>
#include <view/level.h>
#include <event/events.h>
#include <utils/conversions.h>
#include <render/text/text_renderer.h>
#include <render/post_processor.h>

class Screen;

enum GameStatus {
    GAME_MENU,
    GAME_PAUSED,
    GAME_PLAYING
};

struct Mouse {
    double xpos;
    double ypos;
    std::vector<int> inputs;
    std::vector<int> actions;
    bool releaseState = 0;
};

struct Frame {
    int width;
    int height;
};

class Game {
public:
    static Game* activeGame;
    
    GameStatus status;
    Screen* activeScreen;
    Level* activeLevel;
    GLFWwindow* window;
    TextRenderer* tr;
    Mouse mouse;
    Frame frame;
    glm::mat4 projection;
    ResourceManager rm;
    PostProcessor pp;
    
    Game(GLFWwindow* window, Screen* activeScreen, Level* activeLevel, GameStatus status);
    
    /*!
     * @brief Upon calling this method, all the widgets from the active screen will receive an event.
     *
     * @param[in] e The event to be propagated through the widgets.
     */
    void propagateEvent(Event* e);
    
    /*!
     * @brief This is the main method of this class. Updates each widgets from the active screen, and poll events for GLFW's callbacks.
     */
    void update();
    
    /*!
     * @brief Sets the current active screen to be rendered.
     *
     * @param[in] screen The screen which will be active.
     */
    void setActiveScreen(Screen* screen);
    
    /*!
     * @brief Sets the current state of the game to PAUSED.
     */
    void pause();
    
    /*!
     * @brief Sets the current state of the game to PLAYING.
     */
    void resume();
    
    /*!
     * @brief Ends the whole process.
     */
    void quit();
    
private:
    static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    /*!
     * @brief This is a callback function that should be used only for in-game actions, such as player control
     *
     * @param[in] key An integer representing a key, which can be obtained through
     * @param[in] scancode The key's associated scancode.
     * @param[in] action The action done on the key, can be GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT
     * @param[in] mods Modifiers applied to the action, which modifies the key itself. It can be alt, or cmd for example.
     */
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    /*!
     * @brief This is a callback function that should be used only for text input and typing, not for in-game actions such as player control
     *
     * @param[in] codepoint An Unicode codepoint which refers to a single character.
     */
    static void char_callback(GLFWwindow* window, unsigned int codepoint);
};

#endif
