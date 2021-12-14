#include <iostream>
#include <bits/stdc++.h>
#include <string>

using namespace std;

void pohlepni_Algoritam1(vector<vector<double>> matrica, int size){

    int visited[size] = {0};

    int min = INT_MAX;
    double sum = 0;
    int prvi = 0;
    int drugi = 0;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (matrica[i][j] != 0 && matrica[i][j] < min){
                min = matrica[i][j];
                prvi = i;
                drugi = j;
            }
        }
    }

    visited[prvi] = 1;
    visited[drugi] = 1;
    sum = min;

    int i = drugi;
    while (1){
        int counter = 0;
        min = INT_MAX;
        int sljedeci = 0;

        for (int j = 0; j < size; j++){
            if (visited[j] == 0 && matrica[i][j] < min && matrica[i][j] != 0){
                min = matrica[i][j];
                sljedeci = j;
            }
            else{
                counter++;
            }
        }

        if (counter == size){
            sum = sum + matrica[i][prvi];
            break;
        }

        sum = sum + min;
        visited[sljedeci] = 1;
        i = sljedeci;
    }

    cout << "Rezultat pohleptnog algoritma1: " << sum << endl;
}



void pohlepni_Algoritam2(vector<vector<double>> matrica, int size){

    int visited[size] = {0};

    int min = INT_MAX;
    double sum = 0;
    int prvi = 0;
    int drugi = 0;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (matrica[i][j] != 0 && matrica[i][j] < min){
                min = matrica[i][j];
                prvi = i;
                drugi = j;
            }
        }
    }

    visited[prvi] = 1;
    visited[drugi] = 1;
    sum = min;

    int k = prvi;
    int i = drugi;
    while (1){
        int counter_l = 0;
        int counter_r = 0;
        int min_l = INT_MAX;
        int min_r = INT_MAX;

        int sljedeci_l = 0;
        int sljedeci_r = 0;

        for (int j = 0; j < size; j++){
            if (visited[j] == 0 && matrica[i][j] < min_l && matrica[i][j] != 0){
                min_l = matrica[i][j];
                sljedeci_l = j;
            }
            else{
                counter_l++;
            }
        }

        if (counter_l == size){
            sum = sum + matrica[i][prvi];
            break;
        }

        for (int j = 0; j < size; j++){
            if (visited[j] == 0 && matrica[k][j] < min_r && matrica[k][j] != 0){
                min_r = matrica[k][j];
                sljedeci_r = j;
            }
            else{
                counter_r++;
            }

        }

        if (counter_r == size){
            sum = sum + matrica[i][drugi];
            break;
        }

        if (min_l <= min_r){
            visited[sljedeci_l] = 1;
            sum = sum + min_l;
            i = sljedeci_l;
            drugi = sljedeci_l;
        }
        else{
            visited[sljedeci_r] = 1;
            sum = sum + min_r;
            k = sljedeci_r;
            prvi = sljedeci_r;
        }

    }

    cout << "Rezultat pohleptnog algoritma2: " << sum << endl;
}

void Iscrpni_algoritam(vector<vector<double>>& matrica, int n){

    int vrhovi[n] = {0};
    int min = INT_MAX;

    for (int i = 0; i < n; i++){
        vrhovi[i] = i;
    }

    // cout << endl;
    // cout << "Putevi: " << endl;

    do{
        int put = 0;
        int i = 0;

        for (i = 0; i < n - 1; i++){
            // cout << vrhovi[i] + 1 << ", ";
            put = put + matrica[vrhovi[i]][vrhovi[i + 1]];
        }

        // cout << vrhovi[i] + 1 << "   ";

        put = put + matrica[vrhovi[i]][vrhovi[i + 1 - n]];

        // cout << put << endl;
        min = std::min(min, put);

    } while (next_permutation(vrhovi, vrhovi + n));

    cout << "Rezultat iscrpnog pretrazivanja " << min << endl;
}

int main(){

    cout << "Unesite  redom,  odvojene  razmakom,  parametre  n,  a  i  b:";
    double a, b, n;
    cin >> n >> a >> b;


    vector<vector<double>> matrica;
    matrica.resize(n);

    for (int l = 1; l <= n; l++){
        matrica[l - 1].resize(n, 0);
        for (int k = 1; k <= n && k < l; k++){
            matrica[l - 1][k - 1] = (a * k + b * l) * (a * k + b * l) + 1;
            matrica[k - 1][l - 1] = (a * k + b * l) * (a * k + b * l) + 1;

        }
    }

    cout << "Matrica: " << endl;
    for (int k = 1; k <= n; k++){
        for (int l = 1; l <= n; l++){
            cout << matrica[k - 1][l - 1] << "  ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Rezultati: " << endl;
    pohlepni_Algoritam1(matrica, n);
    pohlepni_Algoritam2(matrica, n);
    Iscrpni_algoritam(matrica, n);

    return 0;
}