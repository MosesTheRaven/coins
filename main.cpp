//komentar k rieseniu a premennym je pri int main() nizsie

#include <iostream>

using namespace std;

int CoinsTypeCount, Amount, returnCoinsAmount;
bool foundSolution;
int * coinValue, * coinCount,  *returnValue, * returnCount ;
//globalne pre ulahcnenie prace
//pri pouzivani smernikov som (dufam) zmazal vsetko, s cim som uz dalej nemal v plane pracovat

int getIndex(int searchedNumber){
    //funkcia, ktora vrati index, na ktorom sa nachadza hladane cislo
    //potrebne kvoli quicksortu, ktore pomeni poradie minci
    int retVal = 0;
    for(retVal; retVal < CoinsTypeCount; retVal++){
        if (coinValue[retVal] == searchedNumber) break;
    }
    return retVal;
}

void quicksort(int left, int right){
    //quicksort na zotriedenie minci podla velkosti - toto vyrazne urychli celkovy vypocet
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
    //rekurzia, ktora odcitava od sumy mince, pricom ignoruje tie, ktore uz boli odcitane
    //koncime vetvu rekurzie, ak sme dosiahli sumu, ktoru sme mali vyplatit
    if (remainingSum == 0) {
        //nasli sme nejake riesenie
        foundSolution = true;
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
        //inak zahodime tak, pretoze sme predtym nasli lepsie riesenie
        delete(usedCoins);
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
            delete(usedCoins);
            return;
        }
    }
    //pripad, ze po odcitani nam vznikla zaporna suma ... musime skoncit, lebo nemame spravne riesenie
    else{
        delete(usedCoins);
        return;
    }
}
void output() {
    if(foundSolution){
        returnCoinsAmount = 0;
        for (int i = 0; i < CoinsTypeCount; ++i) {
            returnCoinsAmount += returnCount[i];
        }
        cout << "Pocet pouzitych minci: " << returnCoinsAmount << endl;
        for (int i = 0; i < CoinsTypeCount; ++i) {
            int index = getIndex(returnValue[i]);
            cout << "Minca " << returnValue[i] << ": " << returnCount[index] << endl;
        }
    }
    else{
        cout << "Suma sa neda zaplatit";
    }
}

int main() {
    /*
     * POSTUP RIESENIA:
     * nacitanie vstupu
     *      nominalna hodnota minci do pola coinValue
     *      pocet minci pre danu nominalnu hodnotu do pola coinCount
     * jednoduchym odhadom je vidiet, ze generovanie vsetkych podmnozin by dalo exponencionalnu zlozitost
     * rozhodol som sa preto pouzit niekolko optimalizacii:
     *      1. usporiadanie nominalnych hodnot mincii - quicksort O(n*logn)
     *      2. ukoncenie vypoctu, ak dosiahnem sumu, ktoru mam vyplatit
     *      3. ukoncenie vypoctu, ak presiahnem sumu, ktoru mam vyplatit
     * tato zlozitost je este stale exponencialna vo worst-case (ba este horsia, kvoli triedeniu - to sa ale pre privysoke N strati)
     *          ale v priemere by mala dosahovat prijemne vysledky
     *
     *  smernik returnValue odkazuje na polia, ktore si pamataju povodne zadane poradie mincii
     *
     *  returnCount nastavujem na MAXINT aby som predisiel chybnym prvym scitaniam - hned po prvom dosiahnuti vysledku uz nabera normalne hodnoty
     *
     *  returnCoinsAmount
     */


    //nacitame pocet minci a sumu na zaplatenie
    cin >> CoinsTypeCount >> Amount;
    //naalokujeme miesto pre polia
    coinValue = new int[CoinsTypeCount];
    coinCount = new int[CoinsTypeCount];
    returnCount = new int[CoinsTypeCount];
    returnValue = new int[CoinsTypeCount];
    returnCoinsAmount = 0;
    //nacitame hodnoty
    for (int i = 0; i < CoinsTypeCount; i++) {
        cin >> coinValue[i] >> coinCount[i];
        returnCount[i] = INT8_MAX;
        returnValue[i] = coinValue[i];
    }

    //zotriedime mince podla nominalnej hodnoty
    quicksort(0, CoinsTypeCount);

    //vyplatime sumu
    //pred spustenim rekurzie vytvorim pole, ktore si budem podavat v rekurzii
    int * actualCount = new int[CoinsTypeCount];
    for (int i = 0; i < CoinsTypeCount; ++i) actualCount[i] = 0;
    payout(actualCount, Amount, 0);
    delete(actualCount); // toto mazanie dokonca ani nemusi byt potrebne, kedze mazem aj v payout
    //vypis
    output();
    //mazanie dalej nepouzivanych poli
    delete(coinValue, coinCount, returnCount, returnValue);
    return 0;
}

