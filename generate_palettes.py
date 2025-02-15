palettes = []

with open("palettes.csv", "r") as f:
    for line in f.readlines():
        splits = [f"Color(0x{c})" for c in line.strip().split(",")]
        vector = "{" + ",".join(splits) + "}"
        palettes.append(vector)



with open("./src/Palettes_generated.h", "w") as f:
    f.write(
f"""#include "Color.h"

typedef std::vector<Color> palette;

std::vector<palette> shuffled_palettes();

const std::vector<palette> palettes = {{
""" + ",\n".join(palettes) + "};"

)
