# 🎮 Ludo Game - Gameplay Guide

Quick reference guide for playing the Ludo game.

---

## 🎯 Game Objective

**Get all 4 of your colored pieces to the center of the board (finish line).**

First player to move all 4 pieces to distance 60 wins!

---

## 🎲 Basic Rules

### Moving a Piece from Home
- **You need a 6!** Only rolling a 6 lets you move a piece from home to the board
- The piece enters at your designated start position
- After entering, the piece can move with any dice roll

### Rolling Mechanics
| Roll | Action |
|------|--------|
| **6** | Move your piece + **Roll Again** |
| **6, 6** | Move + Roll Again + **Roll Again** |
| **6, 6, 6** | **Turn CANCELLED!** No movement allowed |
| **1-5** | Move your piece + Next player's turn |

### Capturing Opponent Pieces
- Land on an opponent's piece → **Send it back home!**
- **Exception**: Pieces on **safe zones** cannot be captured
- Safe zones are marked with `*` on the board

### Safe Zones
```
Your piece is protected on these cells:
- Your entry cell
- Cells marked with * on the board
```

### Finishing
- Your piece must travel exactly 60 distance to win
- Distance 60 = center of the board
- All 4 pieces must finish to declare victory

---

## 📊 Game Phases

### Phase 1: Player Setup
1. Start the game
2. Choose number of players (2-4)
3. Confirm to begin

### Phase 2: Gameplay
```
Player Turn Flow:
┌─────────────┐
│ Roll Dice   │
└──────┬──────┘
       │
       ├─ Got 6? 
       │  ├─ YES → Roll Again
       │  └─ NO → Next Player
       │
    ┌──┴──┐
    │     │
  Move  Pass
```

### Phase 3: Victory
- First player with all 4 pieces at distance 60 wins
- "GAME OVER" screen displays winner
- Click "MAIN MENU" to play again

---

## 🎮 Controls

### Main Menu
- Click **START GAME** → Begin gameplay

### Player Setup
- Select number of players
- Confirm to start

### During Gameplay (Human Player Only)
- Click **ROLL DICE** button → Roll the dice
- Piece selection is automatic (first valid piece moves)

### Game Over
- Click **MAIN MENU** → Return to start

---

## 🤖 AI Opponents

Three difficulty levels control AI behavior:

### Easy (Level 1)
- Random piece movement
- No strategy
- Good for learning

### Medium (Level 2)
- Balanced intelligence
- Prefers pieces on board
- Moderate challenge

### Hard (Level 3)
- Aggressive strategy
- Optimized moves
- Very challenging

---

## 🎨 Board Layout

```
    RED Home          GREEN Home
┌─────────────────┐┌──────────────────┐
│  ●  ●           ││           ●  ●   │
│  ●  ●      *    ││    *      ●  ●   │
│               ▲ ││ ▲                │
└────────────────┼─┼──────────────────┘
        │    ┌────┼─┼────┐    │
        │    │            │    │
    RED │   │            │  GREEN
    Lane│   │            │  Lane
        │    │            │    │
        │    └────┼─┼────┘    │
┌────────────────┼─┼──────────────────┐
│           ▼    │ │ ▼           ● ● │
│  ●  ●          ││    *      ●  ●   │
│  ●  ●          ││           ●  ●   │
└─────────────────┴─┘──────────────────┘
   BLUE Home          YELLOW Home
```

**Colors:**
- 🔴 RED: Top-left
- 🟢 GREEN: Top-right
- 🟡 YELLOW: Bottom-right
- 🔵 BLUE: Bottom-left

---

## 📍 Key Positions

### Entry Positions (where pieces enter)
| Player | Position |
|--------|----------|
| RED | (6, 1) |
| GREEN | (1, 8) |
| YELLOW | (8, 13) |
| BLUE | (13, 6) |

### Home Stretch (final 6 cells before finish)
| Player | Cells 53-58 |
|--------|-----------|
| RED | (7,1) → (7,6) |
| GREEN | (1,7) → (6,7) |
| YELLOW | (7,13) → (7,8) |
| BLUE | (13,7) → (8,7) |

### Finish
| Player | Finish Cell |
|--------|------------|
| All | (7, 7) - Center |

---

## 🎓 Strategy Tips

### For Beginners
1. **Get pieces out** - Focus on rolling 6s to enter
2. **Stay safe** - Keep pieces on safe zones when possible
3. **Avoid capture** - Don't land on opponent areas
4. **Move forward** - Always advance pieces when possible

### For Intermediate
1. **Block opponents** - Position pieces to block enemy paths
2. **Capture strategically** - Send back pieces that are far ahead
3. **Risk management** - Balance safety with advancement
4. **Turn efficiency** - Make the most of extra 6 rolls

### For Advanced
1. **Path calculation** - Calculate optimal moves 2-3 turns ahead
2. **Opponent prediction** - Anticipate AI moves
3. **Piece prioritization** - Decide which piece to advance
4. **Endgame tactics** - Manage multiple pieces in home stretch

---

## ⚡ Quick Reference Chart

```
┌─────────────────────────────────────┐
│ DICE ROLL OUTCOMES                  │
├─────────────────────────────────────┤
│ Roll 6        → Move + Roll Again   │
│ Roll 6 + 6    → Move + Roll Again   │
│ Roll 6 + 6 + 6→ Turn Cancelled!     │
│ Roll 1-5      → Move + Next Player  │
├─────────────────────────────────────┤
│ PIECE STATUS                        │
├─────────────────────────────────────┤
│ Distance 0    → In Home             │
│ Distance 1-52 → On Main Board       │
│ Distance 53-59→ In Home Stretch     │
│ Distance 60   → FINISHED! ✓         │
├─────────────────────────────────────┤
│ WINNING CONDITION                   │
├─────────────────────────────────────┤
│ All 4 pieces at distance 60         │
│ Display: "GAME OVER!"               │
│ Winner announced                    │
└─────────────────────────────────────┘
```

---

## 🏆 Winning Strategies

### Rushing Strategy
- Focus on one piece
- Get it to finish as fast as possible
- Works when lucky with 6s

### Balanced Strategy
- Develop all 4 pieces equally
- Minimize capture risk
- Steady progress to victory

### Defensive Strategy
- Keep pieces in safe zones
- Capture opponent pieces aggressively
- Slow but steady advance

### Aggressive Strategy
- Push pieces forward fast
- Take risks for quick wins
- Attack opponent pieces

---

## ❓ Common Questions

### Q: Can I move a piece that's in the home stretch backwards?
**A:** No. Pieces always move forward toward finish.

### Q: What happens if I roll a 6 but have no pieces at home?
**A:** You can still move any piece on the board by 6 spaces.

### Q: Can two of my pieces occupy the same cell?
**A:** Yes, but try to avoid it (they share the space visually).

### Q: What if I can't move my piece without overshooting finish?
**A:** You cannot move. Turn passes to next player.

### Q: Do captured pieces lose their progress?
**A:** Yes, they return to home (distance 0).

---

## 🎯 Common Mistakes to Avoid

1. ❌ Forgetting you need a 6 to leave home
2. ❌ Landing on opponent pieces in safe zones
3. ❌ Not tracking distance (overshoot finish)
4. ❌ Ignoring opponent threats
5. ❌ Forgetting the 3-six turn cancel rule

---

## 🔊 Game Notifications

| Message | Meaning |
|---------|---------|
| "Rolled 6! Roll again..." | You got a 6, you can roll again |
| "3 sixes! Turn cancelled!" | You rolled three 6s in a row, lose your turn |
| "Piece moved! Next player..." | Move executed, next player's turn |
| "No valid moves! Next turn..." | Can't move any piece, skip turn |
| "GAME OVER!" | Someone won! |

---

## 📈 Difficulty Progression

### Beginner Player
1. Play vs Easy AI (3 times)
2. Learn all rules
3. Understand piece movement

### Intermediate Player
1. Play vs Medium AI (5 times)
2. Develop strategies
3. Improve decision making

### Advanced Player
1. Play vs Hard AI (10 times)
2. Master tactics
3. Compete with others

---

## 🎬 Game Example Turn

**Scenario**: It's RED player's turn, 2 pieces in home, 1 on board (distance 20), 1 captured.

```
Turn 1: RED rolls → Gets 6
  • Can bring another piece from home
  • Board piece can move 6 spaces
  • RED gets to roll again ✓

Turn 1 (Reroll): RED rolls → Gets 4
  • Piece at home moves to distance 1 (entered board)
  • Other piece moves from distance 20 → 24
  • Turn passes to next player

Turn 2: GREEN plays...
```

---

## 🎮 Enjoying the Game

✅ **DO:**
- Enjoy the gameplay
- Learn from AI opponents
- Try different strategies
- Have fun!

❌ **DON'T:**
- Get frustrated with AI
- Rush through moves
- Cheat or exploit bugs
- Alt-Tab too much during play

---

## 📖 For More Information

- Read **README.md** for technical details
- Check **INSTALLATION_GUIDE.md** for setup help
- Review the code for learning C++ & OOP

---

**Happy Playing! 🎲**

*Now go defeat those AI opponents!*

---

**Last Updated**: July 2026
**Version**: 1.0 Game Release
