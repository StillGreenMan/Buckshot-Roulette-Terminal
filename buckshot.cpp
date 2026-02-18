#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int myLife=6;
int playerLife=6;
int count=0;
int live=0;
int blank=0;

int seconds(){
	return time(NULL)%60;
}

bool shoot(bool target, bool shots[], int count){
	int lastSec=seconds();
	int test=3;
	while(test>=0){
		int sec = seconds();
		if(lastSec!=sec){
			if(test){
				putchar('.');
			}else{
				putchar('\n');
			}
			lastSec=sec;
			test--;
		}
	}
	if(shots[count-1]){
		printf("*BANG*\n");
		if(target){
			playerLife--;
		}else{
			myLife--;
		}
		return true;
	}
	printf("*click*\n");
	return false;
}

int main(){
	time_t seed = time(NULL);
	srand(seed);
	int bmin=2;
	int bmax=8;
	count=(rand()%(bmax-bmin+1))+bmin;
	bool shots[count];
	printf("Count is %d rounds\n",count);
	for(int i=0;i<count;i++){
		shots[i]=rand()%2;
		if(shots[i]){
			live++;
		}else{
			blank++;
		}
	}
	if(live==0){
		shots[rand()%(bmax)]=true;
		live++;
		blank--;
	}
	printf("Dealer: \"%d LIVE ROUNDS. %d BLANK\"\n",live,blank);

	for(int i=0;i<count;i++){

		printf("*shk*\n");
	}
	bool myTurn=false;
	bool iKnowRound=false;
	while(count>0){
		if(myTurn){
			printf("Dealer: MY TURN! HMMM...\"\n");
			if(count==1){
				iKnowRound=true;
			}
			bool target;
			if(!iKnowRound){
				target=rand()%2;
			}else{
				target=!shots[count-1];
			}
			printf("The dealer points the gun at %s.\n",(target ? "himself":"you"));
			myTurn=!shoot(target,shots,count);
			myTurn = target?myTurn:false;
		}else{
			printf("Dealer: YOUR TURN!\"\n");
			bool action=false;
			while(!action){
				printf("\nShoot yourself? (Y/N)");
				char answer[3];
				fgets(answer,3,stdin);
				if(answer[0]=='y'||answer[0]=='Y'){
					myTurn = shoot(true,shots,count);
					action=true;
				}else if(answer[0]=='n'||answer[0]=='N'){
					shoot(false,shots,count);
					myTurn=true;
					action=true;
				}
			}
		}
		count--;
	}
	printf("Final score:\nPlayer: %d, Dealer: %d\n",playerLife,myLife);
}
