#pragma once

#include <vector>

class VertexBuffer {
  public:
    VertexBuffer() {};
    VertexBuffer(const std::vector<float>& vertices, const int& usage);
    ~VertexBuffer() {};

    void create();
    void bind();
    void unbind();

  private:
    unsigned int m_ID;
    std::vector<float> m_Vertices;
    int m_Usage;
};
