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
        BSTNode<T>* getParent();            // Retorna o pai do nó
        BSTNode<T>* getLeft();              // Retorna o filho esquerdo
        BSTNode<T>* getRight();             // Retorna o filho direito
    protected:
        T data;                             // Dado armazenado no nó
        BSTNode<T>* parent;                 // Ponteiro para o pai
        BSTNode<T> *left;                   // Ponteiro para o filho esquerdo
        BSTNode<T> *right;                  // Ponteiro para o filho direito
};

// Implementação da classe BSTNode

template<typename T>
BSTNode<T>::BSTNode(T data):data(data),parent(nullptr), left(nullptr),right(nullptr)
{ }

template<typename T>
BSTNode<T>::BSTNode(const BSTNode<T>* node):data(node->data),parent(node->parent),left(node->left),right(node->right)
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

template <typename T>
BSTNode<T>* BSTNode<T>::getParent()
{
    return this->parent;
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
        int         height();         // Obtem a altura da arvore
        int         lenght();         // Obtem o número de nós da árvore
        
        BSTNode<T>* maximum();        // Obtem o valor máximo da árvore
        BSTNode<T>* minimum();        // Obtem o valor mínimo da árvore

        void print();                 // Imprime a árvore em formato de árvore
        void print_inorder();         // Imprime a árvore em ordem
        void print_preorder();        // Imprime a árvore em pré-ordem

        ~BST();                       // Destrutor

    private:
        BSTNode<T> *root;             // Ponteiro para a raiz da árvore

        // Métodos auxiliares
        void print(BSTNode<T>* node, const std::string& prefix, bool isLeft);
        void clear(BSTNode<T> *node);
        BSTNode<T>* successor(BSTNode<T>* node); 

        int height(BSTNode<T>* node);
        int lenght(BSTNode<T>* node);
        BSTNode<T>* minimum(BSTNode<T>* node); // retorna o nó com o menor valor da subárvore cuja raiz é node
        BSTNode<T>* maximum(BSTNode<T>* node); // retorna o nó com o maior valor da subárvore cuja raiz é node
        void transplant(BSTNode<T>* u, BSTNode<T>* v); // substitui a subárvore cuja raiz é u pela subárvore cuja raiz é v
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
    BSTNode<T>* y = nullptr;
    BSTNode<T> *x = this->root;
    BSTNode<T> *z = new BSTNode<T>(data);

    while (x != nullptr)
    {
        y = x;
        if (data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        this->root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    return z;
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
    BSTNode<T> *node = this->search(data);
    if (node == nullptr)
        return;
    if (node->left == nullptr)
        transplant(node, node->right);
    else if (node->right == nullptr)
        transplant(node, node->left);
    else
    {
        BSTNode<T> *y = this->minimum(node->right);
        if (y->parent != node)
        {
            transplant(y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        transplant(node, y);
        y->left = node->left;
        y->left->parent = y;
    }
    delete node;
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
    
    int  h = height(node);

    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──" );

    // print the value of the node
    std::cout <<"["<<node->data<<"]("<<h<<")" << std::endl;

    print(node->left , prefix + (isLeft ? "│   " : "    "), true);
    print(node->right, prefix + (isLeft ? "│   " : "    "), false);
}

template <typename T>
BSTNode<T>* BST<T>::successor(BSTNode<T>* x)
{
    if(x == nullptr)
        return nullptr;
    if(x->right != nullptr)
        return minimum(x->right);

    BSTNode<T>* y = x->parent;
    while(y != nullptr && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

template <typename T>
int BST<T>::height(BSTNode<T>* node)
{
    if(node == nullptr)
        return -1;
    return 1 + std::max(height(node->left), height(node->right));
}

template <typename T>
int BST<T>::height()
{
    return height(this->root);
}


template <typename T>
int BST<T>::lenght(BSTNode<T>* node)
{
    if(node == nullptr)
        return 0;
    return 1 + lenght(node->left) + lenght(node->right);
}

template <typename T>
int BST<T>::lenght()
{
    return lenght(this->root);
}


template <typename T>
BSTNode<T>* BST<T>::minimum()
{
    BSTNode<T>* current = this->root;
    while(current->left != nullptr)
        current = current->left;
    return current;
}

template <typename T>
BSTNode<T>* BST<T>::maximum(BSTNode<T>* node)
{
    BSTNode<T>* current = node;
    while(current->right != nullptr)
        current = current->right;
    return current;
}

template <typename T>
BSTNode<T>* BST<T>::minimum(BSTNode<T>* node)
{
    BSTNode<T>* current = node;
    while(current->left != nullptr)
        current = current->left;
    return current;
}

template <typename T>
BSTNode<T>* BST<T>::maximum()
{
    return maximum(this->root);
}


template <typename T>
void BST<T>::transplant(BSTNode<T>* u, BSTNode<T>* v)
{
    if(u->parent == nullptr)
        this->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v != nullptr)
        v->parent = u->parent;
}


#endif

