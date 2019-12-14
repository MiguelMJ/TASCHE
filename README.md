## TASCHE
Text Adventure and Simple CHatbot Engine
***

### Uso
Para una guía detallada de uso, ver la [wiki](https://github.com/MiguelMJ/TASCHE/wiki)

### Compilar TASCHE
TASCHE no tiene dependencias externas. Los scripts necesarios para la compilación en Windows y en Linux están incluidos en la raíz del proyecto. El código fuente de otros proyectos FLOSS está contenido en el directorio [thirdparty](thirdparty) y sus respectivas licencias se en el fichero [LICENSE](LICENSE). Por lo tanto, lo único necesario para compilar TASCHE es ejecutar `./compile.sh` en Linux o `compile.bat` en Windows desde el directorio raíz del proyecto.

### Pendiente
- Permitir una distancia de edit en el matching (autómata de Levenshtein)
- Depurar la interacción entre variables dinámicas y patrones omisibles
- Implementar la opción de cachear las expresiones en una misma búsqueda
- Optimizar los recursos de las expresiones mediante una análisis semántico post-parseo.
- Optimizar los algotimos de comparación (evitar el uso de substr)
