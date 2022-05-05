#include "window.hpp"
#include <stdexcept>
#include <iostream>
#include "rendering/shader.hpp"

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
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // positions
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Shader shader;
  shader.loadShader("assets/shaders/lightingShader.vert", "assets/shaders/lightingShader.frag");
  shader.use();

  // Rendering loop
  while(!glfwWindowShouldClose(m_RawWindow))
  {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(m_RawWindow);
    glfwPollEvents();    
  }
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Window* Window::currentWindow = nullptr;

