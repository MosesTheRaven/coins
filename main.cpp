#include <iostream>

using namespace std;


struct coin{
    int coinValue;
    int coinCount;
};

int CoinsCount, Amount;

int main() {
    std::cout << "Hello, World!" << std::endl;

    cin >> CoinsCount >> Amount;
    // vytvorime pole
    coin * Coins = new coin[CoinsCount];
    //nacitame hodnoty
    for (int i = 0; i < CoinsCount; i++) {
        cin >> Coins[i].coinValue >> Coins[i].coinCount;
    }
    for (int i = 0; i < CoinsCount; ++i) {
        cout << Coins[i].coinValue << " x " << Coins[i].coinCount;
    }

    return 0;
}
