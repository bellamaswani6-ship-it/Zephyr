# Generic GPIO example: STM32F407 and LPC2129

The application logic in `src/main.c` is shared. The selected board macro
chooses the hardware-specific GPIO implementation:

- `CONFIG_BOARD_STM32F4_DISCO`: STM32F407 Discovery, green LED on PD12.
- `CONFIG_BOARD_LPC2129`: LPC2129 example using P0.10.

## Build for STM32F407 with Zephyr

This project is a Zephyr application and can be built for the supported
STM32F407 Discovery board:

```sh
west build -p always -b stm32f4_disco -d build
```

The ELF output is `build/zephyr/zephyr.elf`.

## LPC2129 limitation

The LPC2129 is an ARM7TDMI-S device and is not a standard supported target
in this Zephyr workspace. The LPC2129 header is included as the board-specific
register implementation, but it cannot be built by simply passing
`-b lpc2129`. A custom Zephyr architecture/SoC/board port and toolchain
support would be required. For LPC2129 today, use a standalone bare-metal
build with an appropriate ARM7 toolchain and startup/linker files.

## Hardware caution

Verify the LED pin and polarity on the exact board before connecting it.
Use a current-limiting resistor for an external LED. The delay loop is
compiler/clock dependent and is not a calibrated time delay.
