#include "../src/project.h"
#include <fstream>
#include <random>
#include <functional>
#include <chrono>

typedef std::function<void()> testingFunc;
constexpr int MAX_SIZE_MINI = 1e3;
constexpr int MAX_SIZE_FULL = 1e6;
constexpr int STEP_MINI = 1;
constexpr int STEP_FULL = 1e4;
int MAX_SIZE;
int STEP;

double measureTime(testingFunc func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
}

void print_help() {
  std::cout << "Usage: ./Timing [--full_size | --mini]" << std::endl;
  std::cout << "  --full_size: Measures the runtimes for the full range of 10,000 to 1,000,000 products" << std::endl;
  std::cout << "  --mini: Measures the runtimes for the range of 1 to 1,000 products with missing products added" << std::endl;
}

int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  //Output file
  std::ofstream file;
  if (argc == 1 or string(argv[1]) == "--full_size") {
    file.open("runtimes_full.csv");
    MAX_SIZE = MAX_SIZE_FULL;
    STEP = STEP_FULL;
  } else if (string(argv[1]) == "--mini") {
    file.open("runtimes_mini.csv");
    MAX_SIZE = MAX_SIZE_MINI;
    STEP = STEP_MINI;
  }  else if (string(argv[1]) == "--help") {
    print_help();
    return 0;
  } else {
    std::cout << "Invalid argument " << argv[1] << std::endl;
    print_help();
    return 1;
  }

  //Column Headers
  file << "Size,Linear Search,Binary Search\n";

  //Set up Random Number Generation
  std::random_device rd;
  std::mt19937 gen(rd());

  Catalogo catalogo;
  catalogo.reserve(MAX_SIZE);

  int cnt = 1;
  for (int i = STEP; i <= MAX_SIZE; i += STEP) {
    file << i << ", ";
    
    //Add the missing products
    int tmp = i-catalogo.size();
    while (tmp--) catalogo.adicionarProduto(Produto(cnt++, "Produto", 1.0), false);
    
    //Generate random queries (id's between 1 and 1.5 times the maximum id, yielding an expected 33.3% number of queries of non existent id's)
    std::uniform_int_distribution<int> dist(1, i+(i>>1));
    vector<int> queries;
    queries.reserve(100);
    for (int i = 0; i < 100; i++) queries.push_back(dist(gen));
    
    //Measure the runtimes
    std::unique_ptr<SearchStrategy> curr_strat = std::make_unique<LinearSearchStrategy>();
    catalogo.mudarContexto(curr_strat);
    file << measureTime([&catalogo, &queries](){ for (auto &query : queries) catalogo.buscarProdutoPorId(query); }) << ", ";
    curr_strat = std::make_unique<BinarySearchStrategy>();
    catalogo.mudarContexto(curr_strat);
    file << measureTime([&catalogo, &queries](){ for (auto &query : queries) catalogo.buscarProdutoPorId(query); }) << "\n";

    //Log Measurement Status
    std::cout << "Measured sample size " << i << " successfully" << std::endl;
  }
  return 0;
}