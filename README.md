 Digital Mood Tracker

A console-based mood tracking system built in C++ that allows users to log, manage, and analyze their daily emotional states.

---

## 👥 Team Members & Contributions

| Member | Responsibilities |
|---|---|
| Mohamed Mostafa Taher | Structs, pre-sorted data, global variables, UI functions |
| Mohamed Fadl | UI functions (windows.h), search, integration |
| Mohamed Mostafa Komy | Sign up, login |
| Mohamed Maher | Add mood, delete mood, validation (date/mood/level), integration |
| Karim Haggag | Save & load file, logout |
| Mohamed Ali | Update mood, display all moods |
| Amr Wael | Statistics, main menu |

> Note: While tasks were divided among team members, collaboration was maintained throughout. Each member contributed beyond their primary task.

---

## ✨ Features

- 🔐 User authentication (sign up / login / logout)
- ➕ Add, update, and delete mood entries
- 📋 Display all moods with color-coded console UI
- 🔍 Search moods by date or mood type
- 📊 View statistics (overall or by month)
- 💾 Persistent data storage via text files

---

## 🧠 Mood Types & Levels

**Supported moods:** `happy` · `sad` · `angry` · `stressed` · `calm`  
**Level scale:** 1 (lowest) → 5 (highest)

---

## 🗂️ Project Structure

├── main.cpp         # Full source code

├── users.txt        # Auto-generated: stores user accounts

└── moods.txt        # Auto-generated: stores mood entries


---

## ⚙️ How to Run

> ⚠️ This project uses `windows.h` and is **Windows-only**.

1. Open the project in any C++ IDE (Visual Studio, Code::Blocks, Dev C++)
2. Compile and run `main.cpp`
3. `users.txt` and `moods.txt` will be created automatically on first save

---

## 📌 Constraints

- Max users: **10**
- Max mood entries: **100**
- Password must be at least **8 characters**
- Valid years: **2000 – 2026**

---

## 🏫 Academic Context

Project submitted as part of a university CS course.
