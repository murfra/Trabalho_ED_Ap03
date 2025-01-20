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

#include "../include/SparseMatrix.h"

using namespace std;


// Menu das opções do que fazer                      */corrigir comentário depois
void help(){
    cout << "uso: ./sparse_matrix [-h | --help] [filename]" << endl;
}

int main(int argc, char const *argv[])
{
    SparseMatrix A = SparseMatrix(3, 3);

    if (argc > 1) {
        if (string(argv[1]) == "-h" || string(argv[1]) == "--help") help();
        else help();
    }

    A.insert(1, 1, 1);
    /*A.insert(1, 2, 2);*/
    A.insert(1, 3, 3);
    A.insert(2, 1, 4);
    /*A.insert(2, 2, 5);*/
    A.insert(2, 3, 6);
    A.insert(3, 1, 7);
    /*A.insert(3, 2, 8);*/
    A.insert(1, 3, 9);
    A.insert(3, 3, 9);
    A.print();
    cout << A.get(3, 3) << endl;
    //A.print();
    
    return 0;
}
