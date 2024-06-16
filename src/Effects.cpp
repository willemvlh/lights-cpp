#include "Effects.h"
#include "LedStrip.h"
#include <chrono>
#include <iostream>

Effects::Effects(LedStrip *strip) : _strip(strip){}

template <typename T> 
void shiftArrayRight(T* arr, size_t sz){
 T prev;
 T current;
 for (size_t i = 0; i < sz; i++) {
    current = arr[i];
    arr[i] = i == 0 ? arr[sz-1] : prev;
    prev = current;
  } 
}

void Effects::rainbow(int durationInMilliseconds){
    HSL colors[_strip->numberOfLeds];
    float numberOfLeds = _strip->numberOfLeds;
    std::cout << numberOfLeds;
    for(int i = 1; i <= _strip->numberOfLeds; i++){
        colors[i-1] = { 0xff * i / numberOfLeds , 0.5, 0.5 }; 
    }
    auto start = std::chrono::steady_clock::now();
    auto end = start + std::chrono::milliseconds(durationInMilliseconds);
    while(std::chrono::steady_clock::now() < end){
      _strip->fillAll(colors, 1000);
      shiftArrayRight(colors, numberOfLeds);
    }
}
