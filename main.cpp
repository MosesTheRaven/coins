#include <iostream>
#include <array>

using namespace std;

int CoinsTypeCount, Amount, returnCoinsAmount ;
bool foundSolution;
int * coinValue, * coinCount,  * returnCount ;

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

void payout(int * usedCoins, int remainingSum, int ignoreIndex){
    //cout << "spustila sa rekurzia so sumou" << remainingSum << endl;
    //koncime vetvu rekurzie, ak sme dosiahli sumu, ktoru sme mali vyplatit
    if (remainingSum == 0) {
        foundSolution = true;
        cout << "nasiel som riesenie" << endl;
        for (int i = 0; i < CoinsTypeCount; ++i) {
            cout << "Minca " << coinValue[i] << " " << coinCount[i] - usedCoins[i] << "-krat" << endl;
        }
        //skontrolujeme, ci mame najlepsie riesenie
        int usedCoinsAmount = 0;
        returnCoinsAmount = 0;
        for (int i = 0; i < CoinsTypeCount; ++i) {
            returnCoinsAmount += returnCount[i];
            usedCoinsAmount += coinCount[i] - usedCoins[i];
        }
        if(usedCoinsAmount < returnCoinsAmount){
            for (int i = 0; i < CoinsTypeCount; ++i) {
                returnCount[i] = coinCount[i] - usedCoins[i];
            }
        }
        //inak nechame tak, pretoze sme predtym nasli lepsie riesenie
    }
    //inak sa pokracujeme v rekurzii
    //pripad, ze nam po odcitani z predchadzajucej rekurzie ostalo este nieco, co musime vyplatit
    else if(remainingSum > 0){
        //este existuju mince mensej nominalnej hodnoty
        if(ignoreIndex != CoinsTypeCount){
            //spustime cyklus, ktory postupne vyberie 0, 1, 2, ... az po pocet minci danej nominalnej hodnoty
            for (int i = 0; i <= coinCount[ignoreIndex]; ++i) {
                //vytvorime si nove pole pre kazdu z moznosti vybranych poctov mincii
                int * actualCoinsUsed = new int[CoinsTypeCount];
                //dosadime rovnake hodnoty ako boli predtym
                for (int j = 0; j < ignoreIndex; ++j) {
                    actualCoinsUsed[j] = usedCoins[j];
                }
                for (int j = ignoreIndex; j < CoinsTypeCount; ++j) {
                    actualCoinsUsed[j] = coinCount[j];
                }
                //explicitne odoberieme pocet minci danej nominalnej hodnoty, ktore sme tentokrat vzali
                actualCoinsUsed[ignoreIndex] -= i;
                //spustime rekurziu s novymi paramatrami
                payout(actualCoinsUsed, remainingSum-i*coinValue[ignoreIndex], ignoreIndex + 1);
            }
        }
        else{
        //uz neexistuju ziadne mince mensej nominalnej hodnoty
            return;
        }
    }
    //pripad, ze po odcitani nam vznikla zaporna suma ... musime skoncit, lebo nemame spravne riesenie
    else{
        return;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    //nacitame pocet minci a sumu na zaplatenie
    cin >> CoinsTypeCount >> Amount;
    //naalokujeme miesto pre polia
    coinValue = new int[CoinsTypeCount];
    coinCount = new int[CoinsTypeCount];
    returnCount = new int[CoinsTypeCount];
    returnCoinsAmount = 0;
    //nacitame hodnoty
    for (int i = 0; i < CoinsTypeCount; i++) {
        cin >> coinValue[i] >> coinCount[i];
        returnCount[i] = INT8_MAX;
    }
    //zotriedime mince podla nominalnej hodnoty
    quicksort(0, CoinsTypeCount);
    cout << "zotriedene mince: "<<endl;
    for (int i = 0; i < CoinsTypeCount; i++) {
        cout <<"minca hodnoty: " << coinValue[i] << " " << coinCount[i] <<"-krat"<< endl;
    }
    //vyplatime sumu

    int * actualCount = new int[CoinsTypeCount];

    for (int i = 0; i < CoinsTypeCount; ++i) actualCount[i] = 0;

    payout(actualCount, Amount, 0);
    if(foundSolution){
        cout << endl << "Najlepsie riesenie: " << returnCoinsAmount << " minci"<< endl;
        for (int i = 0; i < CoinsTypeCount; ++i) {
            cout << "Minca " << coinValue[i] << " " << returnCount[i] << "-krat" << endl;
        }
    }
    else{
        cout << "Suma sa neda zaplatit";
    }

    return 0;
}