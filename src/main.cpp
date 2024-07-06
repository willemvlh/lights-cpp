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
  Strip *strip;
  auto args = parse_arguments(argc, argv);
  if (args.count("--terminal") > 0) {
    strip = new TerminalStrip(60);
  } else {
    strip = new LedStrip(60);
  }
  Effects effects(strip);
  if (args.count("--gradient")) {
    effects.gradient(Color{0xff, 51, 0x0}, Color{0xff, 191, 0x0}, 10);
  } else if (args.count("--wheel")) {
    effects.wheel(100, false);
  }
  free(strip);
  return 0;
};
