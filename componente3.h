#ifndef _COMPONENTE3_H_
#define _COMPONENTE3_H_
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include "componente1.h"

struct Nodo {
    char valor;
    std::vector<Nodo*> vecinos; // Arriba, Derecha, Abajo, Izquierda

    Nodo(char valor);
};

struct Grafo{
    std::vector<Nodo*> nodos;
    int anchuraLineas;
    char nombre[50];
};

struct SistemaDeGrafos{
    std::vector<Grafo> grafos;

    void CargarSistemaDeGrafos(ListaSecuencias SecuenciasEnMemoria);
    void ruta_mas_corta(std::string nombreSecuencia, int i,int j,int x,int y);
    void base_remota(std::string nombreSecuencia, int i, int j);
};

#endif