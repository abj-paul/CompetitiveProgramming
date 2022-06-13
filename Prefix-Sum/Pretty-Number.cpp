//https://www.codechef.com/problems/NUM239

#include<iostream>

#define MAX_SIZE  100000 + 1
int pretty_numbers[MAX_SIZE];
int prefix_sum[MAX_SIZE];

void precompute();

int main(){
	int test_cases;
	std::cin>>test_cases;
	
	precompute();

	while(test_cases--){
		int L, R;
		std::cin>>L>>R;
		std::cout<<prefix_sum[R] - ((L<=0)?0:prefix_sum[L-1])<<std::endl;
	}
}

void precompute(){
	pretty_numbers[0] = 0;
	for(int i=1; i<=MAX_SIZE; i++){
		if(i%10==2 || i%10==3 || i%10==9) pretty_numbers[i]=1;
		else pretty_numbers[i] = 0;
	}
	
	prefix_sum[0] = pretty_numbers[0];
	for(int i=1; i<=MAX_SIZE; i++) prefix_sum[i] = prefix_sum[i-1]+ pretty_numbers[i];
}
