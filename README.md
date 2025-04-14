# CSCE43226-Operating-Systems-Project
# Table of Contents  
- [Members](#members)  
- [Project Overview](#project-overview)  
- [Instructions](#instructions)  
- [User Login](#user-login)  
- [Process Select](#process-select)
- [Test Case Example](#test-case-example)
- [Process Example](#process-example)
- [Part 3: Process Scheduling Algorithms](#process-scheduling)
- [Part 4: Virtual Memory](#virtual-memory)

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
      - Completion time
      - Average waiting time
      - Average turnaround time
  - Simulator
      - Sign in
        - Username: admin
        - Password: password123
      - Select Process to simulate
        - Input the number of process to simulate
        - Input arrival time of each process
        - Input burst time of each process
      - Select Process Scheduling Algorithm
      - Simulates Scheduling Algorithm
 
  # Virtual Memory
  - Located under Part 4 -VirtualMemory- Folder
  - Introduction of virtual & physicial memory 
    - Pages (Fixed size of 4KB)
    - Inverted page tables
    - Address translation
  - Displays
    - Page size
    - Virtual memory size
    - Physical memory size
    - Inverted page table
    - Metadata
      - Valid bit
      - Frame number
      - Dirty bit  
  - Simulator
    - Sign in
      - Username: admin
      - Password: password123   
    - Select 'Virtual Memory Simulaton'
    - Create a new process
      - Input size of the new process in bytes
      - Pages are assigned to process
      - New process ID is created
    - Read from memory
      - Input process ID
      - Input virtual address to read
      - Translates virtual address to physical address
    - Write from memory
      - Input process ID
      - Input virtual address to read
      - Translates virtual address to physical address
      - Marks pages as dirty
      - Simulates data modificatio
    - Display inverted page table
      -  Frame
      -  If it is valid or invalid
      -  If the page is dirty or not
    - Display statistics
      -  Page faults
      -  Table searches
      -  Physical frames used
    - Test workloads
          Virtual Memory initialized (Inverted Page Table):
          Page size: 4096 bytes
          Virtual memory: 65536 bytes (16 pages)
          Physical memory: 32768 bytes (8 frames)
          
          === Virtual Memory Simulation ===
          1. Create new process
          2. Read from memory
          3. Write to memory
          4. Display page table
          5. Display statistics
          6. Return to main menu
          Enter choice: 1
          Enter process memory size (bytes): 12000
          Created process 1 with 3 pages
          
          === Virtual Memory Simulation ===
          1. Create new process
          2. Read from memory
          3. Write to memory
          4. Display page table
          5. Display statistics
          6. Return to main menu
          Enter choice: 2
          Enter process ID: 1
          Enter virtual address to read: 5000
          Translating address 5000 for process 1
            Page: 1, Offset: 904
            Searching inverted page table for (PID:1, VPN:1)...
            [Page Fault] Page 1 not in memory. Handling...
            [Page Loaded] Virtual page 1 -> Physical frame 0
            Virtual address 5000 maps to physical address 904
          
          === Virtual Memory Simulation ===
          1. Create new process
          2. Read from memory
          3. Write to memory
          4. Display page table
          5. Display statistics
          6. Return to main menu
          Enter choice: 3
          Enter process ID: 1
          Enter virtual address to write: 8500
          Translating address 8500 for process 1
            Page: 2, Offset: 308
            Searching inverted page table for (PID:1, VPN:2)...
            [Page Fault] Page 2 not in memory. Handling...
            [Page Loaded] Virtual page 2 -> Physical frame 1
            Write operation - marking frame as dirty
            Virtual address 8500 maps to physical address 4404
          
          === Virtual Memory Simulation ===
          1. Create new process
          2. Read from memory
          3. Write to memory
          4. Display page table
          5. Display statistics
          6. Return to main menu
          Enter choice: 4
          Enter process ID: 1
          Inverted Page Table:
          Frame | Valid | Process ID | Virtual Page | Dirty
          ---------------------------------------------
          * 0 | Yes | 1 | 1 | No
          * 1 | Yes | 1 | 2 | Yes
            2 | No | N/A | N/A | No
            3 | No | N/A | N/A | No
            4 | No | N/A | N/A | No
            5 | No | N/A | N/A | No
            6 | No | N/A | N/A | No
            7 | No | N/A | N/A | No
          * Entries marked with * belong to Process 1
        
