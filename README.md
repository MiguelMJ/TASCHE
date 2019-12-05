## TASCHE
Text Adventure and Simple CHatbot Engine
***
##### Tabla de Contenidos
- [Introducción](#introduccion)
- [Patrones](#patrones)
- [Expresiones](#expresiones)
    - [Expresiones como condiciones](#expresiones-como-condiciones)
    - [Expresiones dentro de patrones](#expresiones-dentro-de-patrones)
- [Fichero de especificación](#fichero-de-especificación)

### Introducción
TASCHE es una herramienta para especificar aplicaciones basadas en texto que persigue flexibilidad en el reconocimiento de la entrada y variedad en las respuestas. Para ello , utiliza unos _patrones_ que se explicaran en profundidad más abajo.
El comportamiento básico de un programa TASCHE es el siguiente:

1. Se lee la entrada.
2. Se compara la entrada con todos los patrones almacenados.
3. Para cada patrón que coincida, se comprueban las condiciones asociadas.
4. Para cada condición cumplida, se compone la respuesta a partir del patrón de salida.

Las condiciones en TASCHE se especifican con _expresiones_ en un lenguaje de scripting minimalista. Este mismo lenguaje se utiliza para modificar el estado interno del programa, desde los _patrones_ de salida.

### Patrones
Los patrones TASCHE sirven tanto para reconocer cadenas de texto como para generarlas. Los tipos de patrones son los siguientes:

- **Texto plano**
Reconoce y produce directamente, sin tener en cuenta mayúsculas y minúsculas, una cadena de texto.
`Texto aquí` reconoce y produce `Texto aquí`.
- **Texto omisible**
Reconoce y produce una cadena de texto, así como su ausencia. Se escribe entre corchetes `[]`.
`Texto[ aquí]` reconoce y produce tanto `Texto` como `Texto aquí`.
- **Opción múltiple**
Reconoce y produce una de varias cadenas de texto. Se escribe entre paréntesis `()` separando las opciones con barras verticales `|`.
`Texto (aquí|allí)` reconoce y produce tanto `Texto aquí` como `Texto allí`.
- **Variable**
Reconoce y produce el valor de una variable del estado interno del programa. Se escribe el identificador de la variable precedido por `$`.
Si, por ejemplo, la variable `nombre` contiene el valor `Miguel`, entonces:
`Hola, $nombre` reconoce y produce `Hola, Miguel`.
Los identificadores de las variables siguen las reglas léxicas de las variables de la familia de lenguajes C, C++ o Java.
- **Variable dinámica**
Reconoce cualquier cadena de texto y almacena su valor en una variable de texto. Produce el valor de la variable, igual que las variables normales. Se escribe el identificador de la variable precedido por `>`.
`Me llamo >nombre` reconoce, por 
  - `Me llamo Juan` (nombre = `Juan`)
  - `Me llamo Tony Stark` (nombre = `Tony Stark`)
  - `Me llamo Bond, James Bond` (nombre = `Bond, James Bond`)
- **Script**
Reconoce y produce el resultado de evaluar una _expresión_. Se escribe dicha _expresión_ entre llaves `{}`.
`{3 + 2}` reconoce y produce `5`.

Los patrones pueden combinarse entre sí, por ejemplo:
- `Hola, (amigo[ mío]|$nombre), qué tal[ estás[ (hoy|este día)]][?]`
- `Qué (tiempo|clima) hará en >lugar (dentro de|en) >num días[?]`

### Expresiones
Las expresiones TASCHE son un lenguaje de scripting minimalista. Sirven para manipular el estado interno del programa. Siempre devuelven cadenas de texto.
Especifican las condiciones que se evalúan para responder a una entrada. El valor lógico de 
- **Expresiones numéricas**. Devuelven cadenas de texto númericas.
    Devuelven el número resultado de las operaciones.
    - Números naturales: `1`, `2`, `3`,`42`, etc.
    - Variables precedidas por almohadilla: `#edad`, `#numero_entrada`. Si la variable contiene texto o está vacía, dará un error.
    - Operaciones aritméticas: `+`, `-`, `*`, `/`, `^`(potencia), `%`(módulo).
    - Cualquier otra expresión contenida entre paréntesis `()`.
- **Expresiones textuales**. Devuelven cadenas de texto.
    - Cadenas entre dobles comillas simples: `''texto''` (en lugar de `"texto"`).
    - Variables precedidas por arroba: `@nombre`, `@lugar`.
- **Comparaciones numéricas**. Devuelven `1` ó `0`.
    - `-eq`: igual
    - `-ne`: distinto
    - `-lt`: menor
    - `-le`: menor o igual
    - `-gt`: mayor
    - `-ge`: mayor o igual
- **Comparaciones de texto**. Devuelven `1` ó `0`.
    - `==`: igual
    - `!=`: desigual
- **Operaciones lógicas**. Devuelven `1` ó `0`.
    - `!`: negación (not)
    - `&&`: conjunción (and)
    - `||`: disyunción (or)
- **Asignaciones**. Devuelven una cadena vacía.
    - `@var =` asigna cualquier expresión a `var`.
    - `#var =` asigna sólo una expresión numérica a `var`.

#### Expresiones como condiciones
Tanto en las operaciones lógicas como en la evaluación de las condiciones para las respuestas, el valor lógico de una expresión es verdadero si y solo si el valor que devuelve no es una cadena vacía y no tiene valor numérico 0.
`0`, `000`, `''''`, `1 && 2 -ne 2`, `@variable_indefinida` se evalúan como _falso_
`22`, `''azul''`, `''ab''==''ab'' || 0`, `@variable_no_nula` se evalúan como _verdadero_.

#### Expresiones dentro de patrones


### Fichero de especificación
TASCHE lee un fichero JSON (usando [rapidjson](https://github.com/Tencent/rapidjson)) que debe tener la siguiente estructura:

```JSON
{
"init":"expresion",
"responses": [  ]
}
```
