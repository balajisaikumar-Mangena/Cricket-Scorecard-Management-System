# 🏏 Cricket Scorecard Management System using LPC2148

A real-time embedded cricket scoring system developed using the LPC2148 ARM7TDMI-S microcontroller and Embedded C. The project simulates a professional cricket scoreboard capable of handling complete match scoring, batsman statistics, bowler statistics, innings transitions, target calculation, run-rate analysis, projected score estimation, and automatic winner declaration on a 40x2 LCD display.

---

## 📌 Overview

The Smart Cricket Scoreboard provides a complete cricket match simulation through a keypad-based scoring interface. Users can update runs, wickets, wides, no-balls, and bowler changes while the system continuously updates match statistics and player performance in real time.

---

## 🔌 Circuit Diagram

The complete Smart Cricket Scoreboard hardware was designed and verified using Proteus Professional. The system consists of an LPC2148 ARM7TDMI-S microcontroller interfaced with a 40x2 LCD display and a 4x4 matrix keypad for real-time score entry and display.

<p align="center">
<img width="978" height="600" alt="Circuit Diagram" src="https://github.com/user-attachments/assets/c51afe4f-c236-4476-8a68-666dce120914" />

</p>

---

## 🎯 Features

### Match Management

* Toss Simulation
* Bat/Bowl Selection
* Automatic Team Assignment
* First and Second Innings Handling
* Target Generation
* Match Result Determination

### Batting Features

* Individual Batsman Statistics
* Runs Scored Tracking
* Balls Faced Tracking
* Automatic Strike Rotation
* Automatic New Batsman Entry After Wicket

### Bowling Features

* Runs Conceded Tracking
* Wickets Tracking
* Overs and Ball Count Tracking
* Manual Bowler Selection
* Live Bowler Statistics Display

### Match Statistics

* Team Score
* Wickets Fallen
* Overs Completed
* Current Run Rate (CRR)
* Projected Score (PS)
* Target Tracking

### Result Processing

* Chasing Team Victory Detection
* Defending Team Victory Detection
* Tie Match Detection

---

## 📟 LCD Display Format

The LCD displays:

* Batting Team
* Team Score
* Overs
* Current Run Rate
* Projected Score
* Striker Statistics
* Non-Striker Statistics
* Current Bowler Statistics

---

## ⌨️ Keypad Controls

|  Key  |       Action       |
| ----- | ------------------ |
|   0   |   Dot Ball         |
|   1   |   Single           |
|   2   |   Two Runs         |
|   3   |   Three Runs       |
|   4   |   Four Runs        |
|   6   |   Six Runs         |
|   *   |   Wicket           |
|   /   |   No Ball          |
|   -   |   Wide Ball        |
|   +   |   Change Bowler    |
|   =   |   Confirm Bowler   |

---

## 🛠️ Hardware Requirements

* LPC2148 ARM7TDMI-S Microcontroller
* 40x2 LCD Display
* 4x4 Matrix Keypad
* Power Supply

---

## 💻 Software & Tools

* Embedded C
* Keil uVision IDE
* Proteus Professional
* Flash Magic

---

## 🔬 Simulation

The complete system was designed and validated using Proteus Professional. The simulation includes:

* LPC2148 Microcontroller
* 40x2 LCD Interface
* Matrix Keypad Interface
* Complete Cricket Scoring Logic

The simulation was used to verify score updates, strike rotation, bowler statistics, innings transitions, target calculation, and winner determination before hardware implementation.

---

## 🏗️ System Architecture

---

## 📊 Calculations

### Current Run Rate

```text
CRR = (Runs × 6) / Balls Faced
```

### Projected Score

```text
Projected Score = CRR × Total Overs
```

### Target

```text
Target = First Innings Score + 1
```

---

## 🎓 Concepts Implemented

* Embedded C Programming
* Structures and Pointers
* ARM7 LPC2148 Programming
* LCD Interfacing
* Matrix Keypad Interfacing
* Real-Time Event Handling
* State-Based Application Design
* Cricket Scoring Algorithms

---

## ⭐ Project Highlights

* Real-Time Cricket Match Simulation
* Professional LCD Scoreboard Interface
* Dynamic Batsman and Bowler Statistics
* Automatic Innings Management
* Target Chasing Logic
* Winner Determination System
* LPC2148 ARM7TDMI-S Based Design
* Proteus Professional Simulation
* Modular Embedded C Architecture

---

## 🚀 Future Enhancements

* UART Score Transmission
* CAN Bus Integration
* EEPROM Match Storage
* RTC Integration
* Wireless Scoreboard
* Mobile App Connectivity
* Match History Storage
  
---
