Simple Zephyr reusable-library example

This example demonstrates a small C library split into a header and source file.
The functions print messages; they do not control a physical LED.

Build from this application directory:
    west build -b qemu_x86 -p always

Run:
    west build -t run

Expected output:
    LED ON
    LED OFF
    LED TOGGLED
