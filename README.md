# 🎲 LUDO GAME - C++ OOP with Raylib Graphics

A fully functional **Ludo board game** built with **Object-Oriented C++** and **Raylib graphics library**. Features authentic Ludo rules, AI opponents with multiple difficulty levels, and a responsive GUI.

---

## 📋 Table of Contents

- [Features](#features)
- [Tech Stack](#tech-stack)
- [Requirements](#requirements)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Game Rules](#game-rules)
- [Project Structure](#project-structure)
- [Class Architecture](#class-architecture)
- [Controls](#controls)
- [AI Difficulty Levels](#ai-difficulty-levels)
- [Game States](#game-states)
- [Future Enhancements](#future-enhancements)
- [Author](#author)

---

## ✨ Features

✅ **Complete Ludo Implementation**
- 52-cell main board with 4 player lanes
- Home zones and safe zones for each player
- Home path (final 6 cells before finish)
- Proper piece capture mechanics

✅ **Real Ludo Rules**
- Roll 6 to enter board from home
- Roll 6 = roll again (max 3 consecutive 6s)
- 3 consecutive 6s = turn cancelled
- Safe zones prevent piece capture
- All 4 pieces must reach finish to win

✅ **AI Opponents**
- 3 difficulty levels (Easy, Medium, Hard)
- Smart piece selection algorithms
- Difficulty-based decision making

✅ **Graphical Interface**
- Beautiful Raylib rendering
- Color-coded players (RED, GREEN, YELLOW, BLUE)
- Real-time board updates
- Game status panel
- Win screen

✅ **Professional Architecture**
- Object-Oriented Design with inheritance
- Polymorphism for different player types
- Proper encapsulation
- Clean separation of concerns

---

## 🛠 Tech Stack

| Component | Technology |
|-----------|-----------|
| **Language** | C++ (C++11 standard) |
| **Graphics** | Raylib 4.5+ |
| **IDE** | Visual Studio 2019+ |
| **Build** | Visual Studio Native (MSVC) |
| **Architecture** | OOP with multiple classes |

---

## 📦 Requirements

- **Visual Studio 2019** or later (with C++ development tools)
- **Raylib library** (included in project or downloadable from [raylib.com](https://www.raylib.com/))
- **Windows OS** (x86 or x64)
- **4 GB RAM** (minimum)

---

## 🚀 Installation

### Step 1: Clone the Repository
```bash
git clone https://github.com/yourusername/ludo-game.git
cd ludo-game
```

### Step 2: Open in Visual Studio
1. Open Visual Studio
2. File → Open → Project/Solution
3. Select the `.sln` file from the project directory

### Step 3: Link Raylib
1. Download Raylib from [raylib.com](https://www.raylib.com/)
2. Extract to a known location
3. In Visual Studio:
   - Project Properties → VC++ Directories
   - Add Raylib include path to `Include Directories`
   - Add Raylib lib path to `Library Directories`
   - Linker → Input → Add `raylib.lib`

### Step 4: Build & Run
```
Build → Build Solution (Ctrl+Shift+B)
Debug → Start Debugging (F5)
```

---

## 🎮 How to Play

### Game Startup
1. Launch the game
2. Select number of players on the player setup screen
3. Confirm to start the game

### During Gameplay
1. **Roll Dice**: Click the "ROLL DICE" button (human player only)
2. **Piece Movement**: Automatic selection of first valid piece
3. **Turn Flow**: Follows real Ludo rules
4. **Watch AI Play**: AI players auto-roll and move

### Winning
- Get all 4 pieces to the finish line (center cell)
- Game ends immediately when a player wins
- Winner name displayed on victory screen

---

## 📖 Game Rules

### Board Layout
```
15x15 Grid with 4 colored home zones (6x6 each)
- RED Home: Top-Left
- GREEN Home: Top-Right
- YELLOW Home: Bottom-Right
- BLUE Home: Bottom-Left
```

### Movement Rules

| Rule | Description |
|------|-------------|
| **Entry** | Need to roll a 6 to bring piece from home to board |
| **Extra Roll** | Rolling a 6 gives an extra turn (max 3 consecutive 6s) |
| **Turn Cancel** | 3 consecutive 6s = turn cancelled, no movement |
| **Capture** | Landing on opponent's piece sends it back home (except in safe zones) |
| **Safe Zones** | Pieces in safe zones cannot be captured |
| **Finish** | Must move all 4 pieces to distance 60 (center) to win |

### Safe Zone Locations
- Entry cells: (6,1), (1,8), (8,13), (13,6)
- Additional safe cells: (2,6), (6,12), (8,2), (12,8)

---

## 📁 Project Structure

```
Ludo-Game/
├── MainGame_Raylib_FINAL.cpp      # Main game loop with Raylib GUI
├── Dice.h / Dice.cpp              # Dice rolling logic
├── Cell.h / Cell.cpp              # Board cell representation
├── Piece.h / Piece.cpp            # Individual piece with status tracking
├── Board.h / Board.cpp            # Game board logic and movement rules
├── Player.h / Player.cpp          # Abstract player base class
├── HumanPlayer.h / HumanPlayer.cpp # Human player with input handling
├── AIPlayer.h / AIPlayer.cpp      # AI player with difficulty levels
├── Game.h / Game.cpp              # Game manager and turn control
├── README.md                       # This file
└── LICENSE                        # Project license
```

---

## 🏗 Class Architecture

### Inheritance Hierarchy
```
Player (Abstract Base)
├── HumanPlayer
└── AIPlayer
    └── AI Difficulty (1-3)
```

### Key Classes

#### **Dice**
- `roll()` - Returns 1-6
- `rollDice()` - Handles consecutive 6s tracking

#### **Piece**
- Status: IN_HOME, IN_PLAY, IN_SAFE, IN_FINISH
- `getDistanceMoved()` - Current position (0-60)
- `setStatus()`, `capture()` - State management

#### **Board**
- `movePiece(piece, distance)` - Core movement logic
- `capturePiece(cellID, playerID)` - Capture mechanics
- `isSafeZone(cellID)` - Safe zone checking
- `checkWinner(piece)` - Victory detection

#### **Player (Abstract)**
- `rollDice()` - Rolls and returns value
- `takeTurn()` - Turn logic (overridden by subclasses)
- `pieces[4]` - Array of player pieces

#### **HumanPlayer**
- `takeTurn()` - Waits for console input
- `choosePiece()` - Selects which piece to move

#### **AIPlayer**
- `choosePieceWithDice()` - Difficulty-based selection
- **Levels:**
  - Level 1 (Easy): Random selection
  - Level 2 (Medium): Smart selection
  - Level 3 (Hard): Optimal strategy

#### **Game**
- `setupGame()` - Initialize players and board
- `nextPlayer()` - Advance turn
- `players[4]` - Array of all players
- `gameBoard` - Reference to board instance

---

## 🎮 Controls

| Action | Control |
|--------|---------|
| **Roll Dice** | Click "ROLL DICE" button (Human only) |
| **Start Game** | Click "START GAME" after setup |
| **Return to Menu** | Click "MAIN MENU" on game over screen |
| **Exit Game** | Close window or ESC (platform dependent) |

---

## 🤖 AI Difficulty Levels

### **Easy (Level 1)**
- Random piece selection
- No strategy
- Suitable for beginners

### **Medium (Level 2)**
- Prefers pieces on board
- Avoids risky moves
- Balanced difficulty

### **Hard (Level 3)**
- Aggressive capture strategy
- Prioritizes advancing pieces
- Calculates safe moves
- Most challenging opponent

---

## 🎭 Game States

```
STATE_MAIN_MENU
    ↓
STATE_PLAYER_SETUP (select number of players)
    ↓
STATE_GAME_PLAYING (main game loop)
    ├── TURN_WAITING_ROLL (waiting for dice roll)
    ├── TURN_EXECUTING (moving piece)
    └── (repeat for each player)
    ↓
STATE_GAME_OVER (winner announced)
    ↓
Return to MAIN_MENU
```

---

## 🚀 Future Enhancements

- [ ] Piece selection via mouse click
- [ ] Save/Load game functionality
- [ ] Multiplayer over network
- [ ] Sound effects and background music
- [ ] Smooth animation for piece movement
- [ ] Statistics tracking (wins, games played)
- [ ] Undo/Redo functionality
- [ ] Custom board themes
- [ ] Difficulty progression system

---

## 🐛 Known Limitations

- Only supports 4 players (human + 3 AI)
- No network multiplayer
- No undo functionality
- AI difficulty is fixed at game start

---

## 📝 Code Standards

### Naming Conventions
- **Classes**: PascalCase (`Player`, `HumanPlayer`)
- **Functions**: camelCase (`movePiece()`, `rollDice()`)
- **Variables**: camelCase (`playerID`, `distanceMoved`)
- **Constants**: UPPER_CASE (`CELL_SIZE`, `WINDOW_WIDTH`)

### Best Practices
- Proper encapsulation with private/public sections
- Const correctness where applicable
- Proper memory management (delete dynamically allocated objects)
- Clean separation of game logic and UI
- Comprehensive comments for complex logic

---

## 🧪 Testing

### Manual Testing Checklist
- [ ] Game initializes correctly
- [ ] Dice rolls 1-6 properly
- [ ] Pieces move correct distances
- [ ] Safe zones prevent capture
- [ ] 6 allows extra roll
- [ ] 3 consecutive 6s cancel turn
- [ ] All 4 pieces required to win
- [ ] AI operates at correct difficulty
- [ ] GUI displays correctly
- [ ] Game over screen appears on win

---

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

---

## 👤 Author

**Muhammad Abdullah**
- Student Project: C++ OOP Course
- Ludo Game Implementation with Raylib Graphics
- GitHub: [yourusername](https://github.com/yourusername)

---

## 🙏 Acknowledgments

- **Raylib Community** for the excellent graphics library
- **Game Design** inspired by the traditional Ludo board game
- **OOP Principles** applied throughout the architecture

---

## 📞 Support

For issues, questions, or suggestions:
1. Check the GitHub Issues page
2. Review the code comments
3. Refer to Raylib documentation at [raylib.com](https://www.raylib.com/)

---

## 🎯 Quick Start Command

```bash
# Clone, build, and run
git clone https://github.com/yourusername/ludo-game.git
cd ludo-game
# Open in Visual Studio and run
```

---

**Happy Gaming! 🎲🎮**

*Last Updated: July 2026*
*Version: 1.0 Release*
