#pragma once

#include <unordered_map>
#include <glad/glad.h>
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <vector>

struct BufferElement {
  std::string name;
  unsigned int glType;
  unsigned int count;
  unsigned int byteSize;
};

class BufferLayout {
  public:
    BufferLayout() {};
    ~BufferLayout() {};

    inline std::vector<BufferElement> getElements() { return m_Elements; }
    inline int getStride() { return m_Stride; }

    template <typename T>
    void addElement(const std::string& name, const unsigned int& elementCount) {
      // Check if given type T is valid
      try {
        unsigned int size = typeSizes.at(typeid(T)) * elementCount;

        m_Elements.push_back({ name, glTypes.at(typeid(T)), elementCount, size });
        m_Stride += m_Elements[m_Elements.size() - 1].byteSize;
      }
      catch (const std::out_of_range &e) {
        std::cerr << "Exception at " << e.what() << std::endl;
      }
    }

  private:
    int m_Stride;
    std::vector<BufferElement> m_Elements;

    static std::unordered_map<std::type_index, unsigned int> typeSizes;
    static std::unordered_map<std::type_index, unsigned int> glTypes;
};
