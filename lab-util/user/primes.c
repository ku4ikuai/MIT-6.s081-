#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// 并发版本的素数筛

void sieve(int* left_fd)
{
	int prime;
	int num;
	int pid;
	int right_fd[2];

	close(left_fd[1]);
	if(read(left_fd[0],&prime,sizeof(int)) == 0)
	{
		close(left_fd[0]);
		exit(0);
	}

	printf("prime %d\n",prime);

	pipe(right_fd);
	pid = fork();
	if(pid == 0)
	{
		sieve(right_fd);
	}
	else
	{
		while(read(left_fd[0],&num,sizeof(int)) != 0)
		{
			if(num % prime != 0)
			{
				write(right_fd[1],&num,sizeof(int));
			}
		}
		close(right_fd[1]);
		close(right_fd[0]);
		wait((int *)0);

	}
	
	exit(0);
}

int main()
{
	int pid;
	int fd[2];
	pipe(fd);

	pid = fork();
	if(pid == 0)
	{
		sieve(fd);
	}
	else
	{
		for(int i = 2 ; i <= 35 ;i++)
		{
			write(fd[1],&i,sizeof(int));
		}
		close(fd[1]);
		wait((int*)0);
	}
	
	close(fd[0]);
	exit(0);
}





