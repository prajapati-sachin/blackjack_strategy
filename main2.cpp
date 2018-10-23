#include <bits/stdc++.h>

using namespace std;

struct state{
	int sum;
	int dealercard;
	bool hasAce;
	bool ispair;
	bool dealerAce;
};

double v[10][36];
double expected_reward[19][21];
double p_face;
double p_noface;

void initialize_reward(){
	for(int i=0;i<19;i++){
		for(int j=0;j<21;j++){
			expected_reward[i][j]=-1;
		}
	}
}

void fill_reward(){
	for(int i=0;i<18;i++){
		int player_sum=i+4;
		//without ACE 14-9
		for(int j=14;j>=9;j--){
			double ans=0;
			int dealer_sum=j+2;
			//for normal card
			for(int k=2;k<=9;k++){
				if(dealer_sum+k>21){
					ans+= p_noface*(1);
				}
				else if(dealer_sum+k>=17){
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
				else if(dealer_sum+10==player_sum){
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
					ans+= p_noface*expected_reward[i][dealer_sum+(1-2)];
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
		//with ACE
		for(int j=20;j>=15;j--){
			double ans=0;
			int dealer_sum=j-4;
			//for normal cards
			for(int k=2;k<=9;k++){
				if(dealer_sum+k>21){
					//ans+= p_noface*(1);
					ans+= p_noface*(expected_reward[i][dealer_sum+k-12]);
				}
				else if(dealer_sum+k>=17){
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
				if(dealer_sum==11){
					ans+= p_face*(-1);
				}
				else{
					ans+= p_face*expected_reward[i][dealer_sum-2];					
				}
			//for ACE
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
				ans+= p_noface*expected_reward[i][j+1];
			}
			expected_reward[i][j]=ans;
		}
		//without ACE 8-0
		for(int j=8;j>=0;j--){
			double ans=0;
			int dealer_sum=j+2;
			//for normal card
			for(int k=2;k<=9;k++){
				if(dealer_sum+k>21){
					ans+= p_noface*(-1);					
				}
				else if(dealer_sum+k>=	17){
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
				else if(dealer_sum+10==player_sum){
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
					ans+= p_noface*expected_reward[i][dealer_sum+(1-2)];
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
	
	
	// Last row for dealer's blackjack
	for(int i=0;i<21;i++){
		expected_reward[18][i]=expected_reward[17][i];
	}
	expected_reward[18][8]+=p_noface*(-1);
}

double find_reward(int playersum, int dealersum, bool dealerface, bool dealerAce){
	if(playersum!=21){
		if(dealerAce) return expected_reward[playersum-4][15];
		else return expected_reward[playersum-4][dealersum-2];
	}
	else{
		if(dealerface){
			return expected_reward[18][dealersum-2];
		}
		else if(dealerAce){
			return expected_reward[playersum-4][15];
		}
		else{
			return expected_reward[playersum-4][dealersum-2];
		}
	}
}

void initialize_v(){
	for(int i=0;i<10;i++){
		for(int j=0;j<36;j++){
			int rand1= 1+rand()%5;
			int rand2= rand()%2;
			double rand_val= 0.5+ (1.0/rand1);
			if(rand2==0){
				rand_val*=-1;
			}
			v[i][j]= rand_val;
		}
	}
}

double values(int cat, int sum, int dcard){
	int index1;
	int index2;
	if(cat==1){
		index1= dcard-2;
		index2= sum-5;
		return v[index1][index2];
	}
	else if(cat==2){
		index1= dcard-2;
		index2= psum-2 + 17;
		return v[index1][index2];
	}
	else{
		index1= dcard-2;
		index2= psum-2 + 25;
		return v[index1][index2];	
	}
}

void value_iteration(){
	for(int i=0;i<10;i++){
		double Vn[36];
		// 11 for ACE
		int dealercard=i+2;
		for(int j=0;j<35;j++){
			int category=0;
			if(j>=0 && j<=16)category=1;
			else if(j>=17 && j<=25)category=2;
			else category=3;
			// Normal Sum
			if(category==1){
				int psum=j+5;
				double double_reward=0;
				double stand_reward=0;
				double hit_reward=0;
				bool isAce=false;
				bool isFace=false;
				if(i==8) isFace=true;
				if(i==9) isAce=true;
				// STAND REWARD
					stand_reward=find_reward(psum, dealercard, isFace, isAce);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value(1, psum+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value(1, psum+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*(-1);						
					}
					else{
						hit_reward+= p_face*value(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= p_face*(-1);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce);
					}

				//update V value
				Vn[j]= max(stand_reward, max(double_reward, hit_reward));	
			}
			// One Ace
			else if(category==2){
				int psum=(j-15)+11;
				double double_reward=0;
				double stand_reward=0;
				double hit_reward=0;
				bool isAce=false;
				bool isFace=false;
				if(i==8) isFace=true;
				if(i==9) isAce=true;
				// STAND REWARD
					stand_reward=find_reward(psum, dealercard, isFace, isAce);
				// HIT REWARD
					//ace
					if(psum+1>21){
						hit_reward+= p_noface*value(1, psum-10+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value(2, psum-11+1, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*value(1, psum-10+k, dealercard);
						}
						else{
							hit_reward+= p_noface*value(2, psum-11+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*value(1, psum-10+10, dealercard);						
					}
					else{
						hit_reward+= p_face*value(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+1>21){
						double_reward+= p_noface*2*(find_reward(psum-10+1, dealercard, isFace, isAce));
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= p_noface*2*(find_reward(psum-10+k, dealercard, isFace, isAce));
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= p_noface*2*find_reward(psum, dealercard, isFace, isAce);;						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce);
					}

				//update V value
				Vn[j]= max(stand_reward, max(double_reward, hit_reward));
			}
			//Pair
			else{

			}

		}
	}
}

// void find_policy(){

// }

// void write_policy(){

// }

int main(int argc, char const *argv[]){
	srand(time(0));
	p_face= atof(argv[1]);
	p_noface= (1-p_face)/9.0;
	
	// initialize_reward();
	fill_reward();
	for(int i=0;i<19;i++){
		cout << i+4 << ": ";
		for(int j=0;j<9;j++){
			cout << expected_reward[i][j] << " ";
		}
		cout << expected_reward[i][15];
		cout << endl;
	}

		cout << endl;

		cout << endl;

	for(int i=0;i<19;i++){
		cout << i+4 << ": ";
		for(int j=0;j<21;j++){
			cout << expected_reward[i][j] << " ";
		}
		// cout << expected_reward[i][15];
		cout << endl;
	}
	initialize_v();
	// for(int i=0;i<10;i++){
	// 	cout << i << ": ";
	// 	for(int j=0;j<33;j++){
	// 		cout << v[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	//repeat
	// value_iteration();
	// find_policy();
	// write_policy();

}