#include "core/window.hpp"

int main() {
  Window::currentWindow = new Window(1240, 720, "Voxpile");
  Window::currentWindow->initialize();
  Window::currentWindow->run();

  delete Window::currentWindow;
  Window::currentWindow = nullptr;

  return 0;
}
