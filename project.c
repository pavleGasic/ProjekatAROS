//ukljucivanje potrebnih biblioteka
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//inicijalizacija MUTEX-a
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


//glavne NITI (main threads)
pthread_cond_t agent_thread = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_thread_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_thread_m = PTHREAD_COND_INITIALIZER;
pthread_cond_t smoker_thread_p = PTHREAD_COND_INITIALIZER;

//pomocne NITI(threads for help)
pthread_cond_t tobacco_thread =	PTHREAD_COND_INITIALIZER;
pthread_cond_t paper_thread =	PTHREAD_COND_INITIALIZER;
pthread_cond_t match_thread =	PTHREAD_COND_INITIALIZER;


//logicke promenljive koje sluze za laksi rad sa nitima
bool tobacco = false;
bool paper = false;
bool match = false;
bool agent_bool = true;
bool smoker_tobacco_bool = false;
bool smoker_match_bool = false;
bool smoker_paper_bool = false;

//potpisi funkcija
void* agent(void* ptr);
void* pusher_T(void* ptr);
void* pusher_P(void* ptr);
void* pusher_M(void* ptr);
void* smoker_T(void* ptr);
void* smoker_P(void* ptr);
void* smoker_M(void* ptr);

//main funkcija
int main(int argc, char *argv[]){
	
	
	return 0;
}


//funkcija agent
void *agent(void* ptr){
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutex1);
		while (agent_bool==false){
			pthread_cond_wait(&agent_thread, &mutex1);
		}
		
		int random_number = rand() % 3;
		
		if(random_number == 0){
			agent_bool = false;
			tobacco = true;
			paper = true;
			printf("Uzmi tobacco i paper.");
			pthread_cond_signal(&paper_thread);
			pthread_cond_signal(&tobacco_thread);
		}
		
		else if(random_number == 1){
			agent_bool = false;
			tobacco = true;
			match = true;
			printf("Uzmi tobacco i match.");
			pthread_cond_signal(&tobacco_thread);
			pthread_cond_signal(&match_thread);
		}
		
		else if(random_number == 2){
			agent_bool = false;
			match = true;
			paper = true;
			printf("Uzmi match i paper.");
			pthread_cond_signal(&match_thread);
			pthread_cond_signal(&paper_thread);
		}

						
			pthread_mutex_unlock(&mutex1);
	}
	return 0;
}


//pusher funkcije
void * pusher_T(void* ptr){
	
	
	while(1){
		
		pthread_mutex_lock(&mutex1);
		
		while(!tobacco){
			pthread_cond_wait(&tobacco_thread,&mutex1);
		}
		
		if(paper){
			paper = false;
			agent_bool = false;
			smoker_match_bool = true;
			printf("Pozovi u rad match smoker-a.\n");
			pthread_cond_signal(&smoker_thread_m);
		}
		if(match){
			match = false;
			agent_bool = false;
			smoker_paper_bool = true;
			printf("Pozovi u rad paper smoker-a.\n");
			pthread_cond_signal(&smoker_thread_p);
		}
		
		pthread_mutex_unlock(&mutex1);
		
	}
	return 0;
}

void* pusher_P(void*ptr){
	
	while(1){
		pthread_mutex_lock(&mutex1);
	
		while(!paper){
			pthread_cond_wait(&paper_thread, &mutex1);
		}
	
		if(tobacco){
			tobacco = false;
			agent_bool = false;
			smoker_match_bool = true;
			printf("Pozovi u rad match smoker-a.\n");
			pthread_cond_signal(&smoker_thread_m);
		}
	
		if(match){
			match = false;
			agent_bool = false;
			smoker_tobacco_bool = true;
			printf("Pozovi u rad tobacco smoker-a.\n");
			pthread_cond_signal(&smoker_thread_t);
			}
		
		pthread_mutex_unlock(&mutex1);
	}
	return 0;
}	

void* pusher_M(void* ptr){
	while(1){
		
		pthread_mutex_lock(&mutex1);
		
		while(!match){
			pthread_cond_wait(&match_thread, &mutex1);
		}
		
		if(paper){
			paper = false;
			agent_bool = false;
			smoker_tobacco_bool = true;
			printf("Pozovi u rad tobacco smoker-a.\n");
			pthread_cond_signal(&smoker_thread_t);
		}
		
		if(tobacco){
			tobacco = false;
			agent_bool = false;
			smoker_paper_bool = true;
			printf("Pozovi u rad paper smoker-a.\n");
			pthread_cond_signal(&smoker_thread_p);
			}
		
		pthread_mutex_unlock(&mutex1);
		
	}
	return 0;
}

//smoker funkcije - pravljenje cigareta
void* smoker_T(void* ptr){
	
	while(1){
		pthread_mutex_lock(&mutex2);
		
		while(!smoker_tobacco_bool){
				pthread_cond_wait(&smoker_thread_t, &mutex2);
		}
			
		paper = false;
		match = false;
		smoker_tobacco_bool = false;
		agent_bool = true;
		
		printf("Tobacco smoker pravi cigaretu...\n");
		
		pthread_mutex_unlock(&mutex2);
		
		printf("Tobacco smoker koristi cigaretu...\n");
	}
	
	return 0;
}

void* smoker_M(void* ptr){
	
	while(1){
		
		pthread_mutex_lock(&mutex2);
		
		while(!smoker_match_bool){
			pthread_cond_wait(&smoker_thread_m, &mutex2);
		}
		
		tobacco = false;
		paper = false;
		smoker_match_bool = false;
		agent_bool = true;
		
		printf("Match smoker pravi cigaretu...\n");
		
		pthread_mutex_unlock(&mutex2);
		
		printf("Match smoker koristi cigaretu...\n");
		
	}
}

void* smoker_P(void* ptr){
	while(1){
		
		pthread_mutex_lock(&mutex2);
		
		while(!smoker_paper_bool){
			pthread_cond_wait(&smoker_thread_p, &mutex2);
		}
		
		tobacco = false;
		match = false;
		smoker_paper_bool = false;
		agent_bool = true;
		
		printf("Paper smoker pravi cigaretu...\n");
		
		pthread_mutex_unlock(&mutex2);
		
		printf("Paper smoker koristi cigaretu...\n");
	}
}
