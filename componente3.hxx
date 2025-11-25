#include "componente3.h"

Nodo::Nodo(char letra) : valor(letra) {
  vecinos.push_back(nullptr);
  vecinos.push_back(nullptr);
  vecinos.push_back(nullptr);
  vecinos.push_back(nullptr);
}

void SistemaDeGrafos::CargarSistemaDeGrafos(ListaSecuencias SecuenciasEnMemoria) {
  for (int i = 0; i < this->grafos.size(); i++) {
    for (int j = 0; j < this->grafos[i].nodos.size(); j++) {
      if (this->grafos[i].nodos.size() != 0) {
        delete this->grafos[i].nodos[j];
      }
    }
    this->grafos[i].nodos.clear();
  }
  this->grafos.clear();
  int salto;
  for (int i = 0; i < SecuenciasEnMemoria.secuencias.size(); i++) {
    Grafo aux;
    int anchoDeLinea = SecuenciasEnMemoria.secuencias[i].ancho;
    aux.anchuraLineas = anchoDeLinea;
    strcpy(aux.nombre, SecuenciasEnMemoria.secuencias[i].nombre);
    for (int j = 0; j < SecuenciasEnMemoria.secuencias[i].contenido.size(); j++) {
      for (int k = 0; k < SecuenciasEnMemoria.secuencias[i].ancho; k++) {
        if (*(SecuenciasEnMemoria.secuencias[i].contenido[j] + k) != '\0') {
          Nodo *nodoaux = new Nodo(*(SecuenciasEnMemoria.secuencias[i].contenido[j] + k));
          aux.nodos.push_back(nodoaux);
        } else {
          break;
        }
      }
    }
    for (int j = 0; j < aux.nodos.size(); j++) {
      // Vecino arriba
      salto = j - anchoDeLinea;
      if (salto >= 0) {
        aux.nodos[j]->vecinos[0] = aux.nodos[salto];
      } else {
        aux.nodos[j]->vecinos[0] = nullptr;
      }

      // Vecino derecha
      salto = j + 1;
      if (salto < aux.nodos.size() && salto % anchoDeLinea != 0 && salto != aux.nodos.size()) {
        aux.nodos[j]->vecinos[1] = aux.nodos[salto];
      } else {
        aux.nodos[j]->vecinos[1] = nullptr;
        ;
      }

      // Vecino abajo
      salto = j + anchoDeLinea;
      if (salto < aux.nodos.size()) {
        aux.nodos[j]->vecinos[2] = aux.nodos[salto];
      } else {
        aux.nodos[j]->vecinos[2] = nullptr;
      }
      // Vecino izquierda
      salto = j - 1;
      if (salto >= 0 && j % anchoDeLinea != 0) {
        aux.nodos[j]->vecinos[3] = aux.nodos[salto];
      } else {
        aux.nodos[j]->vecinos[3] = nullptr;
      }
    }

    this->grafos.push_back(aux);
  }
}

void SistemaDeGrafos::ruta_mas_corta(std::string nombreSecuencia, int i, int j, int x, int y) {

  // =======================
  // 1. Buscar el grafo
  // =======================
  Grafo *grafo = nullptr;
  for (Grafo &g : this->grafos) {
    if (nombreSecuencia == g.nombre) {
      grafo = &g;
      break;
    }
  }
  if (!grafo) {
    std::cout << "La secuencia no existe" << std::endl;
    return;
  }

  int ancho = grafo->anchuraLineas;
  int n = grafo->nodos.size();

  // =======================
  // 2. Convertir coordenadas
  // =======================
  int origen = i * ancho + j;
  int destino = x * ancho + y;

  if (origen >= n || destino >= n || origen < 0 || destino < 0) {
    std::cout << "Coordenadas fuera del rango" << std::endl;
    return;
  }

  // =======================
  // 3. Arreglos del Dijkstra
  // =======================
  std::vector<double> dist(n, std::numeric_limits<double>::infinity());
  std::vector<bool> visitado(n, false);
  std::vector<int> pred(n, -1);

  dist[origen] = 0;

  // =======================
  // 4. Dijkstra clásico
  // =======================
  for (int i = 0; i < n; i++) {

    // ---- 4.1 Escoger nodo NO visitado con menor distancia
    int u = -1;
    for (int k = 0; k < n; k++) {
      if (!visitado[k] && (u == -1 || dist[k] < dist[u])) {
        u = k;
      }
    }

    if (u == -1)
      break; // No quedan alcanzables
    visitado[u] = true;
    if (u == destino)
      break; // Ya llegamos al destino

    Nodo *nodoActual = grafo->nodos[u];

    // ---- 4.2 Relajar vecinos
    for (int j = 0; j < 4; j++) {

      Nodo *vecino = nodoActual->vecinos[j];
      if (!vecino)
        continue;

      // Buscar índice del vecino
      int v = -1;
      for (int l = 0; l < n; l++)
        if (grafo->nodos[l] == vecino) {
          v = l;
          break;
        }

      if (v == -1 || visitado[v])
        continue;

      // Peso ASCII
      char a = nodoActual->valor;
      char b = vecino->valor;
      double peso = 1.0 / (1.0 + std::abs(a - b));

      // Relajación estándar
      if (dist[u] + peso < dist[v]) {
        dist[v] = dist[u] + peso;
        pred[v] = u;
      }
    }
  }

  // =======================
  // 5. Reconstrucción del camino
  // =======================
  if (dist[destino] == std::numeric_limits<double>::infinity()) {
    std::cout << "No existe camino entre los puntos dados." << std::endl;
    return;
  }

  std::vector<int> camino;
  for (int v = destino; v != -1; v = pred[v]) {
    camino.push_back(v);
  }
  std::reverse(camino.begin(), camino.end());

  // =======================
  // 6. Imprimir resultados
  // =======================
  std::cout << "Costo total: " << dist[destino] << std::endl;
  std::cout << "Camino: ";
  for (int m : camino) {
    std::cout << "(" << m / ancho << "," << m % ancho << ") ";
  }
  std::cout << std::endl;
}

void SistemaDeGrafos::base_remota(std::string nombreSecuencia, int i, int j) {

  // =======================
  // 1. Buscar el grafo
  // =======================
  Grafo *grafo = nullptr;
  for (Grafo &g : this->grafos) {
    if (nombreSecuencia == g.nombre) {
      grafo = &g;
      break;
    }
  }
  if (!grafo) {
    std::cout << "La secuencia no existe" << std::endl;
    return;
  }

  int ancho = grafo->anchuraLineas;
  int n = grafo->nodos.size();

  // =======================
  // 2. Convertir coordenadas del origen
  // =======================
  int origen = i * ancho + j;

  if (origen >= n || origen < 0) {
    std::cout << "Coordenadas fuera del rango" << std::endl;
    return;
  }

  char letraOrigen = grafo->nodos[origen]->valor;

  // =======================
  // 3. Inicializar Dijkstra
  // =======================
  std::vector<double> dist(n, std::numeric_limits<double>::infinity());
  std::vector<bool> visitado(n, false);
  std::vector<int> pred(n, -1);

  dist[origen] = 0;

  // =======================
  // 4. Dijkstra completo (NO paramos en ningún destino)
  // =======================
  for (int iter = 0; iter < n; iter++) {

    // ---- 4.1 escoger el nodo NO visitado con menor distancia
    int u = -1;
    for (int k = 0; k < n; k++) {
      if (!visitado[k] && (u == -1 || dist[k] < dist[u])) {
        u = k;
      }
    }

    if (u == -1)
      break;  // No hay más alcanzables

    visitado[u] = true;

    Nodo *actual = grafo->nodos[u];

    // ---- 4.2 relajar vecinos
    for (int dir = 0; dir < 4; dir++) {
      Nodo *vec = actual->vecinos[dir];
      if (!vec) continue;

      // hallar índice lineal del vecino
      int v = -1;
      for (int l = 0; l < n; l++) {
        if (grafo->nodos[l] == vec) {
          v = l;
          break;
        }
      }

      if (v == -1 || visitado[v])
        continue;

      // peso ASCII
      double peso = 1.0 / (1.0 + std::abs(actual->valor - vec->valor));

      // relajación estándar
      if (dist[u] + peso < dist[v]) {
        dist[v] = dist[u] + peso;
        pred[v] = u;
      }
    }
  }

  // =======================
  // 5. Buscar la base más remota
  // =======================
  double maxDist = -1.0;
  int nodoRemoto = -1;

  for (int idx = 0; idx < n; idx++) {
    if (idx == origen) continue;

    if (grafo->nodos[idx]->valor == letraOrigen) {   // misma letra
      if (dist[idx] != std::numeric_limits<double>::infinity()) {  // alcanzable
        if (dist[idx] > maxDist) {
          maxDist = dist[idx];
          nodoRemoto = idx;
        }
      }
    }
  }

  if (nodoRemoto == -1) {
    std::cout << "No existe otra base remota con la letra '" 
              << letraOrigen << "'." << std::endl;
    return;
  }

  // =======================
  // 6. Reconstruir el camino
  // =======================
  std::vector<int> camino;
  for (int v = nodoRemoto; v != -1; v = pred[v]) {
    camino.push_back(v);
  }
  std::reverse(camino.begin(), camino.end());

  // =======================
  // 7. Imprimir resultados
  // =======================
  std::cout << "Letra origen: '" << letraOrigen << "'" << std::endl;
  std::cout << "Nodo remoto encontrado con la MISMA letra en: (" 
            << nodoRemoto / ancho << "," << nodoRemoto % ancho << ")\n";

  std::cout << "Distancia total: " << maxDist << std::endl;

  std::cout << "Camino: ";
  for (int v : camino) {
    std::cout << "(" << v / ancho << "," << v % ancho << ") ";
  }
  std::cout << std::endl;
}
