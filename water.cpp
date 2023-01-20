#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <set>

using namespace std;


    bool menorBloqueDer(vector<vector<int>>& heightMap, int fila, int columna, int ele);
    bool menorBloqueIzq(vector<vector<int>>& heightMap, int fila, int columna, int ele);
    bool menorBloqueAbajo(vector<vector<int>>& heightMap, int fila, int columna, int ele);
    bool menorBloqueArriba(vector<vector<int>>& heightMap, int fila, int columna, int ele);

    int maxDepth = 50;
    int counter = 0;

    bool menorBloqueDer(vector<vector<int>>& heightMap, int fila, int columna, int ele){
        if(counter == maxDepth)
            return true;
        counter++;
        cout << "Buscando derecha " << endl;
        for(int i = columna+1; i < heightMap[fila].size(); i++){
            cout << heightMap[fila][i] << " < " << ele << endl;
            if(heightMap[fila][i] < ele){
                return false;
            }else if(heightMap[fila][i]  == ele){
                if(
                    menorBloqueAbajo(heightMap,fila,i,ele) &&
                    menorBloqueArriba(heightMap,fila,i,ele) &&
                    menorBloqueDer(heightMap,fila,i,ele) //&&
                    /*menorBloqueIzq(heightMap,fila,columna,ele)*/)
                    return true;
            }else
            return true;
            
        }
    }
    bool menorBloqueIzq(vector<vector<int>>& heightMap, int fila, int columna, int ele){
        if(counter == maxDepth)
            return true;
        counter++;
        cout << "Buscando izq " << endl;
        for(int i = columna-1; i >= 0; i--){
            cout << heightMap[fila][i] << " < " << ele << endl;
            if(heightMap[fila][i] < ele){
                return false;
            }else if(heightMap[fila][i]  == ele){
                if(
                    menorBloqueAbajo(heightMap,fila,i,ele) &&
                    menorBloqueArriba(heightMap,fila,i,ele) &&
                    /*menorBloqueDer(heightMap,fila,columna,ele) &&*/
                    menorBloqueIzq(heightMap,fila,i,ele))
                    return true;
            }else
            return true;
            
        }
    }

    bool menorBloqueAbajo(vector<vector<int>>& heightMap, int fila, int columna, int ele){
        if(counter == maxDepth)
            return true;
        counter++;
        cout << "Buscando abajo " << endl;
        //cout << fila+1 << " ? " << heightMap.size() << endl; 
        for(int i = fila+1; i < heightMap.size(); i++){
            cout << heightMap[i][columna] << " < " << ele << endl;
            if(heightMap[i][columna] < ele){
                return false;
            }else if(heightMap[i][columna]  == ele){
                if(
                    menorBloqueAbajo(heightMap,i,columna,ele) &&
                    /*menorBloqueArriba(heightMap,i,columna,ele) &&*/
                    menorBloqueDer(heightMap,i,columna,ele) &&
                    menorBloqueIzq(heightMap,i,columna,ele))
                    return true;
            }else
            return true;
        }
        
    }
    
    bool menorBloqueArriba(vector<vector<int>>& heightMap, int fila, int columna, int ele){
        if(counter == maxDepth)
            return true;
        cout << "Buscando arriba " << endl;
        counter++;
        for(int i = fila-1; i >=0; i--){
            cout << heightMap[i][columna] << " < " << ele << endl;
            if(heightMap[i][columna] < ele){
                return false;
            }else if(heightMap[i][columna]  == ele){
                if(
                    /*menorBloqueAbajo(heightMap,i,columna,ele) &&*/
                    menorBloqueArriba(heightMap,i,columna,ele) &&
                    menorBloqueDer(heightMap,i,columna,ele) &&
                    menorBloqueIzq(heightMap,i,columna,ele))
                    return true;
            }else
            return true;
        }
        
    }

    void printMatrix(vector<vector<int>>& heightMap){
        for(auto a : heightMap){
            for(auto b : a){
                cout << b << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printVector(vector<int>& v){
        for(auto a : v){
            cout << a << " ";
        }
        cout << endl;
    }

    int findMinValue(vector<vector<int>>& heightMap) {
        int min = INT8_MAX;
        int ret = -1;
        for(int i = 1; i < heightMap.size();i++){
            for(int j = 1; j < heightMap[i].size()-1;j++){
                if(heightMap[i][j] < min){
                    min = heightMap[i][j];
                    ret = i;
                }
            }
        }
        return ret;
    }

    
    int trapRainWater(vector<vector<int>>& heightMap) {
        bool first = true;
        int water = 0;
        set<int> posiciones;
        int fila = findMinValue(heightMap);
        int columna;
        int curr_height = 0;

        auto max_element = std::max_element(heightMap.begin(), heightMap.end(),
        [](const std::vector<int>& a, const std::vector<int>& b) {
            return *std::max_element(a.begin(), a.end()) < *std::max_element(b.begin(), b.end());
        });
        int altura_max = *std::max_element((*max_element).begin(),(*max_element).end());
        cout << "La altura maxima es " << altura_max <<endl;

        while(curr_height < altura_max){
            for(auto i : heightMap ){
                if (i == heightMap.front() || i == heightMap.back() ){
                    continue;
                }

                auto min = min_element(i.begin(), i.end());
                cout << "El min elementos de la fila " << fila << " : " << *min << endl;
                for(int j = 0; j < i.size();j++){ 
                    if(i[j] == *min){
                        posiciones.insert(j);
                    }
                }

                for(auto k : posiciones){
                    columna = k;
                    cout << "->>["<< fila << "," << columna << "] : " << heightMap[fila][columna] << endl;
                    if(
                    menorBloqueAbajo(heightMap,fila,columna,heightMap[fila][columna]) &&
                    menorBloqueArriba(heightMap,fila,columna,heightMap[fila][columna]) &&
                    menorBloqueDer(heightMap,fila,columna,heightMap[fila][columna]) &&
                    menorBloqueIzq(heightMap,fila,columna,heightMap[fila][columna])){
                        cout << "Rellenando " << endl;
                        heightMap[fila][columna]++;
                        water++;
                    }
                }
                fila = (fila + 1) % (heightMap[0].size()-1);
            }
            fila = 1;
            curr_height++;
            cout << endl << "Aumentando la altura " << curr_height << endl;
            printMatrix(heightMap);
        }
        return water;
    }

    int trapRainWater2(vector<vector<int>>& heightMap) {
        bool first = true;
        int water = 0;
        set<int> posiciones;
        int fila = findMinValue(heightMap);
        int columna;
        int curr_height = 0;

        auto max_element = std::max_element(heightMap.begin(), heightMap.end(),
        [](const std::vector<int>& a, const std::vector<int>& b) {
            return *std::max_element(a.begin(), a.end()) < *std::max_element(b.begin(), b.end());
        });
        int altura_max = *std::max_element((*max_element).begin(),(*max_element).end());
        cout << "La altura maxima es " << altura_max <<endl;

        while(curr_height < altura_max){
            for(int i = fila; i < heightMap.size()-1;i++ ){
                if (i == 0  ){
                    continue;
                }

                auto min = min_element(heightMap.at(i).begin(), heightMap.at(i).end());
                cout << "El min elementos de la fila " << fila << " : " << *min << endl;
                for(int j = 0; j < heightMap.at(i).size();j++){ 
                    if((heightMap.at(i)).at(j) == *min){
                        posiciones.insert(j);
                    }
                }

                for(auto k : posiciones){
                    columna = k;
                    cout << "->>["<< fila << "," << columna << "] : " << heightMap[fila][columna] << endl;
                    if(
                    menorBloqueAbajo(heightMap,fila,columna,heightMap[fila][columna]) &&
                    menorBloqueArriba(heightMap,fila,columna,heightMap[fila][columna]) &&
                    menorBloqueDer(heightMap,fila,columna,heightMap[fila][columna]) &&
                    menorBloqueIzq(heightMap,fila,columna,heightMap[fila][columna])){
                        cout << "Rellenando " << endl;
                        heightMap[fila][columna]++;
                        water++;
                    }
                }
                fila = (fila + 1) % (heightMap[0].size()-1);
            }
            fila = findMinValue(heightMap);
            curr_height++;
            cout << endl << "Aumentando la altura " << curr_height << endl;
            printMatrix(heightMap);
        }
        return water;
    }



int main(){
    vector<vector<int >> caso = { {1,4,3,1,3,2},
                                {3,2,1,3,2,4},
                                {2,3,3,2,3,1}};
    vector<vector<int >> caso2 =   {{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}};
  cout << endl << "Aguas: " << trapRainWater2(caso2) << endl;

  
}
/*

{3,3,3,3,3}
{3,2,2,2,3}
{3,2,1,2,3}
{3,2,2,2,3}
{3,3,3,3,3}

*/
