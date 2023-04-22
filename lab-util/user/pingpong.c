#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main()
{
	
	int fd1[2];
	int fd2[2];
	char buffer[1024];
	pipe(fd1);
	pipe(fd2);

	int pid = fork();
	if(pid == 0) //child process
	{
		read(fd1[0],buffer,sizeof(buffer));
		printf("%d: received %s\n",getpid(),buffer);
		write(fd2[1],"pong",4);
		
	}
	else // parent process
	{
		write(fd1[1],"ping",4);

		read(fd2[0],buffer,sizeof(buffer));
		printf("%d: received %s\n",getpid(),buffer);	
	}

	exit(0);

}