//https://www.codechef.com/problems/MINNOTES

#include<iostream>
#include<algorithm>

int main(){
	int test_cases;
	std::cin>>test_cases;
	while(test_cases--){
		int N;
		std::cin>>N;

		int employee[N], sum=0;
		for(int i=0; i<N; i++){
			std::cin>>employee[i];
			sum+=employee[i];
		}

		// Manual Case
		if(N==1){
			std::cout<<1<<std::endl;
		       	continue;
		}

		// Precomputation

		int prefix_gcd[N], suffix_gcd[N];
		prefix_gcd[0] = employee[0];
		for(int i=1; i<N; i++) prefix_gcd[i] = std::__gcd(prefix_gcd[i-1], employee[i]);

		suffix_gcd[N-1] = employee[N-1];
		for(int i=N-2; i>=0; i--) suffix_gcd[i] = std::__gcd(suffix_gcd[i+1], employee[i]);

		// Main Answer
		int ans = sum/prefix_gcd[N-1];
		for(int i=0; i<N; i++){
			int x = std::__gcd((i<=0)?0:prefix_gcd[i-1], (i>=N-1)?0:suffix_gcd[i+1]);
			int notes = (sum-employee[i])/x + 1;
			ans = std::min(ans, notes);
		}
		std::cout<<ans<<std::endl;
	}
return 0;
}

