#ifndef __COMPONENTE1_H__
#define __COMPONENTE1_H__

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
    std::vector<char*> significado;
    std::vector<char*> aux;

    void cargar();
};

struct Secuencia{
    char nombre[50];
    std::vector<char*> contenido;
    int ancho;
};

struct ListaSecuencias{
    std::vector<Secuencia> secuencias;

    void cargar(const char nombre[]);
    void listarSecuencia();
    void histograma(const char nombre[]);
    void esSubsecuencia(const char subsecuencia[]);
    void enmascarar(const char subsecuencia[]);
    void guardar(const char nombreArchivo[]);
};

void crearComando();
std::vector<std::string> separarComando(std::string entrada);
void escribirComandos(std::vector<Comando> ComandosExistentes);


#endif
