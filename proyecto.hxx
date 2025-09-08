#include "proyecto.h"
#include <iostream>
#include <fstream>
void crearComando()
{
    char otro = 'Y';
    while (otro == 'Y' || otro == 'y')
    {
        Comando comando;
        char opcion;
        bool correcto = false;
        std::cout << "bienvenido a la creacion de comandos" << std::endl;
        std::cout << "Digite el nombre del comando" << std::endl;
        std::cin.ignore();
        std::cin.getline(comando.nombre, 50);

        while (correcto == false)
        {
            std::cout << "Tiene argumentos? Y/N: " << std::endl;
            std::cin >> opcion;
            if (opcion == 'y' || opcion == 'Y')
            {
                comando.argumentos = true;
                correcto = true;
            }
            else if (opcion == 'n' || opcion == 'N')
            {
                comando.argumentos = false;
                correcto = true;
            }
            else
            {
                std::cout << "Error, tiene que elegir Y o N" << std::endl;
                correcto = false;
            }
        }
        std::cout << "Ingrese la descripcion, digite '/' para terminar " << std::endl;
        std::cin.getline(comando.descripcion, 1000, '/');
        std::cout << "Ingrese las posibles salidas digite '/' para terminar " << std::endl;
        std::cin.getline(comando.posiblesSalidas, 1000, '/');
        std::fstream archivo("comandos.guda", std::ios::binary | std::ios::out | std::ios::app);

        if (archivo.write((char *)&comando, sizeof(Comando)))
        {
            std::cout << " Guardado exitoso " << std::endl;
        }
        std::cout << "Desea crear otro comando? y/n\t";
        std::cin >> otro;
    }
}

std::vector<std::string> separarComando(std::string entrada)
{
    int i = 0, j = 0;
    std::string aux, comandoSinEspaciosAlInicio;
    bool leyendoEspacios = true, nuevoArgumento = false, hayArgumentosPorLeer = true;
    std::vector<std::string> retorno;
    for (i = 0; i < (int)entrada.size(); i++)
    {
        if (leyendoEspacios == true)
        {
            if (entrada.at(i) != ' ')
            {
                leyendoEspacios = false;
                i--;
            }
        }
        else
        {
            aux += entrada.at(i);
        }
    }
    comandoSinEspaciosAlInicio = aux;
    aux = "";
    leyendoEspacios = true;

    while (comandoSinEspaciosAlInicio.at(j) != ' ')
    {
        aux += comandoSinEspaciosAlInicio.at(j); // aux guarda el comando como tal
        if(j < ((int)comandoSinEspaciosAlInicio.size())-1)
            j++;
        else{
            hayArgumentosPorLeer = false;
            break;
        }
    }
    retorno.push_back(aux);

    if(hayArgumentosPorLeer == false)
        return retorno;

    aux="";
    for (; j < (int)comandoSinEspaciosAlInicio.size(); j++)
    {
        if (leyendoEspacios == true)
        {
            if (comandoSinEspaciosAlInicio.at(j) != ' ')
            { // se salta los espacios que hay entre argumentos
                leyendoEspacios = false;
                j--;
            }
        }
        else
        {
            if (comandoSinEspaciosAlInicio.at(j) != ' ') //guarda los argumentos en un arreglo
            {
                aux += comandoSinEspaciosAlInicio.at(j);
                nuevoArgumento = true;
            }
            else if (nuevoArgumento == true)
            {
                retorno.push_back(aux);
                aux = "";
                nuevoArgumento = false;
                leyendoEspacios = true;
            }
        }
    }
    retorno.push_back(aux);
    return retorno;
}

void escribirComando(std::vector<Comando> ComandosExistentes){
    std::string comando, argumento;
    std::vector<std::string> argumentos;
    while (comando != "salir")
    {
        bool comandoEncontrado = false;
        bool argumentosCorrectos = false;
        std::cout << "\t$";
        getline(std::cin, comando);

        argumentos = separarComando(comando);
        if (argumentos[0] == "ayuda")
        {
            if ((int)argumentos.size() == 1)
            {
                std::cout << "COMANDOS DISPONIBLES" << std::endl;
                for (int i = 0; i < (int)ComandosExistentes.size(); i++)
                {
                    std::cout << "-" << ComandosExistentes[i].nombre << std::endl;
                }
            }
            else if ((int)argumentos.size() == 2)
            {
                for (int i = 0; i < (int)ComandosExistentes.size(); i++)
                {
                    if (ComandosExistentes[i].nombre == argumentos[1])
                    {
                        std::cout << "Ayuda para el comando: " << std::endl
                             << argumentos[1];
                        if (ComandosExistentes[i].argumentos == true)
                            std::cout << " <Argumento Necesario>";
                        std::cout << std::endl << std::endl << std::endl;
                        std::cout << "Descripcion del comando " << argumentos[1] << std::endl;
                        std::cout << ComandosExistentes[i].descripcion << std::endl << std::endl;
                        std::cout << "Salidas posibles del comando " << argumentos[1] << std::endl;
                        std::cout << ComandosExistentes[i].posiblesSalidas;
                        comandoEncontrado = true;
                    }
                }
                if (comandoEncontrado == false)
                {
                    std::cout << "No se encontro el comando " << argumentos[1] << std::endl;
                    comandoEncontrado = true;
                }
            }
        }
        else if (argumentos[0] != "salir")
        {
            for (int i = 0; i < (int)ComandosExistentes.size(); i++)
            {
                if (ComandosExistentes[i].nombre == argumentos[0])
                {
                    comandoEncontrado = true;
                    argumentosCorrectos = true;
                    if (ComandosExistentes[i].argumentos == true && argumentos.size() != 2)
                    {
                        argumentosCorrectos = false;
                    }
                    else if (ComandosExistentes[i].argumentos == false && argumentos.size() != 1)
                    {
                        argumentosCorrectos = false;
                    }
                }
            }
        }

        // Verifica el comando y la cantidad de argumentos escritos
        if (comandoEncontrado == true)
        {
            std::cout << "El comando fue encontrado";
            if (argumentosCorrectos == true)
            {
                std::cout << " y la cantidad de argumentos es correcta" << std::endl;
            }
            else
            {
                std::cout << " pero la cantidad de argumentos es incorrecta" << std::endl;
            }
        }
        else
        {
            std::cout << "El comando no fue encontrado" << std::endl;
        }
    }
}