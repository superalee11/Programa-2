#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void leermatriz(int n, double matriz[n][n], double vector[n]) {
    printf("Introduce los coeficientes de la matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            if (scanf("%lf", &matriz[i][j]) != 1) {
                printf("Entrada inválida.\n");
                exit(1);
            }
        }
        printf("Introduce el valor del vector independiente en [%d]: ", i + 1);
        if (scanf("%lf", &vector[i]) != 1) {
            printf("Entrada invalida.\n");
            exit(1);
        }
    }
}

void mostrarmatriz(int n, double matriz[n][n], double vector[n]) {
    printf("\nMatriz:\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%8.3lf ", matriz[i][j]);
        }
        //mostrarvector
        printf("| %8.3lf\n", vector[i]);
    }
}

void corregircoeficiente(int n, double matriz[n][n], double vector[n]) {
    int fila, columna;
    printf("Fila a corregir [i]: ");
    scanf("%d", &fila);
    printf("Columna a corregir [j] (o 0 para el vector independiente): ");
    scanf("%d", &columna);

    if(columna==0){
        printf("Introduce el nuevo valor del vector independiente en [%d]: ", fila);
        scanf("%lf", &vector[fila-1]);
    } else {
        printf("Ingresar el nuevo valor para [%d][%d]: ", fila, columna);
        scanf("%lf", &matriz[fila-1][columna-1]);
    }
}

int DD(int n, double matriz[n][n]) {
    for (int i=0; i<n; i++) {
        double suma=0;
        for (int j=0; j<n; j++) {
            if (i != j){
                suma += fabs(matriz[i][j]);
            }
        }
        if(fabs(matriz[i][i])<suma){
            return 0;
        }
    }
    return 1;
}

double determinante(int n, double matriz[n][n]){
    double copiamatriz[n][n];
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            copiamatriz[i][j]=matriz[i][j];
        }
    }

    double det=1;
    for(int i=0; i<n; i++) {
        for(int k=i+1; k<n; k++) {
            if(copiamatriz[i][i]==0)return 0; //si el pivote es cero, determinante=0
            double factor=copiamatriz[k][i]/copiamatriz[i][i];
            for(int j=i; j<n; j++){
                copiamatriz[k][j]-=factor*copiamatriz[i][j];
            }
        }
        det*=copiamatriz[i][i];
    }
    return det;
}

void resolver(int n, double matriz[n][n], double vector[n]) {
    double soluciones[n];
    
    for (int i=n-1; i>=0; i--) {
        soluciones[i]=vector[i];
        for (int j=i+1; j<n; j++) {
            soluciones[i]-=matriz[i][j]*soluciones[j];
        }
        soluciones[i]/=matriz[i][i];
    }
    
    printf("\nSolucion del sistema:\n");
    for (int i=0; i<n; i++) {
        printf("x[%d]=%lf\n", i+1, soluciones[i]);
    }
}

int main(){
    int n, corregir;

    printf("Dimension de la matriz cuadrada: ");
    scanf("%d", &n);

    double matriz[n][n], vector[n];

    leermatriz(n, matriz, vector);

    do {
        mostrarmatriz(n, matriz, vector);
        printf("\nEs correcta la matriz? ([SI=1], [NO=0]): ");
        scanf("%d", &corregir);

        if(!corregir){
            corregircoeficiente(n, matriz, vector);
        }
    }while(!corregir);

    
    int dominante=DD(n, matriz);
    if(dominante){
        printf("\nLa matriz es DD\n");
    }else{
        printf("\nLa matriz NO es diagonalmente dominante\n");
        
        double det=determinante(n, matriz);
        
        if(det!=0){
            printf("El determinante es: %lf\n", det);
            resolver(n, matriz, vector);
        }else{
        printf("El determinante es 0. Por lo tanto el sistema no tiene solucion\n");
        }
    }

    return 0;
}
