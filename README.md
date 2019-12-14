## TASCHE
Text Adventure and Simple CHatbot Engine
***
##### Tabla de Contenidos
- [Introducción](#introducción)
- [Compilar TASCHE](#compilar-tasche)
- [Uso](#uso)
    - [Patrones](#patrones)
    - [Expresiones](#expresiones)
        - [Expresiones como condiciones](#expresiones-como-condiciones)
    - [Fichero de especificación](#fichero-de-especificación)
    - [Consejos y trucos](#consejos-y-trucos)
- [Desarrollo](#Desarrollo)
    - [Utilizar la librería](#utilizar-la-librería)
    - [Modificar los parsers](#modificar-los-parsers)
    - [Funcionalidades por hacer](#funcionalidades-por-hacer)

### Introducción
TASCHE es una herramienta para especificar aplicaciones basadas en texto que persigue flexibilidad en el reconocimiento de la entrada y variedad en las respuestas. Para ello , utiliza unos _patrones_ que se explicaran en profundidad más abajo.
El comportamiento básico de un programa TASCHE es el siguiente:

1. Se lee la entrada.
2. Se compara la entrada con todos los patrones almacenados.
3. Para cada patrón que coincida, se comprueban las condiciones asociadas.
4. Para cada condición cumplida, se compone la respuesta a partir del patrón de salida.

Las condiciones en TASCHE se especifican con _expresiones_ en un lenguaje de scripting minimalista. Este mismo lenguaje se utiliza para modificar el estado interno del programa, desde los _patrones_ de salida.

### Compilar TASCHE
El código fuente de TASCHE está autocontenido. Los scripts necesarios para la compilación en Windows y en Linux están incluidos en la raíz del proyecto. El código fuente de otros proyectos FLOSS está contenido en el directorio [thirdparty](thirdparty) y sus respectivas licencias se encuentran junto a la misma de TASCHE en el fichero [LICENSE](LICENSE).
Por lo tanto, lo único necesario para compilar TASCHE es abrir la terminal, ir al directorio raíz del proyecto y allí ejecutar `./compile.sh` en Linux o `compile.bat` en Windows.
***
### Uso
Para una guía detallada de uso, ver la [wiki](wiki)

### Pendiente
- Permitir una distancia de edit en el matching (autómata de Levenshtein)
- Depurar la interacción entre variables dinámicas y patrones omisibles
- Implementar la opción de cachear las expresiones en una misma búsqueda
- Optimizar los recursos de las expresiones mediante una análisis semántico post-parseo.
- Optimizar los algotimos de comparación (evitar el uso de substr)
