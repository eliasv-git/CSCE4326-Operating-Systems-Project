#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <iostream>
#include <vector>
#include <unordered_map>

// Fixed page size (4KB)
const int PAGE_SIZE = 4096;

// Inverted Page Table Entry
struct InvertedPageEntry {
    int pid = -1;            // Process ID that owns this frame
    int virtualPageNum = -1; // Virtual page number
    bool valid = false;      // Is this frame in use?
    bool dirty = false;      // Has this frame been modified?
};

// Process memory information
struct ProcessInfo {
    int numPages;  // Number of pages allocated to this process
};

class VirtualMemory {
private:
    // Memory parameters
    int virtualMemorySize;   // Total virtual memory size
    int physicalMemorySize;  // Total physical memory size
    int numVirtualPages;     // Number of virtual pages
    int numPhysicalFrames;   // Number of physical frames
    
    // Data structures
    std::vector<InvertedPageEntry> invertedPageTable;  // Inverted page table
    std::unordered_map<int, ProcessInfo> processes;    // Process information
    
    // Statistics
    int pageFaults = 0;
    int tableSearches = 0;

    // Find a frame for a given (pid, page) combination
    int findFrame(int pid, int pageNumber) {
        tableSearches++;
        
        // Search through the inverted page table
        for (int i = 0; i < numPhysicalFrames; i++) {
            if (invertedPageTable[i].valid && 
                invertedPageTable[i].pid == pid && 
                invertedPageTable[i].virtualPageNum == pageNumber) {
                return i;  // Found the frame
            }
        }
        
        return -1;  // Frame not found
    }

public:
    // Constructor
    VirtualMemory(int vMemSize, int pMemSize) : 
        virtualMemorySize(vMemSize), 
        physicalMemorySize(pMemSize) {
        
        // Calculate derived values
        numVirtualPages = virtualMemorySize / PAGE_SIZE;
        numPhysicalFrames = physicalMemorySize / PAGE_SIZE;
        
        // Initialize inverted page table
        invertedPageTable.resize(numPhysicalFrames);
        
        std::cout << "Virtual Memory initialized (Inverted Page Table):\n";
        std::cout << "  Page size: " << PAGE_SIZE << " bytes\n";
        std::cout << "  Virtual memory: " << virtualMemorySize << " bytes (" 
                  << numVirtualPages << " pages)\n";
        std::cout << "  Physical memory: " << physicalMemorySize << " bytes (" 
                  << numPhysicalFrames << " frames)\n";
    }
    
    // Create a new process with specified memory size
    void createProcess(int pid, int memorySize) {
        int numPages = (memorySize + PAGE_SIZE - 1) / PAGE_SIZE;  // Ceiling division
        
        if (numPages > numVirtualPages) {
            std::cout << "Error: Process requires too much memory\n";
            return;
        }
        
        // Store process information
        processes[pid].numPages = numPages;
        
        std::cout << "Created process " << pid << " with " << numPages << " pages\n";
    }
    
    // Find a free frame or evict a page if necessary
    int allocateFrame(int pid, int pageNumber) {
        // Try to find a free frame
        for (int i = 0; i < numPhysicalFrames; i++) {
            if (!invertedPageTable[i].valid) {
                // Found a free frame
                invertedPageTable[i].valid = true;
                invertedPageTable[i].pid = pid;
                invertedPageTable[i].virtualPageNum = pageNumber;
                invertedPageTable[i].dirty = false;
                return i;
            }
        }
        
        // No free frames, use simple random replacement
        int victimFrame = rand() % numPhysicalFrames;
        
        // If the victim frame is dirty, would write it back in a real system
        if (invertedPageTable[victimFrame].dirty) {
            std::cout << "Memory full, replacing dirty frame " << victimFrame 
                      << " (PID:" << invertedPageTable[victimFrame].pid 
                      << ", Page:" << invertedPageTable[victimFrame].virtualPageNum << ")\n";
        } else {
            std::cout << "Memory full, replacing frame " << victimFrame << "\n";
        }
        
        // Update the frame with new information
        invertedPageTable[victimFrame].pid = pid;
        invertedPageTable[victimFrame].virtualPageNum = pageNumber;
        invertedPageTable[victimFrame].dirty = false;
        
        return victimFrame;
    }
    
    // Translate virtual address to physical address
    int translateAddress(int pid, int virtualAddress, bool isWrite = false) {
        // Extract page number and offset
        int pageNumber = virtualAddress / PAGE_SIZE;
        int offset = virtualAddress % PAGE_SIZE;
        
        std::cout << "Translating address " << virtualAddress << " for process " << pid << "\n";
        std::cout << "  Page: " << pageNumber << ", Offset: " << offset << "\n";
        
        // Check if process exists
        if (processes.find(pid) == processes.end()) {
            std::cout << "  Error: Process does not exist\n";
            return -1;
        }
        
        // Check if page number is valid
        if (pageNumber >= processes[pid].numPages) {
            std::cout << "  Error: Page number out of range\n";
            return -1;
        }
        
        // Search inverted page table for the frame
        std::cout << "  Searching inverted page table for (PID:" << pid 
                  << ", VPN:" << pageNumber << ")...\n";
        int frameNumber = findFrame(pid, pageNumber);
        
        // Check if page is in memory
        if (frameNumber == -1) {
            // Page fault - need to load the page
            pageFaults++;
            std::cout << "  [Page Fault] Page " << pageNumber << " not in memory. Handling...\n";
            
            // Allocate a frame
            frameNumber = allocateFrame(pid, pageNumber);
            
            std::cout << "  [Page Loaded] Virtual page " << pageNumber << " -> Physical frame " 
                      << frameNumber << "\n";
        } else {
            std::cout << "  Found in frame " << frameNumber << "\n";
        }
        
        // Mark as dirty if writing
        if (isWrite) {
            invertedPageTable[frameNumber].dirty = true;
            std::cout << "  Write operation - marking frame as dirty\n";
        }
        
        // Calculate physical address
        int physicalAddress = (frameNumber * PAGE_SIZE) + offset;
        
        std::cout << "  Virtual address " << virtualAddress << " maps to physical address " 
                  << physicalAddress << "\n";
        
        return physicalAddress;
    }
    
    // Display inverted page table
    void displayPageTable(int pid) {
        // For inverted page tables, we'll show the entire table but highlight this process's entries
        displayInvertedPageTable(pid);
    }
    
    // Display the inverted page table
    void displayInvertedPageTable(int highlightPid = -1) {
        std::cout << "Inverted Page Table:\n";
        std::cout << "Frame | Valid | Process ID | Virtual Page | Dirty\n";
        std::cout << "---------------------------------------------\n";
        
        for (int i = 0; i < numPhysicalFrames; i++) {
            const InvertedPageEntry& entry = invertedPageTable[i];
            
            // Highlight entries for the specified process
            bool highlight = (highlightPid != -1 && entry.valid && entry.pid == highlightPid);
            
            if (highlight) {
                std::cout << "* ";
            } else {
                std::cout << "  ";
            }
            
            std::cout << i << " | " 
                      << (entry.valid ? "Yes" : "No") << " | "
                      << (entry.valid ? std::to_string(entry.pid) : "N/A") << " | "
                      << (entry.valid ? std::to_string(entry.virtualPageNum) : "N/A") << " | "
                      << (entry.dirty ? "Yes" : "No") << "\n";
        }
        
        if (highlightPid != -1) {
            std::cout << "* Entries marked with * belong to Process " << highlightPid << "\n";
        }
    }
    
    // Display memory usage statistics
    void displayStats() {
        int usedFrames = 0;
        for (int i = 0; i < numPhysicalFrames; i++) {
            if (invertedPageTable[i].valid) usedFrames++;
        }
        
        std::cout << "Memory Statistics:\n";
        std::cout << "  Page faults: " << pageFaults << "\n";
        std::cout << "  Table searches: " << tableSearches << "\n";
        std::cout << "  Physical frames used: " << usedFrames << "/" << numPhysicalFrames << "\n";
        
        // Show which processes are using memory
        std::cout << "  Memory usage by process:\n";
        std::unordered_map<int, int> processFrames;
        
        for (int i = 0; i < numPhysicalFrames; i++) {
            if (invertedPageTable[i].valid) {
                processFrames[invertedPageTable[i].pid]++;
            }
        }
        
        for (const auto& pair : processFrames) {
            double percentage = (static_cast<double>(pair.second) / numPhysicalFrames) * 100.0;
            std::cout << "    Process " << pair.first << ": " 
                      << pair.second << " frames (" 
                      << percentage << "%)\n";
        }
    }
    
    // Show a process's virtual memory map (which virtual pages are in memory)
    void displayProcessMemoryMap(int pid) {
        if (processes.find(pid) == processes.end()) {
            std::cout << "Process " << pid << " does not exist\n";
            return;
        }
        
        std::cout << "Memory Map for Process " << pid << ":\n";
        std::cout << "Virtual Page | In Memory | Frame | Dirty\n";
        std::cout << "--------------------------------------\n";
        
        for (int page = 0; page < processes[pid].numPages; page++) {
            int frame = findFrame(pid, page);
            bool inMemory = (frame != -1);
            bool dirty = inMemory ? invertedPageTable[frame].dirty : false;
            
            std::cout << page << " | " 
                      << (inMemory ? "Yes" : "No") << " | "
                      << (inMemory ? std::to_string(frame) : "N/A") << " | "
                      << (inMemory && dirty ? "Yes" : "No") << "\n";
        }
    }
};

#endif // VIRTUAL_MEMORY_H
