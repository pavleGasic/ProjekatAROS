#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t agent_thread = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_thread_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_thread_m = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_thread_p = PTHREAD_COND_INITIALIZER;

pthread_cond_t tobacco_thread =	PTHREAD_COND_INITIALIZER;
pthread_cond_t paper_thread =	PTHREAD_COND_INITIALIZER;
pthread_cond_t match_thread =	PTHREAD_COND_INITIALIZER;

int tobacco = 0;
int paper = 0;
int match = 0;

int agent_var = 1;
int smoker_tobacco_var = 0;
int smoker_match_var = 0;
int smoker_paper_var = 0;


void *agent(){
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutex1);
		while (agent_var==0){
			pthread_cond_wait(&agent_thread, &mutex1);
		}
		
		int random_number = rand() % 3;
		
		if(random_number == 0){
			agent_var = 0;
			tobacco = 1;
			paper = 1;
			printf("Uzmi tobacco i paper.");
			pthread_cond_signal(&paper_thread);
			pthread_cond_signal(&tobacco_thread);
		}
		
		else if(random_number == 1){
			agent_var = 0;
			tobacco = 1;
			match = 1;
			printf("Uzmi tobacco i match.");
			pthread_cond_signal(&tobacco_thread);
			pthread_cond_signal(&match_thread);
		}
		
		else if(random_number == 2){
			agent_var = 0;
			match = 1;
			paper = 1;
			printf("Uzmi match i paper.");
			pthread_cond_signal(&match_thread);
			pthread_cond_signal(&paper_thread);
		}

						
			pthread_mutex_unlock(&mutex1);
	}
}



int main(int argc, char *argv[]){
	
	
	return 0;
}
