#pragma once

#include <iostream>
#include <optional>
#include <sstream>
#include <limits>
#include "produto.h"
#include "search_strategy.h"

class Catalogo {
  vector<Produto> lista_produtos;
  std::unique_ptr<SearchContext> search_context;

  public:
    Catalogo() : search_context(std::make_unique<SearchContext>()) {}

    bool adicionarProduto(Produto prod_add, bool verbose = true);

    vector<Produto> listarProdutos();

    ProdIterator end() const {return lista_produtos.end();}

    ProdIterator buscarProdutoPorId(int id);

    void mudarContexto(std::unique_ptr<SearchStrategy> &new_strategy) { search_context->setStrategy(new_strategy); }

    size_t size() const { return lista_produtos.size(); }

    void reserve(size_t n) { lista_produtos.reserve(n); }
};

class Pedido {
  vector<Produto> lista_produtos;
  string nome_cliente;

  public:
    Pedido(vector<Produto> produtos,string nome = "", bool verbose = true) : lista_produtos(produtos), nome_cliente(nome) {
      if (verbose) std::cout << "Pedido de " << this->nome_cliente << " criado com sucesso." << std::endl;
    }
    
    void adicionarProduto(Produto prod_add);
    
    float calcularTotal(bool verbose = true);
};
