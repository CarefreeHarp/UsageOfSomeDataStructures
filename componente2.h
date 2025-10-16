#ifndef _COMPONENTE2_H_
#define _COMPONENTE2_H

#include <string>

struct NodoHuffman{
    int frecuencia;
    std::string nombre;

    NodoHuffman* hijoIzquierdo;
    NodoHuffman* hijoDerecho;

    NodoHuffman(std::string nombre, int valorFrecuencia, NodoHuffman* hijoDerecho, NodoHuffman* hijoIzquierdo);
    std::string buscarHoja(NodoHuffman* nodoActual, std::string nombreBuscar);
    void borrarArbol(NodoHuffman* nodo);

};

struct ArbolDeCodificacionHuffman{
    NodoHuffman* raiz;

    void comprimirSecuencias(std::string nombrefabin, ListaSecuencias secuenciasEnMemoria);
    void descomprimirSececuencias(std::string nombrefabin, ListaSecuencias& secuenciasEnMemoria); 
};

struct elementoTablaDeHuffman{
    std::string nombre;
    int numeroFrecuencia;
};

/*FUNCION OPERATOR HECHO CON CHATGPT*/
/*SIRVE PARA LA COMPARACION DE PRIORIDAD EN LA TABLA DE HUFFMAN*/
struct CompararFrecuencia {
    bool operator()(const NodoHuffman* a, const NodoHuffman* b) const;
};

#endif