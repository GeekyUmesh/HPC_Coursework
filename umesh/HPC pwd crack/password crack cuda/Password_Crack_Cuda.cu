#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************
  This program gives an example of a poor way to implement a password cracker
  in CUDA C. It is poor because it acheives this with just one thread, which
  is obviously not good given the scale of parallelism available to CUDA
  programs.
  
  The intentions of this program are:
    1) Demonstrate the use of __device__ and __global__ functions
    2) Enable a simulation of password cracking in the absence of library 
       with equivalent functionality to libcrypt. The password to be found
       is hardcoded into a function called is_a_match.   

  Compile and run with:
    nvcc -o Password_Crack_Cuda Password_Crack_Cuda.cu 
    ./Password_Crack_Cuda
   
  Dr Kevan Buckley, University of Wolverhampton, 2018
*****************************************************************************/

/****************************************************************************
  This function returns 1 if the attempt at cracking the password is 
  identical to the plain text password string stored in the program. 
  Otherwise,it returns 0.
*****************************************************************************/

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

__device__ int is_a_match(char *attempt) {
  char plain_password1[] = "AS1234";
  char plain_password2[] = "UM9849";
  char plain_password3[] = "SN7832";
  char plain_password4[] = "RP8720";


  char *first = attempt;
  char *second = attempt;
  char *third = attempt;
  char *fourth = attempt;
  char *password1 = plain_password1;
  char *password2 = plain_password2;
  char *password3 = plain_password3;
  char *password4 = plain_password4;

  while(*first == *password1) { 
   if(*first == '\0') 
    {
	printf("Password Found: %s\n",plain_password1);
      break;
    }

    first++;
    password1++;
  }
	
  while(*second == *password2) { 
   if(*second == '\0') 
    {
	printf("Password Found: %s\n",plain_password2);
      break;
    }

    second++;
    password2++;
  }

  while(*third == *password3) { 
   if(*third == '\0') 
    {
	printf("Password Found: %s\n",plain_password3);
      break;
    }

    third++;
    password3++;
  }

  while(*fourth == *password4) { 
   if(*fourth == '\0') 
    {
	printf("Password Found: %s\n",plain_password4);
      return 1;
    }

    fourth++;
    password4++;
  }
  return 0;

}


/****************************************************************************
  The kernel function assume that there will be only one thread and uses 
  nested loops to generate all possible passwords and test whether they match
  the hidden password.
*****************************************************************************/

__global__ void  kernel() {
char w, x, y, z;
  
  char password[7];
  password[6] = '\0';

int q = blockIdx.x+65;
int t = threadIdx.x+65;
char firstInitial = q; 
char secondInitial = t; 
    
password[0] = firstInitial;
password[1] = secondInitial;
	for(w='0'; w<='9'; w++){
	  for(x='0'; x<='9'; x++){
	   for(y='0'; y<='9'; y++){
	     for(z='0'; z<='9'; z++){
	        password[2] = w;
	        password[3] = x;
	        password[4] = y;
	        password[5] = z; 
	      if(is_a_match(password)) {
		//printf("Success");
	      } 
             else {
	       // printf("tried: %s\n", password);		  
	         }
	      }
	   }
	}
    }
}


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed
					, (time_elapsed/1.0e9)); 
  return 0;
}



