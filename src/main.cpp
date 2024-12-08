#include <iostream>
#ifdef __arm__
#define CAN_USE_STRIP 1
#else
#define CAN_USE_STRIP 0
#endif

#include "Effects.h"
#include "Show.h"
#include "LedStrip.h"
#include "TerminalStrip.h"
#include "util.h"
#include <cstring>
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
#if CAN_USE_STRIP
    strip = new LedStrip(60);
#else
    std::cerr << "Must use --terminal option in this environment";
    std::exit(-1);
#endif
  }
  if (args.count("--wheel")) {
    Effects eff(strip);
    eff.wheel(5, false);
    eff.wheel(10, true);
  } else if (args.count("--routine4")) {
    routine4(strip);
  }
  else show(strip);
  delete strip;
  return 0;
};
