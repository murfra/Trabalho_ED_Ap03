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

void enfeites1(){
    for (size_t i = 0; i < 18; i++)
    {
        cout << '=';
    }
}

void enfeites2(){
    for (size_t i = 0; i < 18; i++)
    {
        cout << '-';
    }
}

//Função que realiza a operação de soma
//de duas matrizes A e B e retorna uma
//matriz C como o resultado da soma
void Soma(SparseMatrix A, SparseMatrix B){

}

void displayMenu(){
    enfeites1();

    cout << "Olá, meu caro usuário! Em que posso te ajudar?" <<endl;
    enfeites2();
    cout << "(1) Some essas duas matrizes: "<<endl;
    cout << "(2) Multiplique essas duas: "<<endl;

}



// Menu das opções do que fazer                      */corrigir comentário depois
void help(){
    cout << "uso:\n  ./sparse_matrix [-h | --help] [filename]" << endl;
}

int main(int argc, char const *argv[])
{
    SparseMatrix A = SparseMatrix(3, 3);

    if (argc == 1 || string(argv[1]) == "-h" || string(argv[1]) == "--help") help();
    else {
        ifstream file(argv[1]);
        cout << file.is_open() << endl;
    }

    A.insert(1, 3, 3);
    A.insert(1, 3, 10);

    A.insert(2, 3, 1);
    A.insert(2, 3, 7);

    A.insert(3, 3, 1);
    A.insert(3, 3, 4);
    A.insert(3, 3, 9);

    cout << A.get(3, 3) <<endl; // 4
    cout << A.get(1, 3) <<endl; // 10
    cout << A.get(2, 3) <<endl; // 7
    
    A.print();
    //A.print();
    
    return 0;
}
