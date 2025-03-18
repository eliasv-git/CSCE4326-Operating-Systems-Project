# CSCE43226-Operating-Systems-Project
# Table of Contents  
- [Members](#members)  
- [Project Overview](#project-overview)  
- [Instructions](#instructions)  
- [User Login](#user-login)  
- [Process Select](#process-select)
- [Test Case Example](#test-case-example)
- [Process Example](#process-example)
- [Part 3 Process Scheduling Algorithms](#process-scheduling)

# Members
  - Elias Villarreal
  - Nathanielle Delapena
# Instructions
  - Download or copy the files
  - Open a  C++ compiler
  - Make sure all the files are on the compiler
  - Run the main.cpp file
# User Login
 - Program simulates Operating System Boot sequence
 - Simulates user log in
   - Simulates boot-up and loading
   - Hardcoded username and password
     - Username: admin
     - Password: password123 
   - If the username/password is incorrect program returns user to login
# Process Select
 - Program simulates main menu (Program state is running)
 - Requires user to log in using correct name and password 
   - User will be given prompt to select a program (Program is moved to a waiting state)
     - Will not open or run program at this time  
   - Will loop until Shutdown is selected (When shutdown is selected the state of the program is terminated)
# Test Case Example
 - Before the program runs, the program is prepared to be execute (New State)
 - Programs starts running loading the operating system (Running State)
 - Programs waits for user authentification (Waiting State)
   - User inputs Username: admin
   - User unputs Password: password123
 - Program validates the username and password (Ready State)
   - Program loads operating sysetm
 - Prompts the user to select a program (Waiting State)
   - User selects Notepad
   - System outputs selected program (Running State)
 - Prompts the user to select another program (Waiting State)
   - User chooses Shutdown option 
   - Program ends (Terminated State)
  ## Process Example
  Download [Recording 2025-02-24 221634.zip](https://github.com/eliasv-git/CSCE4326-Operating-Systems-Project/blob/main/Recording%202025-02-24%20221634.zip)

  # Process Scheduling
  - Located under Part-3 Scheduling File
  - Process Scheduling Algorithms
    - FCFS (First-Come-First-Serve)
      - Non-Preemtive scheduling algorithm where process that arrives first is executed first
    - SJF (Shortest Job First)
      - Non-Preemtive scheduling where process with shortest CPU burst time is executed first
      - Preemtive Scheduling where the process with the shortest remaining CPU burst time is executed first, and a new process with a
        shorter remaining time can preempt the currently running process.
  - Displays
      - Completion Time
      - Average Waiting Time
      - Average Turnaround Time
- Simulator
    - Sign in
      - Username: admin
      - Password: password123
    - Select Process to simulate
      - Input the number of process to simulate
      - Input arrival time of each process
      - Input burst time of each process
    - Select Process Scheduling Algorithm
    - Simulates scheduling algorithm
