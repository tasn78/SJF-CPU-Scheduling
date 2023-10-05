#include "ShortestJobFirst.h"



int main() {
	std::list <Process> CPU_Processes;

	CPU_Processes = getProcessInfo();

	simulateProcesses(CPU_Processes);
}