#include <stdio.h>
#include <pthread.h>

struct fact_params
{
    int count;
};

void* fact(void* parameters)
{
    struct fact_params *p = (struct fact_params *)parameters;
    int i, factorial = 1;
    void *pp;

    if(p->count != 0)
    {
        for(i = 1; i <= p->count; i++)
            factorial = factorial * i;
    }
    // TODO 3: Return the factorial value
    return NULL;
}

int main()
{
    int n;
    void *p;
    pthread_t thread_id;
    struct fact_params thread_args;

    printf("Enter a number: ");
    scanf("%d", &n);
    thread_args.count = n;

    // TODO 1: Create the thread and pass thread_args as an argument

    // TODO 2: Wait for thread and expect the return value in p
    printf("Factorial = %ld\n", (unsigned long)p);

    return 0;
}
