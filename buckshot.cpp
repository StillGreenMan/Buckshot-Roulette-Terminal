#include <iostream>
#include <random>
#include <chrono>

int myLife=6;
int playerLife=6;
int count=0;
int live=0;
int blank=0;

int seconds(){
	auto now = std::time(nullptr);
	std::tm local{};
	#if defined(_WIN32)
		localtime_s(&local,&now);
	#else
		local = *std::localtime(&now);
	#endif
	int time = local.tm_sec;
	return time;
}

bool shoot(bool target, bool shots[], int count){
	int lastSec=seconds();
	int test=3;
	while(test>=0){
		int sec = seconds();
		if(lastSec!=sec){
			if(test){
				std::cout<<".";
			}else{
				std::cout<<"\n";
			}
			lastSec=sec;
			test--;
		}
	}
	if(shots[count-1]){
		std::cout<<"*BANG*"<<std::endl;
		if(target){
			playerLife--;
		}else{
			myLife--;
		}
		return true;
	}
	std::cout<<"*click*"<<std::endl;
	return false;
}

int main(){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng(seed);
	std::uniform_int_distribution<> c(2,8);
	std::uniform_int_distribution<> bulletchance(0,1);
	count=c(rng);
	bool shots[count];
	std::cout<<"Count is "<<count<<" rounds"<<std::endl;
	for(int i=0;i<count;i++){
		shots[i]=bulletchance(rng);
		if(shots[i]){
			live++;
		}else{
			blank++;
		}
	}
	if(live==0){
		std::uniform_int_distribution<> fuck(0,count-1);
		shots[fuck(rng)]=true;
		live++;
		blank--;
	}
	std::cout<<"Dealer: \""<<live<<" LIVE ROUNDS. "<<blank<<" BLANKS.\""<<std::endl;

	for(int i=0;i<count;i++){
		std::cout<<"*shk*"<<std::endl;
	}
	bool myTurn=false;
	bool iKnowRound=false;
	while(count>0){
		if(myTurn){
			std::cout<<"Dealer: MY TURN!\nHMMM..."<<std::endl;
			if(count==1){
				iKnowRound=true;
			}
			bool target;
			if(!iKnowRound){
				target=bulletchance(rng);
			}else{
				target=!shots[count-1];
			}
			std::cout<<"The dealer points the gun at "<<(target ? "himself.":"you.")<<std::endl;
			myTurn=!shoot(target,shots,count);
			myTurn = target?false:myTurn;
		}else{
			std::cout<<"Dealer: YOUR TURN!"<<std::endl;
			bool action=false;
			while(!action){
				std::cout<<"\n\nShoot yourself? (Y/N)"<<std::endl;
				std::string answer;
				std::cin>>answer;
				if(answer=="yes"||answer=="y"){
					myTurn = shoot(true,shots,count);
					action=true;
				}else if(answer=="no"||answer=="n"){
					shoot(false,shots,count);
					myTurn=true;
					action=true;
				}
			}
		}
		count--;
	}
	std::cout<<"Final score:\nPlayer: "<<playerLife<<", Dealer: "<<myLife<<std::endl;
}
