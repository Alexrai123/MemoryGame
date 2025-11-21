# 🎮 Memory Game - STM32F429I-Discovery

A complete, ready-to-build memory card matching game for the STM32F429I-Discovery board.

## 🚀 Quick Start

### **Download and Run (3 Steps)**

1. **Download this repository:**
   - Click "Code" → "Download ZIP"
   - Extract to your desired location

2. **Open in Keil µVision or STM32CubeIDE:**
   - **Keil:** Open `MDK-ARM/LCD.uvprojx`
   - **STM32CubeIDE:** Import existing project

3. **Build and Flash:**
   - Press F7 to build
   - Press F8 to flash to board
   - Play! 🎮

**That's it!** Everything is included and ready to compile.

---

## 📋 What's Included

This is a **complete STM32 project** with everything you need:

```
MemoryGame/
├── Src/                    # Source files
│   ├── main.c             # Memory Game implementation ⭐
│   ├── stm32f4xx_it.c     # Interrupt handlers
│   ├── stm32f4xx_hal_msp.c
│   └── system_stm32f4xx.c
│
├── Inc/                    # Header files
│   ├── main.h
│   ├── stm32f4xx_hal_conf.h
│   └── ...
│
├── Drivers/                # STM32 HAL & BSP libraries
│   ├── STM32F4xx_HAL_Driver/
│   ├── CMSIS/
│   └── BSP/
│
├── MDK-ARM/                # Keil µVision project
│   └── LCD.uvprojx        # Open this in Keil
│
├── Middlewares/            # USB libraries
│
├── Utilities/              # Additional utilities
│
├── MemoryGame_Optimized/   # Memory Game specific files
│   ├── main.c             # Same as Src/main.c
│   ├── README.md          # Detailed game documentation
│   └── Documentation/     # Technical docs
│
└── LCD.ioc                # STM32CubeMX configuration
```

---

## 🎮 Features

- **Grid Selection**: Choose 3×3 or 4×4 grid at startup
- **Touch Controls**: Touch screen to select and match cards
- **Visual Feedback**: Cards reveal numbers 1-8
- **Win Detection**: "YOU WIN!" message when complete
- **Pairs Counter**: Real-time progress display
- **Serial Debug**: USART1 output at 115200 baud

---

## 🛠️ Requirements

### Hardware
- STM32F429I-Discovery board
- USB cable (for programming and power)

### Software
- **Keil µVision 5** OR **STM32CubeIDE** (free!)
- ST-Link drivers (usually auto-installed)

---

## 📖 How to Build

### Using Keil µVision

1. Open `MDK-ARM/LCD.uvprojx`
2. Press **F7** (Build)
3. Connect board via USB
4. Press **F8** (Download)
5. Game starts automatically!

### Using STM32CubeIDE

1. File → Import → Existing Projects into Workspace
2. Browse to extracted folder
3. Press **Ctrl+B** (Build All)
4. Press **F11** (Debug)
5. Press **F8** (Resume)

---

## 🎯 How to Play

1. **Power on** - Board displays menu
2. **Select grid** - Touch upper half (3×3) or lower half (4×4)
3. **Match pairs** - Touch cards to reveal and match
4. **Win** - Match all pairs to see "YOU WIN!"

### Game Rules
- Cards start hidden (shown as "?")
- Touch to reveal a card's number
- Touch a second card to try matching
- Matching pairs stay revealed
- Non-matching pairs flip back after 800ms
- Win when all pairs are matched!

---

## 🔧 Technical Details

### Memory Usage
- **Flash:** ~45 KB
- **RAM:** ~115 bytes
- **Code:** ~650 lines (optimized)

### Serial Communication
Connect a serial terminal (115200 baud, 8N1):
```
Memory Game - STM32F429I
Touch screen: x=240, y=320
```

### Display
- LCD: 240×320 pixels
- Font: Font16 (main), Font24 (win message)
- Colors: Red (title), Black (text), Green (win)

---

## 📁 Project Structure

### Main Files
- **`Src/main.c`** - Memory Game implementation
- **`Inc/main.h`** - Main header file
- **`MDK-ARM/LCD.uvprojx`** - Keil project file
- **`LCD.ioc`** - STM32CubeMX configuration

### Memory Game Specific
- **`MemoryGame_Optimized/main.c`** - Standalone version
- **`MemoryGame_Optimized/README.md`** - Detailed documentation
- **`MemoryGame_Optimized/Documentation/`** - Technical guides

---

## 🔄 Modifying the Game

### Change Card Symbols
Edit `Src/main.c` around line 200:
```c
// Change from numbers to letters
card_values[0] = 'A'; card_values[1] = 'A';
card_values[2] = 'B'; card_values[3] = 'B';
// etc.
```

### Add Shuffle
Add after card initialization (line 218):
```c
// Simple shuffle
for(uint8_t i = 0; i < total_cards; i++)
{
    uint8_t j = i + (HAL_GetTick() % (total_cards - i));
    uint8_t temp = card_values[i];
    card_values[i] = card_values[j];
    card_values[j] = temp;
}
```

### Adjust Touch Zones
Modify touch detection (lines 270-325) to change card positions.

---

## 📚 Documentation

Detailed documentation available in `MemoryGame_Optimized/Documentation/`:
- **COMPATIBILITY_CHECK.md** - Verification of STM32 compatibility
- **VERIFICATION_REPORT.md** - File integrity check
- **SIMULATOR_TESTING_GUIDE.md** - Testing without hardware
- **ALTERNATIVE_IDES.md** - IDE options and setup

---

## 🧪 Testing

### Compilation Test
```
Build → Rebuild All
Should complete with 0 errors
```

### Hardware Test
1. Flash to board
2. Verify menu displays
3. Test both grid sizes
4. Verify card matching
5. Check win message

---

## 🤝 Contributing

This is a student project, but feel free to:
- Fork and experiment
- Report issues
- Suggest improvements

---

## 📄 License

This project uses STMicroelectronics HAL/BSP libraries licensed under Ultimate Liberty license SLA0044.

---

## 👤 Author

**Alexandru**
- GitHub: [@Alexrai123](https://github.com/Alexrai123)

---

## 🙏 Acknowledgments

- STMicroelectronics for HAL/BSP libraries
- Original X0 Tic-Tac-Toe project for hardware initialization

---

## ⚡ Quick Commands

```bash
# Clone repository
git clone https://github.com/Alexrai123/MemoryGame.git

# Build (Keil)
# Open MDK-ARM/LCD.uvprojx, press F7

# Build (STM32CubeIDE)
# Import project, press Ctrl+B

# Flash
# Press F8 (Keil) or F11 (STM32CubeIDE)
```

---

**Ready to play Memory Game on STM32!** 🎮✨

For detailed game documentation, see [`MemoryGame_Optimized/README.md`](MemoryGame_Optimized/README.md)
