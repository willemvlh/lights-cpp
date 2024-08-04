#include "Show.h"
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
  show(strip);
  delete strip;
  return 0;
};
