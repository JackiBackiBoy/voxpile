#include "vertexBuffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const std::vector<float>& vertices, const int& usage)
  : m_Vertices(vertices), m_Usage(usage) {}

void VertexBuffer::create() {
  glGenBuffers(1, &m_ID);
  bind();
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_Vertices.size(), m_Vertices.data(), m_Usage);
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
