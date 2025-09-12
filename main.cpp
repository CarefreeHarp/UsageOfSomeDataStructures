#include "proyecto.hxx"
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    vector<Comando> ComandosExistentes;
    Comando a;
    fstream ArchivoComandos("comandos.guda", std::ios::binary | std::ios::in | std::ios::out);
    ListaSecuencias hola;
    char histograma[] = "Full_SEQUENCE";
    Codigos jijija;
    char archivo[] = "archivo.fa";
    char subsecuencia[] = "GUILLERMOESGAY";
    jijija.cargar();
    hola.cargar(archivo);
    //hola.listarSecuencia();
    //hola.histograma(histograma);
    //hola.esSubsecuencia(subsecuencia);
    while (ArchivoComandos.read((char *)&a, sizeof(Comando)))
    {
        ComandosExistentes.push_back(a);
    }
    escribirComando(ComandosExistentes);
    return 0;
}