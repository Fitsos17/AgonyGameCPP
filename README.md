# Agony Card Game

A terminal-based C++ implementation of the popular card game "Agony". This project was developed as part of an Object-Oriented Programming (OOP) university course to practice software structure, class design, and terminal interactions.

## 🚀 What I Learned

Building this project was a fantastic hands-on experience. Through developing Agony, I got familiar with and applied the following concepts:
* **C++ Programming:** Gaining a solid understanding of the language's syntax, memory management, and standard libraries.
* **Object-Oriented Programming (OOP):** Designing the game using classes, objects, encapsulation, and clear responsibilities (e.g., `Player`, `Deck`, `Card`, `DiscardPile`).
* **Project Structure:** Learning how to properly organize a larger codebase using header files (`.h`) for declarations and source files (`.cpp`) for implementations.

---

## 🛠️ Compilation and Execution

To run this game, it is **crucial** that you maintain the exact folder and file structure provided in this repository. 

1. Open your terminal.
2. Navigate to the root folder of the project (the directory containing `main.cpp`).
3. Compile the project using `g++` by executing the following command:

> `g++ main.cpp classes/src/*.cpp helpers/src/*.cpp -o agony.exe`

4. Run the generated executable:
   * **On Windows:** `agony.exe`
   * **On Linux/Mac:** `./agony.exe`

---

## 📜 Rules of the Game

Agony is a shedding-type card game played with a standard 52-card deck. 

* **Players:** 2 **OR** 4 players.
* **Dealing:** Each player is dealt 7 cards. The remaining cards form the draw pile, and one card is placed face-up to start the discard pile.
* **Objective:** Empty your hand as fast as possible to keep your penalty points low. The player with the lowest score at the end of the game wins.
* **Basic Gameplay:** On your turn, you must play a card that matches either the **suit** or the **rank** of the top card on the discard pile.
* **Drawing:** If you do not have a playable card (or choose not to play one), you must draw a card from the deck. 
* **Special Card - Ace:** Can be played at any time. The player who drops an Ace gets to declare a new suit that the next player must follow.
* **Special Card - Seven:** Forces the next player to draw 2 cards. However, if that player also holds a 7, they can play it to "stack" the penalty, forcing the *next* player to draw 4 cards, and so on.
* **Special Card - Eight:** Grants the player an immediate extra turn.
* **Special Card - Nine:** Forces the next player to lose their turn (skip).
* **Scoring:** When a round ends, players count the points remaining in their hands. Number cards 2-10 are worth their face value. Jacks, Queens, and Kings are worth 10 points. Aces are worth 11 points.

---

## 🤝 Contributing and Feedback

I am currently learning and expanding my C++ skills! I am very open to any advice, code reviews, or tips on how to improve the structure, logic, or efficiency of this project. Feel free to open an issue or submit a pull request if you have suggestions.