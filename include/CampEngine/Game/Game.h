#ifndef CE_GAME_H
#define CE_GAME_H

#include <CampEngine/Game/Input/Input.h>
#include <CampEngine/Graphics/Level.h>
#include <CampEngine/Graphics/PostProcessor.h>
#include <CampEngine/Graphics/Core/Text/TextRenderer.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>

/*---- Forward Declaration ----*/
class Screen;
class ActionMapper;
/*-----------------------------*/

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

struct FT {
    FT_Library lib;
};

struct GameInfos {
    double time;
    double deltaTime;
};

class Game {
public:
    static Game* activeGame;
    
    ActionMapper* actions;
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
    GameInfos gameInfos;
    
    Game();
    
    /*!
     * @brief This must be called before running the game loop, so as to initialize every variables and libraries correctly.
     *
     * @returns Either the task was done successfully (0 or 1).
     */
    int initialize();
    
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
    FT ft{};
    int init_libs();
    static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    /*!
     * @brief This is a callback function that should be used only for in-game actions, such as player control.
     *
     * @param[in] key An integer representing a key, which can be obtained through.
     * @param[in] scancode The key's associated scancode.
     * @param[in] action The action done on the key, can be GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT.
     * @param[in] mods Modifiers applied to the action, which modifies the key itself. It can be alt, or cmd for example.
     */
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    /*!
     * @brief This is a callback function that should be used only for text input and typing, not for in-game actions such as player control.
     *
     * @param[in] codepoint An Unicode codepoint which refers to a single character.
     */
    static void char_callback(GLFWwindow* window, unsigned int codepoint);

    /*!
     * @brief This is a callback function that detects whenever the window is resized.
     *
     * @param[in] window The concerned window.
     * @param[in] width The new width of the window.
     * @param[in] height The new height of the window.
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    /*!
     * @brief This is a callback function that detects whenever the window should close.
     *
     * @param[in] window The concerned window.
     */
     static void window_close_callback(GLFWwindow* window);

     static void window_refresh_callback(GLFWwindow* window);
};

#endif
