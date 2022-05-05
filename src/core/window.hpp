#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
  public:
    Window(const int& width, const int& height, const std::string& title)
      : m_Width(width), m_Height(height), m_Title(title) {}
    virtual ~Window();

    void initialize();
    void run();

    static Window* currentWindow;
  private:
    int m_Width;
    int m_Height;
    std::string m_Title;
    GLFWwindow* m_RawWindow;

    static void resizeCallback(GLFWwindow* window, int width, int height);
};
