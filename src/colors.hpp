#pragma once

#include <string>
#include <vector>

namespace Colors {
  struct Color
  {
    std::string name;
    int color;
  };

  Color black() {
    return Color{"black", 0x000000};
  }

  Color red() {
    return Color{"red", 0xF44336};
  }

  Color pink() {
    return Color{"pink", 0xE91E63};
  }

  Color amber() {
    return Color{"amber", 0xFFC107};
  }

  Color purple() {
    return Color{"purple", 0x7C4DFF};
  }

  Color blue() {
    return Color{"blue", 0x2196F3};
  }

  static std::vector<Color> colorList {
    black(),
    red(),
    pink(),
    red(),
    purple(),
    blue(),
  };
}