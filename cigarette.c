#include<stdio.h>
#include "sem.h"
#include<stdlib.h>
#include<stdbool.h>

struct semaphore mutex_Agent,Tobacco,Paper,Match,TobaccoSem,PaperSem,MatchSem,mutex,cmut,tMut,pMut,mMut;
bool TobaccoReady,PaperReady,MatchReady;
// The boolean variables are used to indicate the readiness of ingredients on table.
int count=0,tcount,tsmok,psmok,msmok;
/*
count: #cigarettes smoked
tsmok: #tobacco smokers , psmok: #paper smokers, msmok: #match smokers
*/
void makeCigarette(char* ch){
    printf("Smoker %s %d is making a cigarette\n",ch,pthread_self()%100);
}
void smoke(char* ch){
    wait(&cmut);//mutex for count
    printf("\033[0;31m||Now Smoking||\033[0m \033[0;34m%s %d\033[0;32m#cigarette: %d \033[0;0m \n",ch,pthread_self()%100,count+1);
    count++;
    signal(&cmut);
}
    // Agent producing Tobacco and Paper
void *agentTP(void* arg){
    while(1){
    wait(&mutex_Agent);
    printf("Agent placed Tobacco and Paper\n");
    signal(&Tobacco);
    signal(&Paper);
    }
}
    // Agent producing Paper and Match
void *agentPM(void* arg){
    while(1){
    wait(&mutex_Agent);
    printf("Agent placed Paper and Match\n");
    signal(&Paper);
    signal(&Match);
    }
}
    // Agent producing Tobacco and Match
void*agentMT(void* arg){
    while(1){
    wait(&mutex_Agent);
    printf("Agent placed Tobacco and Match\n");
    signal(&Tobacco);
    signal(&Match);
    }
}

    //The three helpers help to determine the state of the ingredients on table
void *helperT(void* num){
    while(1){
        wait(&Tobacco);
        wait(&mutex);
        if(PaperReady){
            PaperReady=false;
            signal(&MatchSem);
        }else if(MatchReady){
            MatchReady=false;
            signal(&PaperSem);
        }else{
            TobaccoReady=true;
        }
        signal(&mutex);
       
    }
}

void *helperP(void* arg){
    while(1){
        wait(&Paper);
        wait(&mutex);
        if(MatchReady){
            MatchReady=false;
            signal(&TobaccoSem);
        }else if(TobaccoReady){
            TobaccoReady=false;
            signal(&MatchSem);
        }else{
            PaperReady=true;
        }
        signal(&mutex);

    }
}
void *helperM(void* num){
    while(1){
        wait(&Match);
        wait(&mutex);
        if(TobaccoReady){
            TobaccoReady=false;
            signal(&PaperSem);
        }else if(PaperReady){
            PaperReady=false;
            signal(&TobaccoSem);
        }else{
            MatchReady=true;
        }
        signal(&mutex);

    }
}
    //The code for smoker holding infinite supply of Tobacco
void *TobaccoSmoker(void *arg){
    char* ch="TS";
   while(1){
        wait(&tMut);
    printf("\033[0;34mTS %d\033[0;0m waiting for Paper & Matches\n",pthread_self()%100);
   // signal(&mutex_Agent);
    wait(&TobaccoSem);
    makeCigarette(ch);
    printf("TobaccoSmoker %d enter CS \n",pthread_self()%100);
    signal(&mutex_Agent);
    smoke(ch);
        signal(&tMut);
    }
}
    //The code for smoker holding infinite supply of Paper
void *PaperSmoker(void* arg){
    char* ch="PS";
   while(1){
        wait(&pMut);
    printf("\033[0;35mPS %d\033[0;0m waiting for Tobacco & Matches\n",pthread_self()%100);
    wait(&PaperSem);
    makeCigarette(ch);
    printf("PaperSmoker %d enter CS  \n",pthread_self()%100);
    signal(&mutex_Agent);
    smoke(ch);
        signal(&pMut);
    }
}
    //The code for smoker holding infinite supply of Match
void *MatchSmoker(void *arg){
    char* ch="MS";
    while(1){
        wait(&mMut);
    printf("\033[0;30mMS %d\033[0;0m waiting for Paper & Tobacco\n",pthread_self()%100);
    wait(&MatchSem);
    makeCigarette(ch);
    printf("MatchSmoker %d entered CS \n",pthread_self()%100);
    signal(&mutex_Agent);
    smoke(ch);
        signal(&mMut);
    }
}
    //creating multiple smokers with Tobacco
void* createTobacco(void* arg){
    pthread_t p[tsmok];
    for(int i=0;i<tsmok;i++)
        pthread_create(&p[i],NULL,TobaccoSmoker,(void*)i);
    for(int i=0;i<tsmok;i++)
        pthread_join(p[i],NULL);
}
    //creating multiple smokers with Paper
void* createPaper(void* arg){
    pthread_t p[psmok];
    for(int i=0;i<psmok;i++)
        pthread_create(&p[i],NULL,PaperSmoker,(void*)i);
    for(int i=0;i<psmok;i++)
        pthread_join(p[i],NULL);
}
    //creating multiple smokers with Match
void* createMatch(void* arg){
    pthread_t p[msmok];
    for(int i=0;i<msmok;i++)
        pthread_create(&p[i],NULL,MatchSmoker,(void*)i);
    for(int i=0;i<msmok;i++)
        pthread_join(p[i],NULL);
}
int main(){
    //creating semaphores
    create(&tMut,1);
    create(&pMut,1);
    create(&mMut,1);
    create(&mutex_Agent,1);
    create(&Tobacco,0);
    create(&Paper,0);
    create(&Match,0);
    create(&PaperSem,0);
    create(&TobaccoSem,0);   
    create(&MatchSem,0);
    create(&mutex,1);
    create(&cmut,1);

    //assuming no ingrediant on table
    MatchReady=PaperReady=TobaccoReady=false;

    printf("Enter the number of Tobacco smokers:\n");
    scanf("%d",&tsmok);
    printf("Enter the number of Paper smokers:\n");
    scanf("%d",&psmok);
    printf("Enter the number of Match smokers:\n");
    scanf("%d",&msmok); 
    printf("Enter the number of cigarettes to be smoked\n");
    scanf("%d",&tcount);
    pthread_t agent[3],pusher[3],p1,p2,p3;

    //creating threads
    pthread_create(&agent[1],NULL,&agentPM,NULL);
    pthread_create(&agent[0],NULL,&agentTP,NULL);
    pthread_create(&agent[2],NULL,&agentMT,NULL);
    pthread_create(&pusher[1],NULL,&helperP,NULL);
    pthread_create(&pusher[0],NULL,&helperT,NULL);
    pthread_create(&pusher[2],NULL,&helperM,NULL);
    pthread_create(&p3,NULL,&createPaper,NULL);
    pthread_create(&p2,NULL,createTobacco,NULL);
    pthread_create(&p1,NULL,createMatch,NULL);

    //waiting until specified cigarettes are smoked
    while(1){
    wait(&cmut);
    if(count==tcount)break;
    signal(&cmut);
    }
    
    return 0;
}