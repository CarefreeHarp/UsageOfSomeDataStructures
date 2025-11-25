#include "componente2.h"
#include <cctype>
#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>
#include <cstring>
#include <bitset>
#include <fstream>



/*FUNCION OPERATOR HECHO CON CHATGPT*/
/*SIRVE PARA LA COMPARACION DE PRIORIDAD EN LA TABLA DE HUFFMAN*/
bool CompararFrecuencia::operator()(const NodoHuffman* a, const NodoHuffman* b) const {
    // Devuelve true si 'a' tiene MAYOR frecuencia que 'b'
    // porque eso hace que 'b' (el más chico) suba al top()
    return a->frecuencia > b->frecuencia;
}

void NodoHuffman::borrarArbol(NodoHuffman* nodo){
    if (nodo != nullptr) {
        borrarArbol(nodo->hijoIzquierdo);
        borrarArbol(nodo->hijoDerecho);
        delete nodo;
    }
}

//esta funcion devuelve el codigo huffman asociado a un caracter enviado como parametro
std::string NodoHuffman::buscarHoja(NodoHuffman* nodoActual, std::string nombreBuscar){
    std::string retorno;
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
    return "F";
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
    if(secuenciasEnMemoria.secuencias.size() == 0){
        std::cout<<std::endl<<"No hay secuencias cargadas, cargue alguna e intente de nuevo"<<std::endl<<std::endl;
        return;
    }
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
        std::string codigoAux = this -> raiz -> buscarHoja(this -> raiz, tablaDeHuffmanDesordenada[i].nombre);
        if(codigoAux == "")
            codigoAux = "0";
        codigosHuffman.push_back(codigoAux);
    }

    for(int i = 0 ; i < caracteresHuffman.size(); i++)
        std::cout<<"Letra: "<<caracteresHuffman[i]<<"\tcodificacion: "<<codigosHuffman[i]<<std::endl;

    /*En cada posicion del vector secuenciasCodificadas, se guarda la cadena de 1s y 0s de cada
    una de las secuencias cargadas en memoria :D */
    std::vector<std::string> secuenciasCodificadas;
    for(int i = 0; i < secuenciasEnMemoria.secuencias.size() ; i++){
        std::string codificacion = "";
        for(int j = 0; j < secuenciasEnMemoria.secuencias[i].contenido.size() ; j++){
            int k = 0;
            while(*(secuenciasEnMemoria.secuencias[i].contenido[j] + k) != '\0'){
                for(int l = 0; l < caracteresHuffman.size();l++){
                    if(std::string(1,*(secuenciasEnMemoria.secuencias[i].contenido[j] + k)) == caracteresHuffman[l]){
                        codificacion += codigosHuffman[l];
                    }
                }
                k++;
            }
        }
        secuenciasCodificadas.push_back(codificacion);
        std::cout<<std::endl<<"SECUENCIA #"<< i+1 <<": "<<codificacion<<" (sin rellenar con 0's)"<<std::endl<<std::endl;
    }




    std::ofstream archivo(nombrefabin, std::ios::binary);
    if (!archivo) {
        std::cout << "El archivo "<<nombrefabin<<" solicitado, no pudo crearse" << std::endl;
        return;
    }

    //escritura de 2 bytes en el archivo indicando la cantidad de bases(letras/caracteres) encontradas
    uint16_t n = static_cast<uint16_t>(tablaDeHuffmanDesordenada.size());
    archivo.write(reinterpret_cast<char*>(&n), sizeof(n));
    if (!archivo) {
        std::cerr << "Error al escribir en el archivo.\n";
        return;
    }

    //escritura de cada símbolo y su frecuencia, 1 y 8 bytes respectivamente
    for (int i = 0; i < tablaDeHuffmanDesordenada.size(); i++) {
        char c = tablaDeHuffmanDesordenada[i].nombre[0];  // un solo char
        uint64_t f = static_cast<uint64_t>(tablaDeHuffmanDesordenada[i].numeroFrecuencia);
        archivo.write(&c, sizeof(c));
        if (!archivo) {
            std::cerr << "Error al escribir en el archivo.\n";
            return;
        }
        archivo.write(reinterpret_cast<char*>(&f), sizeof(f));
        if (!archivo) {
            std::cerr << "Error al escribir en el archivo.\n";
            return;
        }
    }

    //escritura de 4 bytes indicando la cantidad de secuencias
    uint32_t ns = secuenciasEnMemoria.secuencias.size();
    archivo.write(reinterpret_cast<char*>(&ns), sizeof(ns));
    if (!archivo) {
        std::cerr << "Error al escribir en el archivo.\n";
        return;
    }



    //escritura de los nombres de las secuencias
    for (int i = 0; i < secuenciasEnMemoria.secuencias.size(); i++) {
        Secuencia seq = secuenciasEnMemoria.secuencias[i];

        // li es longitud del nombre
        uint16_t li = strlen(seq.nombre);
        archivo.write(reinterpret_cast<char*>(&li), sizeof(li));
        if (!archivo) {
            std::cerr << "Error al escribir en el archivo.\n";
            return;
        }


        //el nombre de la secuencia como tal
        archivo.write(seq.nombre, li);
        if (!archivo) {
            std::cerr << "Error al escribir en el archivo.\n";
            return;
        }

    }

    for (int i = 0; i < secuenciasEnMemoria.secuencias.size(); i++) {
        Secuencia seq = secuenciasEnMemoria.secuencias[i];

        // calcular wi (longitud total real)
        uint64_t wi = 0;
        for (int j = 0; j < seq.contenido.size(); j++) {
            wi += strlen(seq.contenido[j]);
        }
        archivo.write(reinterpret_cast<char*>(&wi), sizeof(wi));
        if (!archivo) {
            std::cerr << "Error al escribir en el archivo.\n";
            return;
        }


        // xi (ancho)
        uint16_t xi = seq.ancho;
        archivo.write(reinterpret_cast<char*>(&xi), sizeof(xi));
        if (!archivo) {
            std::cerr << "Error al escribir en el archivo.\n";
            return;
        }


        // escribir los bits codificados como bytes
        std::string bits = secuenciasCodificadas[i];

        // rellenar hasta múltiplo de 8
        while (bits.size() % 8 != 0)
            bits += '0';

        /*Esta parte se encarga de traducir los 1s y 0s en bytes a bits literales y los escribe en el archivo 
        utilizando la libreria bitset */    
        for (size_t b = 0; b < bits.size(); b += 8) {  //cada iteracion salta de a 8 caracteres

            //substr toma 8 caracteres desde el caracter #b
            //bitset<8> crea conjuntos de 8 bits en este caso
            std::bitset<8> byte(bits.substr(b, 8)); 

            //castea ese bitset en un char (un unico byte)
            unsigned char valor = static_cast<unsigned char>(byte.to_ulong()); 

            //lo escribe en el archivo
            archivo.write(reinterpret_cast<char*>(&valor), 1);
            if (!archivo) {
                std::cerr << "Error al escribir en el archivo.\n";
                return;
            }

        }
    }
    archivo.close();
    std::cout<<std::endl<<std::endl<<" SECUENCIA CODIFICADA CON EXITO EN EL ARCHIVO \" "<<nombrefabin<<" \""<<std::endl;
}




void ArbolDeCodificacionHuffman::descomprimirSececuencias(std::string nombrefabin, ListaSecuencias& secuenciasEnMemoria){
    //se borra el arbol completo ya que estaba guardado en el heap
    //y debemos liberar la memoria antes de crear uno nuevo
    if (this->raiz != nullptr) {
        this->raiz->borrarArbol(this->raiz);
    } 
    
    std::ifstream archivo(nombrefabin, std::ios::binary);
    if (!archivo) {
        std::cout << "No se pueden cargar las secuencias desde "<<nombrefabin << std::endl;
        return;
    }
    //lectura de 2 bytes en el archivo indicando 
    //la cantidad de bases(letras/caracteres) encontradas
    uint16_t n;
    archivo.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (!archivo) {
        std::cerr << "Error al leer del archivo.\n";
        return;
    }
    
    //lectura de cada símbolo y su frecuencia, 1 y 8 bytes respectivamente
    std::vector<elementoTablaDeHuffman> tablaDeHuffmanDesordenada; 
    for (int i = 0; i < n; i++) {
        char c;  // un solo char
        uint64_t f;
        archivo.read(&c, sizeof(c));
            if (!archivo) {
                std::cerr << "Error al leer del archivo.\n";
                return;
            }
        archivo.read(reinterpret_cast<char*>(&f), sizeof(f));
            if (!archivo) {
                std::cerr << "Error al leer del archivo.\n";
                return;
            }
        elementoTablaDeHuffman nuevoElemento;
        nuevoElemento.nombre = std::string(1,c);
        nuevoElemento.numeroFrecuencia = f;
        tablaDeHuffmanDesordenada.push_back(nuevoElemento);
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

    //creacion de la tabla de codigos de huffman para decodificar directamente las secuencias
    //se crea en dos vectores paralelos, uno con los caracteres y otro con los codigos
    std::vector<std::string> codigosHuffman;
    std::vector<std::string> caracteresHuffman;
    for(int i = 0; i < tablaDeHuffmanDesordenada.size(); i++){
        caracteresHuffman.push_back(tablaDeHuffmanDesordenada[i].nombre);
        codigosHuffman.push_back(this -> raiz -> buscarHoja(this -> raiz, tablaDeHuffmanDesordenada[i].nombre));
    }

    for(int i = 0 ; i < caracteresHuffman.size(); i++)
        std::cout<<"Letra: "<<caracteresHuffman[i]<<"\tcodificacion: "<<codigosHuffman[i]<<std::endl;

    //lectura de 4 bytes indicando la cantidad de secuencias
    uint32_t ns;
    archivo.read(reinterpret_cast<char*>(&ns), sizeof(ns));
    if (!archivo) {
        std::cerr << "Error al leer del archivo.\n";
        return;
    }

    for (Secuencia& seqVieja : secuenciasEnMemoria.secuencias) {
        for (char* lineaPtr : seqVieja.contenido) {
            delete[] lineaPtr;  // LIBERAMOS MEMORIA (siempre toca hacerlo)
        }
    }
    secuenciasEnMemoria.secuencias.clear();


    //lectura de los nombres de las secuencias
    for (int i = 0; i < ns; i++) {
        Secuencia seq;

        // li es longitud del nombre
        uint16_t li;
        archivo.read(reinterpret_cast<char*>(&li), sizeof(li));
        if (!archivo) {
            std::cerr << "Error al leer del archivo.\n";
            return;
        }
        
        //el nombre de la secuencia como tal
        archivo.read(seq.nombre, li);
        if (!archivo) {
            std::cerr << "Error al leer del archivo.\n";
            return;
        }
        seq.nombre[li] = '\0'; // Asegurarse de que el nombre esté terminado en null

        secuenciasEnMemoria.secuencias.push_back(seq);
    }
    for (int i = 0; i < ns; i++) {
        Secuencia* seq = &secuenciasEnMemoria.secuencias[i];

        // leer wi (longitud total real)
        uint64_t wi;
        archivo.read(reinterpret_cast<char*>(&wi), sizeof(wi));
        if (!archivo) {
            std::cerr << "Error al leer del archivo.\n";
            return;
        }
        

        // leer xi (ancho)
        uint16_t xi;
        archivo.read(reinterpret_cast<char*>(&xi), sizeof(xi));
        if (!archivo) {
            std::cerr << "Error al leer del archivo.\n";
            return;
        }
        seq->ancho = xi;

        std::string bitsLeidos;   // aquí queda el "binary_code" como string de 0/1
        std::string codigoActual; // aquí acumulamos bits hasta que haces match con un código Huffman
        std::string secuenciaDecodificada; // aquí va la secuencia decodificada completa


        while (secuenciaDecodificada.size() < wi) { //  < wi para saber cuando decodificamos todo sin tener en cuenta los 0 de relleno
            unsigned char byte; //dato de un solo byte
            archivo.read(reinterpret_cast<char*>(&byte), 1); //leemos exactamente 1 byte
            if (!archivo) {
                std::cerr << "Error al leer del archivo.\n";
                return;
            }

            //las siguientes 4 lineas de codigo las hizo CHATGPT, son utilizadas para ir concatenando bit a bit para verificar
            //si es una base nitrogenada valida para decodificar
            for (int b = 7; b >= 0 && secuenciaDecodificada.size() < wi; --b) {
                char bit = ((byte >> b) & 1) ? '1' : '0';
                bitsLeidos.push_back(bit);
                codigoActual.push_back(bit);

                //convertir esos bits a las bases (strings literales)
                for (int k = 0; k < codigosHuffman.size(); ++k) {
                    if (codigoActual == codigosHuffman[k]) {
                        secuenciaDecodificada += caracteresHuffman[k];
                        codigoActual.clear();
                        break;
                    }
                }
            }
        }

        // Divide en líneas de ancho xi y las guarda en secuencias en memoria ya que 
        // la variable seq es un apuntador a las secuencias en memoria
        std::vector<char*> lineas;
        for (size_t pos = 0; pos < secuenciaDecodificada.size(); pos += xi) {
            std::string linea = secuenciaDecodificada.substr(pos, xi);
            char* lineaCStr = new char[linea.size() + 1];
            std::strcpy(lineaCStr, linea.c_str());
            lineas.push_back(lineaCStr);
        }
        seq->contenido = lineas;
    }
    archivo.close();
    std::cout<<std::endl<<std::endl<<"GUARDANDO SECUENCIA DECODIFICADA EN MEMORIA... "<<std::endl;
    std::cout<<"SECUENCIA DECODIFICADA EXITOSAMENTE DESDE EL ARCHIVO \" "<<nombrefabin<<" \""<<std::endl;
}