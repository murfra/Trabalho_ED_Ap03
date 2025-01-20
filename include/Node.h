#ifndef NODE_H
#define NODE_H

// Estrutura do nó para as matrizes esparsas
struct Node
{
    int linha;
    int coluna;
    double valor;
    Node *abaixo;
    Node *direito;

    // Construtor
    Node(int lin, int col) : linha(lin), coluna(col), abaixo(this), direito(this) {}

    // Construtor 
    Node(int lin, int col, double value) : Node(lin, col) {
        this->valor = value;
    }
};

#endif
