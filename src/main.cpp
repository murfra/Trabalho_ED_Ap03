/*
 * Autores:
 * - Carlos Oliveira (Matrícula: 566429)
 * - Murilo Fragoso (Matrícula: 570701)
 *
 * Descrição:
 * Esse código aplica conceitos de listas simplesmente encadeadas para
 * implementar matrizes esparsas.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

#include "../include/SparseMatrix.h"

const char* user = std::getenv(
    #if defined(_WIN32)
        "USERNAME" // No Windows
    #else
        "USER" // Em sistemas UNIX/Linux
    #endif
    );

    
using namespace std;

void readSparseMatrix(SparseMatrix& m, string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int lin, col, i, j;
        double v;

        /*cout << m << endl;*/
        file >> lin >> col;
        m = SparseMatrix(lin, col);

        m.insert(1, 1, 1);
        m.insert(4, 4, 4);
        /*while (file >> i >> j >> v) {*/
        /*    m.insert(i, j, v);*/
        /*}*/
        /*cout << "Ok" << endl;*/
        /*m.print(); // lembrar de apagar*/
    }
}

//Função que realiza a operação de soma
//de duas matrizes A e B e retorna uma
//matriz C como o resultado da soma
SparseMatrix* sum(SparseMatrix& A, SparseMatrix& B) {
    if(A.getCols() == B.getCols() && A.getLines() == B.getLines()){
        SparseMatrix* C = new SparseMatrix(A.getLines(), A.getCols());
        
        for(int i = 1; i <= C->getLines(); i++){
            for (int j = 1; j <= C->getCols(); j++)
            {
                C->insert(i, j, (A.get(i, j) + B.get(i, j)));
            }
        }

        return C;
    }

    else{
        cout << "Não é possível somar matrizes de dimensões distintas ;(" 
        << "Só é possível caso seja 2x2, 3x3 e por assim vai..." << endl;
        return new SparseMatrix();
    }
}

SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B) {
}


void displayMenu() {
    cout << setfill('=') << setw(18) << "" << endl;
    cout << "Olá, ";
    if (user)
    {
      cout << "Olá, " << user << "!";  
    }
    else{
        cout << "Olá!"; 
    }
    
    cout << " Em que posso te ajudar?" << endl;
    cout << setfill('-') << setw(18) << "" << endl;
    cout << "[1] Criar matriz"<< endl;
    cout << "[2] Somar matrizes"<< endl;
    cout << "[3] Multiplicar matrizes"<< endl;
    cout << "[4] Mais comandos" << endl;
}

// Menu de ajuda
void help() {
    cout << "uso:\n" << setw(2) << "" <<
    "./sparse_matrix [-h | --help] [-f | --file] <arquivo>\n";

    cout << "\n" << setw(2) << "" << "-h, --help" << std::setw(14) << "";
    cout << "Mostra opções de ajuda\n";
}

int main(int argc, char const *argv[])
{   
    

    SparseMatrix A = SparseMatrix(3, 3);
    SparseMatrix B = SparseMatrix(3,3);

    // leitura do arquivo
    if (argc == 1 || string(argv[1]) == "-h" || string(argv[1]) == "--help") help();
    // else if (string(argv[1]) == "-f" || string(argv[1]) == "--file") {
    //     cout << "Arquivo carregado!" << endl;
    //     readSparseMatrix(B, argv[2]);
    // }
    else displayMenu();

    // B.print();
    A.insert(1, 3, 3);
    B.insert(1, 1, 1);
    B.insert(1, 3, 10);
    A.print();
    cout << "-----------------" << endl;
    B.print();
    cout << "-----------------" << endl;
    SparseMatrix *C = sum(A, B);
    C->print();
    
    return 0;
}
