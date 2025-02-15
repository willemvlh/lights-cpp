#include "Color.h"

typedef std::vector<Color> palette;

std::vector<palette> shuffled_palettes();

const std::vector<palette> palettes = {
{Color(0x0c0e16),Color(0x2b2f3c),Color(0x7e759b),Color(0xffa15d),Color(0xff6933)},
{Color(0xe9d758),Color(0x297373),Color(0xff8552),Color(0xe6e6e6),Color(0x39393a)},
{Color(0x42cafd),Color(0x66b3ba),Color(0x8eb19d),Color(0xf6efa6),Color(0xf0d2d1)},
{Color(0x211103),Color(0x3d1308),Color(0x7b0d1e),Color(0x9f2042),Color(0xf8e5ee)},
{Color(0xb1740f),Color(0xffd07b),Color(0xfdb833),Color(0x296eb4),Color(0x1789b2)},
{Color(0x08605f),Color(0x177e89),Color(0x598381),Color(0x8e936d),Color(0xa2ad59)},
{Color(0x1a535c),Color(0x4ecdc4),Color(0xf7fff7),Color(0xff6b6b),Color(0xffe66d)},
{Color(0x00bfb2),Color(0x1a5e63),Color(0x028090),Color(0xf0f3bd),Color(0xc64191)}};