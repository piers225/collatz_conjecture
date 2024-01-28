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

bool debugCollatzConjecture(struct Node* head, long startNumber) 
{
    struct Node* previous = head;
    long previousValue = previous->value;

    while (previousValue >= startNumber || previousValue < 1)
    {
        long value = (previousValue & 1) == 0 ? previousValue >> 1 : 3 * previousValue + 1;
        struct Node* current = createNode(value);

        if (containsValue(head, value) == true)
        {
            return false;
        }

        previous->next = current;
        previous = current;
        previousValue = previous->value;

        if (previousValue == 1) 
        {
            return true;
        }
    }

    return true;
}
 
bool collatzConjecture(long startNumber) 
{
    long previousValue = startNumber;

    while (previousValue >= startNumber || previousValue < 1)
    {
        previousValue = (previousValue & 1) == 0 ? previousValue >> 1 : 3 * previousValue + 1;
    }

    return true;
}

int main() 
{
    const long MAX_ITERATIONS = 1000000000000;
    const long START = 2;
    const long PRINT_INCREMENT = (MAX_ITERATIONS / 100);
    for (long  number = START; number < MAX_ITERATIONS; number++)
    {
        bool result = collatzConjecture(number);

        if (result == false)
        {
            struct Node *head = createNode(number);
            debugCollatzConjecture(head, 1);
            filePrintNodes(head, number);
            freeMemory(head);
            break;
        }

        if (number % PRINT_INCREMENT == 0)
        {
            double percentage = ((double)number / MAX_ITERATIONS) * 100;
            printf("Percentage Completion: %.2f%%\r", percentage);
            fflush(stdout);
        }
    }
    printf("\nComplete\n");
    return 0;  // Exit successfully
}