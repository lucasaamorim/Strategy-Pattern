#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class Produto {
  int id;
  string nome;
  float preco;

  public:
    Produto(int id, string nome, float preco);
    int getId() const { return this->id; }
    string getName() const { return this->nome; }
    float getPrice() const { return this->preco; }
};

typedef vector<Produto>::const_iterator ProdIterator;