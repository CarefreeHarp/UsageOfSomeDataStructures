# UsageOfSomeDataStructures — Proyecto (Estructuras de Datos)

## Descripción general
Aplicación de consola que implementa un proyecto de Estructuras de Datos: operaciones básicas sobre archivos en formato **FASTA** usando **estructuras lineales**.  
Permite cargar secuencias, listarlas, generar histogramas, verificar subsecuencias, enmascararlas y guardarlas.  
Además utilizando **árboles de codificación** con el algoritmo de Huffman, se permite comprimir y descomprimir la información de archivos .fa (FASTA) en archivos binarios .fabin


## Estructura del repositorio
```
UsageOfSomeDataStructures/
├─ main.cpp                 # Punto de entrada; incluye la consola interactiva
├─ componente1.h            # Declaraciones (structs y prototipos) pertenecientes al componente 1 del proyecto
├─ componente1.hxx          # Implementaciones (I/O, lógica de comandos y consola) pertenecientes al componente 1 del proyecto
├─ componente2.h            # Declaraciones (structs y prototipos) pertenecientes al componente 2 del proyecto
├─ componente2.hxx          # Implementaciones (I/O, lógica de comandos y consola) pertenecientes al componente 2 del proyecto
├─ archivo.fa               # Archivo FASTA de ejemplo
├─ codigos.txt              # Asociación base → significado (A→Adenina, ...)
├─ comandos.guda            # Binario con las definiciones de comandos disponibles
├─ Makefile                 # Compilar y ejecutar
└─ Proyecto.pdf             # Enunciado y descripción del trabajo a realizar
```

### Archivos de datos
- **archivo.fa**: ejemplo de genoma en formato FASTA, con dos secuencias (`>Full_SEQUENCE` y `>Incomplete_sequence`).  
- **codigos.txt**: mapeo textual de símbolos a su significado biológico (A, C, G, T, U, R, …, X, `-`). El programa lo usa para cargar en memoria los códigos.
- **comandos.guda**: archivo **binario** en el cual persiste la información de los **comandos disponibles**. Se modifica mediante la función interactiva `crearComando` (ver más abajo).

## Compilación
Probado en:
- Ubuntu 24.04 con g++ 13.3.0
- Windows 11 con g++ 10.3.0 (tdm64-1)

### Opción 1: con Makefile (Linux/macOS)
Utilizando el fichero `Makefile`:
```bash
make CompilaryEjecutar
```

### Opción 2: manual (Linux/macOS/Windows)
```bash
g++ main.cpp -o ejecutable.out
./ejecutable.out
```

## Ejecución e interfaz
Al iniciar, la aplicación abre una **consola interactiva** con prompt:
```
    $
```
La consola valida comandos y su cantidad de argumentos con base en lo definido en `comandos.guda`.  
Además soporta un sistema de ayuda con el comando 'ayuda' para ver los comandos disponibles y el uso de cada uno.

### Comandos soportados
- `cargar <nombre_archivo>`  
  Carga en memoria las secuencias del archivo FASTA indicado.  

- `listar_secuencias`  
  Imprime cuántas secuencias hay en memoria y, por cada una:
  - Si la secuencia es **completa** (no contiene `-`): `Secuencia <descripcion> contiene b bases`  
  - Si es **incompleta** (contiene `-`): `Secuencia <descripcion> contiene al menos b bases`

- `histograma <descripcion_secuencia>`  
  Muestra el conteo de cada símbolo en la secuencia solicitada.  

- `es_subsecuencia <subsecuencia>`  
  Cuenta cuántas veces aparece la subsecuencia en **todas** las secuencias cargadas.  

- `enmascarar <subsecuencia>`  
  Reemplaza todas las ocurrencias de la subsecuencia por `X` en las secuencias cargadas.  
  Al finalizar informa cuántas subsecuencias fueron enmascaradas o si no encontró ninguna.

- `guardar <nombre_archivo>`  
  Escribe en archivo nuevo con el nombre solicitado las secuencias actualmente en memoria (incluyendo enmascarado).  
  Mantiene la justificación por líneas tal como fue cargada. Informa éxito o error al guardar.

- `codificar <nombre_archivo.fabin>`  
  Por medio del algoritmo de Huffman y con la estructura especificada en el componente2 del pdf del proyecto, se
  comprime la información de todas las secuencias cargadas en memoria y se guardan en un archivo binario con el nombre especificado.

- `decodificar <nombre_archivo.fabin>`  
  Por medio del algoritmo de Huffman y con la estructura especificada en el componente2 del pdf del proyecto, se
  descomprime la información de un archivo .fabin solicitado por el usuario y se carga en memoria la información de todas las secuencias
  reemplazando las que ya hubiese ahí.

- `salir`  
  Termina la ejecución.

- `ayuda` y `ayuda <comando>`  
  Lista los comandos existentes (según `comandos.guda`) y muestra su descripción y salidas posibles.

## (EJEMPLO) Ejecución con los archivos existentes
```
    $ cargar archivo.fa
    $ listar_secuencias
    $ histograma Full_SEQUENCE
    $ es_subsecuencia GA
    $ enmascarar GA
    $ guardar salida.fa
```
Revisa el archivo `salida.fa` generado para verificar el guardado (estructura FASTA y líneas justificadas).

## Créditos
- Autores: Daniel Ramírez y Guillermo Aponte 
- Curso: Estructuras de Datos — Pontificia Universidad Javeriana.
