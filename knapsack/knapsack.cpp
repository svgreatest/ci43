#include <vector>
#include <iostream>

class Knapsack {
    public:
        std::vector<int> weights;
        std::vector<int> values;
        int W;
        int knapsack_dp();
};

int Knapsack::knapsack_dp() {
    std::vector<std::vector<int>> opt;
    int i = values.size();
    opt.resize(i+1);
    for (int j = 0; j <= i; j++) {
        opt[j].resize(W);
    }
    for (int j = 0; j < i; j++) {
        opt[j][0] = 0;
    }
    for (int j = 0; j <= W; j++) {
        opt[0][j] = 0;
    }

    for (int i = 1; i <= (int)values.size(); i++) {
        for(int w = 1; w <= W; w++) {
            if (weights[i-1] <= w) {
                opt[i][w] = std::max(opt[i-1][w], values[i-1] + opt[i-1][w-weights[i-1]]);
            } else {
                opt[i][w] = opt[i-1][w];
            }
        }
    }

    for (int i = 0; i <= (int)values.size(); i++)
    {
        for (int j = 0; j <= W; j++)
        {
            std::cout << opt[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return opt[i][W];
}

/*
for (int i = 0; i < (int)weights.size(); i++)
{
    for (int j = 0; j <= W; j++)
    {
        std::cout << opt[i][j] << " ";
    }
    std::cout << std::endl;
}
*/


int main() {
    Knapsack k = Knapsack();
    k.values = {60, 50, 70, 30};
    k.weights = {5, 3, 4, 2};
    k.W = 5;
    std::cout<<k.knapsack_dp()<<std::endl;
    
}