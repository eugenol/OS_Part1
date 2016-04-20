/********************************************************
* Operating Systems for Engineers: Assignment           *
* Group Members:    Eugene Olivier      205510031       *
*                   David Parker        213             *
*                   Ahmad Bin Khalid    213             *
*
*
*********************************************************/

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

//Function Prototypes
unsigned long int get_seed(void);

int main(int argc, char **argv)
{
    //Input values
    long int num_processes;
    double ave_num_proc_per_time;
    double ave_burst_time_per_proc;
    long int num_priority_levels;
    
    unsigned long int seed;
    unsigned long int burst_time;
    unsigned long int priority;
    unsigned int arrival_time = 0;
    
    FILE * fptr;
    gsl_rng * r; //Instance of random number generator

    //Check if all the arguments have been passed
    if(argc<5)
    {
        printf("Usage: input_generator <number of processes> <average number of process arrivals per unit time> <average burst time per proces> <number of priority levels>\n");
        return EXIT_FAILURE;
    }

    //Convert arguments to numbers
    num_processes = strtol(argv[1],NULL,10);
    ave_num_proc_per_time = atof(argv[2]);
    ave_burst_time_per_proc = atof(argv[3]);
    num_priority_levels = strtol(argv[4],NULL,10);
        
    fptr = fopen("input.txt","w"); //Open file for writing
    
    
    r = gsl_rng_alloc(gsl_rng_mt19937); //Create instance of random number generator // (gsl_rng_taus);
    
    //Check if rng is created
    if(!r)
    {
        printf("Error: Could not instantiate random number generator.\n");
        return EXIT_FAILURE; 
    }

    seed = get_seed(); //get seed value from entropy pool  
    gsl_rng_set (r, seed); //Seed the rng 

    for(long int i = 0; i < num_processes; i++)
    {
        // arrival time using poisson distribution
        if(i)  
            arrival_time +=  gsl_ran_poisson(r, ave_num_proc_per_time);
        
        // burst time using exponential distribution
        burst_time =  (unsigned long int )ceil(gsl_ran_exponential(r, ave_burst_time_per_proc));
        
        // priority using random number
        //priority = gsl_rng_get(r) % num_priority_levels + 1;
        priority = gsl_rng_uniform_int(r,num_priority_levels);
        
        //print to file
        fprintf(fptr,"Process%lu %u %lu %lu\n",i,arrival_time,burst_time,priority);
    }
     
    fclose(fptr); //Close file
    gsl_rng_free (r); //Free memory associated with the generator
    
    return 0;
}

// Get seed value from linux entropy pool
unsigned long int get_seed(void)
{
    unsigned long int seed =0;
    FILE *fptr;
    
    fptr = fopen("/dev/urandom","r");
    fread(&seed,sizeof(unsigned long int),1,fptr);
    fclose(fptr);
    
    return seed;
}