# Estudo Dirigido Sobre Desempenho, Otimização de Código e Padrões de Projeto - Boas Práticas de Programação (DIM0501)

Lucas Apolonio de Amorim

# Estudo sobre o Padrão Strategy e Análise de Complexidade

Implementação do gerenciamento de estoque de uma loja utilizando o padrão Strategy para comparar diferentes algoritmos de busca.

## Sobre o Padrão Strategy

O projeto implementa o padrão Strategy para alternar entre dois algoritmos de busca:
- Busca Linear (O(n))
- Busca Binária (O(log n))

O padrão permite trocar o algoritmo de busca em tempo de execução, mantendo o código limpo e extensível.

## Análise de Desempenho

O programa inclui ferramentas para medir e visualizar o desempenho dos algoritmos:

1. **Coleta de Dados**: Usando [time_measurement.cpp](./timing/time_measurement.cpp), medimos os tempos de execução para:
  - Arrays pequenos (1 a 1.000 elementos)
  - Arrays grandes (10.000 a 1.000.000 elementos)

2. **Visualização**: Através de [plotting.ipynb](./timing/plotting.ipynb), geramos gráficos comparativos que demonstram:
  - Comparação direta entre busca linear e binária
  - Ajuste com curvas teóricas (linear e logarítmica)
  - Análise em diferentes escalas

**[Relatório Completo Aqui](./docs/relatorio.pdf)**

### Compilação e Testes:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
```

### Executando os Testes Unitários:
```bash
ctest --test-dir build
```

### Executando o Programa:
```bash
./EstudoDirigido
```