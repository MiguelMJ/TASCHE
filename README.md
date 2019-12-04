## TASCHE
Text Adventure and Simple CHatbot Engine

### Introducción
TASCHE es una herramienta para especificar aplicaciones basadas en texto que persigue flexibilidad en el reconocimiento de la entrada y variedad en las respuestas. Para ello , utiliza unos _patrones_ que se explicaran en profundidad más abajo.

El comportamiento básico de un programa TASCHE es el siguiente:

1. Se lee la entrada.
2. Se compara la entrada con todos los patrones almacenados.
3. Para cada patrón que coincida, se comprueban las condiciones asociadas.
4. Para cada condición cumplida, se compone la respuesta a partir del patrón de salida.

Las condiciones en TASCHE se especifican con _expresiones_ en un lenguaje de scripting minimalista. Este mismo lenguaje se utiliza para modificar el estado interno del programa, desde los _patrones_ de salida.

###

### Fichero de especificación
TASCHE lee un fichero JSON (usando [rapidjson](https://github.com/Tencent/rapidjson)) que debe tener la siguiente estructura:

```JSON
{
"init":"expresion",
"responses": [  ]
}
```
