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

#include "../include/SparseMatrix.h"

using namespace std;


// Menu das opções do que fazer                      */corrigir comentário depois
void menu(){
    
}

int main(int argc, char const *argv[])
{
    SparseMatrix A = SparseMatrix(3, 3);
    if (argc > 1) {
        cout << argv[1] << endl;
    }
    else {
        cout << "uso: ./sparse_matrix [-h | --help] [filename]" << endl;
    }

    A.print();

    
    return 0;
}
