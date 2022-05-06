#include "indexBuffer.hpp"
#include <glad/glad.h>

void IndexBuffer::create() {
  glGenBuffers(1, &m_ID);
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_Indices.size(),
               m_Indices.data(), m_Usage);
}

void IndexBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
