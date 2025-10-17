#include "componente1.hxx"
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    vector<Comando> ComandosExistentes;
    Comando aux;
    fstream ArchivoComandos("comandos.guda", std::ios::binary | std::ios::in | std::ios::out);
    while (ArchivoComandos.read((char *)&aux, sizeof(Comando))) //carga los comandos del archivo comandos.guda
    {
        ComandosExistentes.push_back(aux);
    }
    escribirComandos(ComandosExistentes);
    return 0;
}