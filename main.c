#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node 
{
    long  value;
    struct Node *next; 
};

bool containsValue(struct Node *head, long targetValue) 
{
    struct Node *current = head;
    while (current != NULL) 
    {
        if (current->value == targetValue) 
        {
            return true; 
        }
        current = current->next;
    }
    return false; 
}

int lastNumber(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL) 
    {
        current = current->next;
    }
    return current->value; 
}
 
void freeMemory(struct Node *head) 
{
    struct Node *current = head;
    while (current != NULL) 
    {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
}

void filePrintNodes(struct Node *head, long number) 
{
    FILE *file = fopen("output.txt", "w");
    fprintf(file, "%ld -", number);
    struct Node *current = head;
    while (current != NULL) 
    {
        fprintf(file, " %ld -> ", current->value);
        current = current->next;
    }
    fprintf(file, "\n");
    fclose(file);
}

bool collatzConjecture(struct Node *head, struct Node *previous, long startNumber) 
{
    struct Node *current = (struct Node *)malloc(sizeof(struct Node));
    current->next = NULL;
    long value = (previous->value & 1) == 0 ?
        previous->value / 2 :
        3 * previous->value + 1;
    current->value = value;

    if (value == 1) 
    {
        previous->next = current;
        return true;
    }

    if (value > 1 && value < startNumber) 
    {
        previous->next = current;
        return true;
    }

    if (containsValue(head, value))
    {
        previous->next = current;
        return false;
    }

    previous->next = current;

    return collatzConjecture(head, current, startNumber);
    
}
 
int main() 
{
    const int MAX_ITERATIONS = 9999999;
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    head->next = NULL;
    for (long  number = 1; number < MAX_ITERATIONS; number++)
    {
        head->value = number;
        bool result = collatzConjecture(head, head, number);
        if (result == false)
        {
            filePrintNodes(head, number);
            break;
        }
        freeMemory(head->next);
        head->next = NULL;
        double percentage = ((double)number / MAX_ITERATIONS) * 100;
        printf("Percentage Completion: %.2f%%\r", percentage);
        fflush(stdout);
    }
    printf("\nComplete\n");
    return 0;  // Exit successfully
}