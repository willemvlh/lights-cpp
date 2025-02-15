#include "Palettes_generated.h"
#include <random>
#include <algorithm>

std::vector<palette> shuffled_palettes(){
    auto copy = palettes;
    auto rd = std::random_device();
    auto rng = std::default_random_engine {rd()};
    std::ranges::shuffle(copy, rng);
    return copy;
}
