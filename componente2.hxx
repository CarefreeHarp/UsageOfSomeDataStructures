#include "componente2.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>


/*FUNCION OPERATOR HECHO CON CHATGPT*/
/*SIRVE PARA LA COMPARACION DE PRIORIDAD EN LA TABLA DE HUFFMAN*/
bool CompararFrecuencia::operator()(const NodoHuffman* a, const NodoHuffman* b) const {
    // Devuelve true si 'a' tiene MAYOR frecuencia que 'b'
    // porque eso hace que 'b' (el más chico) suba al top()
    return a->frecuencia > b->frecuencia;
}

//esta funcion devuelve el codigo huffman asociado a un caracter enviado como parametro
std::string NodoHuffman::buscarHoja(NodoHuffman* nodoActual, std::string nombreBuscar){
    string retorno;
    if(nodoActual -> nombre.length() == 1){
        if(nodoActual -> nombre == nombreBuscar){
            return "";
        }
        return "F";
    } else {
        if(nodoActual -> hijoIzquierdo != nullptr){
            retorno = "0" + buscarHoja(nodoActual -> hijoIzquierdo, nombreBuscar);
            if(retorno.at(retorno.length() - 1) != 'F'){
                return retorno;
            }
        } 
        if(nodoActual -> hijoDerecho != nullptr){
            retorno = "1" + buscarHoja(nodoActual -> hijoDerecho, nombreBuscar);
            if(retorno.at(retorno.length() - 1) != 'F'){
                return retorno;
            }
        }
    }
}

NodoHuffman::NodoHuffman(std::string valorNombre, int valorFrecuencia, NodoHuffman* hijoDerecho, NodoHuffman* hijoIzquierdo) : nombre (valorNombre), frecuencia(valorFrecuencia), hijoIzquierdo(hijoIzquierdo), hijoDerecho(hijoDerecho) {}


//Para seguir la estructura de alrchivo .fabin requerida por el proyecto,
//se utilizó chatGPT para ingresar los datos en el archivo binario .fabin
//ya que la escritura en el archivo binario debe hacerse byte a byte
//y no se puede hacer escribiendo la estructura completa de la secuencia.
//Por lo anterior, y dado que el tema no lo hemos visto en clase
//utilizamos chatGPT para escribir en el archivo binario utilizando tipos de datos 
//estándar como uint8_t, uint32_t y uint64_t
void ArbolDeCodificacionHuffman::comprimirSecuencias(std::string nombrefabin, ListaSecuencias secuenciasEnMemoria){
    std::vector<elementoTablaDeHuffman> tablaDeHuffmanDesordenada; 
    bool encontrado;
    for(int i = 0; i < secuenciasEnMemoria.secuencias.size(); i++){
        for(int j = 0; j < secuenciasEnMemoria.secuencias[i].contenido.size(); j++){
            int l = 0;
            while(*(secuenciasEnMemoria.secuencias[i].contenido[j] + l) != '\0'){
                encontrado = false;
                for(int k = 0; k < tablaDeHuffmanDesordenada.size(); k++){
                    if (tablaDeHuffmanDesordenada[k].nombre == std::string(1,*(secuenciasEnMemoria.secuencias[i].contenido[j] + l))){
                        tablaDeHuffmanDesordenada[k].numeroFrecuencia++;
                        encontrado = true;
                    }
                }
                if (encontrado == false){
                    elementoTablaDeHuffman nuevoElemento;
                    nuevoElemento.nombre = std::string(1,*(secuenciasEnMemoria.secuencias[i].contenido[j] + l));
                    nuevoElemento.numeroFrecuencia = 1;
                    tablaDeHuffmanDesordenada.push_back(nuevoElemento);
                }
                l++;
            }
        }
    }

    //creacion de la tabla de huffman ordenada
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, CompararFrecuencia> tablaDeHuffmanOrdenada;
    for(int i = 0; i < tablaDeHuffmanDesordenada.size(); i++){
        tablaDeHuffmanOrdenada.push(new NodoHuffman(tablaDeHuffmanDesordenada[i].nombre, tablaDeHuffmanDesordenada[i].numeroFrecuencia, nullptr, nullptr));
    }

    //creacion del arbol de huffman
    while(tablaDeHuffmanOrdenada.size() > 1){
        NodoHuffman* hijoDerecho = tablaDeHuffmanOrdenada.top();
        tablaDeHuffmanOrdenada.pop();
        NodoHuffman* hijoIzquierdo = tablaDeHuffmanOrdenada.top();
        tablaDeHuffmanOrdenada.pop();
        

        NodoHuffman* padre = new NodoHuffman("Padre de ( " + hijoIzquierdo->nombre + " & " + hijoDerecho->nombre + " )" , hijoDerecho->frecuencia + hijoIzquierdo->frecuencia, hijoDerecho, hijoIzquierdo);
        tablaDeHuffmanOrdenada.push(padre);
    }
    this -> raiz = tablaDeHuffmanOrdenada.top();


    //creacion de la tabla de codigos de huffman para codificar directamente las secuencias
    //se crea en dos vectores paralelos, uno con los caracteres y otro con los codigos
    std::vector<std::string> codigosHuffman;
    std::vector<std::string> caracteresHuffman;
    for(int i = 0; i < tablaDeHuffmanDesordenada.size(); i++){
        caracteresHuffman.push_back(tablaDeHuffmanDesordenada[i].nombre);
        codigosHuffman.push_back(this -> raiz -> buscarHoja(this -> raiz, tablaDeHuffmanDesordenada[i].nombre));
    }




    /* YA SOLO FALTA CODIFICAR CADA SECUENCIA EN BASE A ESOS DOS ARREGLOS PARALELOS AHHHH*/









    std::ofstream archivo(nombrefabin, std::ios::binary);
    if (!archivo) {
        std::cerr << "El archivo fabin no fue creado correctamente" << std::endl;
        return;
    }

    //escritura de 2 bytes en el archivo indicando la cantidad de bases(letras/caracteres) encontradas
    uint16_t n = static_cast<uint16_t>(tablaDeHuffmanDesordenada.size());
    archivo.write(reinterpret_cast<char*>(&n), sizeof(n));

    //escritura de cada símbolo y su frecuencia, 1 y 8 bytes respectivamente
    for (int i = 0; i < tablaDeHuffmanDesordenada.size(); i++) {
        char c = tablaDeHuffmanDesordenada[i].nombre[0];  // un solo char
        uint64_t f = static_cast<uint64_t>(tablaDeHuffmanDesordenada[i].numeroFrecuencia);
        archivo.write(&c, sizeof(c));
        archivo.write(reinterpret_cast<char*>(&f), sizeof(f));
    }

    //escritura de 4 bytes indicando la cantidad de secuencias
    uint32_t ns = secuenciasEnMemoria.secuencias.size();
    archivo.write(reinterpret_cast<char*>(&ns), sizeof(ns));


    //escritura de las secuencias
    for (int i = 0; i < secuenciasEnMemoria.secuencias.size(); i++) {
        Secuencia seq = secuenciasEnMemoria.secuencias[i];

        // li es longitud del nombre
        uint16_t li = strlen(seq.nombre);
        archivo.write(reinterpret_cast<char*>(&li), sizeof(li));

        //el nombre de la secuencia como tal
        archivo.write(seq.nombre, li);
    }




}