# Modelos de Programación Emergente

## Proyecto I: Perceptrón Simple

### Enunciado

```
Desarrolle una RNA basada en el Perceptrón Simple que permita el reconocimiento de letras minúsculas (vocales: a,e,i,o,u) manuscritas.
La entrada será un archivo contentivo del caracter fotografiado, o una matrix 16x10 que simule el caracter, a analizar.
```

### Entrada elegida

Archivo de texto con 16 líneas y 16 números separados por espacios, que representen la letra a analizar.

#### Ejemplo de archivo de entrada:

```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 1 1 1 0 0 0 0
0 0 0 1 0 0 1 0 0 0
0 0 1 1 0 0 0 1 0 0
0 1 1 0 0 0 1 1 0 0
0 1 0 1 1 1 1 0 0 0
0 1 0 0 0 0 0 0 0 0
0 1 1 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 1 1 1 0 0 1 0 0
0 0 0 0 1 1 1 1 0 0
0 0 0 0 0 0 0 0 0 0
```

### Compilación

1. Clonar el repositorio.
2. Dentro del directorio resultante, ejecutar uno de los siguientes comandos, dependiendo del compilador del que se disponga:
```bash
g++ main.cpp network/*.cpp neuron/*.cpp utils/*.cpp vector-operations/*.cpp -o nn
```
```bash
clang++ main.cpp network/*.cpp neuron/*.cpp utils/*.cpp vector-operations/*.cpp -o nn
```

### Utilización

Ejecutar el archivo `nn` resultante.

#### Ejecución Sencilla

Al ejecutar el programa, se crea una red neuronal desde cero (o se carga la base de conocimiento y se instancia con ella, si se encuentra alguna en la carpeta de ejecución)

Si el programa se ejecuta sin argumentos, se le informa al usuario de los parámetros que puede utilizar.

#### Entrenamiento

Si se ejecuta el programa con el argumento `train`, también debe pasársele un numero no negativo entero como tercer argumento. Esto representa las 'épocas', o la cantidad de veces que la red neuronal itera sobre el conjunto de entrenamiento. La red neuronal carga los ejemplos de entrenamiento (contenidos en la carpeta `training-samples/` y aprende de ellos. Luego del entrenamiento, se almacena la base de conocimiento en un archivo `base.txt`.

#### Prueba

Si se ejecuta el programa con el argumento `test` sin pasar un tercer argumento, la red neuronal cargará e intentará clasificar todo el conjunto de prueba (contenido en la carpeta `testing-samples/`), dando un reporte acerca de su rendimiento al final del proceso.

Si se pasa un tercer argumento, el programa asumirá que se trata de la ruta de un archivo de entrada, e intentará cargarlo en memoria para luego clasificarlo. Por ejemplo, ejecutar `./nn test ./letter.txt` cargará el archivo `letter.txt` que se encuentra en la misma carpeta que el ejecutable (asumimos que `nn` es el ejecutable del programa)

#### Ayuda

Para más ayuda, se puede ejecutar el programa con el argumento `help`.

# Nota

El código está comentado en inglés por mera costumbre.
