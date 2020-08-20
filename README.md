<img src="logo.jpg" alt="logo" width="350"/>

# Text Adventure and Simple CHatbot Engine

![dependencies](https://img.shields.io/badge/dependencies-none-green) [![documentation](https://img.shields.io/badge/documentation-wiki-green)](https://github.com/MiguelMJ/TASCHE/wiki)![GitHub repo size](https://img.shields.io/github/repo-size/MiguelMJ/TASCHE)

***
Lee [este documento en español :es:](README_ES.md) 

### Usage
For a detailed guide see the [wiki](https://github.com/MiguelMJ/TASCHE/wiki) (soon in English too!)

### Build TASCHE

TASCHE has no dependencies, but to build it you must have Flex and Bison in your computer.

To build the project use plain make:

```
cd /project/path
make
```

### To do

* [ ] Embed Lua to replace the expressions.

- [ ] Allow an edit distance in the input matching (Levenshtein Automata)
- [x] Debug the interaction between dynamic variables and omisible patterns (branch dynamic_and_omisibles).
- [ ] Implement more verbose and debug options.
- [ ] Module for knowledge bases.
- [ ] Extend documetation.
- [ ] Optimize the comparison algorithms (too many substr).
