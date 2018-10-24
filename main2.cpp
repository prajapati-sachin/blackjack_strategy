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
double v_nodouble[10][36];
// Hit 1
// Stand 2
// Double 3
// Split 4
int policy[10][36];
double expected_reward[21][21];
double p_face;
double p_noface;
char move(int a){
	if(a==1) return 'H';
	else if(a==2) return 'S';
	else if(a==3) return 'D';
	else if(a==4) return 'P';
}


void initialize_reward(){
	for(int i=0;i<19;i++){
		for(int j=0;j<21;j++){
			expected_reward[i][j]=-1;
		}
	}
}

void fill_reward(){
	for(int i=0;i<19;i++){
		int player_sum=i+4;
		if(i==18) player_sum--;
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
					if(i!=18) ans+=0;
					else ans+=p_face*(1);
						
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
					if(i!=18) ans+=0;
					else ans+=p_noface*(1);
						
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
					if(i!=18) ans+=0;
					else ans+=p_face*(1);
						
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
						if(i!=18) ans+=0;
						else ans+=p_noface*(1);
						
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
	
	// Second Last row for both blackjack
	for(int i=0;i<21;i++){
		expected_reward[19][i]=(1.5)*expected_reward[18][i];
	}
	expected_reward[19][8]+=(1.5)*p_noface*(-1);

	// Last row for dealer's blackjack
	for(int i=0;i<21;i++){
		expected_reward[20][i]=expected_reward[17][i];
	}
	expected_reward[20][8]+=p_noface*(-1);
}

double find_reward(int playersum, int dealersum, bool dealerface, bool dealerAce, bool bj){
	if(playersum!=21){
		if(dealerAce) return expected_reward[playersum-4][15];
		else return expected_reward[playersum-4][dealersum-2];
	}
	else{
		if(bj){
			if(dealerface){
				return expected_reward[19][dealersum-2];
			}
			else if(dealerAce){
				return expected_reward[19][15];
			}
			else{
				return expected_reward[19][dealersum-2];
			}
		}
		else{
			if(dealerface){
				return expected_reward[20][dealersum-2];
			}
			else if(dealerAce){
				return expected_reward[playersum-4][15];
			}
			else{
				return expected_reward[playersum-4][dealersum-2];
			}
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
			v_nodouble[i][j]=rand_val;
		}
	}
}

double value(int cat, int sum, int dcard){
	int index1;
	int index2;
	if(cat==1){
		index1= dcard-2;
		index2= sum-5;
		return v[index1][index2];
	}
	else if(cat==2){
		index1= dcard-2;
		index2= sum-2 + 17;
		return v[index1][index2];
	}
	else if(cat==3){
		index1= dcard-2;
		index2= sum-2 + 26;
		return v[index1][index2];	
	}
}

double value_nodouble(int cat, int sum, int dcard){
	int index1;
	int index2;
	if(cat==1){
		index1= dcard-2;
		index2= sum-5;
		return v_nodouble[index1][index2];
	}
	else if(cat==2){
		index1= dcard-2;
		index2= sum-2 + 17;
		return v_nodouble[index1][index2];
	}
	else if(cat==3){
		index1= dcard-2;
		index2= sum-2 + 26;
		return v_nodouble[index1][index2];	
	}
}

double value_iteration(){
	double max_change=0;
	for(int i=0;i<10;i++){
		double Vn[36];
		int polic[36];
		// 11 for ACE
		int dealercard=i+2;
		for(int j=0;j<36;j++){
			int category=0;
			if(j>=0 && j<=16)category=1;
			else if(j>=17 && j<=25)category=2;
			else if (j>=26 && j<=34)category=3;
			else category=4;
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
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value_nodouble(1, psum+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value_nodouble(1, psum+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*(-1);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= 2*p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= 2*p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= 2*p_face*(-1);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//update V value
				Vn[j]= max(stand_reward, max(double_reward, hit_reward));
				if(Vn[j]==double_reward){
					polic[j]=3;
				}
				else if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}
				
				// if(i==1 && j==4){
				// 	cout << "Policy: "<< move(polic[j]) << endl;
				// 	cout << "Value: " << Vn[j] << endl;
				// 	cout << "double_reward: " << double_reward << endl;
				// 	cout << "stand_reward: " << stand_reward << endl;
				// 	cout << "hit_reward: " << hit_reward << endl;
				// 	cout << "-----------------------------------" << endl;
				// }

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
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+1>21){
						hit_reward+= p_noface*value_nodouble(1, psum-10+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum-11+1, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*value_nodouble(1, psum-10+k, dealercard);
						}
						else{
							hit_reward+= p_noface*value_nodouble(2, psum-11+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*value_nodouble(1, psum-10+10, dealercard);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+1>21){
						double_reward+= p_noface*2*(find_reward(psum-10+1, dealercard, isFace, isAce, false));
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= p_noface*2*(find_reward(psum-10+k, dealercard, isFace, isAce, false));
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= p_face*2*find_reward(psum, dealercard, isFace, isAce, false);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//update V value
				Vn[j]= max(stand_reward, max(double_reward, hit_reward));
				if(Vn[j]==double_reward){
					polic[j]=3;
				}
				else if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}

				// if(i==3 && j==18){
				// 	cout << "Policy: "<< move(polic[j]) << endl;
				// 	cout << "Value: " << Vn[j] << endl;
				// 	cout << "double_reward: " << double_reward << endl;
				// 	cout << "stand_reward: " << stand_reward << endl;
				// 	cout << "hit_reward: " << hit_reward << endl;
				// 	cout << "-----------------------------------" << endl;
				// }				
			}
			//Pair
			else if(category==3){
				int psum=2*(j-24);
				double double_reward=0;
				double stand_reward=0;
				double hit_reward=0;
				double split_reward=0;
				bool isAce=false;
				bool isFace=false;
				if(i==8) isFace=true;
				if(i==9) isAce=true;
				// STAND REWARD
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value_nodouble(1, psum+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value_nodouble(1, psum+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*(-1);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= 2*p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= 2*p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= 2*p_face*(-1);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//SPLIT REWARD
					//ace
					int card=psum/2;
					if(card!=10){
						split_reward+=p_noface*value(2, card, dealercard);
					}
					else{
						//player blackjack
						split_reward+=p_noface*find_reward(psum+1, dealercard, isFace, isAce, true);						
					}
					//normal cards
					for(int k=2;k<=9;k++){
						if(card==k) split_reward+=p_noface*value(3, card, dealercard);
						else split_reward+=p_noface*value(1, card+k, dealercard);	
					}
					//face
					split_reward+=p_face*value(1, card+10, dealercard);
					split_reward*=2;
				//update V value
				Vn[j]= max(split_reward, max(stand_reward, max(double_reward, hit_reward)));
				if(Vn[j]==double_reward){
					polic[j]=3;
				}
				else if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}
				
				else if(Vn[j]==split_reward){
					polic[j]=4;
				}				
				
				// if(i==3 && j==28){
				// 	cout << "Policy: "<< move(polic[j]) << endl;
				// 	cout << "Value: " << Vn[j] << endl;
				// 	cout << "double_reward: " << double_reward << endl;
				// 	cout << "stand_reward: " << stand_reward << endl;
				// 	cout << "hit_reward: " << hit_reward << endl;
				// 	cout << "split_reward: " << split_reward << endl;
				// 	cout << "-----------------------------------" << endl;
				// }
			}
			//Pair of ACE
			else{
				int psum=12;
				double double_reward=0;
				double stand_reward=0;
				double hit_reward=0;
				double split_reward=0;
				bool isAce=false;
				bool isFace=false;
				if(i==8) isFace=true;
				if(i==9) isAce=true;
				// STAND REWARD
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value_nodouble(2, 2, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value_nodouble(2, k+1, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*value_nodouble(1, psum-10+10, dealercard);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}


				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= 2*p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= 2*p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= p_face*2*find_reward(psum, dealercard, isFace, isAce, false);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//SPLIT REWARD
					//ace
						split_reward+=p_noface*find_reward(psum, dealercard, isFace, isAce, false);						
					//normal cards
					for(int k=2;k<=9;k++){
						split_reward+=p_noface*find_reward(psum-1+k, dealercard, isFace, isAce, false);	
					}
					//face
					split_reward+=p_face*find_reward(psum-1+10, dealercard, isFace, isAce, false);
					split_reward*=2;
				//update V value
				Vn[j]= max(split_reward, max(stand_reward, max(double_reward, hit_reward)));
				if(Vn[j]==double_reward){
					polic[j]=3;
				}
				else if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}
				
				else if(Vn[j]==split_reward){
					polic[j]=4;
				}				
			}
			
			
		}
		//update v
		for(int m=0;m<36;m++){
			double update= abs(Vn[m]-v[i][m]);
			if(update>max_change){
				max_change=update;
			}
			v[i][m]=Vn[m];
			policy[i][m]=polic[m];	
		}
		
	}


	return max_change;
}


double value_iteration_nodouble(){
	double max_change=0;
	for(int i=0;i<10;i++){
		double Vn[36];
		int polic[36];
		// 11 for ACE
		int dealercard=i+2;
		for(int j=0;j<36;j++){
			int category=0;
			if(j>=0 && j<=16)category=1;
			else if(j>=17 && j<=25)category=2;
			else if (j>=26 && j<=34)category=3;
			else category=4;
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
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value_nodouble(1, psum+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value_nodouble(1, psum+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*(-1);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= 2*p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= 2*p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= 2*p_face*(-1);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//update V value
				Vn[j]= max(stand_reward, hit_reward);
				if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}
				
				// if(i==1 && j==4){
				// 	cout << "Policy: "<< move(polic[j]) << endl;
				// 	cout << "Value: " << Vn[j] << endl;
				// 	cout << "double_reward: " << double_reward << endl;
				// 	cout << "stand_reward: " << stand_reward << endl;
				// 	cout << "hit_reward: " << hit_reward << endl;
				// 	cout << "-----------------------------------" << endl;
				// }

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
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+1>21){
						hit_reward+= p_noface*value_nodouble(1, psum-10+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum-11+1, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*value_nodouble(1, psum-10+k, dealercard);
						}
						else{
							hit_reward+= p_noface*value_nodouble(2, psum-11+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*value_nodouble(1, psum-10+10, dealercard);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}

				// DOUBLE REWARD
					//ace
					if(psum+1>21){
						double_reward+= p_noface*2*(find_reward(psum-10+1, dealercard, isFace, isAce, false));
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= p_noface*2*(find_reward(psum-10+k, dealercard, isFace, isAce, false));
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= p_face*2*find_reward(psum, dealercard, isFace, isAce, false);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//update V value
				Vn[j]= max(stand_reward, hit_reward);
				if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}

				// if(i==3 && j==18){
				// 	cout << "Policy: "<< move(polic[j]) << endl;
				// 	cout << "Value: " << Vn[j] << endl;
				// 	cout << "double_reward: " << double_reward << endl;
				// 	cout << "stand_reward: " << stand_reward << endl;
				// 	cout << "hit_reward: " << hit_reward << endl;
				// 	cout << "-----------------------------------" << endl;
				// }				
			}
			//Pair
			else if(category==3){
				int psum=2*(j-24);
				double double_reward=0;
				double stand_reward=0;
				double hit_reward=0;
				double split_reward=0;
				bool isAce=false;
				bool isFace=false;
				if(i==8) isFace=true;
				if(i==9) isAce=true;
				// STAND REWARD
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value_nodouble(1, psum+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value_nodouble(1, psum+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*(-1);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}
				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= 2*p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= 2*p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= 2*p_face*(-1);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//SPLIT REWARD
					//ace
					int card=psum/2;
					if(card!=10){
						split_reward+=p_noface*value_nodouble(2, card, dealercard);
					}
					else{
						//player blackjack
						split_reward+=p_noface*find_reward(psum+1, dealercard, isFace, isAce, true);						
					}
					//normal cards
					for(int k=2;k<=9;k++){
						if(card==k) split_reward+=p_noface*value_nodouble(3, card, dealercard);
						else split_reward+=p_noface*value_nodouble(1, card+k, dealercard);	
					}
					//face
					split_reward+=p_face*value_nodouble(1, card+10, dealercard);
					split_reward*=2;
				//update V value
				Vn[j]= max(split_reward, max(stand_reward,  hit_reward));
				if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}
				
				else if(Vn[j]==split_reward){
					polic[j]=4;
				}				
				
				// if(i==3 && j==28){
				// 	cout << "Policy: "<< move(polic[j]) << endl;
				// 	cout << "Value: " << Vn[j] << endl;
				// 	cout << "double_reward: " << double_reward << endl;
				// 	cout << "stand_reward: " << stand_reward << endl;
				// 	cout << "hit_reward: " << hit_reward << endl;
				// 	cout << "split_reward: " << split_reward << endl;
				// 	cout << "-----------------------------------" << endl;
				// }
			}
			//Pair of ACE
			else{
				int psum=12;
				double double_reward=0;
				double stand_reward=0;
				double hit_reward=0;
				double split_reward=0;
				bool isAce=false;
				bool isFace=false;
				if(i==8) isFace=true;
				if(i==9) isAce=true;
				// STAND REWARD
					stand_reward=find_reward(psum, dealercard, isFace, isAce, false);
				// HIT REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) hit_reward+= p_noface*(-1);
						else hit_reward+= p_noface*value_nodouble(1, psum+1, dealercard);
					}
					else{
						hit_reward+= p_noface*value_nodouble(2, psum, dealercard);
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							hit_reward+= p_noface*(-1);
						}
						else{
							hit_reward+= p_noface*value_nodouble(1, psum+k, dealercard);
						}	
					}
					//face card
					if(psum+10>21){
						hit_reward+= p_face*value_nodouble(1, psum-10+10, dealercard);						
					}
					else{
						hit_reward+= p_face*value_nodouble(1, psum+10, dealercard);
					}


				// DOUBLE REWARD
					//ace
					if(psum+11>21){
						if(psum+1>21) double_reward+= 2*p_noface*(-1);
						else{
							double_reward+= p_noface*2*(find_reward(psum+1, dealercard, isFace, isAce, false));
						}
					}
					else{
						double_reward+= p_noface*2*(find_reward(psum+11, dealercard, isFace, isAce, false));						
					}
					//normal card
					for(int k=2;k<=9;k++){
						if(psum+k>21){
							double_reward+= 2*p_noface*(-1);
						}
						else{
							double_reward+= p_noface*2*find_reward(psum+k, dealercard, isFace, isAce, false);
						}	
					}
					//face card
					if(psum+10>21){
						double_reward+= p_face*2*find_reward(psum, dealercard, isFace, isAce, false);						
					}
					else{
						double_reward+= p_face*2*find_reward(psum+10, dealercard, isFace, isAce, false);
					}

				//SPLIT REWARD
					//ace
						split_reward+=p_noface*find_reward(psum, dealercard, isFace, isAce, false);						
					//normal cards
					for(int k=2;k<=9;k++){
						split_reward+=p_noface*find_reward(psum-1+k, dealercard, isFace, isAce, false);	
					}
					//face
					split_reward+=p_face*find_reward(psum-1+10, dealercard, isFace, isAce, false);
					split_reward*=2;
				//update V value
				Vn[j]= max(split_reward, max(stand_reward,  hit_reward));
				if(Vn[j]==hit_reward){
					polic[j]=1;
				}
				else if(Vn[j]==stand_reward){
					polic[j]=2;
				}
				
				else if(Vn[j]==split_reward){
					polic[j]=4;
				}				
			}
			
			
		}
		//update v
		for(int m=0;m<36;m++){
			double update= abs(Vn[m]-v_nodouble[i][m]);
			if(update>max_change){
				max_change=update;
			}
			v_nodouble[i][m]=Vn[m];
			//policy[i][m]=polic[m];	
		}
		
	}


	return max_change;
}

void write_policy(){
	for(int i=0;i<15;i++){
		cout << i+5 << "\t";
		for(int j=0;j<10;j++){
			cout << move(policy[j][i]); 
			if(j!=9) cout << " ";
				
		}
		cout << endl;
	}
	for(int i=0;i<8;i++){
		cout << "A" << i+2 << "\t";
		for(int j=0;j<10;j++){
			cout << move(policy[j][i+17]) ;
			if(j!=9) cout << " ";

		}
		cout << endl;
	}
	for(int i=0;i<9;i++){
		cout << i+2<< i+2 << "\t";
		for(int j=0;j<10;j++){
			cout << move(policy[j][i+26]) ;
			if(j!=9) cout << " ";

		}
		cout << endl;
	}

		cout << "AA"<<  "\t";
		for(int j=0;j<10;j++){
			cout << move(policy[j][35]);
			if(j!=9) cout << " ";
		}
		// cout << endl;

}

int main(int argc, char const *argv[]){
	srand(time(0));
	p_face= atof(argv[1]);
	p_noface= (1-p_face)/9.0;
	
	initialize_reward();
	fill_reward();
	// for(int i=0;i<21;i++){
	// 	cout << i+4 << ": ";
	// 	for(int j=0;j<9;j++){
	// 		cout << expected_reward[i][j] << " ";
	// 	}
	// 	cout << expected_reward[i][15];
	// 	cout << endl;
	// }

	// 	cout << endl;

	// 	cout << endl;

	// for(int i=0;i<21;i++){
	// 	cout << i+4 << ": ";
	// 	for(int j=0;j<21;j++){
	// 		cout << expected_reward[i][j] << " ";
	// 	}
	// 	// cout << expected_reward[i][15];
	// 	cout << endl;
	// }
	initialize_v();
	// for(int i=0;i<10;i++){
	// 	cout << i << ": ";
	// 	for(int j=0;j<33;j++){
	// 		cout << v[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	// cout << endl;
	// cout << endl;

	//repeat
	// for(int i=0;i<20;i++){
	// 	cout <<"Max change iteration" <<value_iteration_nodouble() << endl;
	// 	value_iteration_nodouble();
	// }
	
	while(1){
		double changing = value_iteration_nodouble();
		if(changing<0.000000000001){
			// cout << changing << endl;
			break;
		}
	}


	// for(int i=0;i<20;i++){
	// 	// cout <<"Max change iteration" <<value_iteration() << endl;
	// 	value_iteration();
	// }


	while(1){
		double changing = value_iteration();
		if(changing<0.000000000001){
			// cout << changing << endl;
			break;
		}
	}
	// for(int i=0;i<10;i++){
	// 	cout << i << ": ";
	// 	for(int j=0;j<33;j++){
	// 		cout << v[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	// find_policy();
	write_policy();

}