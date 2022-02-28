// Assignment 1, 3320 CISC
// Shterenberg, Simon

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	// I. Initialize out stream
	std::ofstream outFile("hw1_output.txt");
	
	
	// II. Split execution between parent (P) and child (C) processes
	int pid = fork();  // duplicate current process P (P --> C)
	
	// i. branch for parent process (P)
	if (pid > 0)
	{
		outFile << "I am the grandparent process. PID is " << getpid() << "\n";
		outFile.close();
		kill(-1, SIGCONT); std::cout << "SIGCONT sent" << "\n";
		wait(NULL);
	}	
	
	// ii. branch for child process (C)
	if (pid == 0)
	{
		std::cout << "SIGSTOP not yet sent" << "\n";
		raise(SIGSTOP);
		std::cout << "gone past SIGSTOP" << "\n";
		int pid_c = fork();  // duplicate current process C (c --> GC)
		
		// a. branch for process C
		if (pid_c > 0)
		{
			std::cout << "In C branch" << "\n";
			outFile << "I am the parent process. PID is " << getpid() << "\n";
			outFile.close();
			kill(-1, SIGCONT);
			wait(NULL);
		}
		
		// b. branch for grandchild process (GC)
		if (pid_c == 0)
		{
			std::cout << "In GC Branch" << "\n";
			raise(SIGSTOP);
			outFile << "I am the grandchild process. PID is " << getpid() << "\n";
			outFile.close();
		}
		
		// iii. If child was not created, notify user of error
		if (pid_c == -1)
		{
			std::cout << "Error (Process C): child could not be created" << "\n";
		}
	}
	
	// iii. If child was not created, notify user of error
	if (pid == -1)
	{
		std::cout << "Error (Process P): child could not be created" << "\n";
	}
	
	
	// III. End of program
	return 0;
}
