# SPDX-FileCopyrightText: 2021 Kattni Rembor for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""
CircuitPython NeoPixel Blink example - blinking the built-in NeoPixels.
"""
import time
import board
import neopixel

pixel = neopixel.NeoPixel(board.NEOPIXEL, 2)

while True:
    pixel.fill((255, 0, 0))
    time.sleep(0.5)
    pixel.fill((0, 0, 0))
    time.sleep(0.5)
