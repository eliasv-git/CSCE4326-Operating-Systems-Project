#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>  // For INT_MAX

class Scheduler {
private:
    std::vector<Process> processes;
    double avgWaitingTime;
    double avgTurnaroundTime;
    
public:
    Scheduler() : avgWaitingTime(0), avgTurnaroundTime(0) {}
    
    bool isEmpty() const {
        return processes.empty();
    }
    
    void addProcess(const Process& process) {
        processes.push_back(process);
    }
    
    void addProcesses(const std::vector<Process>& newProcesses) {
        processes.insert(processes.end(), newProcesses.begin(), newProcesses.end());
    }
    
    // Run FCFS scheduling
    void runFCFS() {
        // Sort processes by arrival time
        std::sort(processes.begin(), processes.end(), 
                 [](const Process& a, const Process& b) { return a.arrivalTime < b.arrivalTime; });
        
        int currentTime = 0;
        
        for (auto& p : processes) {
            // If the process hasn't arrived yet, advance time
            if (currentTime < p.arrivalTime) {
                currentTime = p.arrivalTime;
            }
            
            // Calculate waiting time (time spent in ready queue)
            p.waitingTime = currentTime - p.arrivalTime;
            
            // Update process completion time
            p.completionTime = currentTime + p.burstTime;
            
            // Calculate turnaround time (completion time - arrival time)
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            
            // Advance time
            currentTime = p.completionTime;
        }
        
        calculateStatistics();
    }
    
    // Run SJF scheduling
    void runSJF(bool preemptive = false) {
        if (!preemptive) {
            // Non-preemptive SJF
            std::sort(processes.begin(), processes.end(), 
                     [](const Process& a, const Process& b) { return a.arrivalTime < b.arrivalTime; });
            
            int currentTime = 0;
            std::vector<Process> readyQueue;
            std::vector<Process> completedProcesses;
            size_t i = 0;
            
            while (i < processes.size() || !readyQueue.empty()) {
                // Add all processes that have arrived to the ready queue
                while (i < processes.size() && processes[i].arrivalTime <= currentTime) {
                    readyQueue.push_back(processes[i]);
                    i++;
                }
                
                if (!readyQueue.empty()) {
                    // Sort ready queue by burst time
                    std::sort(readyQueue.begin(), readyQueue.end(), 
                             [](const Process& a, const Process& b) { return a.burstTime < b.burstTime; });
                    
                    // Get the process with shortest burst time
                    Process p = readyQueue.front();
                    readyQueue.erase(readyQueue.begin());
                    
                    // Calculate waiting time
                    p.waitingTime = currentTime - p.arrivalTime;
                    
                    // Update process statistics
                    p.completionTime = currentTime + p.burstTime;
                    p.turnaroundTime = p.completionTime - p.arrivalTime;
                    
                    // Advance time
                    currentTime = p.completionTime;
                    
                    // Add to completed processes
                    completedProcesses.push_back(p);
                } else {
                    // If no processes are ready, increment time
                    currentTime++;
                }
            }
            
            // Update the original processes with the results
            for (const auto& cp : completedProcesses) {
                for (auto& p : processes) {
                    if (p.pid == cp.pid) {
                        p.completionTime = cp.completionTime;
                        p.turnaroundTime = cp.turnaroundTime;
                        p.waitingTime = cp.waitingTime;
                        break;
                    }
                }
            }
        } else {
            // Preemptive SJF (Shortest Remaining Time First)
            std::sort(processes.begin(), processes.end(), 
                     [](const Process& a, const Process& b) { return a.arrivalTime < b.arrivalTime; });
            
            int currentTime = 0;
            std::vector<Process> remainingProcesses = processes;
            std::vector<bool> completed(processes.size(), false);
            std::vector<int> startTimes(processes.size(), -1);
            std::vector<int> runningTimes(processes.size(), 0);
            int completedCount = 0;
            
            // Reset remaining times
            for (auto& p : remainingProcesses) {
                p.remainingTime = p.burstTime;
            }
            
            while (completedCount < static_cast<int>(processes.size())) {
                int shortestIndex = -1;
                int shortestRemaining = INT_MAX;
                
                // Find process with shortest remaining time
                for (size_t i = 0; i < remainingProcesses.size(); i++) {
                    if (!completed[i] && 
                        remainingProcesses[i].arrivalTime <= currentTime && 
                        remainingProcesses[i].remainingTime < shortestRemaining) {
                        shortestRemaining = remainingProcesses[i].remainingTime;
                        shortestIndex = i;
                    }
                }
                
                // If no process is found, advance time to next arrival
                if (shortestIndex == -1) {
                    int nextArrival = INT_MAX;
                    for (size_t i = 0; i < remainingProcesses.size(); i++) {
                        if (!completed[i] && remainingProcesses[i].arrivalTime < nextArrival) {
                            nextArrival = remainingProcesses[i].arrivalTime;
                        }
                    }
                    currentTime = nextArrival;
                    continue;
                }
                
                // Record start time if this is the first time the process is running
                if (startTimes[shortestIndex] == -1) {
                    startTimes[shortestIndex] = currentTime;
                }
                
                // Execute the process for 1 time unit
                remainingProcesses[shortestIndex].remainingTime--;
                runningTimes[shortestIndex]++;
                currentTime++;
                
                // Check if the process is completed
                if (remainingProcesses[shortestIndex].remainingTime == 0) {
                    completed[shortestIndex] = true;
                    completedCount++;
                    
                    // Update process statistics
                    remainingProcesses[shortestIndex].completionTime = currentTime;
                    remainingProcesses[shortestIndex].turnaroundTime = 
                        remainingProcesses[shortestIndex].completionTime - 
                        remainingProcesses[shortestIndex].arrivalTime;
                    remainingProcesses[shortestIndex].waitingTime = 
                        remainingProcesses[shortestIndex].turnaroundTime - 
                        remainingProcesses[shortestIndex].burstTime;
                }
            }
            // Update the original processes with the results
            for (size_t i = 0; i < remainingProcesses.size(); i++) {
                for (auto& p : processes) {
                    if (p.pid == remainingProcesses[i].pid) {
                        p.completionTime = remainingProcesses[i].completionTime;
                        p.turnaroundTime = remainingProcesses[i].turnaroundTime;
                        p.waitingTime = remainingProcesses[i].waitingTime;
                        break;
                    }
                }
            }
        }
        
        calculateStatistics();
    }
    
    // Calculate average waiting time and turnaround time
    void calculateStatistics() {
        double totalWaitingTime = 0;
        double totalTurnaroundTime = 0;
        
        for (const auto& p : processes) {
            totalWaitingTime += p.waitingTime;
            totalTurnaroundTime += p.turnaroundTime;
        }
        
        avgWaitingTime = totalWaitingTime / processes.size();
        avgTurnaroundTime = totalTurnaroundTime / processes.size();
    }
    
    // Display results in a simple table format
    void displayResults() {
        std::cout << "\nProcess Scheduling Results:\n";
        std::cout << "+---------+-----------------+------------+----------------+-----------------+\n";
        std::cout << "| Process | Arrival Time    | Burst Time | Waiting Time   | Turnaround Time |\n";
        std::cout << "+---------+-----------------+------------+----------------+-----------------+\n";
        
        for (const auto& p : processes) {
            std::cout << "| P" << std::setw(6) << p.pid 
                      << " | " << std::setw(15) << p.arrivalTime 
                      << " | " << std::setw(10) << p.burstTime 
                      << " | " << std::setw(14) << p.waitingTime 
                      << " | " << std::setw(15) << p.turnaroundTime << " |\n";
        }
        
        std::cout << "+---------+-----------------+------------+----------------+-----------------+\n";
        std::cout << "Average Waiting Time: " << avgWaitingTime << " time units\n";
        std::cout << "Average Turnaround Time: " << avgTurnaroundTime << " time units\n";
    }
    
    // Clear all data
    void clear() {
        processes.clear();
        avgWaitingTime = 0;
        avgTurnaroundTime = 0;
    }
};

#endif // SCHEDULER_H