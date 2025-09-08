#ifndef __PROYECTO_H__
#define __PROYECTO_H__

#include <string>
#include <vector>

struct Comando{
    char nombre[50];
    bool argumentos = false;
    char argumento[50];
    char descripcion[1000];
    char posiblesSalidas[1000];

    
};


void crearComando();
std::vector<std::string> separarComando(std::string entrada);
void escribirComando(std::vector<Comando> ComandosExistentes);


#endif
