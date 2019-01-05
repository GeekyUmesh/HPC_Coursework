#include <time.h>
#include <pthread.h>
#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
 

int n_passwords = 4;

char *encrypted_passwords[] = {

 "$6$KB$Ip9USzIu4RGq195kU648P/AqIUcEpv5gYTJSMBlXCgXEHnvggJI2YqWJc9CWbzCATg8xpaevYXcF8mlZJheJG0",

"$6$KB$R9NGlRbiGb6ihCvwi2DDKoXs.UaWHGLxMm/.gbx17yEqBMkwR3Nf5LWkozVdBxWMPRyPjxKUaB8NgtcQcFLni.",

"$6$KB$cVsORgWA1ekhpjH3rjs.vP0D1758tB1Vb4zBrlq5zC0NZELmJpFklXnuO87ylRFXc8rPY9Yk2f.V.aNVltul41",

"$6$KB$UH1ItfoWG9QUlMKf0LzfFcIxrUF0DbMz0x3gscXlOaV65KLv1CYqo5rYIDhjsW9TsHpt5Sr9Zmbf.W1ZlWCBF1"
};

 
void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

 

void crack(){
   int k;
  pthread_t t1, t2;

  void *first();
  void *second();
  
  for(k=0;k<n_passwords;k<k++) {
    pthread_create(&t1, NULL, first, encrypted_passwords[k] );
    pthread_create(&t2, NULL, second, encrypted_passwords[k]);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}
}

void *first(char *salt_and_encrypted){
 int a,b,c;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='M'; a++){
    for(b='A'; b<='Z'; b++){
       for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a,b,c);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
       }
    }
  }
printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
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

void *second(char *salt_and_encrypted){
int x, y, z;     
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;  
  substr(salt, salt_and_encrypted, 0, 6);

  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
       for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
       }
    }
  }
   printf("%d solutions explored\n", count);
}

 

int main(int argc, char *argv[]) {
   
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  
    crack();
    
    
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 


  return 0;
}
