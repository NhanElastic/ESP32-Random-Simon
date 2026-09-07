# ESP32 Random Simon

A Simon memory game built with **ESP32**, **C++**, and the **Arduino framework**.

The project focuses on applying clean embedded software design principles, including non-blocking state machines, hardware abstraction, button debouncing, and separation of game logic from hardware control.

## Features

* 4-button Simon memory game
* 4 corresponding LEDs
* SSD1306 OLED display
* Random sequence generation
* Debounced button input
* Non-blocking LED sequence presentation using `millis()`
* State-machine-based game flow
* Win and lose handling
* Restart support
* Wokwi simulation support
* PlatformIO project structure

## Hardware

| Component                  | Quantity |
| -------------------------- | -------: |
| ESP32 DevKit               |        1 |
| LEDs                       |        4 |
| Push buttons               |        4 |
| SSD1306 128x64 OLED        |        1 |
| LED resistors              |        4 |
| Button pull-down resistors |        4 |
| Breadboard                 |        1 |

### Pin Mapping

#### LEDs

| Color  | GPIO |
| ------ | ---: |
| Red    |   12 |
| Green  |   14 |
| Blue   |   27 |
| Yellow |   26 |

#### Buttons

| Color  | GPIO |
| ------ | ---: |
| Red    |    4 |
| Green  |    5 |
| Blue   |   16 |
| Yellow |   25 |

#### OLED

| Signal | GPIO |
| ------ | ---: |
| SDA    |   21 |
| SCL    |   22 |

## How It Works

The game starts by waiting for the player to press a button.

A random sequence is then generated and presented through the LEDs. The player must reproduce the sequence using the corresponding buttons.

After completing a level successfully, the sequence length increases.

If the player enters an incorrect input, the game ends. If the player reaches the maximum level, the game ends with a win.

After the result is displayed, pressing a button starts a new game.

## Game Flow

```text
START
  |
  | button press
  v
GENERATE_SEQUENCE
  |
  v
SHOW_SEQUENCE
  |
  v
WAITING_INPUT
  |
  +---- wrong input ----------> END_GAME
  |
  +---- sequence complete ----> LEVEL_COMPLETE
                                   |
                                   v
                               nextLevel()
                                /       \
                         continue       max level
                            |               |
                            v               v
                    GENERATE_SEQUENCE   END_GAME
                                           |
                                           v
                                   WAITING_RESTART
                                           |
                                           | button press
                                           v
                                       new game
```

## Project Structure

```text
src/
├── configs/
│   └── Pins.h
│
├── game/
│   ├── PlayerInput/
│   ├── SequencePresenter/
│   ├── GameResult.h
│   ├── GameState.h
│   ├── SimonGame.cpp
│   └── SimonGame.h
│
├── hardware/
│   ├── Buttons/
│   ├── Display/
│   └── LED/
│
├── utils/
│   └── SequenceGenerator/
│
└── main.cpp
```

### Architecture

`SimonGame` acts as the main application controller and coordinates the different game components.

```text
                    SimonGame
                   /    |     \
                  /     |      \
         PlayerInput    |    SequencePresenter
            /    \      |       /       \
           /      \     |      /         \
 ButtonManager   LedManager   LEDs   DisplayManager
                         \
                          \
                    SequenceGenerator
```

The responsibilities are separated as follows:

* **SimonGame** — controls the overall game state and game lifecycle.
* **PlayerInput** — processes player input and validates it against the generated sequence.
* **SequencePresenter** — presents the sequence using LEDs and the OLED without blocking the main loop.
* **SequenceGenerator** — generates random game sequences.
* **ButtonManager** — handles physical button input and debouncing.
* **LedManager** — controls the four LEDs.
* **DisplayManager** — manages OLED output.

## Non-Blocking Design

Instead of using long `delay()` calls, sequence presentation and end-game animations are driven by `millis()`.

This allows the main loop to remain responsive:

```cpp
void loop() {
    game.update();
}
```

Each call to `update()` performs only the work required for the current game state and then returns.

This structure makes the firmware easier to extend with additional asynchronous functionality in the future.

## State Machine

The game is implemented using an explicit state machine.

```cpp
enum class GameState {
    START,
    GENERATE_SEQUENCE,
    SHOW_SEQUENCE,
    WAITING_INPUT,
    LEVEL_COMPLETE,
    END_GAME,
    WAITING_RESTART
};
```

The result of a completed game is stored separately from the current state:

```cpp
enum class GameResult {
    NONE,
    WIN,
    LOSE
};
```

This keeps two different concepts separated:

* `GameState` describes **what the game is currently doing**.
* `GameResult` describes **how the game ended**.

## Development

The project uses:

* C++
* ESP32
* Arduino framework
* PlatformIO
* Adafruit GFX
* Adafruit SSD1306
* Wokwi

## Build

Clone the repository:

```bash
git clone https://github.com/NhanElastic/ESP32-Random-Simon.git
cd ESP32-Random-Simon
```

Build with PlatformIO:

```bash
pio run
```

Upload to an ESP32:

```bash
pio run --target upload
```

Open the serial monitor:

```bash
pio device monitor
```

## Simulation

The repository includes:

```text
diagram.json
wokwi.toml
```

so the project can be simulated with **Wokwi** without requiring physical hardware.

When using VS Code, install:

* PlatformIO IDE
* Wokwi Simulator

Build the firmware with PlatformIO and start the Wokwi simulation.

## What I Learned

This project was built as an introduction to embedded software development.

The main concepts practiced were:

* designing an explicit state machine
* replacing blocking delays with `millis()`-based timing
* debouncing physical button inputs
* separating hardware access from application logic
* managing dependencies between C++ classes
* organizing an embedded project into independent components
* designing game lifecycle transitions such as start, level progression, game end, and restart

## Author

**Võ Thành Nhân**

GitHub: [NhanElastic](https://github.com/NhanElastic)
