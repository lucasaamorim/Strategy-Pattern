#include <gtest/gtest.h>
#include "../src/project.h" 

// Produto::Produto()
TEST(CONSTRUTOR_PRODUTO, NORMAL) {
    ASSERT_NO_THROW(Produto(1, "Produto1", 10.0));
}

// Somente preco negativo
TEST(CONSTRUTOR_PRODUTO, PRECO_NEGATIVO) {
    ASSERT_THROW(Produto(1, "Produto1", -10.0), string);
}

// Somente nome vazio
TEST(CONSTRUTOR_PRODUTO, NOME_VAZIO) {
    ASSERT_THROW(Produto(1, "", 10.0), string);
}

// Somente id negativo
TEST(CONSTRUTOR_PRODUTO, ID_NEGATIVO) {
    ASSERT_THROW(Produto(-1, "Produto1", 10.0), string);
}

// Id negativo, nome vazio e preco negativo
TEST(CONSTRUTOR_PRODUTO, TODOS_ERRADOS) {
    ASSERT_THROW(Produto(-1, "", -10.0), string);
}

// Catalogo::adicionarProduto()
TEST(ADICIONAR_PRODUTO_CATALOGO, NORMAL) {
    Catalogo catalogo;
    Produto produto1(1, "Produto1", 10.0);
    ASSERT_TRUE(catalogo.adicionarProduto(produto1));
}

//Produto com o mesmo id de outro já inserido
TEST(ADICIONAR_PRODUTO_CATALOGO, ID_REPETIDO) {
    Catalogo catalogo;
    Produto produto1(1, "Produto1", 10.0);
    Produto produto2(1, "Produto2", 20.0);
    catalogo.adicionarProduto(produto1);
    ASSERT_FALSE(catalogo.adicionarProduto(produto2));
}

// Catalogo::listarProdutos()
TEST(LISTAR_PRODUTOS, LISTA_VAZIA) {
    Catalogo catalogo;
    ASSERT_TRUE(catalogo.listarProdutos().empty());
}

TEST(LISTAR_PRODUTOS, LISTA_NAO_VAZIA) {
    Catalogo catalogo;
    Produto produto1(1, "Produto1", 10.0), produto2(2, "Produto2", 20.0);
    catalogo.adicionarProduto(produto1);
    catalogo.adicionarProduto(produto2);
    ASSERT_EQ(catalogo.listarProdutos().size(),2);
}

// Catalogo::buscarProdutoPorId()
//Produto procurado no catálogo
TEST(BUSCAR_PRODUTO, PRODUTO_NO_CATALOGO) {
    Catalogo catalogo;
    Produto produto1(1, "Produto1", 10.0);
    catalogo.adicionarProduto(produto1);
    Produto prod = *catalogo.buscarProdutoPorId(1);
    ASSERT_EQ(prod.getId(), 1);
}

//Produto procurado fora do catálogo
TEST(BUSCAR_PRODUTO, PRODUTO_FORA_DO_CATALOGO) {
    Catalogo catalogo;
    auto produtoEncontrado = catalogo.buscarProdutoPorId(99);
    ASSERT_FALSE(produtoEncontrado != catalogo.end());
}

// Pedido::adicionarProduto Tests
TEST(ADICIONAR_PRODUTO_PEDIDO, NORMAL) {
    Pedido pedido({}, "Cliente1");
    Produto produto1(1, "Produto1", 10.0);
    pedido.adicionarProduto(produto1);
    ASSERT_EQ(pedido.calcularTotal(), 10.0);
}

// Adicionar o mesmo produto mais de uma vez
TEST(ADICIONAR_PRODUTO_PEDIDO, MESMO_PRODUTO) {
    Pedido pedido({}, "Cliente1");
    Produto produto1(1, "Produto1", 10.0);
    pedido.adicionarProduto(produto1);
    pedido.adicionarProduto(produto1); // Same ID
    ASSERT_EQ(pedido.calcularTotal(), 20.0);
}

// Pedido::calcularTotal()
//Total menor que 100
TEST(CALCULAR_TOTAL, TOTAL_SEM_DESCONTO) {
    Pedido pedido({}, "Cliente1");
    pedido.adicionarProduto(Produto(1, "Produto1", 10.0));
    pedido.adicionarProduto(Produto(2, "Produto2", 20.0));
    ASSERT_EQ(pedido.calcularTotal(), 30.0);
}

//Total maior que 100
TEST(CALCULAR_TOTAL, TOTAL_COM_DESCONTO) {
    Pedido pedido({}, "Cliente1");
    pedido.adicionarProduto(Produto(1, "Produto1", 60.0));
    pedido.adicionarProduto(Produto(2, "Produto2", 50.0));
    ASSERT_EQ(pedido.calcularTotal(), 99.0);
}

//Produtos com preços muito altos
TEST(CALCULAR_TOTAL, TOTAL_OVERFLOW) { 
    Pedido pedido({}, "Cliente1");
    pedido.adicionarProduto(Produto(1, "Produto1", 10.0));
    pedido.adicionarProduto(Produto(2, "Produto2", std::numeric_limits<float>::max()));
    ASSERT_THROW(pedido.calcularTotal(), const char*);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
