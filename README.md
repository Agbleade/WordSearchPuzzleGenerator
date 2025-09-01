# Word Search Puzzle Generator 

This is a **C++ word search puzzle generator** that creates a 10x10 word search game board from a list of words.  
Words are read from a text file, placed randomly in the grid (in all 8 possible directions), and the remaining empty cells are filled with random letters. The final puzzle and word list are displayed in the console.

---

##  Features
- Reads up to **10 words** from an input file (`PuzzleWords.txt`).
- Supports **8 directions** for word placement:
  - Horizontal (left → right, right → left)  
  - Vertical (top → bottom, bottom → top)  
  - Diagonal (↘, ↖, ↙, ↗)  
- Handles **word overlaps** (shared letters) if valid.  
- Fills empty grid spaces with random **A–Z letters**.  
- Displays both:
  - Puzzle with only words placed.
  - Completed puzzle with filler letters.
- Prints the **list of hidden words** at the end.


