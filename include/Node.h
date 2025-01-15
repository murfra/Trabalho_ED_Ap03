#ifndef NODE_H
#define NODE_H

// Estrutura do nó para as matrizes esparsas
struct Node
{
    Node *direito = this;
    Node *abaixo = this;
    int linha;
    int coluna;
    double valor = 0;

    // Construtor
    Node(int lin, int col) {
        this->linha = lin;
        this->coluna = col;
    }

    // Construtor 
    Node(int lin, int col, double value)
    {
        this->linha = lin;
        this->coluna = col;
        this->valor = value;
    }
};

#endif
