#include "componente1.h"
#include <cstring>
#include <fstream>
#include "componente2.hxx"
#include <string>
void crearComando() {
  char otro = 'Y';
  while (otro == 'Y' || otro == 'y') {
    Comando comando;
    char opcion;
    bool correcto = false;
    std::cout << "bienvenido a la creacion de comandos" << std::endl;
    std::cout << "Digite el nombre del comando" << std::endl;
    std::cin.getline(comando.nombre, 50);

    while (correcto == false) {
      std::cout << "Tiene argumentos? Y/N: " << std::endl;
      std::cin >> opcion;
      if (opcion == 'y' || opcion == 'Y') {
        comando.argumentos = true;
        correcto = true;
      } else if (opcion == 'n' || opcion == 'N') {
        comando.argumentos = false;
        correcto = true;
      } else {
        std::cout << "Error, tiene que elegir Y o N" << std::endl;
        correcto = false;
      }
    }
    std::cout << "Ingrese la descripcion, digite '/' para terminar " << std::endl;
    std::cin.getline(comando.descripcion, 1000, '/');
    std::cout << "Ingrese las posibles salidas digite '/' para terminar " << std::endl;
    std::cin.getline(comando.posiblesSalidas, 1000, '/');
    std::fstream archivo("comandos.guda", std::ios::binary | std::ios::out | std::ios::app);

    if (archivo.write((char *)&comando, sizeof(Comando))) {
      std::cout << " Guardado exitoso " << std::endl;
    }
    std::cout << "Desea crear otro comando? y/n\t";
    std::cin >> otro;
    std::cin.ignore();
  }
}

void Codigos::cargar() {
  std::ifstream cargar("codigos.txt");
  char linea[50];
  if (!cargar) {
    std::cout << "El archivo no fue cargado correctamente";
    return;
  }
  while (cargar.getline(linea, 50)) {
    char *cadena = new char[strlen(linea) + 1];
    strcpy(cadena, linea);
    codigo.push_back(*(cadena));
    significado.push_back(cadena + 2);
    aux.push_back(cadena);
  }
  std::cout << "El archivo fue cargado correctamente" << std::endl;
}

void ListaSecuencias::cargar(const char *nombre) {
  bool primeraVez = true;
  Secuencia aux;
  strcpy(aux.nombre, "");
  char cadena[1000];
  int contador = 0;
  std::ifstream cargar(nombre);
  if (!cargar) {
     std::cout << nombre << " no se encuentra o no puede leerse." << std::endl;;
    return;
  }
  if (cargar.peek() == std::ifstream::traits_type::eof()) {
    std::cout << nombre << " no contiene ninguna secuencia" << std::endl;
    return;
  } 
  while (cargar.getline(cadena, 1000)) {
    if (cadena[0] == '>') {
      contador++;
      if (strcmp(aux.nombre, "") != 0) {
        secuencias.push_back(aux);
      }
      strcpy(aux.nombre, cadena + 1);
      aux.contenido.clear();
      primeraVez = true;
    } else {
      char *linea = new char[strlen(cadena) + 1];
      strcpy(linea, cadena);

      // guardar la copia en el vector
      aux.contenido.push_back(linea);
      if (primeraVez == true) {
        aux.ancho = (int)strlen(cadena);
        primeraVez = false;
      }
    }
  }
  secuencias.push_back(aux);
  std::cout << contador << " secuencias cargadas correctamente desde " << nombre << std::endl;
  cargar.close();
}

void ListaSecuencias::listarSecuencia() {
  bool completa = true;
  int cantidadBases = 0;
  std::cout << "Hay " << secuencias.size() << " cargadas en memoria: " << std::endl;
  if(secuencias.size() == 0){
    std::cout << "No hay secuencias cargadas en memoria." << std::endl;
    }
    else{
  for (int i = 0; i < secuencias.size(); i++) {
    completa = true;
    cantidadBases = 0;
    std::cout << "Secuencia " << secuencias[i].nombre;
    for (int j = 0; j < secuencias[i].contenido.size(); j++) {
      int k = 0;
      while (*(secuencias[i].contenido[j] + k) != '\0') {
        if (*(secuencias[i].contenido[j] + k) != '-') {
          cantidadBases++;
        } else {
          completa = false;
        }
        k++;
      }
    }
    if (completa == true) {
      std::cout << " contiene " << cantidadBases << " bases" << std::endl;
    } else {
      std::cout << " contiene al menos " << cantidadBases << " bases" << std::endl;
    }
   }
  }
  
}

void ListaSecuencias::histograma(const char nombre[]) {
  bool encontrado = false;
  int posicion;
  std::vector<int> cantidadCodigos;
  char simbolos[18] = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
  for (int l = 0; l < 18; l++) {
    cantidadCodigos.push_back(0);
  }
  for (int i = 0; i < secuencias.size(); i++) {
    if (strcmp(secuencias[i].nombre, nombre) == 0) {
      encontrado = true;
      posicion = i;
    }
  }
  if (encontrado == true) {
    for (int j = 0; j < secuencias[posicion].contenido.size(); j++) {
      int k = 0;
      std::cout << "Linea " << j + 1 << std::endl;
      while (*(secuencias[posicion].contenido[j] + k) != '\0') {
        for (int m = 0; m < 18; m++) {
          if (*(secuencias[posicion].contenido[j] + k) == simbolos[m]) {
            cantidadCodigos[m]++;
          }
        }
        k++;
      }
      for (int n = 0; n < 18; n++) {
        std::cout << simbolos[n] << ": " << cantidadCodigos[n] << "\t";
        cantidadCodigos[n] = 0;
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "Secuencia invalida " <<std::endl;
  }
}
void ListaSecuencias::esSubsecuencia(const char subsecuencia[]) {
  char *ptr;
  int contador = 0;
  if (secuencias.size() != 0) {
    for (int i = 0; i < secuencias.size(); i++) {
      for (int j = 0; j < secuencias[i].contenido.size(); j++) {
        ptr = strstr(secuencias[i].contenido[j], subsecuencia);
        while (ptr != nullptr) {
          ptr = strstr(ptr, subsecuencia);
          if (ptr != nullptr) {
            contador++;
            ptr++;
          }
        }
      }
    }
    if (contador == 0) {
      std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria" << std::endl;
    } else {
      std::cout << "La subsecuencia dada se repite " << contador << " veces dentro de las secuencias cargadas en memoria" << std::endl;
    }
  } else {
    std::cout << "No hay secuencias cargadas en memoria" << std::endl;
    return;
  }
}

void ListaSecuencias::enmascarar(const char subsecuencia[]) {
  char *ptr;
  int largoSubsecuencia = strlen(subsecuencia);
  int contador = 0;
  if (secuencias.size() != 0) {
    for (int i = 0; i < secuencias.size(); i++) {
      for (int j = 0; j < secuencias[i].contenido.size(); j++) {
        ptr = strstr(secuencias[i].contenido[j], subsecuencia);
        while (ptr != nullptr) {
          ptr = strstr(ptr, subsecuencia);
          if (ptr != nullptr) {
            for (int k = 0; k < largoSubsecuencia; k++) {
              ptr[k] = 'X';
            }
            contador++;
            ptr++;
          }
        }
      }
    }
  } else {
    std::cout << "No hay secuencias cargadas en memoria" << std::endl;
    return;
  }
  if (contador == 0) {
    std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada." << std::endl;
  } else {
    std::cout << contador << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria." << std::endl;
  }
}

void ListaSecuencias::guardar(const char nombreArchivo[]) {
  std::ofstream guardar(nombreArchivo);
  if (secuencias.size() == 0) {
    std::cout << "No hay secuencias cargadas en memoria." << std::endl;
    guardar.close();
    return;
  }
  if (!guardar.is_open()) {
    std::cout << "Error guardando en " << nombreArchivo << std::endl;
    return;
  }
  for (int i = 0; i < secuencias.size(); i++) {
    guardar << ">" << secuencias[i].nombre << "\n";
    for (int j = 0; j < secuencias[i].contenido.size(); j++) {
      guardar << secuencias[i].contenido[j] << "\n";
    }
  }

  guardar.close();
  std::cout << "Las secuencias han sido guardadas en " << nombreArchivo << std::endl;
}

std::vector<std::string> separarComando(std::string entrada) {
  int i = 0, j = 0;
  std::string aux, comandoSinEspaciosAlInicio;
  bool leyendoEspacios = true, nuevoArgumento = false, hayArgumentosPorLeer = true;
  std::vector<std::string> retorno;
  for (i = 0; i < (int)entrada.size(); i++) {
    if (leyendoEspacios == true) {
      if (entrada.at(i) != ' ') {
        leyendoEspacios = false;
        i--;
      }
    } else {
      aux += entrada.at(i);
    }
  }
  comandoSinEspaciosAlInicio = aux;
  aux = "";
  leyendoEspacios = true;

  while (comandoSinEspaciosAlInicio.at(j) != ' ') {
    aux += comandoSinEspaciosAlInicio.at(j); // aux guarda el comando como tal
    if (j < ((int)comandoSinEspaciosAlInicio.size()) - 1)
      j++;
    else {
      hayArgumentosPorLeer = false;
      break;
    }
  }
  retorno.push_back(aux);

  if (hayArgumentosPorLeer == false)
    return retorno;

  aux = "";
  for (; j < (int)comandoSinEspaciosAlInicio.size(); j++) {
    if (leyendoEspacios == true) {
      if (comandoSinEspaciosAlInicio.at(j) != ' ') { // se salta los espacios que hay entre argumentos
        leyendoEspacios = false;
        j--;
      }
    } else {
      if (comandoSinEspaciosAlInicio.at(j) != ' ') // guarda los argumentos en un arreglo
      {
        aux += comandoSinEspaciosAlInicio.at(j);
        nuevoArgumento = true;
      } else if (nuevoArgumento == true) {
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

void escribirComandos(std::vector<Comando> ComandosExistentes) {
  std::string comando, argumento;
  std::vector<std::string> argumentos;
  ListaSecuencias secuenciasEnMemoria;
  while (comando != "salir") {
    bool comandoEncontrado = false;
    bool argumentosCorrectos = false;
    std::cout << "\t$";
    getline(std::cin, comando);

    argumentos = separarComando(comando);
    if (argumentos[0] == "ayuda") {
      if ((int)argumentos.size() == 1 || ((int)argumentos.size() == 2 && argumentos[1] == "")) {
        std::cout << "COMANDOS DISPONIBLES" << std::endl;
        for (int i = 0; i < (int)ComandosExistentes.size(); i++) {
          std::cout << "-" << ComandosExistentes[i].nombre << std::endl;
        }
      } else if ((int)argumentos.size() == 2) {
        for (int i = 0; i < (int)ComandosExistentes.size(); i++) {
          if (ComandosExistentes[i].nombre == argumentos[1]) {
            std::cout << "Ayuda para el comando: " << std::endl
                      << argumentos[1];
            if (ComandosExistentes[i].argumentos == true)
              std::cout << " <Argumento Necesario>";
            std::cout << std::endl
                      << std::endl
                      << std::endl;
            std::cout << "Descripcion del comando " << argumentos[1] << std::endl;
            std::cout << ComandosExistentes[i].descripcion << std::endl
                      << std::endl;
            std::cout << "Salidas posibles del comando " << argumentos[1] << std::endl;
            std::cout << ComandosExistentes[i].posiblesSalidas;
            comandoEncontrado = true;
          }
        }
      }
      if (comandoEncontrado == false) {
        std::cout << "No se encontro ayuda para el comando \" ";
        for (int i = 1; i < argumentos.size(); i++)
          std::cout << argumentos[i];
        std::cout << " \"" << std::endl;
        comandoEncontrado = true;
      }

    } else if (argumentos[0] != "salir") {
      for (int i = 0; i < (int)ComandosExistentes.size(); i++) {
        if (ComandosExistentes[i].nombre == argumentos[0]) {
          comandoEncontrado = true;
          argumentosCorrectos = true;
          if (ComandosExistentes[i].argumentos == true && argumentos.size() != 2) {
            argumentosCorrectos = false;
          } else if (ComandosExistentes[i].argumentos == false && argumentos.size() != 1) {
            argumentosCorrectos = false;
          }
        }
      }
    }

    // Verifica el comando y la cantidad de argumentos escritos
    if (comandoEncontrado == true && argumentos[0] != "ayuda") {
      if (argumentosCorrectos == true) {
        if (argumentos[0] == "cargar") {
          std::cout << "Cargando archivo..." << std::endl;
          secuenciasEnMemoria.cargar(argumentos[1].c_str());
        } else if (argumentos[0] == "listar_secuencias") {
          std::cout << "Listando secuencias..." << std::endl;
          secuenciasEnMemoria.listarSecuencia();
        } else if (argumentos[0] == "histograma") {
          std::cout << "Mostrando histograma..." << std::endl;
          secuenciasEnMemoria.histograma(argumentos[1].c_str());
        } else if (argumentos[0] == "es_subsecuencia") {
          std::cout << "Buscando subsecuencia..." << std::endl;
          secuenciasEnMemoria.esSubsecuencia(argumentos[1].c_str());
        } else if (argumentos[0] == "enmascarar") {
          std::cout << "Enmascarando subsecuencia..." << std::endl;
          secuenciasEnMemoria.enmascarar(argumentos[1].c_str());
        } else if (argumentos[0] == "guardar") {
          std::cout << "Guardando datos..." << std::endl;
          secuenciasEnMemoria.guardar(argumentos[1].c_str());
        } else if (argumentos[0] == "codificar") {
          ArbolDeCodificacionHuffman Arbol;
          Arbol.comprimirSecuencias(argumentos[1], secuenciasEnMemoria);
        }
      } else {
        std::cout << " La cantidad de argumentos es incorrecta" << std::endl;
      }
    } else if (argumentos[0] != "ayuda" && argumentos[0] != "salir") {
      std::cout << "El comando no fue encontrado" << std::endl;
    }
  }
}