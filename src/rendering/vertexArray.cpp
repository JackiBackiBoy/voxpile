#include "vertexArray.hpp"

void VertexArray::create() {
  glGenVertexArrays(1, &m_ID);
}

void VertexArray::compileBufferLayout(const BufferLayout& layout) {
  m_BufferLayout = layout;

  std::vector<BufferElement> elements = m_BufferLayout.getElements();
  int offset = 0;

  for (unsigned int i = 0; i < elements.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, elements[i].count, elements[i].glType,
                          GL_FALSE, m_BufferLayout.getStride(),
                          reinterpret_cast<void*>(offset));

    offset += elements[i].byteSize;
  }
}

void VertexArray::bind() {
  glBindVertexArray(m_ID);
}

void VertexArray::unbind() {
  glBindVertexArray(0);
}
