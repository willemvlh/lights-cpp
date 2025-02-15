#include "Constants.h"
#include "Effects.h"
#include "Show.h"
#include "LedStrip.h"
#include "TerminalStrip.h"
#include "util.h"
#include <cstring>
#include <string>
#include <unordered_set>
#include <iostream>

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
    strip = new TerminalStrip(NUMBER_OF_LEDS);
  } else {
#ifdef __arm__
    strip = new LedStrip(NUMBER_OF_LEDS);
#else
    std::cerr << "Must use --terminal option in this environment";
    std::exit(-1);
#endif
  }
  Show show(strip);
  std::cout << "hello?" <<std::endl;
  if (args.count("--wheel")) {
    Effects eff(strip);
    eff.wheel(5, false);
    eff.wheel(10, true);
  } else if (args.count("--routine2")) {
    show.routine2();
  } else if (args.count("--routine3")) {
    show.routine3();
  } else if (args.count("--routine4")) {
    show.routine4();
  } else if (args.count("--routine5")) {
    show.routine5();
  } else if (args.count("--routine6")) {
    show.routine6();
  } else if (args.count("--routine7")) {
    show.routine7();
  }
  else show.run();
  delete strip;
  return 0;
};
