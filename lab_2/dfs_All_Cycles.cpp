#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int N = 100;

enum node_states_en{
    UNVISITED,  //0 po defaultu
    INSTACK,    //svaki sljedeci je za +1 po defaultu
    VISITED
};


class Graph{
private:
    int size;
    vector<vector<int>> graph;
    vector<vector<int>> cycles;

    vector<int> previous;
    vector<vector<int>> mark;

    int broj_ciklusa = 0;

public:
    Graph(int edges){
        this->size = edges + 10;
        this->graph.resize(size);
        this->cycles.resize(size);
        this->previous.resize(size, 0);

        mark.resize(size);
        for (int i = 0; i < size; i++){
            this->mark[i].resize(size, 0);
        }
    }

    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void printEdges(){
        for (int i = 0; i < 9; i++){
            cout << "graph[" << i + 1 << "] = ";
            for (int x : graph[i + 1]){
                cout << x << ", ";
            }
            cout << endl;
        }
    }

    //c - dijete / child
    //p - roditelj /parent
    void dfs_ciklus(int c, int p, vector<int> visited){

        if (visited[c] == VISITED){
            return;
        }

        if (visited[c] == INSTACK){

            broj_ciklusa++;
            int cur = p;
            mark[broj_ciklusa][cur] = broj_ciklusa;

            while (cur != c){
                cur = previous[cur];
                mark[broj_ciklusa][cur] = broj_ciklusa;
            }
            return;
        }
        previous[c] = p;


        visited[c] = INSTACK;


        //dfs
        for (int v : graph[c]){

            if (v == previous[c]){
                continue;
            }
            dfs_ciklus(v, c, visited);
        }

        visited[c] = VISITED;
    }

    void printCiklus(){

        for (int vect_in; vect_in <= broj_ciklusa; vect_in++){
            for (int i = 0; i < size; i++){
                if (mark[vect_in][i] != 0)
                    cycles[mark[vect_in][i]].push_back(i);
            }
        }


        for (int i = 1; i <= broj_ciklusa; i++){
            cout << "Ciklus " << i << ". " ": ";
            for (int x : cycles[i])
                cout << x << " ";
            cout << endl;
        }
        cout << endl;
    }

    void printNajveci(){
        if (broj_ciklusa == 0){
            return;
        }

        int max = 0;
        int index = 0;

        for (int i = 0; i <= broj_ciklusa; i++){
            int brojac = 0;
            for (int x : cycles[i]){
                brojac++;
            }
            if (brojac > max){
                max = brojac;
                index = i;
            }

        }

        cout << "Najveci ciklus " << " : ";
        int counter = 0;
        for (int x : cycles[index]){
            cout << x << " ";
            counter++;
        }
        cout << endl;
        cout << "Size: " << counter;
    }

};

int main(){

    string line;
    int size;
    int element = 0;
    int counter = 0;
    vector<vector<int>> matrix;
    ifstream file("02.txt");

    if (file.is_open()){
        file >> size;
        matrix.resize(size);


        getline(file, line);

        for (int i = 0; i < size; i++){
            matrix[i].resize(size);
            for (int j = 0; j < size; j++){
                file >> element;
                matrix[i][j] = element;
                element == 1 ? counter++ : 0;
            }
        }

        file.close();
    }

    Graph G3(counter / 2);

    for (int i = 0; i < size; i++){
        if (i > 0)
            cout << endl;
        for (int j = 0; j < size; j++){
            cout << matrix[i][j] << " ";
        }
    }
    cout << endl;
    cout << endl;

    for (int i = 0; i < size; i++){
        for (int j = i; j < size; j++){
            if (matrix[i][j] == 1){
                // cout << "u = " << i + 1 << "v = " << j + 1 << endl;
                G3.addEdge(i + 1, j + 1);
            }
        }
    }
    int N = counter / 2;
    vector<int> visited(N, 0);


    G3.printEdges();
    G3.dfs_ciklus(1, -1, visited);
    G3.printCiklus();
    G3.printNajveci();


}
