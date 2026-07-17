# 🔧 Ludo Game - Installation & Setup Guide

Complete step-by-step guide to install and run the Ludo game on your Windows system.

---

## 📋 Prerequisites

- Windows 7/8/10/11 (32-bit or 64-bit)
- Visual Studio 2019 or 2022 (Community Edition is free)
- 500 MB free disk space
- Administrator access (for Visual Studio installation)

---

## ⬇️ Step 1: Download Visual Studio

### If you don't have Visual Studio installed:

1. Download **Visual Studio Community** from: [visualstudio.microsoft.com](https://visualstudio.microsoft.com/)
2. Run the installer
3. Select **Desktop development with C++** workload
4. Click **Install** (takes 15-30 minutes)
5. Restart your computer

---

## ⬇️ Step 2: Download Raylib

### Option A: Pre-built Binaries (Recommended)

1. Visit [raylib.com/download](https://www.raylib.com/download.html)
2. Download **raylib w64 (Visual Studio)** for 64-bit or **raylib w32** for 32-bit
3. Extract to a convenient location (e.g., `C:\raylib\`)
4. Inside should be `lib/` and `include/` folders

### Option B: Build from Source

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/projects/VS2019
# Open the .sln file and build the project
```

---

## 📥 Step 3: Clone the Ludo Game Repository

```bash
git clone https://github.com/yourusername/ludo-game.git
cd ludo-game
```

Or download as ZIP and extract.

---

## ⚙️ Step 4: Configure Visual Studio Project

### 4.1 Open the Project
1. Open Visual Studio
2. File → Open → Project/Solution
3. Navigate to your `ludo-game` folder
4. Open the `.sln` file

### 4.2 Set Include Directories
1. Right-click the project → **Properties**
2. Go to **VC++ Directories**
3. Click **Include Directories** → Edit
4. Add: `C:\raylib\include` (or your Raylib path)
5. Click OK

### 4.3 Set Library Directories
1. Still in **VC++ Directories**
2. Click **Library Directories** → Edit
3. Add: `C:\raylib\lib` (or your Raylib path)
4. Click OK

### 4.4 Link Raylib Library
1. Right-click project → **Properties**
2. Go to **Linker → Input**
3. Click **Additional Dependencies** → Edit
4. Add: `raylib.lib`
5. Click OK

### 4.5 Set Platform
1. At the top of VS, change **Solution Platforms** to match Raylib:
   - If using 64-bit Raylib: Select **x64**
   - If using 32-bit Raylib: Select **Win32**

---

## 🏗️ Step 5: Build the Project

1. **Rebuild Solution**: Ctrl+Shift+B
2. Wait for compilation to complete
3. Check **Output** window:
   - ✅ `Build succeeded` = Ready to run
   - ❌ `Build failed` = See error messages below

### Common Build Errors

#### Error: "raylib.h: No such file or directory"
- Solution: Check Include Directories path is correct (Step 4.2)

#### Error: "raylib.lib not found"
- Solution: Check Library Directories path is correct (Step 4.3)
- Make sure platform matches (32-bit vs 64-bit)

#### Error: "Unresolved external symbol"
- Solution: Ensure `raylib.lib` is in Additional Dependencies (Step 4.4)

---

## ▶️ Step 6: Run the Game

1. Press **F5** or Debug → Start Debugging
2. Game window should open
3. Enjoy! 🎮

### Running without Debugger
- Press **Ctrl+F5** for faster startup
- Use this for actual gameplay

---

## 🧪 Troubleshooting

### Game won't start
- [ ] Check Visual Studio build succeeded
- [ ] Verify Raylib library path is correct
- [ ] Ensure platform (x64/Win32) matches Raylib

### Graphics not rendering
- [ ] Update GPU drivers
- [ ] Make sure OpenGL 3.3+ is supported
- [ ] Try running in compatibility mode

### Slow performance
- [ ] Close other applications
- [ ] Check CPU/RAM usage
- [ ] Verify GPU drivers are up to date

### Game crashes on startup
- [ ] Check console for error messages
- [ ] Verify all class files are in project
- [ ] Rebuild solution from scratch

---

## 📁 Project File Checklist

Ensure all these files are in your project folder:

```
✅ MainGame_Raylib_FINAL.cpp
✅ Dice.h / Dice.cpp
✅ Cell.h / Cell.cpp
✅ Piece.h / Piece.cpp
✅ Board.h / Board.cpp
✅ Player.h / Player.cpp
✅ HumanPlayer.h / HumanPlayer.cpp
✅ AIPlayer.h / AIPlayer.cpp
✅ Game.h / Game.cpp
✅ README.md
✅ LICENSE
```

---

## 🖥️ System Information

Check your system specs:

1. **Windows**: Settings → System → About
2. **Processor**: Should be Intel/AMD from 2010+
3. **GPU**: Right-click desktop → Graphics Settings
4. **RAM**: Settings → System → About (8GB+ recommended)

---

## 🎯 Recommended Setup

For best experience:

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| Windows | 7 SP1+ | 10/11 |
| RAM | 4 GB | 8 GB+ |
| GPU | Integrated | NVIDIA/AMD |
| Disk | 500 MB | 1 GB |
| Processor | Dual-core | Quad-core |

---

## ✅ Verify Installation

After building, test with this checklist:

1. [ ] Window opens with correct title "Ludo - Raylib"
2. [ ] Board renders correctly (4 colored zones)
3. [ ] All 16 tokens visible in home positions
4. [ ] Roll button appears and is clickable
5. [ ] Console shows debug messages
6. [ ] Game runs without crashes

---

## 🚀 Next Steps

Once installed successfully:

1. Read **README.md** for game rules
2. Play a test game
3. Try different AI difficulty levels
4. Explore the code in Visual Studio
5. Make modifications as desired

---

## 📞 Getting Help

If you encounter issues:

1. **Google the error message** - Often has solutions
2. **Check Raylib FAQ**: [raylib.com/faq.html](https://www.raylib.com/faq.html)
3. **Visual Studio Documentation**: Built into VS (F1 key)
4. **GitHub Issues**: Post your problem with error details
5. **Stack Overflow**: Search for similar issues

---

## 🎓 Learning Resources

- **Raylib Documentation**: https://raylib.com/docs.html
- **C++ Reference**: https://cppreference.com/
- **Game Development**: https://gamedev.stackexchange.com/
- **YouTube Tutorials**: Search "Raylib C++ tutorial"

---

## 🔄 Updating Raylib

To update to a newer Raylib version:

1. Download new Raylib version
2. Update Include/Library paths in Step 4.2-4.3
3. Rebuild solution (Ctrl+Shift+B)
4. Test the game

---

## 💾 Project Backup

Recommended before making changes:

```bash
# Create backup
copy C:\path\to\ludo-game C:\path\to\ludo-game-backup

# Or use Git
git commit -m "Before major changes"
git push origin main
```

---

## 🎉 Success!

Once the game runs successfully:

```
✅ Installation Complete
✅ Ready for Gameplay
✅ Ready for Modifications
✅ Ready for Submission
```

**Enjoy your Ludo game!** 🎲

---

**Last Updated**: July 2026
**For**: Ludo Game v1.0 Release
