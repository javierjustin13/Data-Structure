#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double  hash(double dps, double clipCap, double ROF, double price) {
    return (dps * clipCap + ROF) / price;
}



int main() {
    double AK47 = hash(36, 30, 600, 2700); 
    double Sawed = hash(96, 8, 70, 1200); 
    double P90 = hash(26, 50, 857, 2350);
    double Tec9 = hash(33, 18, 500, 500);
    double AUG = hash(28, 30, 666, 3300);
    double XM = hash(88, 7, 171, 2000);

    printf("AK47: %lf\n", AK47);
    printf("Sawed: %lf\n", Sawed);
    printf("P90: %lf\n", P90);
    printf("Tec9: %lf\n", Tec9);
    printf("AUG: %lf\n", AUG);
    printf("XM: %lf\n", XM);
    
    return 0;
}