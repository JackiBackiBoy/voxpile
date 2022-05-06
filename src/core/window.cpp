#include "window.hpp"
#include <stdexcept>
#include <iostream>
#include "rendering/shader.hpp"
#include "rendering/bufferLayout.hpp"
#include "rendering/vertexArray.hpp"
#include "rendering/vertexBuffer.hpp"
#include "rendering/indexBuffer.hpp"

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
  std::vector<float> vertices = {
     0.5f,  0.5f, 0.0f, // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };

  std::vector<unsigned int> indices = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };


  VertexArray vao;
  vao.create();
  vao.bind();

  VertexBuffer vbo(vertices, GL_STATIC_DRAW);
  vbo.create();

  IndexBuffer ibo(indices, GL_STATIC_DRAW);
  ibo.create();

  BufferLayout layout;
  layout.addElement<float>("position", 3);

  vao.compileBufferLayout(layout);

  vbo.unbind();
  vao.unbind();



  Shader shader;
  shader.loadShader("assets/shaders/lightingShader.vert", "assets/shaders/lightingShader.frag");
  shader.use();

  // Rendering loop
  while(!glfwWindowShouldClose(m_RawWindow))
  {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao.unbind();

    glfwSwapBuffers(m_RawWindow);
    glfwPollEvents();    
  }
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Window* Window::currentWindow = nullptr;

