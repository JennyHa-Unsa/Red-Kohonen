#ifndef __NEURONA_KOH_H__
#define __NEURONA_KOH_H__
#include <random>
class Neurona_Koh
{
private:
    double* coordenadas;
    double* pesos;
    int s_pesos;
    double salida;
public:
    Neurona_Koh();
    double* Iniciar(int, int, int);
    double Activacion(double*);
    double Preactivacion(double*);
    double Funcion(double);
    double* Ubicacion();
    ~Neurona_Koh();
};
Neurona_Koh::Neurona_Koh(){
    coordenadas = nullptr;
    pesos = nullptr;
    s_pesos = 0;
    salida = 0;
}
double* Neurona_Koh::Iniciar(int s_p, int x, int y)
{
    coordenadas = new double[2];
    coordenadas[0] = x;
    coordenadas[1] = y;
    pesos = new double[s_p];
    s_pesos = s_p;
    for (int i = 0; i < s_pesos; i++){
        pesos[i] = double((1 + std::rand()) % 100)/100.0;
    }
    return pesos;
}
double Neurona_Koh::Activacion(double* entrada){
    return Funcion(Preactivacion(entrada));
}
double Neurona_Koh::Preactivacion(double* entrada){
    double sum = 0;
    for (int i = 0; i < s_pesos; i++){
        sum += (entrada[i] * pesos[i]);
    }
    return sum;
}
double Neurona_Koh::Funcion(double Z){
    if(Z > 0){
        return Z;
    }else{
        return 0;
    }
}
double* Neurona_Koh::Ubicacion(){
    return coordenadas;
}
Neurona_Koh::~Neurona_Koh()
{
}
#endif