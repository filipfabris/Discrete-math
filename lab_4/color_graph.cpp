#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph{
private:
    int vertices;
    int brojac = 0;
    int brojac2 = 0;
    vector<vector<int>> graph;
    vector<int> color;

public:
    Graph(int size){
        this->vertices = size;
        this->graph.resize(vertices);
        this->color.resize(vertices, 0);
    }

    void addEdge(int u, int v){
        graph[u].push_back(v);
        graph[v].push_back(u);

    }

    void printEdges(){
        for (int i = 0; i < vertices; i++){
            cout << "graph[" << i << "] = ";
            for (int x : graph[i]){
                cout << x << ", ";
            }
            cout << endl;
        }
    }

    //complete graph chech
    int findMaxDecree(bool& check){
        int max = 0;
        int counter = 0;
        for (int i = 0; i < vertices; i++){
            for (int j : graph[i]){
                counter++;

            }
            if (counter > max){
                if (max != 0 && check){
                    check = false;
                }
                max = counter;
            }
            counter = 0;
        }
        return max;
    }

    void Chromatic_index(){
        bool complete_graph = true; //check it

        int decree = findMaxDecree(complete_graph); //max vertex decree
        int G_granica;  //Upper bond

        if (decree == 1){
            cout << "Null graph is, 1-colored";
            return;
        }

        if (complete_graph){
            cout << "Complete graph is, " << vertices << "-colored";
            return;
        }

        if (decree < 3)
            G_granica = decree + 1; //Theorem
        else
            G_granica = decree; //Broks Theorem

        int D_granica = 2;

        bool flag = false;  //falg if lower bond is biger then upper bond
        while (D_granica < G_granica){
            flag = Color_graph(D_granica, 0);
            if (flag == true){
                cout << "Graph is " << D_granica << "-colored" << endl;
                print_colored_verticies();
                return;
            }
            D_granica++;
        }
        cout << "Graph is " << G_granica << "-colored" << endl;
        print_colored_verticies();
        return;

    }

    void print_colored_verticies(){
        for (int i = 0; i < vertices; i++)
            cout << color[i] << " ";
    }

    //color-index
    //vrh - current vertex
    bool Color_graph(int c_index, int vrh){
        if (vrh == vertices){
            return true;
        }

        for (int i = 1; i <= c_index; i++){

            if (Color_check(vrh, i) == true){
                color[vrh] = i;

                if (Color_graph(c_index, vrh + 1) == true){
                    return true;
                }
                //backtracking
                color[vrh] = 0;
            }

        }

        return false;
    }

    //vrh
    //c-chech if you can color vertex vrh with color c
    bool Color_check(int vrh, int c){
        for (int i = 0; i < graph[vrh].size(); i++){
            for (int j : graph[graph[vrh][i]]){
                if (vrh == j && c == color[graph[vrh][i]]){
                    return false;
                }
            }
        }
        return true;
    }


};

void Adjacency_matrix(vector<vector<int>>& matrix){
    for (auto i : matrix){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void LoadFile(int& verticles, int& S, vector<int>& S_elements){

    string line;

    ifstream file("C:/Users/filip/Desktop/Discrete_math/lab_4/graf.txt");

    if (file.is_open()){
        file >> verticles;

        getline(file, line);
        file >> S;
        S_elements.resize(S);

        getline(file, line);

        int element = 0;

        for (int i = 0; i < S; i++){
            file >> element;
            S_elements[i] = element;
        }

        file.close();
    }

}

int main(){

    int verticles;
    int S;
    vector<int> S_elements;
    LoadFile(verticles, S, S_elements);

    Graph g(verticles);
    vector<vector<int>> matrix(verticles, vector<int>(verticles, 0));

    for (int i = 1; i <= verticles; i++){
        for (int j = i + 1; j <= verticles; j++){
            int el = j - i;
            el = abs(el);
            for (int x : S_elements){
                if (el == x){
                    g.addEdge(i - 1, j - 1);  //Inputs for graph class
                    matrix[i - 1][j - 1] = 1; //Inputs for adjency matrix
                    matrix[j - 1][i - 1] = 1;
                }

            }
        }
    }

    Adjacency_matrix(matrix);
    //g.printEdges();
    g.Chromatic_index();

    return 0;
}