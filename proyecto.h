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

struct Codigos{
    std::vector<char> codigo;
    std::vector<char[10]> significado;
};

struct Secuencia{
    char nombre[50];
    std::vector<char*> contenido;
    int ancho;


    };

struct ListaSecuencias{
    std::vector<Secuencia> secuencias;

    void cargar(char nombre[]);
    void listarSecuencia();
    void histograma(char nombre[]);
    void esSubsecuencia(char subsecuencia[]);
    void enmascarar(char subsecuencia[]);
    void guardar(char nombreArchivo[]);
};

void crearComando();
std::vector<std::string> separarComando(std::string entrada);
void escribirComando(std::vector<Comando> ComandosExistentes);


#endif
