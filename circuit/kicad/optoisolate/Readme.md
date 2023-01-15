# Opto-Isolator Protection Circuit Example

This example show some simple opto-isolation circuit to protect a low voltage chip.

![images](kicad6/optoisolate.png?raw=true)

In this example, the protected chip is ATTiny85 which control an induction load (electric motor).

## Main Idea

The main idea behind this:
- Separated voltage levels
- No actual electronic signals

## Key Components

The key components here is:
- **Voltage regulator like AMS1117, AP2114H, etc.** 
	- This part convert 12V into 3.3V, prevent overvoltage, and separate this two power-line segments
- **Current Diode or Schottky Diode like 1N400x or SS34.**
	- This part separate the GND voltage references about 0.8V and prevent back-current
- **Optoswitch like 4N35, PC817, H11L1, etc.**
	- This part relay transmits signal from main chip to the load switch like MOSFETs or Relays without actual electronic signal connected.