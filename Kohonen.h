
#ifndef __KOHONEN_H__
#define __KOHONEN_H__
#include "Neurona_Koh.h"
#include <math.h>
class Kohonen
{
private:
    double *entradas;
    Neurona_Koh **neuronas;
    double ***pesos;
    int s_entradas;
    int filas;
    int columnas;
    double Vecindad(double, double);
    double Distancia(double*,double*);
    void BusquedaBMU(double*, double &, double*);
public:
    Kohonen(int, int, int);
    void Entrenar(double**, int, int);
    void Imprimir();
    ~Kohonen();
};

Kohonen::Kohonen(int s_e, int fl, int cl)
{
    filas = fl;
    columnas = cl;
    s_entradas = s_e;
    entradas = new double[s_entradas];
    neuronas = new Neurona_Koh*[filas];
    pesos = new double**[filas];
    for (int f = 0; f < filas; f++){
        pesos[f] = new double*[columnas];
        neuronas[f] = new Neurona_Koh[columnas];
        for (int c = 0; c < columnas; c++){
            pesos[f][c] = neuronas[f][c].Iniciar(s_entradas, f, c);
        }
    }
}
double Kohonen::Vecindad(double dist, double radio){
    //FUNCION GAUSSEANA
    return pow(2.71828,(dist*dist)/(-2 * radio * radio));
}
double Kohonen::Distancia(double* A, double* B){
    double sum = 0;
    for (int e = 0; e < s_entradas; e++){
        sum += ((A[e] - B[e]) * (A[e] - B[e]));
    }
    return pow(sum, 0.5);
}
void Kohonen::BusquedaBMU(double * BMU, double & r_activacion,double* X){
    r_activacion = -1;
    for (int f = 0; f < filas; f++){
        for (int c = 0; c < columnas; c++){
            double dist = Distancia(X, pesos[f][c]);
            if(r_activacion == -1){
                r_activacion = dist;
                BMU[0] = f;
                BMU[1] = c;
            }else{
                if(dist < r_activacion){
                    r_activacion = dist;
                    BMU[0] = f;
                    BMU[1] = c;
                }
            }
        }
    }
}
void Kohonen::Entrenar(double ** X_entr, int s_X, int max_epocas){
    double * BMU = new double[2];
    double r_activacion, radio, dist_BMU, t_a, h_gn;
    int tiempo;
    t_a = 0.2;
    radio = 2.0;
    tiempo = 0;
    for (; tiempo < max_epocas; tiempo++){
        t_a -= tiempo * 0.01;
        radio -= tiempo * 0.10;
        if(t_a == 0 || radio == 0){
            break;
        }
        for (int i = 0; i < s_X; i++){
            //BUSCAR NEURONA GANADORA
            BusquedaBMU(BMU, r_activacion, X_entr[i]);
            std::cout<<"Ganador: |"<<BMU[0]<<"|"<<BMU[1]<<"|\n";
            //ADAPTAR PESOS
            for (int f = 0; f < filas; f++){
                for (int c = 0; c < columnas; c++){
                    dist_BMU = Distancia(neuronas[f][c].Ubicacion(), BMU);
                    if(dist_BMU <= radio){
                        h_gn = Vecindad(dist_BMU,radio);
                        for (int e = 0; e < s_entradas; e++){
                            pesos[f][c][e] += (t_a * h_gn * (X_entr[i][e] - pesos[f][c][e]));
                        }
                    }
                }
            }
        }
    }
}
void Kohonen::Imprimir(){
    double *tmp;
    for (int f = 0; f < filas; f++){
        for (int c = 0; c < columnas; c++){
            std::cout<<"---------------------------------------------\n";
            std::cout<<"Neurona |"<<f<<"|"<<c<<"|\n";
            tmp = neuronas[f][c].Ubicacion();
            std::cout<<"["<<tmp[0]<<", "<<tmp[1]<<"]\n";
            std::cout<<"["<<pesos[f][c][0];
            for (int e = 1; e < s_entradas; e++){
                std::cout<<", "<<pesos[f][c][e];
            }
            std::cout<<"]\n";
        }
    }
}
Kohonen::~Kohonen()
{
}

#endif
