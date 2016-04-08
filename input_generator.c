#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc<5)
    {
        printf("Usage: input_generator <number of processes>
                 <average number of process arrivals per unit time>
                 <average burst time per proces> <number of priority levels>");
    }
}