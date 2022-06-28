class Solution {
public:
    int maxProfit(int K, vector<int>& prices) {
        
        //finds solution using dynamic programming
        //subproblems are starting on the ith day, 0<=i<N
        //  and having k transactions left, 0<=k<=K
        int N = prices.size();
        if(N==0){
            return 0; 
        }
        int maxProf[N][K+1]; //DP array of max val

        //base case: k=0, or no transactions left
        for(int i=0; i<N; i++){
            maxProf[i][0] = 0;         
        }

        //base case: i=N. Buying on the last day is always nonoptimal
        for(int k=0; k<=K; k++){
            maxProf[N-1][k] = 0;
        }
        
        
        int maxChoice = 0;
        int sellToday = 0;
        int sellLastDay = 0;
        
        //decursing the bellman equation using for loops
        for(int i=N-2; i>=0; i--){
            for(int k=1; k<=K; k++){
                // two options on day i. We either don't buy, or we buy and choose a future date to sell
                //if we don't buy
                maxChoice = maxProf[i+1][k];

                //otherwise, if we buy, we have to sell eventually, say on the (i+j)th day. Never selling is nonoptimal
                //then this is just the subproblem, with some cost/profit already incurred and with one less transaction
                for(int j=1; j<N-i-1; j++){
                    sellToday = -prices[i] + prices[i+j] + maxProf[i+j+1][k-1];
                    if(sellToday > maxChoice){
                        maxChoice = sellToday;
                    }
                }
                
                //always sell on the last day if needed, then no further searching to do
                int sellLastDay = -prices[i] + prices[N-1];
                if(sellLastDay > maxChoice)
                    maxProf[i][k] = sellLastDay;
                else
                    maxProf[i][k] = maxChoice;
                
                
            }
        }

        return maxProf[0][K];   
    }
};
