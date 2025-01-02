#pragma once

#include "produto.h"
#include <memory>

class SearchStrategy {
  public:
    virtual ~SearchStrategy() = default;
    virtual ProdIterator search(const std::vector<Produto> &produtos, const int &id_buscado) = 0;
};

class BinarySearchStrategy : public SearchStrategy {
  public:
    BinarySearchStrategy() = default;
    ProdIterator search(const std::vector<Produto> &produtos, const int &id_buscado) override;
};

class LinearSearchStrategy : public SearchStrategy {
  public:
    LinearSearchStrategy() = default;
    ProdIterator search(const std::vector<Produto> &produtos, const int &id_buscado) override;
};

class SearchContext {
  std::unique_ptr<SearchStrategy> strategy;

  public:
    SearchContext(std::unique_ptr<SearchStrategy> &strategy) : strategy(std::move(strategy)) {}
    SearchContext() : strategy(std::make_unique<LinearSearchStrategy>()) {}

    ProdIterator search(const std::vector<Produto> &produtos, const int &id_buscado) {
      return strategy->search(produtos, id_buscado);
    }

    void setStrategy(std::unique_ptr<SearchStrategy> &strategy) {
      this->strategy = std::move(strategy);
    }
};