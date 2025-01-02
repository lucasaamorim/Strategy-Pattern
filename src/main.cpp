#include "project.h"

int main() {
  try {
    // Create products
    Produto prod1(1, "Notebook", 2500.50);
    Produto prod2(2, "Smartphone", 1800.00);
    Produto prod3(3, "Fone de Ouvido", 300.00);

    // Teste: erros na declaração do produto
    //Produto invalidProd(-1, "", -10.00);

    // Adicionando produtos ao catalogo
    Catalogo catalogo;
    catalogo.adicionarProduto(prod1);
    catalogo.adicionarProduto(prod2);
    catalogo.adicionarProduto(prod3);

    // Tentar adicionar um produto duplicado
    Produto duplicateProd(1, "Cadeira", 500.00);
    catalogo.adicionarProduto(duplicateProd);

    // Listar os produtos do catalogo
    auto produtos = catalogo.listarProdutos();

    // Buscar um produto pelo id
    auto found = catalogo.buscarProdutoPorId(2);
    if (found != catalogo.end()) {
        std::cout << "Produto encontrado: " << found->getName() << "\n";
    } else {
        std::cout << "Produto não encontrado.\n";
    }

    // Buscar por produto inexistente
    auto notFound = catalogo.buscarProdutoPorId(99);
    if (notFound == catalogo.end()) {
        std::cout << "Produto 99 não encontrado.\n";
    }

    // Criar um pedido
    Pedido pedido({prod1, prod3}, "Jose Costa");
    pedido.adicionarProduto(prod2);

    // Calcular o total do pedido
    float total = pedido.calcularTotal();
    std::cout << "Total do pedido: R$" << total << std::endl;

  } catch (const std::string& error) {
    std::cerr << "Erro: " << error << std::endl;
  } catch (const char* error) {
    std::cerr << "Erro: " << error << std::endl;
  } catch (...) {
    std::cerr << "Erro desconhecido" << std::endl;
  }
  return 0;
}
