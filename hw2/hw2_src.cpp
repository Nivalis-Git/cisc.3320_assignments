// Assignment 2, 3320 CISC
// Shterenberg, Simon


#include <fstream>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include <semaphore.h>
	#include <fcntl.h>
	#include <sys/stat.h>
#include <vector>
#include <random>


int main()
{
// Setting up out-stream, semaphores, and random number generator.
	std::ofstream outFile("hw2_output.txt");
	
	std::vector<std::string> vRsrc;  // a vector to associate resource names with an index
	vRsrc.push_back("printer");
	vRsrc.push_back("plotter");
	vRsrc.push_back("scanner");
	
	sem_t *sem_printer, *sem_plotter, *sem_scanner;
	sem_printer = sem_open("printer", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 5);
	sem_plotter = sem_open("plotter", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 6);
	sem_scanner = sem_open("scanner", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 4);
	
	std::random_device rnd;
	
	
// .
	int pid = fork();
	
	if (pid == 0)
	{
		std::uniform_int_distribution<int> dstr(0,2);
		std::string rsrc_name( vRsrc[dstr(rnd)] );
		int rsrc_qty;
		int pid = fork();
		
		if (pid == 0)
		{
			raise(SIGSTOP);
			outFile << "dsds\n";
			sem_t *rsrc_sem = sem_open(rsrc_name.c_str(),0);
			sem_getvalue(rsrc_sem, &rsrc_qty);
			
			outFile << "PID: " << getpid() << "\t" << "Resource Type: " << rsrc_name << "\n";
			outFile << rsrc_qty << "\n";
			outFile.close();
		} 
		
		if (pid > 0)
		{
			//std::uniform_int_distribution<int> dstr(0,2);
			
			//std::string rsrc_name( vRsrc[dstr(rnd)] );
			sem_t *rsrc_sem = sem_open(rsrc_name.c_str(),0);
			//int rsrc_qty;
			sem_getvalue(rsrc_sem, &rsrc_qty);
			
			outFile << "PID: " << getpid() << "\t" << "Resource Type: " << rsrc_name << "\n";
			outFile << rsrc_qty << "\n";
			
			kill(-1, SIGCONT);
			outFile.close();
		}
	}
	
	if (pid > 0)
	{
		wait(NULL);
		outFile.close();
	}
	
	
// . End of program
	return 0;
}
