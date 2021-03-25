/*
  Name: Karanveer Sandhu
  PID: 6096890
  I hearby declare that this source code is original
  and not anyone else's work.
*/

/*
  Program Description:
  This program finds all the prime numbers from 1 - n
  (n is specified in the #define part)
  using some number of processes. The prime numbers are then
  outputed to the screen.
  Usage: mpirun -np <#ofprocesses> countprimes
*/

#include <mpi.h>
#include <stdio.h>

#define LASTPRIME 50000

int check_prime(int n)
{
  int i = n - 1; // number to check to see if n is divisible by it.
  int isPrime = 1; // whether the number n is prime.
  int isDone = 0;  // whether we are done checking if the number is prime.
  while (!isDone && i > 1)
  {
    if (n % i == 0) // if n is divisible by i
    {
      isPrime = 0; // n is not prime
      isDone = 1;  // we are done with the loop
    }
    i--; // go down to next number.
  }

  // return whether it is prime or not.
  return isPrime;
}

int main (int argc, char * argv[])
{
  long int i;
  int id; // Process rank / which process.
  int p; // Number of processes
  double elapsedTime; // amount of time elapsed.
  int count; // the number of primes found by each process.
  int global_count; // total number of primes
  
  // Do a multiprocess program and put id and rank into variables.
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  // Start timer
  MPI_Barrier(MPI_COMM_WORLD);
  elapsedTime = - MPI_Wtime();
  
  // for each number from 2 to the number. Each process check every pth number
  count = 0;
  for (i = id + 2; i < LASTPRIME; i += p)
  {
    if (check_prime(i)) // if the number is a prime.
    {
      // increment the counter.
      count++;
      // print out the primes and which process found it.
      printf("Process %d found prime number %d\n", id, i);
      fflush(stdout);
    }
  }

  MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Stop the timer
  elapsedTime += MPI_Wtime();
  
  // print how much time it took.
  if (id == 0)
  {
    printf("The time it took is %8.6f seconds\n", elapsedTime);
    fflush(stdout);
  }

  // Done with multiprocessor communications.
  MPI_Finalize();
  
  // print how many primes were there.
  if (id == 0)
  {
    printf("There are %d many primes from 1 to %d.\n", global_count, LASTPRIME);
  }
  return 0;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~Thank you grading my program~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~