# 🏏 Cricket Scorecard Management System using LPC2148

A real-time embedded cricket scoring system developed using the LPC2148 ARM7TDMI-S microcontroller and Embedded C. The project simulates a professional cricket scoreboard capable of handling complete match scoring, batsman statistics, bowler statistics, innings transitions, target calculation, run-rate analysis, projected score estimation, and automatic winner declaration on a 40x2 LCD display.

---

## 📌 Overview

The Smart Cricket Scoreboard provides a complete cricket match simulation through a keypad-based scoring interface. Users can update runs, wickets, wides, no-balls, and bowler changes while the system continuously updates match statistics and player performance in real time.

---

## 🔌 Block Diagram

<p align="center">
<img width="676" height="545" alt="image" src="https://github.com/user-attachments/assets/68f77ce1-befb-4d13-a767-c4a255e50559" />
</p>

---

## 🔌 Circuit Diagram

The complete Smart Cricket Scoreboard hardware was designed and verified using Proteus Professional. The system consists of an LPC2148 ARM7TDMI-S microcontroller interfaced with a 40x2 LCD display and a 4x4 matrix keypad for real-time score entry and display.

<p align="center">
<img width="978" height="600" alt="Circuit Diagram" src="https://github.com/user-attachments/assets/c51afe4f-c236-4476-8a68-666dce120914" />

</p>

---

🎯 Features

🏏 Match Management

* Toss Simulation for determining the batting and bowling team.
* Bat/Bowl Selection based on toss outcome.
* Dynamic Team Assignment.
* Complete First and Second Innings Management.
* Automatic Innings Transition.
* Automatic Target Generation after the first innings.
* Real-Time Match State Management.
* Automatic Match Completion Detection.
* Winner Determination Logic.

---

🏏 Batting Features

* Individual Batsman Statistics Tracking.
* Runs Scored Tracking.
* Balls Faced Tracking.
* Strike Rate Calculation.
* Automatic Strike Rotation on Singles and Triples.
* Strike Change at the End of Every Over.
* Automatic New Batsman Entry after Wicket.
* Support for Complete Batting Line-up.
* Live Striker and Non-Striker Management.
* Not-Out Batsman Tracking.

---

🎳 Bowling Features

* Individual Bowler Statistics Tracking.
* Runs Conceded Tracking.
* Wickets Tracking.
* Overs and Ball Count Tracking.
* Bowling Figure Management.
* Manual Bowler Selection.
* Automatic Over Completion Handling.
* Live Bowler Statistics Display.

---

➕ Extras Management

No Ball

* Adds Extra Run to Team Score.
* Runs scored after No Ball are added to Team Total.
* Runs scored after No Ball are added to Batsman Score.
* Bowler Concedes Extra Runs.
* Delivery is treated as an Extra Ball.
* Automatically Triggers Free Hit.

Free Hit

* Automatically Activated after No Ball.
* Runs are counted normally.
* Supports Strike Rotation.
* Free Hit Status Management.
* Real-Time Free Hit Processing.

Wide Ball

* Adds Extra Run to Team Score.
* Additional Wide Runs Supported.
* Delivery is treated as an Extra Ball.
* Batsman Ball Count Remains Unchanged.
* Bowler Concedes Wide Runs.

---

📊 Match Statistics

* Team Score Tracking.
* Wickets Fallen Tracking.
* Overs Completed Tracking.
* Current Run Rate (CRR) Calculation.
* Projected Score (PS) Calculation.
* Target Tracking During Chase.
* Live Match Summary Display.
* Real-Time Scoreboard Updates.

---

📟 LCD Scoreboard Features

* Professional 40x2 LCD User Interface.
* Live Team Score Display.
* Wickets Display.
* Overs Display.
* Current Run Rate (CRR) Display.
* Projected Score (PS) Display.
* Striker Statistics Display.
* Non-Striker Statistics Display.
* Current Bowler Statistics Display.
* Match Result Display.

---

🔄 Match Flow Features

* Ball-by-Ball Score Updates.
* Real-Time Statistics Update.
* Automatic Strike Management.
* Automatic Over Completion Handling.
* Automatic Bowler Change Request.
* Innings Completion Detection.
* Target Chase Monitoring.
* Match End Detection.

---

🏆 Result Processing

* Chasing Team Victory Detection.
* Defending Team Victory Detection.
* Tie Match Detection.
* All-Out Match Handling.
* Target Achieved Detection.
* Automatic Winner Announcement.

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
