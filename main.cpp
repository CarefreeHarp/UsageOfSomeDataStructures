#include "proyecto.hxx"
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    vector<Comando> ComandosExistentes;
    Comando a;
    fstream ArchivoComandos("comandos.guda", std::ios::binary | std::ios::in | std::ios::out);

    while (ArchivoComandos.read((char *)&a, sizeof(Comando)))
    {
        ComandosExistentes.push_back(a);
    }
    escribirComando(ComandosExistentes);
    return 0;
}