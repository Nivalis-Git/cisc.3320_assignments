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


void unlink(std::vector<char*> &vSem);


int main()
{
// I. Setting up out-stream, semaphores, and random number generator.
	std::ofstream outFile("hw2_output.txt");	
	
	sem_t *sem_printer, *sem_plotter, *sem_scanner;
	sem_printer = sem_open("printer", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 5);
	sem_plotter = sem_open("plotter", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 6);
	sem_scanner = sem_open("scanner", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 4);
	
	std::vector<char*> vRsrc;  // a vector to associate the semaphores with an index
	vRsrc.insert( vRsrc.end(), {"printer", "plotter", "scanner"} );
	
	std::random_device rnd;
	
	
// .
	//for (int i = 0; i < 4; i)
	
	int pid = fork();
	
	if (pid == 0)
	{
		std::uniform_int_distribution<int> dstr(1,3);
		char* rsrc_name = vRsrc[dstr(rnd)-1];
		sem_t *rsrc_sem = sem_open(rsrc_name, 0);
		
		outFile << "Child PID: " << getpid()
		        << "\t\t" << "Resource Type: " << rsrc_name << "\n";
		
		outFile << "Child PID: " << getpid();		
		while (sem_wait(rsrc_sem) != 0)
		{
		  outFile << "\t\t" << "Request Status: Failed" << "\n";
		  sleep(dstr(rnd)+1);
		}
		outFile << "\t\t" << "Request Status: Succeeded" << "\n\n";
		
		sleep(dstr(rnd));
		sem_post(rsrc_sem);
		sem_close(rsrc_sem);
		outFile.close();
	}
	
	if (pid > 0)
	{
		wait(NULL);
		outFile.close();
	}
	
	
// . End of program
	unlink(vRsrc);
	return 0;
}

void unlink(std::vector<char*> &vSem)
{
  for (char* sem : vSem)
  {
    sem_unlink(sem);
  }
}
