// Tom Steinman
// 10/5/2023

#include "ShortestJobFirst.h"


//  Function for user input of integers for processes and returns a list (linked list) of struct Processes
//  Outline of for for loop and exception handling derived from Chat GTP
std::list <Process> getProcessInfo() {
    int numberOfProcesses;

    while (true) {
        // Exception handling for invalid input
        try {
            std::cout << "Enter the number of processes: ";
            std::cin >> numberOfProcesses;

            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input. Please enter an integer.");
            }
            break;
        }

        // Catches any invalid input
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::list<Process> Processes;

    // Loop based on number of processes, user adds arrival and burst times for each process
    //  Process ID starts at 0
    for (int i = 0; i < numberOfProcesses; ++i) {
        Process p;
        p.process_id = i;

        while (true) {
            try {
                std::cout << "Enter Arrival Time for P" << p.process_id << ": ";
                std::cin >> p.arrival_Time;

                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input. Please enter an integer.");
                }

                break; // If no exception is thrown, exit the loop
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        while (true) {
            try {
                std::cout << "Enter Burst Time for P" << p.process_id << ": ";
                std::cin >> p.burst_Time;

                if (std::cin.fail()) {
                    throw std::invalid_argument("Invalid input. Please enter an integer.");
                }

                break; // If no exception is thrown, exit the loop
            }

            // Catches
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cin.clear();
                // https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears cin buffer
            }
        }
        // Adds process to list
        Processes.push_back(p);
    }

    return Processes;
}


//  Compares arrival times between 2 processes
bool compareArrivalTimes(const Process& a, const Process& b) {
    return a.arrival_Time < b.arrival_Time;
}


//  Compares burst times between 2 processes
bool compareBurstTimes(const Process& a, const Process& b) {
    return a.burst_Time < b.burst_Time;
}

//  Sorts by arrival times
void sortByArrivalTimes(std::list<Process>& processes) {
    processes.sort(compareArrivalTimes);
}


//  Simulates process completion using currentTime in ms.
void simulateProcesses(std::list<Process>& processes) {

    std::list<Process> processQueue; // Queue for processes once they have arrived
    double currentTime = 0;
    double waitTime = 0;            // Individual process wait time
    double totalAVG_WaitTime = 0;   // Total average wait time of all processes; totalWaitTime / number of processes
    double totalWaitTime = 0;       // Total sum of the wait time of all processes
    double completion_Time = 0;     // currentTime + burst time
    size_t number_of_processes = processes.size();

    sortByArrivalTimes(processes); // Sort by arrival time
    
    //  Loop will continue as long as either list is not empty
    while (!processes.empty() || !processQueue.empty()) { // Used Chat GPT for correct while loop
        // Move processes that have arrived to the processQueue
        auto process = processes.begin();
        while (process != processes.end()) {            // Moves processes from list of processes to process queue if arrived
            if (process->arrival_Time <= currentTime) { // Compares if process has arrived based on current time
                processQueue.push_back(*process);       // Adds arrived processes to queue to be processed
                process = processes.erase(process);     // Removes process from
            }
            else {
                break;
            }
        }

        if (!processQueue.empty()) {
            // Sort the processQueue by burst time to find the shortest job
            processQueue.sort(compareBurstTimes);

            // Execute the shortest job
            Process shortestJob = processQueue.front();
            completion_Time = shortestJob.burst_Time + currentTime;
            processQueue.pop_front();

            // Prints processes as they "execute"
            std::cout << "Executing Process " << shortestJob.process_id << " from time " << currentTime << " to ";
            completion_Time = currentTime + shortestJob.burst_Time;
            std::cout << completion_Time << std::endl;

            // Calculate wait time for the completed process
            waitTime = completion_Time - (shortestJob.arrival_Time + shortestJob.burst_Time);
            

            // Increment time based on previous burst time and current time
            currentTime += shortestJob.burst_Time;
        }
        else {
            // No process has arrived yet, move time forward
            currentTime++;
        }
        // Adds all wait times of each process
        totalWaitTime += waitTime;
    }

    // Calculate the total average wait time
    totalAVG_WaitTime = totalWaitTime / number_of_processes;
    // Prints totalAVG_WaitTime
    std::cout << "\nTotal Average Waiting Time: " << totalAVG_WaitTime << std::endl;
    processQueue.clear(); // Clears processQueue list
}

