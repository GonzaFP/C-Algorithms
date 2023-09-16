#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
 int number;
 struct  Node *nextAddress;
}node;
typedef struct stack
{
 char string[10];
 int top;
}stack;
int main(void)
{
 char word[] = "HELLO";
 stack rever;
 rever.top = -1;
 if (rever.top == 9)
 {
  return 1;
 }
 for (int i = 0; i < 5; i++)
 {
   rever.string[i] = word[i];
   rever.top++; 
 }
 printf("%s\n",word);
 for (int j = 0; j < 5; j++)
 {
  word[j] = rever.string[rever.top];
  rever.top--;
 }
 printf("%s\n",word);
 // int numbers[] = {1,2,3,4};
 // node * head = NULL;
 // for (int i = 0; i < 4; i++)
 // {
 //   node *ptr = malloc(sizeof(node));
 //  ptr->number = numbers[i];
 //  ptr->nextAddress = head;
 //  head = ptr;
 // }
 //  node *temp = head;

 // for (int j = 0; j < 4; j++)
 // {
 //  printf("%d\n", temp->number);
 //  temp = temp->nextAddress;
 // }
}