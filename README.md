# Slot Machine Simulation Project

## Introduction
My project simulates a slot machine game using a hardware platform. This game is a replica of a slot machine.

### What the project does
The project allows users to experience the basic mechanics of a slot game. By pressing a button, an animation symbolizing the run is triggered, and the result is displayed by a combination of emojis.

### The purpose of the project
The project is educational. Also, the goal is to provide an engaging experience to the user while learning about the logic of gambling.

### The idea from which I started
I proposed to combine entertainment with education, using a well-known concept - slot machine. The idea was inspired by the popularity of gambling, but with an emphasis on simplicity and safety, without financial implications.

### Why it's useful
It is useful because it can help gambling addicts to play without financial implications.

## General Description

## Hardware Design
###1.![Diagram Bloc]![image](https://github.com/user-attachments/assets/1e849494-b9d1-440c-81a4-4719f75e4b1a)
###2.![Electrict Schema] ![WhatsApp Image 2024-12-17 at 00 42 38_42159778](https://github.com/user-attachments/assets/96b41914-e1e5-4bb3-ae6d-9550f79d8282)
###3.![Componente]
1	Arduino Uno	1	Microcontroller principal	kit
2	Matrice LED 8x8	1	Controlata prin MAX7219	Datasheet MAX7219 : https://www.analog.com/media/en/technical-documentation/data-sheets/MAX7219-MAX7221.pdf 
3	LCD 16x2 (fara I2C)	1	Afisaj	kit
4	Joystick	1	pentru control	kit
5	Buzzer 	1	kit
8	Cables	20+	Conexiuni electrice	
9	Breadboard	1		
10 MiniBreadboard 1 

###4.![Components Used and Their Roles:]

Arduino Uno:
The main microcontroller that controls all components.

8x8 LED Matrix with MAX7219:
Used to display the game state.

16x2 LCD (without I2C):

Displays game information (e.g., score, status).
Connected via digital pins 

Joystick:

Controls movements and selections in the game.

Passive Buzzer:

Generates sounds based on game actions.

Potentiometers:

LCD Contrast Adjustment: Central pin → VO pin on the LCD.

###5.![Pin Connections Table]\
Component	Arduino Uno Pin	Component Pin	Description
8x8 LED Matrix (MAX7219)	D11	DIN	Data input (SPI)
D13	CLK	Clock signal (SPI)
D10	CS	Chip select (SPI)
LCD 16x2	D4, D5, D6, D7, D8, D9	RS, EN, D4-D7	Data/control pins
Joystick	A1, A0, D2	VRx, VRy, SW	Analog inputs + button
Buzzer	D9	(+)	PWM signal for sound
Potentiometer (Contrast)	-	VO (LCD)	Adjust LCD contrast
Potentiometer (Volume)	-	Buzzer control	Adjust buzzer volume


Here is the energy consumption section formatted for GitHub in Markdown:

###6.![Power Consumption]
Arduino Uno:
Operates at 5V and can directly power the connected components.

8x8 LED Matrix (MAX7219):
The MAX7219 manages the current for the LEDs with a maximum of 40 mA per segment.

Buzzer and LCD:
Both have a low power consumption, approximately 20-30 mA each.

###7.![Image of implamantation]

## Software Design

## Results

   


   
