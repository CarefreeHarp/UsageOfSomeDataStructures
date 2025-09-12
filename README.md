# UsageOfSomeDataStructures — Proyecto (Estructuras de Datos)

## Descripción general
Aplicación de consola que implementa un proyecto de Estructuras de Datos: operaciones básicas sobre archivos en formato **FASTA** usando **estructuras lineales**.  
Permite cargar secuencias, listarlas, generar histogramas, verificar subsecuencias, enmascararlas y guardarlas.


## Estructura del repositorio
```
UsageOfSomeDataStructures/
├─ main.cpp                 # Punto de entrada; incluye la consola interactiva
├─ proyecto.h               # Declaraciones (structs y prototipos)
├─ proyecto.hxx             # Implementaciones (I/O, lógica de comandos y consola)
├─ archivo.fa               # Archivo FASTA de ejemplo
├─ codigos.txt              # Asociación base → significado (A→Adenina, ...)
├─ comandos.guda            # Binario con las definiciones de comandos disponibles
├─ Makefile                 # Compilar y ejecutar
└─ Proyecto.pdf             # Enunciado y descripcion del trabajo a realizar
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
  Mensajes esperados (según contenido):
  - `n secuencias cargadas correctamente desde <nombre_archivo>.`  
  - `<nombre_archivo> no contiene ninguna secuencia.`  
  - `<nombre_archivo> no se encuentra o no puede leerse.`

- `listar_secuencias`  
  Imprime cuántas secuencias hay en memoria y, por cada una:
  - Si la secuencia es **completa** (no contiene `-`): `Secuencia <descripcion> contiene b bases`  
  - Si es **incompleta** (contiene `-`): `Secuencia <descripcion> contiene al menos b bases`

- `histograma <descripcion_secuencia>`  
  Muestra el conteo de cada símbolo en la secuencia.  
  Implementación actual: el programa imprime un resumen **por línea** de la secuencia (muestra `Linea <k>` y luego los conteos `A: x C: y ... '-' : z`).

- `es_subsecuencia <subsecuencia>`  
  Cuenta cuántas veces aparece la subsecuencia en **todas** las secuencias cargadas.  
  Si no hay secuencias en memoria, imprime el mensaje correspondiente.

- `enmascarar <subsecuencia>`  
  Reemplaza todas las ocurrencias de la subsecuencia por `X` en las secuencias cargadas.  
  Al finalizar informa cuántas subsecuencias fueron enmascaradas o si no encontró ninguna.

- `guardar <nombre_archivo>`  
  Escribe en disco las secuencias actualmente en memoria (incluyendo enmascarado).  
  Mantiene la justificación por líneas tal como fue cargada. Informa éxito o error al guardar.

- `salir`  
  Termina la ejecución.

- `ayuda` y `ayuda <comando>`  
  Lista los comandos existentes (según `comandos.guda`) y muestra su descripción y salidas posibles.

## Flujo de uso recomendado
1. **Cargar tabla de códigos** (automático dentro de tu `main.cpp` vía `Codigos::cargar()` leyendo `codigos.txt`).  
2. **Cargar secuencias**:  
   ```
       $ cargar archivo.fa
   ```
3. **Listar** para validar:  
   ```
       $ listar_secuencias
   ```
4. **Consultar histograma** de una secuencia concreta:  
   ```
       $ histograma Full_SEQUENCE
   ```
5. **Buscar subsecuencia** o **enmascararla**:  
   ```
       $ es_subsecuencia ATGC
       $ enmascarar ATGC
   ```
6. **Guardar cambios**:  
   ```
       $ guardar salida.fa
   ```
7. **Ayuda** general o por comando:  
   ```
       $ ayuda
       $ ayuda cargar
   ```

## Sobre `comandos.guda` y `crearComando`
- `comandos.guda` persiste un arreglo de estructuras `Comando` con los campos:
  - `nombre` (char[50])
  - `argumentos` (bool: si requiere argumento)
  - `argumento` (char[50]: etiqueta/nombre del argumento)
  - `descripcion` (char[1000])
  - `posiblesSalidas` (char[1000])
- La función `crearComando()` permite **agregar** comandos de forma interactiva; cada comando se añade al final del archivo binario.  
- La consola (`escribirComando`) usa este archivo para:
  - Validar si un comando existe.
  - Verificar si necesita argumento o no.
  - Proveer ayuda (`ayuda` / `ayuda <comando>`).

> Si `comandos.guda` no existe o está vacío, la consola se ejecuta, pero no validará comandos (no habrá nada que listar en `ayuda`). En este repositorio se incluye un `comandos.guda` con definiciones base.

## Notas de implementación
- El programa manipula secuencias en memoria con **estructuras lineales** (vectores), acorde a la Entrega 1.  
- El conteo del histograma incluye todos los símbolos definidos para FASTA, incluido `X` (máscara) y `-` (espacio de longitud indeterminada).  
- Las operaciones de enmascarado se hacen in-place reemplazando caracteres por `X` en el contenido cargado.

## Pruebas rápidas con los archivos de ejemplo
```
    $ cargar archivo.fa
    $ listar_secuencias
    $ histograma Full_SEQUENCE
    $ es_subsecuencia ATG
    $ enmascarar ATG
    $ guardar salida.fa
```
Revisa el archivo `salida.fa` generado para verificar el guardado (estructura FASTA y líneas justificadas).

## Créditos
- Autor: Daniel Ramírez (UsageOfSomeDataStructures).
- Curso: Estructuras de Datos — Pontificia Universidad Javeriana.
- Entrega: #1 — Componente 1.
