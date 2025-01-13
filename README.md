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
###  1.Diagram Bloc
![image](https://github.com/user-attachments/assets/1e849494-b9d1-440c-81a4-4719f75e4b1a)
### 2.Electrict Schema
![arduino_slot_game_block_diagram 2](https://github.com/user-attachments/assets/24672675-0dbc-464b-899b-235f1d7a5ea2)

### 3.Componente
| **Nr.** | **Component**         | **Cantitate** | **Descriere**                          | **Link/Datasheet**                                                                 |
|---------|-----------------------|---------------|----------------------------------------|----------------------------------------------------------------------------------|
| **1**   | Arduino Uno           | 1             | Microcontroller principal              | [Kit](#)                                                                        |
| **2**   | Matrice LED 8x8       | 1             | Controlată prin MAX7219                | [MAX7219 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX7219-MAX7221.pdf) |
| **3**   | LCD 16x2 (fără I2C)   | 1             | Afișaj                                 | [Kit](#)                                                                        |
| **4**   | Joystick              | 1             | Control pentru mișcări și selecții     | [Kit](#)                                                                        |
| **5**   | Buzzer                | 1             | Generare sunete                        | [Kit](#)                                                                        |
| **6**   | Cabluri (Jumper Wires)| 20+           | Conexiuni electrice                    | [Kit](#)                                                                        |
| **7**   | Breadboard            | 1             | Platformă pentru prototipare           | [Kit](#)                                                                        |
| **8**   | Mini Breadboard       | 1             | Prototipare pentru componente mici     | [Kit](#)                                                                        |


### 4.Components Used and Their Roles:

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

### 5.Pin Connections Table
### Pin Connections Table

| **Component**                 | **Arduino Uno Pin**          | **Component Pin**         | **Description**                    |
|-------------------------------|-----------------------------|---------------------------|------------------------------------|
| **8x8 LED Matrix (MAX7219)**  | **D11**                     | **DIN**                   | Data input (SPI)                   |
|                               | **D13**                     | **CLK**                   | Clock signal (SPI)                 |
|                               | **D12**                     | **CS**                    | Chip select (SPI)                  |
| **LCD 16x2**                  | **D5, D6, D7, D8, D9,D10**  | **RS, EN, D4-D7**         | Data/control pins                  |
| **Joystick**                  | **A1, A0, D4**              | **VRx, VRy, SW**          | Analog inputs + button             |
| **Buzzer**                    | **D9**                      | **(+)**                   | PWM signal for sound               |
| **Potentiometer (Contrast)**  | **-**                       | **VO (LCD)**              | Adjust LCD contrast                |
| **Potentiometer (Volume)**    | **-**                       | **Buzzer control**        | Adjust buzzer volume               |


### 6.Power Consumption
Arduino Uno:
Operates at 5V and can directly power the connected components.

8x8 LED Matrix (MAX7219):
The MAX7219 manages the current for the LEDs with a maximum of 40 mA per segment.

Buzzer and LCD:
Both have a low power consumption, approximately 20-30 mA each.

![WhatsApp Image 2024-12-17 at 11 26 16_666d2a9e](https://github.com/user-attachments/assets/9dc866eb-8d4e-4a92-b38a-e2a1d3b4f219)



### 7.Image of implamantation

## Software Design

#### Libraries:

LedControl.h
This library is used to control the 8x8 LED matrix connected through the MAX7219 driver.

Why this library :

1.It simplifies managing LED matrices for using the MAX7219

2.It allows me to adjust brightness with setIntensity() and clear the display with clearDisplay().


LiquidCrystal.h
This library is used to control an LCD display.

Why this library :

To display game information such as score and menu on an LCD.

Arduino.h

Why this library :

The core library that provides essential functions for the project.

#### The laboratories used in this project :

Lab 2: Interrupts and Timers
In this project, timers are essential for controlling the flow of the game. The game’s timers are responsible for:

Controlling how fast the symbols spin on the LED matrix.
Creating precise delays between different game actions.
The game uses default timers from the Arduino library to ensure the slot machine runs smoothly and consistently.

Lab 3: PWM (Pulse Width Modulation)
The buzzer in the slot machine uses PWM to generate sound effects.
Sound effects are played at different moments in the game:

When the game starts.
When the symbols spin.
When the player wins or loses.
The project uses the tone() function, which relies on PWM to generate sounds with different frequencies and durations.

Lab 4: ADC (Analog-to-Digital Converter)
The joystick is a key component of the project. It’s used to:

Navigate through menus.
Select the bet amount.
Control the symbol selection.
The project uses the analogRead() function to convert the joystick’s position into digital values that the Arduino can understand.

Lab 5: SPI (Serial Peripheral Interface)
The LED matrix is controlled using SPI communication.
SPI allows the Arduino to quickly send data to the LED matrix to display symbols like:

Stars
Diamonds
Number 7




## Results
https://www.youtube.com/shorts/4Pm8iQ6MwEQ


## Functionality of the game 

###Snake Game Project Description
#### 1. Game Menu

When the game starts, a menu system is displayed on the LCD screen with the following options:

Start Game – Begin the Slot Machine game.
Leaderboard – View the top 5 player scores.
Settings – Adjust game settings such as Sound ON/OFF and Bet Amount.

Use the joystick to navigate the menu:

Move up/down to switch between options.
Press the joystick button to select an option.

#### 2. Gameplay: How the Slot Machine Works
The game is played on an 8x8 LED matrix, where the symbols spin and stop at random to determine the result.

Game Steps:
Choose your bet amount (5, 10, 20, or 50 points).
Press the joystick button to spin the reels.
The LED matrix shows spinning symbols, and after a short delay, the reels stop on 3 random symbols.
Based on the combination of symbols, the game calculates if you win or lose.

#### 3. Symbols and Winning Combinations

Combination	Payout Multiplier	Description
🎰 777	x10	Jackpot!
⭐️ Star, Star, Star	x20	Big Win!
💎 Diamond, Diamond, Diamond	x5	Small Win
🎰🎰⭐️ Two 7s + One Star	x10	Mixed Win
💎💎⭐️ Two Diamonds + One Star	x5	Mixed Win
⭐️⭐️🎰 Two Stars + One 7/Diamond	x2	Small Win
❌ Other Combinations	Lose Bet	Better luck next time!

 #### 4. Score Display
The current score is shown on the LCD screen during the game.
The bet amount and winning payouts are also displayed on the LCD.
After each round, you can choose a new bet before spinning again.

#### 5. Sound Effects (Buzzer)
The game includes sound effects through a buzzer:

Startup sound – Played when the game starts.
Spinning sound – Played when the reels spin.
Win sound – Played when you win a round.
Lose sound – Played when you lose a round.
The sound can be turned ON or OFF in the Settings menu.

#### 6. Game Over & Restart
The game ends if the player runs out of points.

At Game Over:

The LCD screen shows “Game Over!” and a funny message like “Du-te la Amanet”.
The player can restart the game by pressing the joystick button.
#### 7. User Controls (Joystick Navigation)
Joystick Up/Down – Navigate through the menu or adjust the bet amount.
Joystick Left/Right – Switch between symbols during the game.
Joystick Button Press – Select an option in the menu or spin the reels.

## Conclusion

Overall, it was a great hands-on experience that showed me how different hardware components can work together to create an interactive system. It also made me realize how important it is to think about user experience by adding features like a menu, sound effects, and a leaderboard to make the game more fun.



   


   
