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
		std::cout << "I am the grandparent process. PID is " << getpid() << "\n";
		kill(-1, SIGCONT);
		waitpid(0, NULL, 0);
	}
	
	// ii. branch for child process (C)
	if (pid == 0)
	{
		raise(SIGSTOP);
		int pid_c = fork();  // duplicate current process C (c --> GC)
		
		// a. branch for process C
		if (pid_c > 0)
		{
			//raise(SIGSTOP);
			std::cout << "I am the parent process. PID is " << getpid() << "\n";
			wait(NULL);
		}
		
		// b. branch for grandchild process (GC)
		if (pid_c == 0)
		{
			//raise(SIGSTOP);
			std::cout << "I am the grandchild process. PID is " << getpid() << "\n";
		}
	}
	
	
	// III. Close the program
	outFile.close();
}
