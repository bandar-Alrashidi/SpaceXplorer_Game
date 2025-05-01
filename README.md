# SpaceXplorer

**SpaceXplorer** is a text-based space exploration game developed in C. It features real-time keyboard controls, dynamic objects like asteroids and junk, player firing mechanisms, a final boss battle, file handling for save/load, and a scoring system — all rendered in a console grid.

**Features**:
- Intro screen and main menu (from intro.txt)
- Real-time player movement (arrow keys)
- Bullet firing mechanics (spacebar)
- Random junk and asteroid spawning
- Collision detection
- Player score, health, and timer
- Boss battle with bombs
- Save, load, and reset game states
- Clean UI with structured game loop

**How to Build and Run**:
1. Clone or download the project.
2. Open terminal in the project folder.
3. Compile with:  
   `gcc main.c game.c utility.c -o SpaceXplorer`
4. Run the game using:  
   `./SpaceXplorer`
> Make sure intro.txt is in the same directory as the compiled binary.

**Game Controls**:
- Arrow Keys: Move the spaceship
- Spacebar: Fire bullets
- S: Save game
- L: Load game
- R: Reset game
- Q: Quit (if implemented)

**How to Play**:
Move to collect junk and shoot asteroids. Gain score by surviving and hitting enemies. Defeat the boss when it appears to win the game.

**Version History (CHANGELOG)**:
- V_1.0: Added intro screen, main menu, and player movement  
- V_1.1: Added firing mechanism  
- V_2.0: Added junk and asteroid movements  
- V_2.1: Added time, score, and health  
- V_2.2: Added collision detection  
- V_3.0: Added file handling to save/load/reset  
- V_4.0: Added boss and movement  
- V_4.1: Added boss bomb mechanics and collisions  
- V_5.0: Finalized the game with minor adjustments

**License**:  
Free for educational and personal use.
