/*
 * Autores:
 * - Carlos Oliveira (Matrícula: 566429)
 * - Murilo Fragoso (Matrícula: 570701)
 *
 * Descrição:
 * Esse código aplica conceitos de listas simplesmente encadeadas para
 * implementar matrizes esparsas.
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/SparseMatrix.h"

using namespace std;

// Função responsável por ler um arquivo e retornar
// uma SparseMatrix conforme está no arquivo lido
void readSparseMatrix(SparseMatrix& m, string filename) {
  ifstream file(filename);

  if (!file.is_open()) {
    throw runtime_error("Arquivo inválido ou não encontrado!");
  }

  int lin, col, i, j;
  double v;

  file >> lin >> col;
  SparseMatrix aux = SparseMatrix(lin, col);

  while (file >> i >> j >> v) aux.insert(i, j, v);

  m = SparseMatrix(aux);

}

// Função que realiza a operação de soma
// de duas matrizes A e B e retorna uma
// matriz C como o resultado da soma
SparseMatrix *sum(SparseMatrix &A, SparseMatrix &B) {
  if (A.getCols() == B.getCols() && A.getLines() == B.getLines()) {
    SparseMatrix *C = new SparseMatrix(A.getLines(), A.getCols());

    for (int i = 1; i <= C->getLines(); i++) {
      for (int j = 1; j <= C->getCols(); j++) {
        C->insert(i, j, (A.get(i, j) + B.get(i, j)));
      }
    }

    return C;
  } else {
    cout << "Não é possível somar matrizes de dimensões distintas ;("
         << "Só é possível caso seja 2x2, 3x3 e por assim vai..." << endl;
    return new SparseMatrix();
  }
}

SparseMatrix *multiply(SparseMatrix &A, SparseMatrix &B) {
  if (A.getCols() != B.getLines()) {
    cout << "Não é possível multiplicar as matrizes ;("
         << "O número de colunas da matriz A deve ser igual ao número de "
            "linhas da matriz B."
         << endl;
    return nullptr;
  }

  SparseMatrix *C = new SparseMatrix(A.getLines(), B.getCols());

  for (int i = 1; i <= A.getLines(); i++) {
    for (int j = 1; j <= B.getCols(); j++) {
      double soma = 0;

      for (int k = 1; k <= A.getCols(); k++) {
        soma += A.get(i, k) * B.get(k, j);
      }

      C->insert(i, j, soma);
    }
  }

  return C;
}

void displayMenu() {
  cout << "Olá, seja bem-vindo(a)!\n";
  cout << "ATENÇÃO: Caso precise ver os comandos digite: !comandos" << endl;
}

// Menu de ajuda
void help() {
  cout << "uso:\n"
       << setw(2) << ""
       << "./sparse_matrix [-h | --help] [-f | --file=ARQUIVO]\n";

  cout << "\n" << setw(2) << "" << "-h, --help" << setw(14) << "";
  cout << "Mostra opções de ajuda\n";
  cout << "\n" << setw(2) << "" << "-f, --file=ARQUIVO" << setw(14) << "";
  cout << "Lê um ARQUIVO que especifica uma matriz esparsa" << endl;
}

void comandos() {
  cout << "\nComandos disponíveis:\n"
       << setw(2) << "" << "!comandos - Exibe esta lista de comandos\n"
       << setw(2) << ""
       << "create i j - Cria uma matriz esparsa com i linhas e j colunas\n"
       << setw(2) << ""
       << "size i - Exibe o número de elementos da matriz de índice i\n"
       << setw(2) << ""
       << "insert i j v l - Insere o valor v na célula (i, j) da matriz de "
          "índice l\n"
       << setw(2) << ""
       << "get i j l - Obtém o valor na célula (i, j) da matriz de índice l\n"
       << setw(2) << "" << "print l - Exibe a matriz de índice l\n"
       << setw(2) << ""
       << "sum a b - Soma as matrizes de índices a e b e armazena o resultado "
          "no vetor\n"
       << setw(2) << ""
       << "multiply a b - Multiplica as matrizes de índices a e b e armazena o "
          "resultado no vetor\n"
       << setw(2) << ""
       << "show - Exibe todas as matrizes armazenadas no vetor\n"
       << setw(2) << "" << "exit - Sai do programa e libera a mémoria\n";
}

int main(int argc, char const *argv[]) {
  string arg1 = string(argv[1]);

  vector<SparseMatrix> matrizes;

  // leitura do arquivo
  if (argc == 1 || arg1 == "-h" || arg1 == "--help")
    help();
  else if (arg1 == "-f" || arg1 == "--file") {
    matrizes.push_back(SparseMatrix(1, 1));
    cout << "Arquivo carregado!" << endl;
    readSparseMatrix(matrizes[0], argv[2]);
    matrizes[0].print();
  } else
    displayMenu();

  while (true) {
    string comando, token;
    getline(cin, comando);
    stringstream ss{comando};
    ss >> token;

    cout << "$" << ss.str() << endl;
    // comandos disponíveis
    if (token == "!comandos") {
      comandos();
    }

    // exit
    if (token == "exit") {
      matrizes.clear();
      break;
    }

    // create m, n
    else if (token == "create") {
      int m, n;
      ss >> m >> n;
      matrizes.push_back(SparseMatrix(m, n));
    }

    // size
    else if (token == "size") {
      int i;
      ss >> i;
      cout << "size matrix " << i << ": " << matrizes[i].size();
    }

    // insert i, j, v(valor) l
    else if (token == "insert") {
      int i, j, l;
      double v;
      ss >> i >> j >> v >> l;
      matrizes[l].insert(i, j, v);
    }

    // get da célula i, j
    else if (token == "get") {
      int i, j, l;
      ss >> i >> j >> l;
      cout << "valor na célula (" << i << ", " << j
           << ") é: " << matrizes[l].get(i, j) << endl;
    }

    // print matriz i
    else if (token == "print") {
      int l;
      ss >> l;
      matrizes[l].print();
    }

    // somar matrizes A e B
    else if (token == "sum") {
      int a, b;
      ss >> a >> b;
      SparseMatrix *resultado = sum(matrizes[a], matrizes[b]);
      if (resultado != nullptr) {
        matrizes.push_back(*resultado);
        delete resultado;
      }
    }

    // multiplicar matrizes A e B
    else if (token == "multiply") {
      int a, b;
      ss >> a >> b;
      SparseMatrix *resultado = multiply(matrizes[a], matrizes[b]);
      if (resultado != nullptr) {
        matrizes.push_back(*resultado);
        delete resultado;
      }
    }

    // exibir matrizes
    else if (token == "show") {
      auto index = 0;
      for (auto &matrix : matrizes) {
        cout << "matriz[" << index++ << "] :" << endl;
        matrix.print();
      }
    }

    else {
      cout << "O comando que você inseriu é inválido/ não existe ;( " << endl;
    }
  }

  return 0;
}
