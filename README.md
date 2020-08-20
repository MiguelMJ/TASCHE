<p align="center"><img src="logo.jpg" alt="logo" width="350"/></p>

<h1 align="center">Text Adventure and Simple CHatbot Engine</h1>

<p align="center">
<img alt="dependencies" src="https://img.shields.io/badge/dependencies-none-green">
<a href="https://github.com/MiguelMJ/TASCHE/wiki"><img alt="documentation" src="https://img.shields.io/badge/documentation-wiki-green"></a>
<img alt="GitHub repo size" src="https://img.shields.io/github/repo-size/MiguelMJ/TASCHE">
</p>

[Léeme en español :es:](README_ES.md) 

### Description
TASCHE is a tool for specifying text-based applications that seeks flexibility in the input recognition and response generation.
For a detailed guide see the [wiki](https://github.com/MiguelMJ/TASCHE/wiki) .
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
