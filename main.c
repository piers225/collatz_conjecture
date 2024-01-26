#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    long  value;
    struct Node *next; 
};

int containsValue(struct Node *head, long  targetValue) 
{
    struct Node *current = head;
    while (current != NULL) 
    {
        if (current->value == targetValue) 
        {
            return 1; 
        }
        current = current->next;
    }
    return 0; 
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

void filePrintNodes(FILE *file, struct Node *head, int number) 
{
    fprintf(file, "%ld -", number);
    struct Node *current = head;
    while (current != NULL) 
    {
        fprintf(file, " %ld -> ", current->value);
        current = current->next;
    }
    fprintf(file, "\n");
}

void collatzConjecture(struct Node *head, struct Node *previous) 
{
    struct Node *current = (struct Node *)malloc(sizeof(struct Node));
    current->next = NULL;
    if (previous->value % 2 == 0) 
    {
        current->value = previous->value / 2;
    }
    else 
    {
        current->value = 3 * previous->value + 1;
    }

    if (containsValue(head, current->value) == 1)
    {
        previous->next = current;
        return;
    }

    previous->next = current;

    if (current->value != 1) 
    {
        collatzConjecture(head, current);
    }
}
 
int main() 
{
    FILE *file = fopen("output.txt", "w");
    const int MAX_ITERATIONS = 999999;
    for (long  number = 2; number < MAX_ITERATIONS; number++)
    {
        struct Node *head = (struct Node *)malloc(sizeof(struct Node));
        head->value = number;
        collatzConjecture(head, head);
        if (containsValue(head, 1) == 0)
        {
            filePrintNodes(file, head, number);
        }
        freeMemory(head);
        double percentage = ((double)number / MAX_ITERATIONS) * 100;
        printf("Percentage Completion: %.2f%%\r", percentage);
        fflush(stdout);
    }
    fclose(file);
    printf("\nComplete\n");
    return 0;  // Exit successfully
}