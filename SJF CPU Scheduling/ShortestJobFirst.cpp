#include "ShortestJobFirst.h"



//  Function for user input of integers for processes and returns a list (linked list) of struct Processes
//  Outline of for for loop and exception handling derived from Chat GTP
std::list <Process> getProcessInfo() {
    int numberOfProcesses;

    while (true) {
        try {
            std::cout << "Enter the number of processes: ";
            std::cin >> numberOfProcesses;

            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input. Please enter an integer.");
            }
            break;
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::list<Process> Processes;

    // Loop based on number of processes, adding burst and arrival times for each process
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
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

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


//  Simulates process completion using currentTime in ms
void simulateProcesses(std::list<Process>& processes) {

    size_t number_of_processes = processes.size();

    sortByArrivalTimes(processes); // Sort by arrival time

    int currentTime = 0;
    double totalWaitingTime = 0;

    while (!processes.empty()) {
        // First sorted process
        auto running_process = processes.begin();

        while (running_process != processes.end() &&
            running_process->arrival_Time <= currentTime) {
            ++running_process;
        }

        if (running_process == processes.begin()) {
            // No process has arrived yet, move time forward
            currentTime++;
        }
        else {
            // Execute the shortest job
            running_process--;
            Process shortestJob = *running_process;
            processes.erase(running_process);

            std::cout << "Executing Process " << shortestJob.process_id << " from time " << currentTime << " to ";
            currentTime += shortestJob.burst_Time;
            std::cout << currentTime << std::endl;

            totalWaitingTime += currentTime - shortestJob.arrival_Time - shortestJob.burst_Time;
        }
    }

    double averageWaitingTime = totalWaitingTime / number_of_processes;
    std::cout << "Average Waiting Time: " << averageWaitingTime << std::endl;
}