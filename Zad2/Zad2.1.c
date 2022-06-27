#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>

int sumOfNums(int num);
int SumOfNumsInFile(char *fname);

int main(int argc,char** argv)
{
    int p[2];
    if(pipe(p) < 0)
    {
        perror("pipe");
    }

    pid_t pid;
    for(int i=1;i<argc;i++)
    {
        pid = fork();
        if(pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(pid == 0)
        {
            int sum = SumOfNumsInFile(argv[i]);
            printf("--%s - %d\n",argv[i],sum);
            if(sum == -1)
            {
                exit(EXIT_FAILURE);
            }
            write(p[1],&sum,sizeof(int));
            fprintf(stdout,"%s - %d\n",argv[i],sum);
            exit(EXIT_SUCCESS);
        }
    }
    int sum = 0,num;
    for(int i=1;i<argc;i++)
    {
        wait(NULL);
    }
    while((read(p[0],&num,sizeof(int))) != -1)
    {
        printf("check\n");
        sum += num;
    }
    fprintf(stdout,"From all:%d\n",sum);
    return 0;
}

int SumOfNumsInFile(char *fname)
{
    int i = 0;
    int num;
    int sum = 0;
    FILE *f;
    f = fopen(fname,"r");
    if(f == NULL)
    {
        perror(fname);
        return -1;
    }
    while(fscanf(f,"%d",&num) != EOF)
    {
        sum += sumOfNums(num);
    }
    fclose(f);
    return sum;
}
int sumOfNums(int num)
{
    int sum = 0;
    while(num != 0)
    {
        sum += num%10;
        num /= 10;
    }
    return sum;
}