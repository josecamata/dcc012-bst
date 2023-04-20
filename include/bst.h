#ifndef BST_H__
#define BST_H__

#include <iostream>
#include <stack>

/*
    Implementação: 
    Arvore de busca binária
    Autor: Jose J. Camata
*/


template <typename T>
class BST;

/* 
    Classe BSTNode
      - Classe que representa um nó da árvore de busca binária
      
      A classe BSTNode é uma classe template, ou seja, pode ser usada com qualquer 
      tipo de dado

      A classe possui os seguintes atributos:
        - data: o dado armazenado no nó
        - left: ponteiro para o filho esquerdo
        - right: ponteiro para o filho direito
*/


template<typename T>
class BSTNode
{
    friend class BST<T>;
    public:
        BSTNode(T data);                    // Construtor
        BSTNode(const BSTNode<T>* node);    // Construtor de cópia
        T getData();                        // Retorna o dado armazenado no nó
        BSTNode<T>* getLeft();              // Retorna o filho esquerdo
        BSTNode<T>* getRight();             // Retorna o filho direito
    protected:
        T data;                             // Dado armazenado no nó
        BSTNode<T> *left;                   // Ponteiro para o filho esquerdo
        BSTNode<T> *right;                  // Ponteiro para o filho direito
};

// Implementação da classe BSTNode

template<typename T>
BSTNode<T>::BSTNode(T data):data(data),left(nullptr),right(nullptr)
{ }

template<typename T>
BSTNode<T>::BSTNode(const BSTNode<T>* node):data(node->data),left(node->left),right(node->right)
{ }

template<typename T>
T BSTNode<T>::getData()
{
    return this->data;
}

template <typename T>
BSTNode<T>* BSTNode<T>::getLeft()
{
    return this->left;
}

template <typename T>
BSTNode<T>* BSTNode<T>::getRight()
{
    return this->right;
}

/*
    Classe BST
      - Classe que representa uma árvore de busca binária

      A classe BST é uma classe template, ou seja, pode ser usada com qualquer 
      tipo de dado

      A classe possui os seguintes atributos:
        - root: ponteiro para a raiz da árvore

*/


template <typename T>
class BST
{
    public:
        BST();                        // Construtor
        BSTNode<T>* insert(T data);   // Insere um dado na árvore
        void        remove(T data);   // Remove um dado da árvore
        BSTNode<T>* search(T data);   // Busca um dado na árvore

        void print();                 // Imprime a árvore em formato de árvore
        void print_inorder();         // Imprime a árvore em ordem
        void print_preorder();        // Imprime a árvore em pré-ordem

        ~BST();                       // Destrutor

    private:
        BSTNode<T> *root;             // Ponteiro para a raiz da árvore

        // Métodos auxiliares
        void print(BSTNode<T>* node, const std::string& prefix, bool isLeft);
        void clear(BSTNode<T> *node);
};

// Implementação da classe BST

template <typename T>
BST<T>::BST():root(nullptr)
{ }


// Inserção de um dado na árvore
// Etapas:
// 1. Se a árvore estiver vazia, insere o dado na raiz
// 2. Se a árvore não estiver vazia, percorre a árvore até encontrar um nó folha
// 3. Insere o dado no nó folha
template <typename T>
BSTNode<T>* BST<T>::insert(T data)
{
    BSTNode<T>* new_node = new BSTNode<T>(data);
    if (this->root == nullptr)
    {
        this->root = new_node;
        return this->root;
    }

    BSTNode<T> *current = this->root;
    BSTNode<T> *parent  = nullptr;
    while (current != nullptr)
    {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (data < parent->data)
        parent->left = new_node;
    else
        parent->right = new_node;

    return new_node;
}

//Remoção de um dado da árvore
// Etapas:
// 1. Busca o dado na árvore
// 2. Se o dado não estiver na árvore, retorna
// 3. Se o dado estiver na árvore, remove o nó
// 4. Se o nó a ser removido for um nó folha, basta remover o nó
// 5. Se o nó a ser removido tiver apenas um filho, basta substituir o nó pelo filho
// 6. Se o nó a ser removido tiver dois filhos, basta substituir o nó pelo sucessor

template <typename T>
void BST<T>::remove(T data)
{
    // Passo 1:
    BSTNode<T> *current = this->root;
    BSTNode<T> *parent  = nullptr;
    while (current != nullptr)
    {
        if (data == current->data)
            break;
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    // Passo 2
    if (current == nullptr)
        return;

    // Passo 4
    if (current->left == nullptr && current->right == nullptr)
    {
        if (parent == nullptr)
            this->root = nullptr;
        else if (parent->left == current)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete current;
    } // Passo 5
    else if (current->left == nullptr || current->right == nullptr)
    {
        BSTNode<T> *child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr)
            this->root = child;
        else if (parent->left == current)
            parent->left = child;
        else
            parent->right = child;
        delete current;
    }
    else
    {
        // Passo 6
        BSTNode<T> *parent_of_successor = current;
        BSTNode<T> *successor = current->right;
        while (successor->left != nullptr)
        {
            parent_of_successor = successor;
            successor = successor->left;
        }
        current->data = successor->data;
        if (parent_of_successor->left == successor)
            parent_of_successor->left = successor->right;
        else
            parent_of_successor->right = successor->right;
        delete successor;
    }
}


// Busca de um dado na árvore
// Etapas:
// 1. Se a árvore estiver vazia, retorna nullptr
// 2. Se a árvore não estiver vazia, percorre a árvore até encontrar o dado
// 3. Se o dado não estiver na árvore, retorna nullptr
// 4. Se o dado estiver na árvore, retorna o nó que contém o dado
template <typename T>
BSTNode<T>* BST<T>::search(T data)
{
    BSTNode<T> *current = this->root;
    while (current != nullptr)
    {
        if (data == current->data)
            return current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

template<typename T>
void BST<T>::print()
{
    print(this->root, "", false);
}


// Imprime a árvore em ordem
// Implementação usando uma pilha para simular a recursão
template <typename T>
void BST<T>::print_inorder()
{
    std::stack<BSTNode<T>*> stack;
    BSTNode<T> *current = this->root;
    while (current != nullptr || !stack.empty())
    {
        while (current != nullptr)
        {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        std::cout << current->data << " ";
        current = current->right;
    }
    std::cout << std::endl;
}

template <typename T>
void BST<T>::print_preorder()
{
    std::stack<BSTNode<T>*> stack;
    BSTNode<T> *current = this->root;
    while (current != nullptr || !stack.empty())
    {
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        current = current->right;
    }
    std::cout << std::endl;
}

template <typename T>
void BST<T>::clear(BSTNode<T> *node)
{
    if (node == nullptr)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
BST<T>::~BST()
{
    clear(this->root);
}

template <typename T>
void BST<T>::print(BSTNode<T>* node, const std::string& prefix, bool isLeft)
{
    if(node == nullptr)
        return;
    
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──" );

    // print the value of the node
    std::cout <<"["<<node->data<<"]" << std::endl;

    print(node->left , prefix + (isLeft ? "│   " : "    "), true);
    print(node->right, prefix + (isLeft ? "│   " : "    "), false);
}


#endif

