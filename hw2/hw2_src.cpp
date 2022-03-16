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
// I. Setting up out-stream, semaphores, and random number generator.
	std::ofstream outFile("hw2_output.txt");	
	
	sem_t *sem_printer, *sem_plotter, *sem_scanner;
	sem_printer = sem_open("printer", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 5);
	sem_plotter = sem_open("plotter", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 6);
	sem_scanner = sem_open("scanner", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 4);
	
	std::vector<sem_t*> vSem;  // a vector to associate the semaphores with an index
	vSem.insert( vSem.end(), {sem_printer, sem_plotter, sem_scanner} );
	
	int num;
	sem_getvalue(sem_printer, &num);
	outFile << num << "\n";
	
	std::random_device rnd;
	
	
// .
	int pid = fork();
	
	if (pid == 0)
	{
		std::uniform_int_distribution<int> dstr(0,2);
		//sem_t *rsrc_sem = sem_open(rsrc_name.c_str(), 0);
		sem_t *rsrc_sem = vSem[dstr(rnd)];
		int rsrc_qty;
		sem_getvalue(rsrc_sem, &rsrc_qty);
		
		outFile << "PID: " << getpid() << "\t" << "Resource Type: " << rsrc_name << "\n";
		outFile << rsrc_qty << "\n";
		
		outFile.close();
		//sem_close(rsrc_sem);
	}
	
	if (pid > 0)
	{
		wait(NULL);
		outFile.close();
	}
	
	
// . End of program
	return 0;
}