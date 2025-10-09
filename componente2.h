#ifndef _COMPONENTE2_H_
#define _COMPONENTE2_H

#include <string>

struct NodoHuffman{
    int frecuencia;
    char caracter;

    NodoHuffman* hijoIzquierdo;
    NodoHuffman* hijoDerecho;

    NodoHuffman();
};

struct ArbolDeCodificacionHuffman{
    NodoHuffman* raiz;

    ArbolDeCodificacionHuffman(string mensaje);
};

struct elementoTablaDeHuffman{
    std::string nombre;
    int numeroFrecuencia;
};

/*FUNCION OPERATOR HECHO CON CHATGPT*/
/*SIRVE PARA LA COMPARACION DE PRIORIDAD EN LA TABLA DE HUFFMAN*/
struct CompararFrecuencia {
    bool operator()(const elementoTablaDeHuffman a, const elementoTablaDeHuffman b) const;
}

#endif