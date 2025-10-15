#include "componente2.h"
#include <cctype>
#include <iostream>

/*FUNCION OPERATOR HECHO CON CHATGPT*/
/*SIRVE PARA LA COMPARACION DE PRIORIDAD EN LA TABLA DE HUFFMAN*/
bool CompararFrecuencia::operator()(const elementoTablaDeHuffman a, const elementoTablaDeHuffman b) const {
    // Devuelve true si 'a' tiene MAYOR frecuencia que 'b'
    // porque eso hace que 'b' (el más chico) suba al top()
    return a.numeroFrecuencia > b.numeroFrecuencia;
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

ArbolDeCodificacionHuffman::ArbolDeCodificacionHuffman(std::string mensaje, ListaSecuencias secuenciasEnMemoria){
    
}

