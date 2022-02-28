// Assignment 1, 3320 CISC
// Shterenberg, Simon


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
		outFile << "I am the grandparent process. PID is " << getpid() << "\n";
		outFile.close();
		kill(-1, SIGCONT);  // continues C
		wait(NULL);
	}
	
	// ii. branch for child process (C)
	if (pid == 0)
	{
		raise(SIGSTOP);  // stop process C so that P can print first
		int pid_c = fork();
		
		// a. branch for process C
		if (pid_c > 0)
		{
			outFile << "I am the parent process. PID is " << getpid() << "\n";
			outFile.close();
			kill(-1, SIGCONT);  // continues GC
			wait(NULL);
		}
		
		// b. branch for grandchild process (GC)
		if (pid_c == 0)
		{
			raise(SIGSTOP);  // stop GC so that C can print first
			outFile << "I am the grandchild process. PID is " << getpid() << "\n";
			outFile.close();
		}
	}
	
	
// III. End of program
	return 0;
}
