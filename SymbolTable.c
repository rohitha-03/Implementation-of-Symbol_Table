#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 100
#define TABLE_SIZE 101 

typedef struct variable_tag
{
    char var[MAX_SIZE];
    int data;
    struct  variable_tag *next;
}variable;

typedef struct Stable_tag
{
    variable *table[TABLE_SIZE];
    struct Stable_tag *prev_level;
}SymbolTable;

SymbolTable *current_level=NULL;

int hash(char s[MAX_SIZE])
{
   int i,h;
   i=0;h=0;
   int n = strlen(s) - 1;
   while(s[i] != '\0')
   {
        int m = (int)s[i];
        h = h + m * pow(10,n-i);
        i++;
   }
   return (h%TABLE_SIZE);
}

void Initialize_Scope()
{
    printf("initializing new level\n");
    SymbolTable *new_level = (SymbolTable *)malloc(sizeof(SymbolTable));
    for(int i=0;i<TABLE_SIZE;i++)
    {
        new_level->table[i] = NULL;
    }
    new_level->prev_level = current_level;
    current_level = new_level;
}

void Insert(char str[MAX_SIZE],int value)
{
    int index = hash(str);
    variable *temp = (variable *)malloc(sizeof(variable));
    strcpy(temp->var,str);
    temp->data = value;
    temp->next = current_level->table[index];
    current_level->table[index] = temp;
}

int Lookup_in_level(SymbolTable *level,char str[MAX_SIZE])
{
    int index = hash(str);
    variable *ptr = level->table[index];
    while(ptr!= NULL)
    {
        if(strcmp(ptr->var,str)==0)
        {
            return ptr->data;
        }
        ptr = ptr->next;
    }
    return -1;
}

void Lookup(char str[MAX_SIZE])
{
    SymbolTable *level = current_level;
    int k,flag=0;
    while(level != NULL && flag==0)
    {
        k = Lookup_in_level(level,str);
        if(k != -1)
        {
            printf("%d \n",k);
            flag=1;
        }
        level = level->prev_level;
    }
    if(flag==0)
    {
        printf("Error no variable found\n");
    }
}

void Finalyze_Scope()
{
    printf("Deleting current level\n");
    SymbolTable *nptr = current_level;
    current_level = current_level->prev_level;
    free(nptr);
}

int main()
{
    FILE *fp = fopen("input.txt","r");
    char word[MAX_SIZE];
    char name[MAX_SIZE];
    int val;
    if(fp == NULL)
    {
        printf("error opening in file");
    }
    else
    {
        while (fscanf(fp, "%s", word) != EOF)
        {
            if(strcmp(word,"begin")==0)
            {
                Initialize_Scope();
            }
            else if(strcmp(word,"assign")==0)
            {
                fscanf(fp, "%s", name);
                fscanf(fp,"%s",word);
                val = atoi(word);
                Insert(name,val);

            }
            else if(strcmp(word,"print")==0)
            {
                fscanf(fp,"%s",name);
                Lookup(name);
            }
            else if(strcmp(word,"end")==0)
            {
                Finalyze_Scope();
            }
        }
    }

    fclose(fp);
    return 0;
}