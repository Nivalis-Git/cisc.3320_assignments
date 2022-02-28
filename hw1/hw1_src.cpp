#include <string>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

int main()
{
	// I. Initialize out stream
	std::ofstream outFile("hw1_output.txt");
	
	
	// II. Split execution between parent (P) and child (C) processes
	int pid = fork();  // duplicate current process P (P --> C)
	
	// i. branch for parent process (P)
	if (pid > 0)
	{
		string s("I am the grandparent process. PID is ");
		s.append( std::to_string(getpid()) );
		s.append("\n");
		outFile << s;
		kill(-1, SIGCONT);
		wait(NULL);
	}	
	
	// ii. branch for child process (C)
	if (pid == 0)
	{
		raise(SIGSTOP);
		int pid_c = fork();  // duplicate current process C (c --> GC)
		
		// a. branch for process C
		if (pid_c > 0)
		{
			string s("I am the parent process. PID is ");
			s.append( std::to_string(getpid()) );
			s.append("\n");
			outFile << s;
			kill(-1, SIGCONT);
			wait(NULL);
		}
		
		// b. branch for grandchild process (GC)
		if (pid_c == 0)
		{
			raise(SIGSTOP);
			string s("I am the grandchild process. PID is ");
			s.append( std::to_string(getpid()) );
			s.append("\n");
			outFile << s;
		}
	}
	
	
	// III. Close the program
	outFile.close();
}
