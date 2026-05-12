# Proyecto_Matematicas_Discretas_S1-2026

## 1. Descripción
El código presente, al entregarle un mapa con un número de calles y un número de puntos turisticos, y le muestra al usuario el camino entre todos estos puntos, permitiendo al usuario planear una ruta de turismo donde pueda recorrer todos los puntos de interes.
Este proyecto se realizo para la asignatura de Matemáticas Discretas, impartida el primer semestre de 2026, en la universidad de Concepción, por la profesora Lilian Salinas Ayala. El motivo de proyecto fue para demostrar y pulir los conocimientos respecto a la teoria de grafos y digrafos.

## 2. Modelado Matemático
Aquí puedes describir brevemente los conceptos aplicados:
* **Estructuras:** Para trabajar con el mapa, se trabajara este como si fuera un grafo.
* **Algoritmos:**  Para calcular las distancias, se usara el algoritmo de BFS.

## 3. Tecnologías Utilizadas
* **Lenguaje:** Lenguaje C
* **Documentación:** El informe del proyecto fue realizado en Latex.
* **Librerías:** Las librerias usadas en el desarrollo del proyecto son:
    -   math.h.
    -   string.h
    -   stdio.h

## 4. Instalación y Ejecución
Tanto el archivo comprimido donde se entregara la tarea, como en el repositorio de GitHub, habra un archivo '.exe' con el código compilado. En caso de que se quiera volver a compilar, se debe realizar lo siguiente:

```bash
# Clonar el repositorio
git clone [https://github.com/Gquilodran/Proyecto_Matematicas_Discretas_S1-2026]

# Abrir la carpeta descargada, luego abrir una terminal ejecutar el siguiente comando:
gcc main.c -o mapa.exe -lm

# Luego ejecute el código con el siguiente comando
./main.exe

#El programa le pedira ingresar el nombre de un mapa que tiene que estar en un archivo .txt, este archivo puede estar en la misma carpeta del ejecutable o en la carpeta de mapas_tipos. En este ultimo caso, se debe ingresar: "mapas_tipos/[nombre del mapa]

## Documentación
#En este mismo repositorio se encuentra un documento PDF donde se guarda la documentación más profunda del proyecto y del código realizado. Igualmente se puede revisar el siguiente link que llevara a la página donde se desarollo el documento.
* **Overleaf:** [Acceder al Informe Final](https://www.overleaf.com/read/vydnvzhvtgwb#af8556)

```

## 👥 Autores
Proyecto desarrollado por el grupo conformado por:
* **Jose Efrain Gonzalez Aguayo**
* **Gonzalo Alejandro Quilodran Neira** 
* **Mario Andres Salgado Jaque**

## Licencia
Se proíbe el uso de este proyecto para su uso comercial o con fines de lucro sin previa consulta a los autores. Este proyecto fue realizado para un área académica de la Universidad de Concepción.

