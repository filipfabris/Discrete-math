#include <iostream>
#include <math.h>

using namespace std;

//Pomocne funkcije za rjesavanje linearnog sustava
void Cramer(double sustav[], double rjesenje[]){
    double a = sustav[0];
    double b = sustav[1];
    double e = sustav[2];

    double c = sustav[3];
    double d = sustav[4];
    double f = sustav[5];

    double determinanta = a * d - b * c;
    if (determinanta != 0){
        double x = (e * d - b * f) / determinanta;
        double y = (a * f - e * c) / determinanta;
        rjesenje[0] = x;
        rjesenje[1] = y;
    }
    else{
        printf("Determinanta je 0\n"
            "Nema rjesenja ili ih je beskonacno mnogo\n");
    }
}

//Pomocna funkcija za izracun nultocki
void kvadratnaJednazba(double a, double b, double c, double polje[]){
    double x1, x2, diskriminanta, realni_dio, imaginarni_dio;

    diskriminanta = b * b - 4 * a * c;

    if (diskriminanta > 0){
        x1 = (-b + sqrt(diskriminanta)) / (2 * a);
        x2 = (-b - sqrt(diskriminanta)) / (2 * a);
        polje[0] = x1;
        polje[1] = x2;
    }

    else if (diskriminanta == 0){
        x1 = -b / (2 * a);
        polje[0] = x1;
        polje[1] = x1;
    }

    else{
        realni_dio = -b / (2 * a);
        imaginarni_dio = sqrt(-diskriminanta) / (2 * a);
        throw std::invalid_argument("RJESENJA SU IMAGINARNA!");
    }
    return;
}





double rekurzija(int const1, int const2, double prvi_clan, double drugi_clan, int n){
    double F0 = prvi_clan;
    double F1 = drugi_clan;
    double Fn = 0;

    if (n == 0){
        return prvi_clan;
    }
    if (n == 1){
        return drugi_clan;
    }

    for (int i = 2; i <= n; i++){
        Fn = const2 * F0 + const1 * F1;
        F0 = F1;
        F1 = Fn;
    }
    return Fn;

}





double zatvorenaForma(int const1, int const2, double prvi_clan, double drugi_clan, int n){
    double nul_tocke[2] = {0, 0};
    try{
        kvadratnaJednazba(1.0, -const1, -const2, nul_tocke);
    }
    catch (exception& e){
        cerr << "Problem: " << e.what() << endl;
        exit(1);
    }

    double sustav[6] = {0, 0, 0, 0, 0, 0};
    double rjesenje[2] = {0, 0};

    if (nul_tocke[0] == nul_tocke[1]){

        sustav[0] = powf(nul_tocke[0], 0);
        sustav[1] = 0 * powf(nul_tocke[1], 0);
        sustav[2] = prvi_clan;

        sustav[3] = powf(nul_tocke[0], 1);
        sustav[4] = 1 * powf(nul_tocke[1], 1);
        sustav[5] = drugi_clan;

        Cramer(sustav, rjesenje);

        return rjesenje[0] * pow(nul_tocke[0], n) + rjesenje[1] * n * pow(nul_tocke[1], n);

    }
    else{

        sustav[0] = powf(nul_tocke[0], 0);
        sustav[1] = powf(nul_tocke[1], 0);
        sustav[2] = prvi_clan;

        sustav[3] = powf(nul_tocke[0], 1);
        sustav[4] = powf(nul_tocke[1], 1);
        sustav[5] = drugi_clan;

        Cramer(sustav, rjesenje);

        return rjesenje[0] * pow(nul_tocke[0], n) + rjesenje[1] * pow(nul_tocke[1], n);
    }
}


int main(){
    int const1 = 0;
    int const2 = 0;
    cout << "Unesite prvi koeficijent lambda_1 rekurzivne  relacije : ";
    cin >> const1;

    cout << "Unesite drugi koeficijent lambda_2 rekurzivne  relacije : ";
    cin >> const2;

    double prvi_clan = 0;
    double drugi_clan = 0;
    cout << "Unesite  vrijednost  nultog  clana  niza  a_0: ";
    cin >> prvi_clan;
    cout << "Unesite  vrijednost  prvog  clana  niza  a_1: ";
    cin >> drugi_clan;

    int trazeni_clan = 0;
    cout << "Unesite  redni  broj  n  trazenog  clana  niza: ";
    cin >> trazeni_clan;

    if (const1 == 0 && const2 == 0){
        cout << "Slucaj 1: " << endl;
        cout << "Clanovi su 0 " << endl;
        return 0;
    }

    if (prvi_clan == 0 && drugi_clan == 0){
        cout << "Slucaj 2: " << endl;
        cout << "Svi clanovi su 0 " << endl;
        return 0;
    }

    double rjesenje = 0;
    rjesenje = rekurzija(const1, const2, prvi_clan, drugi_clan, trazeni_clan);
    cout << "Rjesenje pomocu rekurzije: " << rjesenje << endl;

    rjesenje = zatvorenaForma(const1, const2, prvi_clan, drugi_clan, trazeni_clan);
    cout << "Rjesenje pomocu zatvorene forme: " << rjesenje << endl;

    return 0;
}