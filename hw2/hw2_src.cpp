// Assignment 2, 3320 CISC
// Shterenberg, Simon


#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int main()
{
// I. Initialize out stream
	std::ofstream outFile;
	
	
// II. Split execution between parent (P) and child (C) processes
	int pid = fork();
	
	
// III. End of program
	return 0;
}
