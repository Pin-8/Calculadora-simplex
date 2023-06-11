#include <iostream>
#include <vector>

using namespace std;

int main() {
    int variables=2;
    int restricciones=3;
    vector<float> z, h, v; // variables auxiliares (Almacenan valores temporalmente)
    vector<vector<float>> matriz;
    vector<int> x;    
    int i, j;
    int Col_Pivote, Fila_Pivote;

    

    z.resize(variables + 1, 0);
    matriz.resize(restricciones + 1, vector<float>(variables + 1, 0));
    x.resize(restricciones + 1, 0);
    h.resize(variables + 1, 0);
    v.resize(restricciones + 1, 0);
    
    //Valores de utilidad
    z[0]=120; // A
    z[1]=90;  // B
    
    //Filas 1.
    matriz[0][0] = 0.3;  //Columna
    matriz[0][1] = 0.4;  //Columna
    matriz[0][2] = 100;  //Columna
    //Filas 2.
    matriz[1][0] = 0.5;  //Columna
    matriz[1][1] = 0.2;  //Columna
    matriz[1][2] = 120;  //Columna
    //Filas 3.
    matriz[2][0] = 0.2;  //Columna
    matriz[2][1] = 0.4;  //Columna
    matriz[2][2] = 100;  //Columna




    cout << "+---------------------+\n";
    cout << "Matriz Original : "<< "\n";
    cout << "+---------------------+\n";
    for (j = 0; j < restricciones; j++) {
        cout << "| x" <<  j  << " | " << matriz[j][variables] << " | ";
        for (i = 0; i < variables; i++) {
                cout << matriz[j][i] << " |";
        }
        cout << "\n";
    }






       
     //***************** muestro los valores de z *****************
    cout<<"+---------------------+";
    cout << "\n| Z  = " ;

    for (int i = 0; i < z.size()-1; i++) {
          
            cout << " "<< z[i] ;  
            if (i==0){ cout << " +";  };       
    }
    cout << "      | \n+---------------------+";




    // ***************** Relleno el resto de la matriz *****************
    for (j = 0; j < restricciones; j++) {  
        x[j] = 0;
        x[j]--;
    }


    // ***************** Paso 1: Construir la tabla inicial *****************
    matriz[restricciones].resize(variables + 1, 0);
    for (i = 0; i <= variables; i++) {
        matriz[restricciones][i] = -z[i];
        for (j = 0; j < restricciones; j++) {
            matriz[restricciones][i] += matriz[j][i] * z[x[j]];
        }
    }

    // ***************** tabla primaria *****************
    cout << "\n\n+---------------------+\n";
    cout << "Matriz Primera iteración : "<< "\n";
    cout << "+---------------------+\n";
    for (j = 0; j < restricciones; j++) {
        cout << "| x" << j << " | " << matriz[j][variables] << " | ";
        for (i = 0; i < variables; i++) {
           
                cout << matriz[j][i] << " |";
            
        }
        cout << "\n";
    }
      cout<<"+---------------------+";

    cout << "\n| Z | " << matriz[restricciones][variables] << " | ";
    for (i = 0; i < variables; i++) {
        cout << matriz[restricciones][i] << " | ";
    }
    cout << "\n+---------------------+";





    while (true) {
        // ***************** 2: Encuentro la columna pivote *****************
        Col_Pivote = 1;
        for (i = 0; i < variables; i++) {
            if (matriz[restricciones][i] < matriz[restricciones][Col_Pivote]) {
                Col_Pivote = i;
            }
        }
        if (matriz[restricciones][Col_Pivote] >= 0) {
            break;  // Se ha alcanzado la solución óptima
        }




        // ***************** 3: Encuentro la fila pivote (Fila_Pivote) *****************
        Fila_Pivote = 1;
        for (j = 0; j < restricciones; j++) {
            if (matriz[j][variables] * matriz[Fila_Pivote][Col_Pivote] < matriz[Fila_Pivote][variables] * matriz[j][Col_Pivote]) {
                Fila_Pivote = j;
            }
        }




        // ***************** 4: Actualizar la tabla con sus nuevos valores *****************
        for (i = 0; i <= variables; i++) {
            h[i] = matriz[Fila_Pivote][i];
        }
        for (j = 0; j <= restricciones; j++) {
            v[j] = matriz[j][Col_Pivote];
        }
        for (i = 0; i <= variables; i++) {
            for (j = 0; j <= restricciones; j++) {
                matriz[j][i] -= h[i] * v[j] / h[Col_Pivote];
            }
        }
        for (i = 0; i <= variables; i++) {
            matriz[Fila_Pivote][i] = h[i] / v[Fila_Pivote];
        }
        x[Fila_Pivote] = Col_Pivote;
    } // fin del while





    // ***************** 5: Mostrar la solución óptima *****************
    cout << "\n\n+----------------+\n";
    cout << "Matriz final : "<< "\n";
    cout << "+----------------+\n";
    for (j = 0; j < restricciones; j++) {
        cout << "| x" << x[j] + 1 << " | " << matriz[j][variables] << " | ";
        for (i = 0; i < variables; i++) {
            if (i == Col_Pivote && j == Fila_Pivote) {
                cout << matriz[j][i] << "*"; //selecciono el pivote *
            } else {
                cout << matriz[j][i] << " ";
            }
        }
        cout << "|\n";
    }
    cout << "+----------------+\n";






    //***************** Muestro la ultima iteración *****************
    cout << "| Z | " << matriz[restricciones][variables] << " | ";
    for (i = 0; i < variables; i++) {
        cout << matriz[restricciones][i] << " ";
    }
      cout << "|";
      cout << "\n+----------------+\n\n";

    // ***************** Muestro los valores x1,x2 y z *****************
    cout << "Solucion:\n";  
    for (j = 0; j < restricciones; j++) {
        if (x[j] + 1 != 0) {
            cout << "x" << x[j] + 1 << " = " << matriz[j][variables] << "\n";
            cout << "solucion optima Z: " << matriz[j + 3][variables] << " Cajas \n";
        }
    }


    return 0;
}





