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

    A.insert(2, 2, 7);
    A.insert(3, 3, 8);
    A.insert(1, 1, 5);
    A.insert(1, 2, 4);
    A.print();
    /*A.dbg_print();*/
    
    return 0;
}
