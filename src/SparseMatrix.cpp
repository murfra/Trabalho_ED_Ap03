#include "../include/SparseMatrix.h"

#include <iostream>

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n)
{
    if (m <= 0 || m > linhas || n <= 0 || n > colunas) throw std::runtime_error("Invalid line or column");
  
    // Inicilizando nós sentinela para cada linha m e coluna n
    for(int i = m+n; i >= 1; i--)
    {
        if (i > n) // inicilizando as colunas (0, n)
        {
            Node *aux = new Node(0, i-n);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        }
        else // inicilizando as linhas (m, 0);
        {
            Node *aux = new Node(i, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
    }

}

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix()
{
    /*
        [][][][d]
        []()()(^)
        []()()(^)
        []()(<)(^)<-

        Objetivo: precisamos apagar todos os nós não-sentinelas, ou seja, até que o abaixo->linha seja != 0
        verificar se a coluna possui nós abaixo dela, se não apaga o nó, fazendo apontar para outro lugar
    */
    // while (m_head->direito != m_head && m_head->abaixo != m_head) {
    //     Node *aux = m_head;
        
    //     while (aux->direito->coluna != 0) {
    //         if (aux->direito->direito->abaixo->linha == 0) {
    //             Node *temp = aux->direito->direito;
    //             aux->direito = temp->direito;
    //             delete temp;
    //         }
    //         aux = aux->direito;
    //     }

    //     Node *temp = aux->abaixo;
    //     if (aux->abaixo->linha == 0) {
    //         std::cout << "direita: " << '(' << aux->abaixo->direito->linha << ", " << aux->abaixo->direito->coluna
    //         << ") -> " << aux->abaixo->direito->valor << std::endl; 
    //     }
    //     else {
    //         aux->abaixo = temp->abaixo;
    //         std::cout << "deleted: "  << '(' << temp->linha << ", " << temp->coluna << ") -> " << temp->valor << std::endl;
    //         delete temp;
    //     }
    // }
}

void SparseMatrix::insert(int i, int j, double value)
{
    // Teste de verificação de limites para as linhas
    // veja que não podem ser negativas
    
    if (i <= 0 || i > linhas || j <= 0 || j > colunas){
        throw std::runtime_error("Invalid line or column");
    }
    
    else if (value != 0)
    {
        Node *aux = m_head->direito;

        while (aux->coluna != j) aux = aux->direito; // move o aux até a coluna j

        // verifica se já existe //
        if (aux->abaixo->linha == i && aux->abaixo->coluna == j) {
            aux->abaixo->valor = value;
        }
        //
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

double SparseMatrix::get(int i, int j) // precisa ser implementada
{
    //Verifica se os parâmetros i(linha) e j (coluna)
    //estão dentro dos limites
    if (i <= 0 || i > linhas || j <= 0 || j > colunas){
        throw std::runtime_error("Invalid line or column");
    }

    //Cria um ponteiro para Node que
    //recebe m_head
    Node* aux = m_head;
    
    //Percorre até a coluna especificada
    //pelo paramêtro j
    while (aux->coluna != j)
    {
        aux = aux->direito;
    }
    
    //Percorre até a linha especificada
    //pela parâmetro i
    while (aux->linha != i)
    { 
        aux = aux->abaixo;
    } 

    //Por fim, retorna o valor apontado
    //pelo ponteiro para Node ax
    return aux->valor;
}

void SparseMatrix::print() { // acredito que dê pra melhorar
    Node *aux = m_head->abaixo;

    for (int i = 1; i <= linhas; i++)
    {
        Node *temp = aux->direito; // pega o valor direito do aux, seria algo como m_head->abaixo->direito
        std::cout << "[ ";
        for (int j = 1; j <= colunas; j++)
        {
            if (temp->coluna == j) std::cout << temp->valor << " ";
            else std::cout << 0 << " ";

            if (j == temp->coluna) temp = temp->direito;
        }

        aux = aux->abaixo;
        std::cout << ']' << std::endl;
    }
}
