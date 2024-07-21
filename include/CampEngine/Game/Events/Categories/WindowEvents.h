//
// Created by Noah Campagne on 21/07/2024.
//

#ifndef CE_WINDOW_EVENTS_H
#define CE_WINDOW_EVENTS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <CampEngine/Game/Events/Event.h>


class WindowEvent : public Event {
public:
    WindowEvent(const std::string& name) : Event(name) {};
    virtual ~WindowEvent() = default;

    GLFWwindow* window = nullptr;
};

class FramebufferResizeEvent : public WindowEvent {
public:
    FramebufferResizeEvent() : WindowEvent("FramebufferResizeEvent") {};
    virtual ~FramebufferResizeEvent() = default;

    int width, height;
};

class WindowShouldCloseEvent : public WindowEvent {
public:
    WindowShouldCloseEvent() : WindowEvent("WindowShouldCloseEvent") {};
    virtual ~WindowShouldCloseEvent() = default;
};

#endif
