#include <bits/stdc++.h>

struct state{
	int sum;
	int dealercard;
	bool hasAce;
	bool ispair;
	bool dealerAce;
};

float v[10][33];
float expected_reward[18][21];
float p_face;
float p_noface;

void fill_reward(){
	for(int i=0;i<18;i++){
		int player_sum=i+4;
		//without ACE
		for(int j=14;j>=0;j--){
			float ans=0;
			int dealer_sum=j+2;
			for(int k=2;k<=9;k++){

			}
		}
		//with ACE
		for(int j=15;j<21;j++){

		}
	}
}

void initialize_v(){

}

void value_iteration(){

}

void find_policy(){

}

void write_policy(){

}

int main(int argc, char const *argv[]){
	p_face= argv[1];
	p_noface= (1-p_face)/9;
	fill_reward();
	initialize_v();
	//repeat
	value_iteration();
	find_policy();
	write_policy();

}