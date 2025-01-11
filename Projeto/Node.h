#ifndef NODE_H
#define NODE_H

//Estrutura do nó para as matrizes esparsas
struct Node
{
    Node *direito;
    Node *abaixo;
    int linha;
    int coluna;
    double valor;

    //Construtor 
    Node(int lin, int col, double value)
    {
        this->linha = lin;
        this->coluna = col;
        this->valor = value;
        this->abaixo = nullptr;
        this->direito = nullptr;
    }

    
};




#endif