#include "search_strategy.h"

/**
 * @brief Realiza uma busca linear em um vetor de produtos
 * 
 * Percorre sequencialmente o vetor de produtos comparando o ID de cada
 * produto com o ID buscado.
 * 
 * @param produtos Vetor de produtos onde será realizada a busca
 * @param id_buscado ID do produto que está sendo procurado
 * @return ProdIterator Iterador apontando para o produto encontrado ou produtos.end() se não encontrado
 */
ProdIterator LinearSearchStrategy::search(const std::vector<Produto> &produtos, const int &id_buscado) {
  for (auto it = produtos.begin(); it != produtos.end(); ++it) {
    if (it->getId() == id_buscado) return it;
  }
  return produtos.end();
}

/**
 * @brief Realiza uma busca binária em um vetor de produtos
 * 
 * Implementa o algoritmo de busca binária assumindo que o vetor está
 * ordenado por ID. Divide o espaço de busca pela metade a cada iteração.
 * 
 * @param produtos Vetor ordenado de produtos onde será realizada a busca
 * @param id_buscado ID do produto que está sendo procurado
 * @return ProdIterator Iterador apontando para o produto encontrado ou produtos.end() se não encontrado
 */
ProdIterator BinarySearchStrategy::search(const std::vector<Produto> &produtos, const int &id_buscado) {
  auto IdComp = [] (const Produto &prod, const int &id) -> bool { return prod.getId() < id; };
  auto begin = produtos.begin(), end = produtos.end();
  
  while(end - begin > 1) {
    auto middle = begin+((end-begin)/2);
    if (IdComp(*middle, id_buscado)) begin = middle+1;
    else end =middle;
  }
  return begin->getId() == id_buscado ? begin : produtos.end();
}