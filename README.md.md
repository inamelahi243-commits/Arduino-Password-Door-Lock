# 🔐 Password Door Lock System

A PIN-based electronic door lock system built with an Arduino Uno, a 4x4 matrix keypad, and a servo-driven locking mechanism. The system uses two separate PINs — one to open the door and another to close it — with real-time feedback shown on a 16x2 I2C LCD display.

## 📋 Table of Contents

- [Overview](#overview)
- [Components Used](#components-used)
- [How It Works](#how-it-works)
- [Circuit Diagram / Wiring](#circuit-diagram--wiring)
- [Simulation](#simulation)
- [Installation & Upload Instructions](#installation--upload-instructions)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Security Note](#security-note)
- [License](#license)

## Overview

This project simulates a keypad-secured door lock. The user enters a 4-digit PIN on a matrix keypad to unlock the door (rotating a servo motor to an "open" position) and a different 4-digit PIN to lock it again. The system gives instant visual and audible feedback via an LCD screen, LEDs, and a buzzer.

## Components Used

| Component              | Quantity | Purpose                                  |
|-------------------------|----------|-------------------------------------------|
| Arduino Uno              | 1        | Main microcontroller                      |
| 4x4 Matrix Keypad        | 1        | PIN entry input                           |
| I2C LCD 16x2 Display     | 1        | Displays prompts and status messages      |
| Servo Motor              | 1        | Simulates the door lock/unlock mechanism  |
| Green LED                | 1        | Indicates correct PIN entry               |
| Red LED                  | 1        | Indicates incorrect PIN entry             |
| Buzzer                   | 1        | Audible feedback for correct/incorrect PIN|
| Jumper Wires & Breadboard | -        | Connections                              |

## How It Works

1. **Startup**: On power-up, the LCD prompts the user to `Enter Open PIN`, and the servo starts at the locked position (0°).
2. **PIN Entry**: As the user presses keys on the keypad, each digit is captured and masked with an `*` on the LCD's second row.
3. **Verification**: Once 4 digits are entered, the code is compared against the expected PIN:
   - **Correct "Open" PIN** (while the door is locked) → Green LED lights up, buzzer beeps once, LCD shows `DOOR OPENED`, and the servo rotates to 90° to simulate unlocking. The system then prompts for the "Close" PIN.
   - **Correct "Close" PIN** (while the door is open) → Green LED lights up, buzzer beeps once, LCD shows `DOOR CLOSED`, and the servo returns to 0°. The system then prompts for the "Open" PIN again.
   - **Incorrect PIN** → Red LED lights up, buzzer sounds a longer warning tone, and the LCD displays `WRONG PASSWORD` before returning to the appropriate prompt.
4. **State Handling**: A boolean `doorOpened` flag tracks whether the door is currently open or closed, ensuring the correct PIN is checked depending on the current state.
5. **Input Reset**: After every attempt (successful or not), the entered PIN buffer and LCD are cleared, ready for the next entry.

### Default PINs
- **Open PIN**: `1234`
- **Close PIN**: `4321`

> You can change these by editing the `openPIN[]` and `closePIN[]` variables in the `.ino` file.

## Circuit Diagram / Wiring

### Pin Connections

**Keypad (4x4):**
| Keypad Pin | Arduino Pin |
|------------|-------------|
| Row 1–4    | 9, 8, 7, 6  |
| Col 1–4    | 5, 4, 3, 2  |

**Other Components:**
| Component     | Arduino Pin |
|---------------|-------------|
| Green LED     | 10          |
| Red LED       | 11          |
| Buzzer        | 12          |
| Servo Signal  | 13          |
| LCD (I2C)     | SDA → A4, SCL → A5 (Uno) |

> The I2C LCD address used in this code is `0x27`. If your LCD isn't detected, run an I2C scanner sketch to find the correct address and update it in the code.

## Simulation

Before wiring the physical hardware, you can simulate and test this project using:

- **[Tinkercad Circuits](https://www.tinkercad.com/)** – Free, browser-based simulator. Supports Arduino Uno, keypad, LCD (non-I2C by default — you may need to adapt or use a library workaround), servo, LEDs, and buzzer.
- **[Proteus](https://www.labcenter.com/)** – Professional circuit simulation software with full support for I2C LCDs and servo motors; ideal for a more accurate hardware simulation before committing to a physical build.

Both tools let you build the circuit virtually, upload this exact `.ino` code, and test the full PIN logic without any physical components.

## Installation & Upload Instructions

1. **Install the Arduino IDE** from [arduino.cc](https://www.arduino.cc/en/software) if you haven't already.
2. **Install required libraries** via *Sketch → Include Library → Manage Libraries*, and search for/install:
   - `Keypad` by Mark Stanley, Alexander Brevig
   - `LiquidCrystal I2C` by Frank de Brabander (or Marco Schwartz)
   - `Servo` (usually pre-installed with the IDE)
3. **Clone or download this repository**:
   ```bash
   git clone https://github.com/<your-username>/Password_Door_Lock.git
   ```
4. **Open the sketch**: Launch `Password_Door_Lock.ino` from the `Password_Door_Lock` folder in the Arduino IDE.
5. **Select your board and port**: *Tools → Board → Arduino Uno*, and *Tools → Port → (your COM/serial port)*.
6. **Upload**: Click the Upload button (→) to flash the code to your Arduino.
7. **Wire the circuit** as described above, then power the board and test PIN entry via the keypad.

## Usage

1. Power on the circuit — the LCD will display `Enter Open PIN`.
2. Enter `1234` on the keypad to open the door.
3. The servo rotates, the green LED lights up, and the LCD prompts for the close PIN.
4. Enter `4321` to close the door again.
5. Entering an incorrect PIN at any stage triggers the red LED, a warning buzz, and a `WRONG PASSWORD` message.

## Project Structure

```
Password_Door_Lock/
├── Password_Door_Lock.ino
└── README.md
```

## Security Note

This project is intended for **educational and hobbyist purposes**. The PINs are hardcoded directly into the source code, which is fine for learning and prototyping but is **not suitable for real-world security applications** without significant hardening (e.g., EEPROM-stored/encrypted PINs, lockout after failed attempts, etc.).

## License

This project is open-source and available under the [MIT License](LICENSE). Feel free to use, modify, and distribute it.
