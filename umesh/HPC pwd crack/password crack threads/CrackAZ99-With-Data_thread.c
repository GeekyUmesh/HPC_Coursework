// To compile cc -o CrackAZ99-With-Data_thread CrackAZ99-With-Data_thread.c -lcrypt -pthread
#include <time.h>
#include <pthread.h>
#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
 

int n_passwords = 4;

char *encrypted_passwords[] = {

 "$6$KB$yQGJw.Sdx7s6aoXdtCWYUPmABAulKV8kR11LNS7sDqdXm49UzEJgoF59WuYjM5zTWEcc/YA208QToKjJdxFbL/",

"$6$KB$VRF6JntIKJrvSJye.xLvMrLouQnoikD.82AjM8bOMVh2OUojyX3om4B8VX9IDvaasrWT7DirQQyXu31CZ1Anx1",

"$6$KB$xeBtIZZU6LsXok16.yMo.fgGNqzd0llnKW7xL.DBnxKZasKaSnoxunsRTgvZ3t/icn3M.UpM6I2nrk7pZtqKs.",

"$6$KB$xwNLscq42S8JSSpTcE59XO6x5aA5oY15cnYd1PAibDmhFFrVaXaClQiig540xCwsqLJLuug8udvR9F51FgpNg/"
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
