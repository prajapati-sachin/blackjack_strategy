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
		//with ACE
		for(int j=20;j>=15;j--){
			float ans=0;
			int dealer_sum=j-4;
			//for normal cards
			for(int k=2;k<=9;k++){
				if(dealer_sum+k>=17){
					if(dealer_sum+k>player_sum){
						ans+= p_noface*(-1);
					}
					else if(dealer_sum+k==player_sum){
						ans+=0;
					}
					else{
						ans+= p_noface*(1);
					}
				}
				else if(dealer_sum+k<17){
					ans+= p_noface*expected_reward[i][j+k];
				}
			}

			//for face card
				ans+= p_face*expected_reward[i][dealer_sum-2];
			//for ACE
			if(dealer_sum+1>=17){
				if(dealer_sum+k>player_sum){
						ans+= p_noface*(-1);
				}
				else if(dealer_sum+k==player_sum){
					ans+=0;
				}
				else{
					ans+= p_noface*(1);
				}
			}
			else{
				ans+= p_noface*expected_reward[i][j+1];
			}
		}
		//without ACE
		for(int j=14;j>=0;j--){
			float ans=0;
			int dealer_sum=j+2;
			//for normal card
			for(int k=2;k<=9;k++){
				if(dealer_sum+k>17){
					if(dealer_sum+k>player_sum){
						ans+= p_noface*(-1);
					}
					else if(dealer_sum+k==player_sum){
						ans+=0;
					}
					else{
						ans+= p_noface*(1);
					}
				}
				else if(dealer_sum+k<17){
					ans+= p_noface*expected_reward[i][j+k];
				}				
			}
			//for face card
			if(dealer_sum+10>21){
				ans+=p_face*(1);
			}
			else if(dealer_sum+10>=17 && dealer_sum+10<=21){
				if(dealer_sum+10>player_sum){
					ans+= p_face*(-1);
				}
				else if(dealer_sum+k==player_sum){
					ans+=0;
				}
				else{
					ans+= p_face*(1);
				}
			}
			else{
				ans+= p_face*expected_reward[i][dealer_sum+(10-2)];
			}
			//for ACE
			bool bust;
			if(dealer_sum+11>21){
				bust=true;
			}
			else{
				bust=false;
			}
			
			if(bust){
				if(dealer_sum+1>=17){
					if(dealer_sum+1>player_sum){
						ans+= p_noface*(-1);
					}
					else if(dealer_sum+1==player_sum){
						ans+=0;
					}
					else{
						ans+= p_noface*(1);
					}
				}
				else{
					ans+= p_face*expected_reward[i][dealer_sum+(1-2)];
				}
			}
			else{
				if(dealer_sum+11>=17){
					if(dealer_sum+11>player_sum){
						ans+= p_noface*(-1);
					}
					else if(dealer_sum+11==player_sum){
						ans+=0;
					}
					else{
						ans+= p_noface*(1);
					}
				}
				else{
					ans+= p_noface*expected_reward[i][dealer_sum+11-11+14+1];
				}	
			}
			expected_reward[i][j]=ans;
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