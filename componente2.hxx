#include "componente2.h"
#include <iostream>
#include <cctype>


/*FUNCION OPERATOR HECHO CON CHATGPT*/
/*SIRVE PARA LA COMPARACION DE PRIORIDAD EN LA TABLA DE HUFFMAN*/
bool CompararFrecuencia::operator()(const elementoTablaDeHuffman& a, const elementoTablaDeHuffman& b) const {
    // Devuelve true si 'a' tiene MAYOR frecuencia que 'b'
    // porque eso hace que 'b' (el más chico) suba al top()
    return a.frecuencia > b.frecuencia;
}

NodoHuffman::NodoHuffman(int valorFrecuencia, NodoHuffman* hijoDerecho, NodoHuffman* hijoIzquierdo) : frecuencia(valorFrecuencia), hijoIzquierdo(hijoIzquierdo), hijoDerecho(hijoDerecho) {
    char respuesta;
    std::cout<<"El nodo es hoja?";
    std::cin>>respuesta;
    if(tolower(respuesta)== 'Y'){
        std::cout<<"Cual es el caracter de la hoja?";
        std::cin>>this -> caracter;
    }

}

ArbolDeCodificacionHuffman::ArbolDeCodificacionHuffman(string mensaje){

}

