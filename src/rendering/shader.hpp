#pragma once

#include <string>
#include <vector>

class Shader {
  public:
    Shader() {};
    ~Shader() {};

    void loadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void use();

  private:
    std::string parseShader(const std::string& path);

    unsigned int m_ID;
};
