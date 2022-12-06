#pragma once

#include <string>
#include <vector>

namespace Colors {
  struct Color
  {
    std::string name;
    int color;
  };

  Color white() {
    return Color{"white", 0xFFFFFF};
  }

  Color black() {
    return Color{"black", 0x000000};
  }

  Color red() {
    return Color{"red", 0xF44336};
  }

  Color pink() {
    return Color{"pink", 0xE91E63};
  }

  Color purple() {
    return Color{"purple", 0xab47bc};
  }

  Color indigo() {
    return Color{"indigo", 0x5c6bc0};
  }

  Color blue() {
    return Color{"blue", 0x42a5f5};
  }

  Color cyan() {
    return Color{"cyan", 0x26c6da};
  }

  Color teal() {
    return Color{"teal", 0x26a69a};
  }

  Color green() {
    return Color{"green", 0x66bb6a};
  }

  Color lime() {
    return Color{"lime", 0xd4e157};
  }

  Color yellow() {
    return Color{"yellow", 0xdffee58};
  }

  Color amber() {
    return Color{"amber", 0xFFC107};
  }

  Color orange() {
    return Color{"orange", 0xffa726};
  }

  static std::vector<Color> colorList {
    black(),
    white(),
    red(),
    pink(),
    purple(),
    indigo(),
    blue(),
    cyan(),
    teal(),
    green(),
    lime(),
    yellow(),
    amber(),
    orange()
  };
}