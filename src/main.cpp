#include "Effects.h"
#include "LedStrip.h"
#include "TerminalStrip.h"
#include "util.h"
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>

std::unordered_set<std::string> parse_arguments(int argc, char **argv) {
  std::unordered_set<std::string> args;
  for (int i = 1; i < argc; ++i) {
    std::string str = argv[i];
    args.insert(str);
  }
  return args;
}

int main(int argc, char **argv) {
  srand(static_cast<unsigned int>(time(0))); // seed random number generator
  Strip *strip;
  auto args = parse_arguments(argc, argv);
  if (args.count("--terminal") > 0) {
    strip = new TerminalStrip(60);
  } else {
    strip = new LedStrip(60);
  }
  Effects effects(strip);
  if (args.count("--gradient")) {
    effects.gradient(
        std::vector<Color>{Color::Black, Color::Pink, Color::Black}, 10);
  } else if (args.count("--wheel")) {
    effects.wheel(100, false);
  } else if (args.count("--shift")) {
    effects.shift();
  } else if (args.count("--shiftg")) {
    effects.shiftGradient();
  }
  free(strip);
  return 0;
};
