#pragma once

#include "vertexBuffer.hpp"
#include "bufferLayout.hpp"

class VertexArray {
  public:
    VertexArray() {};
    ~VertexArray() {};

    void create();
    void compileBufferLayout(const BufferLayout& layout);
    void bind();
    void unbind();

  private:
    unsigned int m_ID;
    VertexBuffer m_VBO;
    BufferLayout m_BufferLayout;
};
