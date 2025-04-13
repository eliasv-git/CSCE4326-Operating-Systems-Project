#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <iostream>
#include <vector>
#include <unordered_map>

// Fixed page size (4KB)
const int PAGE_SIZE = 4096;

// Page Table Entry
struct PageTableEntry {
    bool valid = false;      // Is this page in memory?
    int frameNumber = -1;    // Which frame contains this page?
    bool dirty = false;      // Has this page been modified?
};

class VirtualMemory {
private:
    // Memory parameters
    int virtualMemorySize;   // Total virtual memory size
    int physicalMemorySize;  // Total physical memory size
    int numVirtualPages;     // Number of virtual pages
    int numPhysicalFrames;   // Number of physical frames
    
    // Data structures
    std::vector<bool> frameUsed;  // Track which frames are in use
    std::unordered_map<int, std::vector<PageTableEntry>> pageTables;  // Process page tables
    
    // Statistics
    int pageFaults = 0;

public:
    // Constructor
    VirtualMemory(int vMemSize, int pMemSize) : 
        virtualMemorySize(vMemSize), 
        physicalMemorySize(pMemSize) {
        
        // Calculate derived values
        numVirtualPages = virtualMemorySize / PAGE_SIZE;
        numPhysicalFrames = physicalMemorySize / PAGE_SIZE;
        
        // Initialize frame tracking
        frameUsed.resize(numPhysicalFrames, false);
        
        std::cout << "Virtual Memory initialized:\n";
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
        
        pageTables[pid].resize(numPages);
        std::cout << "Created process " << pid << " with " << numPages << " pages\n";
    }
    
    // Find a free frame or return -1 if none available
    int allocateFrame() {
        for (int i = 0; i < numPhysicalFrames; i++) {
            if (!frameUsed[i]) {
                frameUsed[i] = true;
                return i;
            }
        }
        
        // No free frames, use simple random replacement
        int victimFrame = rand() % numPhysicalFrames;
        std::cout << "Memory full, replacing frame " << victimFrame << "\n";
        return victimFrame;
    }
    
    // Translate virtual address to physical address
    int translateAddress(int pid, int virtualAddress, bool isWrite = false) {
        // Extract page number and offset
        int pageNumber = virtualAddress / PAGE_SIZE;
        int offset = virtualAddress % PAGE_SIZE;
    
        // Check if process exists
        if (pageTables.find(pid) == pageTables.end()) {
            std::cout << "Error: Process does not exist\n";
            return -1;
        }
    
        // Check if page number is valid
        if (pageNumber >= pageTables[pid].size()) {
            std::cout << "Error: Page number out of range\n";
            return -1;
        }
    
        // Get the page table entry
        PageTableEntry& entry = pageTables[pid][pageNumber];
    
        // Check if page is in memory
        if (!entry.valid) {
            // Page fault - need to load the page
            pageFaults++;
            std::cout << "[Page Fault] Page " << pageNumber << " not in memory. Handling...\n";
        
            // Allocate a frame
            int frameNumber = allocateFrame();
        
            // Update page table
            entry.valid = true;
            entry.frameNumber = frameNumber;
            entry.dirty = false;
        
            std::cout << "[Page Loaded] Virtual page " << pageNumber << " -> Physical frame " 
                      << frameNumber << "\n";
        }
    
        // Mark as dirty if writing
        if (isWrite) {
            entry.dirty = true;
        }
    
        // Calculate physical address
        int physicalAddress = (entry.frameNumber * PAGE_SIZE) + offset;
    
        std::cout << "Virtual address " << virtualAddress << " maps to physical address " 
              << physicalAddress << "\n";
    
        return physicalAddress;
    }
    
    // Display page table for a process
    void displayPageTable(int pid) {
        if (pageTables.find(pid) == pageTables.end()) {
            std::cout << "Process " << pid << " does not exist\n";
            return;
        }
        
        std::cout << "Page Table for Process " << pid << ":\n";
        std::cout << "Page | Valid | Frame | Dirty\n";
        std::cout << "-------------------------\n";
        
        for (size_t i = 0; i < pageTables[pid].size(); i++) {
            const PageTableEntry& entry = pageTables[pid][i];
            std::cout << i << " | " 
                      << (entry.valid ? "Yes" : "No") << " | "
                      << (entry.valid ? std::to_string(entry.frameNumber) : "N/A") << " | "
                      << (entry.dirty ? "Yes" : "No") << "\n";
        }
    }
    
    // Display memory usage statistics
    void displayStats() {
        int usedFrames = 0;
        for (int i = 0; i < numPhysicalFrames; i++) {
            if (frameUsed[i]) usedFrames++;
        }
        
        std::cout << "Memory Statistics:\n";
        std::cout << "  Page faults: " << pageFaults << "\n";
        std::cout << "  Physical frames used: " << usedFrames << "/" << numPhysicalFrames << "\n";
    }
};

#endif // VIRTUAL_MEMORY_H