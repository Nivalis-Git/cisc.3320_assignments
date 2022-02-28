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
	int pid = fork();
	
	// i. branch for parent process (P)
	if (pid > 0)
	{
		sleep(1);
		std::cout << "I am the grandparent process. PID is " << getpid() << "\n";
		outFile.close();
		std::cout << "SIGCONT not yet sent" << "\n";
		kill(-1, SIGCONT); std::cout << "SIGCONT sent" << "\n";
		wait(NULL);
	}
	
	// ii. branch for child process (C)
	if (pid == 0)
	{
		int pid_c = fork();
		std::cout << getpid() << ": SIGSTOP not yet raised" << "\n";
		raise(SIGSTOP); std::cout << getpid() << ": SIGSTOP raised" << "\n";
		
		// a. branch for process C
		if (pid_c > 0)
		{
			//std::cout << "(C) SIGSTOP not yet raised" << "\n";
			//raise(SIGSTOP); std::cout << "(C) SIGSTOP raised" << "\n";
			std::cout << "I am the parent process. PID is " << getpid() << "\n";
			outFile.close();
			kill(-1, SIGCONT);
			wait(NULL);
		}
		
		// b. branch for grandchild process (GC)
		if (pid_c == 0)
		{
			//std::cout << "(GC) SIGSTOP not yet raised" << "\n";
			raise(SIGSTOP); //std::cout << "(GC) SIGSTOP raised" << "\n";
			std::cout << "I am the grandchild process. PID is " << getpid() << "\n";
			outFile.close();
		}
	}
	
	
// III. End of program
	return 0;
}
