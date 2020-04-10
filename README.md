## TASCHE
Text Adventure and Simple CHatbot Engine
***
Soon there will be an English version of the documentation of this project!

### Uso
Para una guía detallada de uso, ver la [wiki](https://github.com/MiguelMJ/TASCHE/wiki)

### Compilar TASCHE
TASCHE no tiene dependencias externas. Los scripts necesarios para la compilación en Windows y en Linux están incluidos en la raíz del proyecto. El código fuente de otros proyectos FLOSS está contenido en el directorio [thirdparty](thirdparty) y sus respectivas licencias se en el fichero [LICENSE](LICENSE). Por lo tanto, lo único necesario para compilar TASCHE es ejecutar `./compile.sh` en Linux o `compile.bat` en Windows desde el directorio raíz del proyecto.

### Pendiente

* [ ] Integrar scripts de Lua para sustituir las expresiones

- [ ] Permitir una distancia de edit en el matching (autómata de Levenshtein)
- [ ] Depurar la interacción entre variables dinámicas y patrones omisibles (branch dynamic_and_omisibles en marcha)
- [ ] Optimizar los algoritmos de comparación (evitar el uso de substr)
- [ ] Perfeccionar distintas opciones y niveles de verbose y debug
- [ ] Añadir tipos diccionario y lista a las expresiones
- [ ] Implementar conexión directa con bases de datos y bases de conocimiento
- [ ] Extender documentación para usar la librería en desarrollo de nuevas aplicaciones
