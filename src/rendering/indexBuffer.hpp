#pragma once

#include <vector>

class IndexBuffer {
  public:
    IndexBuffer() {};
    IndexBuffer(const std::vector<unsigned int>& indices, const int& usage)
      : m_Indices(indices), m_Usage(usage) {};
    ~IndexBuffer() {};

    void create();
    void bind();
    void unbind();

  private:
    unsigned int m_ID;
    std::vector<unsigned int> m_Indices;
    int m_Usage;
};
