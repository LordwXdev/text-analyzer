# Text Analyzer (C)

A simple command-line **Text Analyzer written in C**.  
This project analyzes a text file and provides useful statistics like number of lines, words, characters, and most frequent words.

This project is built **step by step for learning purposes**, focusing on real C programming concepts such as file handling, memory management, and clean project structure.

---

## Features

- Count lines in a text file
- Count words in a text file
- Count characters in a text file
- Build word frequency statistics
- Display the most frequent words
- Search how many times a word appears
- Safe memory handling (no leaks)

---

## Project Structure


---

## How It Works

1. The user provides a text file as input.
2. The program reads the file safely.
3. Text is analyzed line by line and character by character.
4. Statistics are calculated using dedicated functions.
5. Results are printed to the terminal.

The logic is separated from the control flow to keep the code clean and readable.

---

## Compilation

Use `gcc` to compile the project:

```bash
gcc main.c analyze.c -o text_analyzer
