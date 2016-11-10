#include <iostream>
#include <array>

using namespace std;

int CoinsCount, Amount;

int * coinValue, * coinCount, * returnValue,  * returnCount ;

void quicksort(int left, int right){
    if(left < right){
        int boundary = left;
        for(int i = left + 1; i < right; i++){
            if(coinValue[i] > coinValue[left]){
                int swapLeft = i;
                int swapRight = ++boundary;

                int tmpCount = coinCount[swapRight];
                int tmpValue = coinValue[swapRight];

                coinCount[swapRight] = coinCount[swapLeft];
                coinValue[swapRight]= coinValue[swapLeft];
                coinCount[swapLeft] = tmpCount;
                coinValue[swapLeft] = tmpValue;
            }
        }
        int swapLeft = left;
        int swapRight = boundary;

        int tmpCount = coinCount[swapRight];
        int tmpValue = coinValue[swapRight];

        coinCount[swapRight] = coinCount[swapLeft];
        coinValue[swapRight] = coinValue[swapLeft];
        coinCount[swapLeft] = tmpCount;
        coinValue [swapLeft]= tmpValue;

        quicksort(left, boundary);
        quicksort(boundary + 1, right);
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    //nacitame pocet minci a sumu na zaplatenie
    cin >> CoinsCount;
    //naalokujeme miesto pre polia
    coinValue = new int[CoinsCount];
    coinCount = new int[CoinsCount];
    returnValue = new int[CoinsCount];
    returnCount = new int[CoinsCount];
    //nacitame hodnoty
    for (int i = 0; i < CoinsCount; i++) {
        cin >> coinValue[i] >> coinCount[i];
    }
    //zotriedime mince podla nominalnej hodnoty

    quicksort(0, CoinsCount);
    cout << "zotriedene mince: "<<endl;
    for (int i = 0; i < CoinsCount; i++) {
        cout <<"minca hodnoty: " << coinValue[i] << " " << coinCount[i] <<"-krat"<< endl;
    }
    return 0;
}