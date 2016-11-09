#include <iostream>
#include <array>

using namespace std;

struct coin{
    int coinValue;
    int coinCount;
};

int CoinsCount, Amount;

void quicksort(coin  array[], int left, int right){
    if(left < right){
        int boundary = left;
        for(int i = left + 1; i < right; i++){
            if(array[i].coinValue > array[left].coinValue){
                int swapLeft = i;
                int swapRight = ++boundary;

                int tmpCount = array[swapRight].coinCount;
                int tmpValue = array[swapRight].coinValue;

                array[swapRight].coinCount = array[swapLeft].coinCount;
                array[swapRight].coinValue= array[swapLeft].coinValue;
                array[swapLeft].coinCount = tmpCount;
                array[swapLeft].coinValue = tmpValue;
            }
        }
        int swapLeft = left;
        int swapRight = boundary;

        int tmpCount = array[swapRight].coinCount;
        int tmpValue = array[swapRight].coinValue;

        array[swapRight].coinCount = array[swapLeft].coinCount;
        array[swapRight].coinValue= array[swapLeft].coinValue;
        array[swapLeft].coinCount = tmpCount;
        array[swapLeft].coinValue = tmpValue;

        quicksort(array, left, boundary);
        quicksort(array, boundary + 1, right);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    cin >> CoinsCount >> Amount;
    // vytvorime pole
    coin * Coins = new coin[CoinsCount];
    //nacitame hodnoty
    for (int i = 0; i < CoinsCount; i++) {
        cin >> Coins[i].coinValue >> Coins[i].coinCount;
    }
    cout << "Zotriedene pole minci" << endl;

    quicksort(Coins, 0, CoinsCount);

    for (int i = 0; i < CoinsCount; ++i) {
        cout << Coins[i].coinValue << "x" << Coins[i].coinCount << endl;
    }

    return 0;
}
