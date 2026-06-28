#!/usr/bin/env python3

from PIL import Image
import sys

if len(sys.argv) != 3:
    print("Usage: png_to_chr.py input.png output.chr")
    sys.exit(1)

input_path = sys.argv[1]
output_path = sys.argv[2]

img = Image.open(input_path)

if img.mode != "P":
    print(f"Expected indexed PNG mode 'P', got {img.mode}")
    print("This simple converter expects an indexed PNG.")
    sys.exit(1)

width, height = img.size

if width % 8 != 0 or height % 8 != 0:
    print("Image dimensions must be multiples of 8.")
    sys.exit(1)

pixels = img.load()
chr_bytes = bytearray()

for tile_y in range(0, height, 8):
    for tile_x in range(0, width, 8):
        plane0 = []
        plane1 = []

        for row in range(8):
            b0 = 0
            b1 = 0

            for col in range(8):
                color = pixels[tile_x + col, tile_y + row]

                if color > 3:
                    print(
                        f"Pixel at ({tile_x + col},{tile_y + row}) uses palette index {color}; NES tiles need indexes 0-3."
                    )
                    color = color % 4

                bit0 = color & 1
                bit1 = (color >> 1) & 1

                b0 |= bit0 << (7 - col)
                b1 |= bit1 << (7 - col)

            plane0.append(b0)
            plane1.append(b1)

        chr_bytes.extend(plane0)
        chr_bytes.extend(plane1)

with open(output_path, "wb") as f:
    f.write(chr_bytes)

print(f"Wrote {len(chr_bytes)} bytes to {output_path}")
print(f"Tiles: {len(chr_bytes) // 16}")
