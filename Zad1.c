#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define ITEMS_COUNT 10

uint16_t unique = 0;

typedef struct 
{
    uint16_t Number;
    char Description[251];
    double Weight;
    double Price;
}Item;

typedef struct node {
    Item data;
    struct node* next;
} node_t;

int randNum(int min,int max);
double randReal(double min, double max);
void randName(char* name);
void generateData(Item* data);
void push(node_t** list,Item data);
double totalItemsWeight(node_t* items);
node_t *minPriceItem(node_t* items);
void Print(node_t *list);

int main()
{
    srand(time(NULL));
    node_t *head = NULL;
    for(int i=0;i<ITEMS_COUNT;i++)
    {
        Item temp;
        generateData(&temp);
        push(&head,temp);
    }
    Print(head);

    return 0;
}

void Print(node_t *list)
{
    node_t* current = list;
    while(current != NULL)
    {
        fprintf(stdout,"%4hu %90s %4.2lf %5.2lf\n",
        current->data.Number,current->data.Description,
        current->data.Weight,current->data.Price);
        current = current->next;
    }
    fprintf(stdout,"Total weight:%.2lf\n",totalItemsWeight(list));
    node_t *minPrice = minPriceItem(list);
    fprintf(stdout,"Min price element:\n");
    fprintf(stdout,"%4hu %90s %4.2lf %5.2lf\n",
    minPrice->data.Number,minPrice->data.Description,
    minPrice->data.Weight,minPrice->data.Price);
}

node_t *minPriceItem(node_t* items)
{
    node_t* current = items;
    if(current == NULL)
    {
        return NULL;
    }
    node_t *minPrice = current;
    current = current->next;
    while(current != NULL)
    {
        if(minPrice->data.Price > current->data.Price)
        {
            minPrice = current;
        }
        current = current->next;
    }
    return minPrice;

}

double totalItemsWeight(node_t* items)
{
    node_t* current = items;
    if(current == NULL)
    {
        return -1;
    }
    double sumWeights = 0;
    while(current != NULL)
    {
        sumWeights += current->data.Weight;
        current = current->next;
    }
    return sumWeights;
}

void generateData(Item* data){
    data->Number = unique;
    unique++;
    randName(data->Description);
    data->Weight = randReal(0.1,100.0);
    data->Price = randReal(1.0,1500.0);
}

void push(node_t** list,Item data){
    node_t* n = malloc(sizeof(node_t));
    n->data.Number = data.Number;
    strcpy(n->data.Description,data.Description);
    n->data.Weight = data.Weight;
    n->data.Price = data.Price;
    n->next = *list;
    *list = n;
}

int randNum(int min,int max)
{
    return min + rand() % (max - min + 1);
}

double randReal(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void randName(char* name)
{
    int i = 0;
    int lettersInWord;
    int numberOfWords;
    numberOfWords = randNum(5,10);
    name[i] = randNum('A','Z');
    i++;
    lettersInWord = randNum(1,10);
    for(int j = 1;j<lettersInWord;j++)
    {
        name[i] = randNum('a','z');
        i++;
    }
    name[i] = ' ';
    i++;
    numberOfWords--;
    while(numberOfWords > 0)
    {
        lettersInWord = randNum(1,10);
        for(int j = 0;j<lettersInWord;j++)
        {
            name[i] = randNum('a','z');
            i++;
        }
        name[i] = ' ';
        i++;
        numberOfWords--;
    }
    name[i] = '\0';
    
    
}