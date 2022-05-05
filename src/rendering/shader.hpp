#pragma once

#include <string>
#include <vector>

class Shader {
  public:
    Shader() {};
    ~Shader() {};

    void loadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void use();

    inline std::vector<char>& getVertexShaderCode() { return m_VertexShaderCode; }
    inline std::vector<char>& getFragmentShaderCode() { return m_FragmentShaderCode; }

  private:
    unsigned int m_ID;
    std::vector<char> m_VertexShaderCode;
    std::vector<char> m_FragmentShaderCode;
};
