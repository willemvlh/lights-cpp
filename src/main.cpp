#include "CacheInspector.h"
#include "Constants.h"
#include "Effects.h"
#include "InterpolationCache.h"
#include "LedStrip.h"
#include "Logger.h"
#include "Scheduler.h"
#include "TerminalStrip.h"
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

void inspectCache() {
  auto &cache = InterpolationCache::current();
  CacheInspector inspector(cache);
  inspector.report();
}

int main(int argc, char **argv) {
  Logger::setLevel(Debug);
  srand(static_cast<unsigned int>(time(0))); // seed random number generator
  Strip *strip;
  auto args = parse_arguments(argc, argv);
  if (args.count("--terminal") > 0) {
    strip = new TerminalStrip(NUMBER_OF_LEDS);
  } else {
#ifdef USE_WS2811
    strip = new LedStrip(NUMBER_OF_LEDS);
#else
    std::cerr << "Must use --terminal option in this environment";
    std::exit(-1);
#endif
  }
  if (args.count("--hue")){
    InterpolationCache::current().interpolationType = HUE;
  }
  if (args.count("--no-wait")) {
    strip->setDelay(false);
  }
  if (args.count("--no-render")) {
    strip->setRender(false);
  }
  Scheduler show(strip);
  std::thread t(inspectCache);
  t.detach();
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
  } else if (args.count("--routine8")) {
    show.routine8();
  } else if (args.count("--routine9")) {
    show.routine9();
  } else if (args.count("--routine10")) {
    show.routine10();
  } else if (args.count("--test")) {
    show.test();
  } else if (args.count("--perf")) {
    show.perf();
  } else
    show.run();
  delete strip;
  return 0;
};
