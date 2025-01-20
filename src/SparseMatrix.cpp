#include "../include/SparseMatrix.h"

#include <iostream>
#include <stdexcept>

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n) {
    if (m <= 0 || m > linhas || n <= 0 || n > colunas) throw std::out_of_range("Invalid line or column");
  
    // Inicilizando nós sentinela para cada linha m e coluna n
    for(int i = m+n; i >= 1; i--) {
        if (i > n) { // inicilizando as colunas (0, n)
            Node *aux = new Node(0, i-n);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        }
        else { // inicilizando as linhas (m, 0);
            Node *aux = new Node(i, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
    }
}

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix() {
    //Cara, a ideia é usar como condição se o final do loop é igual a cabeça
    //fica mais ou menos assim
    //  col
    //  |
    //  v
    //[][][][]
    //[]()()() atual recebe o col->abaixo(1,1)
    //[]()()()
    //[]()()()
    //
    // dai o temp recebe o atual só pro atual poder receber o atual->abaixo (se deslocar)
    // apaga o temp que aponta para o (1,1) {antiga posição do atual}
    // dai faz algo similar só que com as colunas sentinelas
    // por último é que apaga a coluna da cabeça

    // Libera os nós em cada coluna

    // Começa de (0, 1) 
    Node* col = m_head->direito;
    while (col != m_head) // Anda as colunas
    {
        Node* atual = col->abaixo; // Primeiro nó na coluna (1,1)
        while (atual != col) // Percorre todos os nós na coluna
        {
            
            Node* temp = atual;
            atual = atual->abaixo;
            delete temp; // Libera o nó atual
        }
        

        Node* temp = col;
        col = col->direito;
        delete temp; // Libera o nó sentinela da coluna
    }

    // Libera os nós sentinelas das linhas
    Node* linha = m_head->abaixo; // Começa na primeira linha (1, 0)
    while (linha != m_head) // Anda as linhas
    {
        Node* temp = linha;
        linha = linha->abaixo;
        delete temp; // Libera o nó sentinela da linha
    }

    delete m_head;
}

void SparseMatrix::insert(int i, int j, double value) {
    // Teste de verificação de limites para as linhas
    // veja que não podem ser negativas
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }
    
    else if (value != 0) {
        Node *aux = m_head->direito;

        while (aux->coluna != j) aux = aux->direito; // move o aux até a coluna j
        while (aux->abaixo->linha != 0 && aux->abaixo->linha != i) aux = aux->abaixo;

        // verifica se já existe uma célula na posição i, j
        if (aux->abaixo->linha == i) aux->abaixo->valor = value;
        else {
            Node *temp = new Node(i, j, value);
            temp->abaixo = aux->abaixo;
            aux->abaixo = temp;

            aux = m_head->abaixo; // redefine aux para começar da linha 1, coluna 0
            while (aux->linha != i) aux = aux->abaixo; // move o aux até a linha i
            
            // move até o último "direito", até a última coluna, no caso
            while (aux->direito->coluna != 0) aux = aux->direito;

            temp->direito = aux->direito; // faz temp apontar para onde aux apontava (o começo da linha)
            aux->direito = temp; // aponta o direito para o temp
            
        }
    }
}

// Possível erro: caso em que i e j não estão definidos na matriz
double SparseMatrix::get(int i, int j) {
    //Verifica se os parâmetros i(linha) e j (coluna)
    //estão dentro dos limites
    if (i <= 0 || i > linhas || j <= 0 || j > colunas)
    {
        throw std::out_of_range("Invalid line or column");
    }

    //Cria um ponteiro para Node que recebe m_head
    Node* aux = m_head;
    
    //Percorre até a coluna especificada pelo paramêtro j
    while (aux->coluna != j) aux = aux->direito;
    
    //Percorre até a linha especificada pelo parâmetro i
    while (aux->linha != i) aux = aux->abaixo;

    //Por fim, retorna o valor apontado pelo ponteiro
    //para Node ax
    return aux->valor;
}

void SparseMatrix::print() { // acredito que dê pra melhorar
    Node *aux = m_head->abaixo;

    for (int i = 1; i <= linhas; i++) {
        Node *temp = aux->direito; // pega o valor direito do aux, seria algo como m_head->abaixo->direito

        std::cout << "[ ";
        for (int j = 1; j <= colunas; j++) {
            if (temp->coluna == j) std::cout << temp->valor << " ";
            else std::cout << 0 << " ";

            if (j == temp->coluna) temp = temp->direito;
        }
        aux = aux->abaixo;
        std::cout << ']' << std::endl;
    }
}
