#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int M;
int currentRow = 1;
pthread_mutex_t mutex;

void* Execute(void* arg);
int comp(const void* el1, const void* el2);

int main()
{
    pthread_mutex_init(&mutex,NULL);
    int N;
    fscanf(stdin,"%d %d",&N,&M);
    int *arr = malloc(sizeof(int) * M);
    pthread_t *th = malloc(sizeof(pthread_t) * N);
    char fname[30];
    for(int i=0;i<N + 1;i++)
    {
        int rowNum;
        char str[4];
        scanf("%s %d",str,&rowNum);

        for(int j=0;j<M;j++)
        {
            scanf("%d",&arr[j]);
        }
    }
    scanf("%s",fname);
    FILE* f = fopen(fname,"w");
    fclose(f);
    for(int i=0;i<N;i++)
    {
        int temp = i;
        pthread_create(&th[i],NULL,Execute,(void*)fname);
    }
    for(int i=0;i<N;i++)
    {
        pthread_join(th[i],NULL);
    }
    return 0;
}

void* Execute(void* arg)
{
    pthread_mutex_lock(&mutex);
    rewind(stdin);
    int rowNum = 0;
    int *arr = malloc(sizeof(int) * M);
    char str[4];
    while(rowNum != *(int*)arg)
    {
        fscanf(stdin,"%s %d",str,&rowNum);
    }
    char fname[30];
    printf("%s %d ",str,rowNum);
    for(int i=0;i<M;i++)
    {
        fscanf(stdin,"%d",&arr[i]);
        printf("%d",arr[i]);
    }
    qsort(arr,M,sizeof(arr[0]),comp);
    
    FILE *f = fopen((char*)arg,"a");
    fprintf(f,"%s %d ",str,rowNum);
    for(int i=0;i<M;i++)
    {
        fprintf(f,"%d ",arr[i]);
    }
    fprintf(f,"\n");
    pthread_mutex_unlock(&mutex);
    
}

int comp(const void* el1, const void* el2)
{
    return *(int*)el1 - *(int*)el2;
}