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

struct Node* createNode(long value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->next = NULL;
    node->value = value;
    return node;
}

bool collatzConjecture(struct Node* head, struct Node* previous, long startNumber) 
{
    long previousValue = previous->value;
    long value = (previousValue & 1) == 0 ? previousValue / 2 : 3 * previousValue + 1;
    struct Node* current = createNode(value);

    while (value < 1 || value >= startNumber)
    {
        if (containsValue(head, value) == true)
        {
            previous->next = current;
            return false;
        }
        previous->next = current;
        previous = current;
        previousValue = previous->value;
        value = (previousValue & 1) == 0 ? previousValue / 2 : 3 * previousValue + 1;
        current = createNode(value);
    }

    previous->next = current;
    return true;
}
 
int main() 
{
    const int MAX_ITERATIONS = 100000000;
    const int START = 2;
    struct Node *head = createNode(0);
    for (long  number = START; number < MAX_ITERATIONS; number++)
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
        if (number % 100 == 0)
        {
            double percentage = ((double)number / MAX_ITERATIONS) * 100;
            printf("Percentage Completion: %.2f%%\r", percentage);
            fflush(stdout);
        }
    }
    printf("\nComplete\n");
    return 0;  // Exit successfully
}