// Tom Steinman
// 10/5/2023

#pragma once

#ifndef SHORTESTJOBFIRST_H
#define SHORTESTJOBFIRST_H

#include <iostream>
#include <list>
#include <stdexcept>
#include <algorithm>

// Process struct including ID, arrival time and burst time of each process (all integers)
struct Process {
	int process_id = 0;
	int arrival_Time = 0;
	int burst_Time = 0;
	int waiting_Time = 0;
};


//  Function for user input of integers for processes and returns a list (linked list) of struct Processes
//  Outline of for for loop and exception handling derived from Chat GTP
std::list <Process> getProcessInfo();

//  Compares arrival times between 2 processes
bool compareArrivalTimes(const Process& a, const Process& b);

//  Compares burst times between 2 processes
bool compareBurstTimes(const Process& a, const Process& b);

//  Uses arrival time comparison to sort by arrival time
void sortByArrivalTimes(std::list<Process>& processes);

//  Simulates process completion using currentTime in ms
void simulateProcesses(std::list<Process>& processes);


#endif // SHORTESTJOBFIRST_H