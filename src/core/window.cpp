#include "window.hpp"
#include <stdexcept>
#include <iostream>

Window::~Window() {
  glfwDestroyWindow(m_RawWindow);
  glfwTerminate();
}

void Window::initialize() {
  // Initialize GLFW
  if (!glfwInit()) {
    throw std::runtime_error("GLFW ERROR: Failed to initialize GLFW!");
    std::exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_RawWindow = glfwCreateWindow(m_Width, m_Height, "Voxpile", NULL, NULL);
  if (!m_RawWindow) {
    throw std::runtime_error("GLFW ERROR: Failed to create OpenGL context!");
    std::exit(-1);
  }

  glfwMakeContextCurrent(m_RawWindow);
  glfwSetFramebufferSizeCallback(m_RawWindow, resizeCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("GLAD ERROR: Failed to initialize GLAD!");
    std::exit(-1);
  }
}

void Window::run() {
  // Rendering loop
  while(!glfwWindowShouldClose(m_RawWindow))
  {
    glfwSwapBuffers(m_RawWindow);
    glfwPollEvents();    
  }
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Window* Window::currentWindow = nullptr;
