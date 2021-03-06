<p align="center"><img src="logo.jpg" alt="logo" width="350"/></p>

<h1 align="center">Text Adventure and Simple CHatbot Engine</h1>

<p align="center">
<img alt="dependencies" src="https://img.shields.io/badge/dependencies-none-green">
<a href="https://github.com/MiguelMJ/TASCHE/wiki"><img alt="documentation" src="https://img.shields.io/badge/documentation-wiki-green"></a>
<a href="LICENSE"><img alt="license" src="https://img.shields.io/badge/license-MIT-green"></a>
<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/MiguelMJ/TASCHE">
</p>

[Readme in english :gb::us:](README.md)

### Uso
Para una guía detallada de uso, ver la [wiki](https://github.com/MiguelMJ/TASCHE/wiki)

### Compilar TASCHE
TASCHE no tiene dependencias externas, pero para compilarlo hace falta disponer de Flex y Bison.

Para compilar el proyecto, make debería bastar:

```
cd /project/path
make
```

### Pendiente

* [ ] Integrar scripts de Lua para sustituir las expresiones

- [ ] Permitir una distancia de edit en el matching (autómata de Levenshtein)
- [x] Depurar la interacción entre variables dinámicas y patrones omisibles (branch dynamic_and_omisibles en marcha)
- [ ] Perfeccionar distintas opciones y niveles de verbose y debug
- [ ] Módulo para bases de conocimiento
- [ ] Extender la documentación.
- [ ] Optimizar los algoritmos de comparación (evitar el uso de substr)
