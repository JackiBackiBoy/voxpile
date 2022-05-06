#include "bufferLayout.hpp"

std::unordered_map<std::type_index, unsigned int> BufferLayout::typeSizes = {
  { std::type_index(typeid(float)), 4 }
};

std::unordered_map<std::type_index, unsigned int> BufferLayout::glTypes = {
  { typeid(float), GL_FLOAT },
  { typeid(double), GL_DOUBLE },
  { typeid(char), GL_BYTE },
  { typeid(unsigned char), GL_UNSIGNED_BYTE },
  { typeid(int), GL_INT },
  { typeid(unsigned int), GL_UNSIGNED_INT },
  { typeid(short), GL_SHORT },
  { typeid(unsigned short), GL_UNSIGNED_SHORT }
};
