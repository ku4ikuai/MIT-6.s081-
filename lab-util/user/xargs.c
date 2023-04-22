#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAX_LINE_LEN 100

int read_line(char* buf)
{
    char* p = buf;
    while(read(0,p,1) > 0)
    {
        if(*p != '\n')
        {
            p++;
        }
        else
        {
            *p = 0;
            return 0;
        }

    }
    *p = 0;
    return 1; 
}

int main(int argc, char *argv[])  // echo bye | xargs echo hello
{
    int read_end = 0;
    char line[MAX_LINE_LEN];
    char *args[MAXARG];
    int pid = 0;

    for(int i = 1; i < argc ; i++)
    {
        args[i-1] = argv[i]; // echo hello
    }

    do
    {
        read_end = read_line(line); // bye
        //fprintf(1,"line is %s\n",line);
        if(line[0] == 0)
        {
            continue;
        }
        pid = fork();

        if(pid == 0) // child process
        {
            args[argc-1] = line; // echo hello bye
            //fprintf(1,"argv[1] is %s\n",argv[1]);
            //fprintf(1,"args is %s\n",args[0]);
            exec(argv[1],args);
            fprintf(2,"exec %s error\n",args[0]);
            exit(1);
        }
        else
        {
            wait(0);
        }

    }while(read_end != 1 );
    

    exit(0);

}