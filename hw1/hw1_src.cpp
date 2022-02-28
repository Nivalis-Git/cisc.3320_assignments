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
	
	if (pid > 0)
	{
		kill(-1, SIGSTOP);
	}
	else {
	}
	
	// i. branch for child process (C)
	if (pid == 0)
	{
		int pid_c = fork();  // duplicate current process C (c --> GC)
		
		// a. branch for process C
		if (pid_c > 0)
		{
			//raise(SIGSTOP);
			outFile << "I am the parent process. PID is " << getpid() << "\n";
			wait(NULL);
		}
		
		// b. branch for grandchild process (GC)
		if (pid_c == 0)
		{
			//raise(SIGSTOP);
			outFile << "I am the grandchild process. PID is " << getpid() << "\n";
		}
	}
	
	// ii. branch for parent process (P)
	/*if (pid > 0)
	{
		outFile << "I am the grandparent process. PID is " << getpid() << "\n";
		kill(-1, SIGCONT);
		while(wait(NULL) > 0);
	}*/
	
	
	// III. Close the program
	outFile.close();
}
