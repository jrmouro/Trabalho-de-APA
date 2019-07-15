#include <iostream>
#include "../include/QuickSort.h"
#include "../include/Cenario1.h"
#include "../include/Cenario2.h"

int main() {

    unsigned vetorN[] = {500, 5000, 50000, 100000};

    Cenario1 cen1(vetorN, 4, 0.1f), cen2(vetorN, 4, 0.5f), cen3(vetorN, 4, 2.0f);  
    
    cen1.executar("F01", 10);

    cen2.executar("F05", 10);

    cen3.executar("F20", 10);

    Cenario2 cen4(vetorN, 4, 0.1f), cen5(vetorN, 4, 0.5f), cen6(vetorN, 4, 2.0f);  
    
    cen4.executar("F01", 10);

    cen5.executar("F05", 10);

    cen6.executar("F20", 10);

       

}