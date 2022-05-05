#include "shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

void Shader::loadShader(const std::string& vertexPath, const std::string& fragmentPath) {
  std::string vertexCode = parseShader(vertexPath);
  std::string fragmentCode = parseShader(fragmentPath);

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // 2. Compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];
     
  // vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  };

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  // print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  };

  // shader Program
  m_ID = glCreateProgram();
  glAttachShader(m_ID, vertex);
  glAttachShader(m_ID, fragment);
  glLinkProgram(m_ID);
  // print linking errors if any
  glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
    
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(m_ID);
}

std::string Shader::parseShader(const std::string& path) {
  std::ifstream shaderFile;
  shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try 
  {
    // open files
    shaderFile.open(ENGINE_DIR + path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf(); // read into string stream
    shaderFile.close();

    return shaderStream.str();
  }
  catch(std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  return "";
}

