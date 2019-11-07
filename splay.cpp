#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <fstream>
using namespace std;
/*
	OPERACIONES <Busqueda, insercion, extraccion>
	ROTACIONES <Zig Zig (Rotacion doble); Zig Zag(RS-der-izq) ; Zig (Simple D-I)>
	Zig -> X->hijo izq o der de raiz
	Zig Zig  -> x-> es hijo izq de otro hijo izq
				x-> es hijo der de otro hijo der
	Zig Zag  -> x-> es hijo izq de un hijo der
				x-> es hijo der de un hijo izq
	 

	Busqueda: Encuentra el elemento y lo pone en la raiz
				Si nodo se encuentra se pone el ultimo nodo 
				en la raiz

	Insercion: Se ingresa el nodo donde le corresponde
				Luego se pone en la raiz

	Extraccion: Se localiza el nodo y se ubica a la raiz
				Se elimina la raiz y se unen los subarboles

		raiz-> valor menor del arbol derecho o valor mayor del arbol izq
*/
#include <iostream>
using namespace std;
struct Node 
{
	Node* father;
	Node* rightSon;
	Node* leftSon;
	int value;
};

class SplayTree
{
		Node* root;
		bool isEmpty()
		{
			return root == NULL;
		}
		bool search_if_not_empty(int element)
		{
			Node* actualNode = root;

			while (true) 
			{
				if (actualNode->value == element) 
				{
					floation(actualNode);
					return true;
				}
				else if (actualNode->value < element) 
				{
					if (actualNode->rightSon == NULL) 
					{
						floation(actualNode);
						return false;
					}
					else 
					{
						actualNode = actualNode->rightSon;
					}
				}
				else 
				{
					if (actualNode->leftSon == NULL) 
					{
						floation(actualNode);
						return false;
					}
					else 
					{
						actualNode = actualNode->leftSon;
					}
				}

			}
		}
		bool remove_if_not_empty(int elem)
		{
			Node* actualNode = root;
			while (true)
			{

				if (actualNode->value == elem) 
				{
					return remove_node(actualNode);
				}
				else if (actualNode->value < elem)
				{
					if (actualNode->rightSon == NULL)
					{
						floation(actualNode);
						return false;
					}
					else
					{
						actualNode = actualNode->rightSon;
					}
				}
				else
				{
					if (actualNode->leftSon == NULL)
					{
						floation(actualNode);
						return false;
					}
					else
					{
						actualNode = actualNode->leftSon;
					}
				}
			}
		}
		void get_biggest(Node* &actualNode)
		{
			actualNode = root->leftSon;

			while (actualNode->rightSon != NULL)
			{
				actualNode = actualNode->rightSon;
			}
		}

		
		bool insert_if_empty(int element)
		{
			root = new  Node;
			root->rightSon = NULL;
			root->leftSon = NULL;
			root->father = NULL;
			root->value = element;
			return true;
		}
		bool insert_if_not_empty(int element)
		{
			Node* actualNode;
			actualNode = root;
			while (true)
			{
				if (actualNode->value == element) 
				{
					floation(actualNode);
					return false;
				}
				else if (actualNode->value < element) 
				{
					if (study_right_son(actualNode, element)) 
						return true;
				}
				else
				{
					if (study_left_son(actualNode, element)) 
						return true;
				}
			}
		}

		bool study_right_son(Node* &actualNode, int element)
		{
			if (actualNode->rightSon == NULL)
			{
				insert_to_right_son(actualNode, element);
				return true;
			}
			actualNode = actualNode->rightSon;
			return false;
		}
		bool study_left_son(Node* &actualNode, int element)
		{
			if (actualNode->leftSon == NULL)
			{
				insert_to_left_son(actualNode, element);
				return true;
			}
			actualNode = actualNode->leftSon;
			return false;
		}
		void insert_to_right_son(Node* &actualNode, int element)
		{
			actualNode->rightSon = new Node;
			actualNode->rightSon->rightSon = NULL;
			actualNode->rightSon->leftSon = NULL;
			actualNode->rightSon->father = actualNode;
			actualNode->rightSon->value = element;
			floation(actualNode->rightSon);
		}
		void insert_to_left_son(Node* &actualNode, int element)
		{
			actualNode->leftSon = new Node;
			actualNode->leftSon->rightSon = NULL;
			actualNode->leftSon->leftSon = NULL;
			actualNode->leftSon->father = actualNode;
			actualNode->leftSon->value = element;
			floation(actualNode->leftSon);
		}
		void updateParents(Node* &n, Node* &aux)
		{
			aux = n->father;
			n->father = n->father->father;
			aux->father = n;
		}
		void updateGrandpa(Node* &n, Node* &aux)
		{	
			if (n->father != NULL)
			{
				if (n->father->rightSon == aux)
				{
					n->father->rightSon = n;
				}
				else
				{
					n->father->leftSon = n;
				}
			}
		}
		void L(Node* n)
		{
			Node* aux;
			updateParents(n, aux);
			aux->rightSon = n->leftSon;
			if (n->leftSon != NULL)
			{
				aux->rightSon->father = aux;
			}
			n->leftSon = aux;
			updateGrandpa(n, aux);
		}
		void R(Node* n)
		{
			Node* aux;
			updateParents(n, aux);
			aux->leftSon = n->rightSon;
			if (aux->leftSon != NULL)
			{
				aux->leftSon->father = aux;
			}
			n->rightSon = aux;
			updateGrandpa(n, aux);
		}
		bool rotate_if_father(Node* &actualNode)
		{
			if (actualNode->father->rightSon == actualNode)
			{
				L(actualNode);
				root = actualNode;
				return true;
			}
			else if (actualNode->father->leftSon == actualNode)
			{
				R(actualNode);
				root = actualNode;
				return true;
			}
			return false;
		}
		void rotate_if_grandpa(Node* &actualNode)
		{
			bool entered = false;
			if (actualNode->father->father->leftSon != NULL) 
			{
				if (actualNode->father->father->leftSon->leftSon == actualNode) {
					R(actualNode->father);
					R(actualNode);
					entered = true;
				}
				else if (actualNode->father->father->leftSon->rightSon == actualNode)
				{
					L(actualNode);
					R(actualNode);
					entered = true;
				}
			}
			if (!entered && actualNode->father->father->rightSon != NULL) 
			{
				if (actualNode->father->father->rightSon->rightSon == actualNode)
				{
					L(actualNode->father);
					L(actualNode);
				}
				else if (actualNode->father->father->rightSon->leftSon == actualNode)
				{
					R(actualNode);
					L(actualNode);
				}
			}
		}
		void floation(Node* n)
		{

			Node* actualNode = n;
			while (true)
			{
				if (actualNode->father != NULL && actualNode->father->father != NULL)
				{
					rotate_if_grandpa(actualNode);
				}
				else if (actualNode->father != NULL)
				{
					if (rotate_if_father(actualNode)) break;
				}
				else
				{
					root = actualNode;
					break;
				}
			}
		}
	public:
		SplayTree()
		{
			root=NULL;
		}
		bool remove_node(Node* &actualNode)
		{
			floation(actualNode);
			if (root->leftSon == NULL)
			{
				if (root->rightSon != NULL)	root->rightSon->father = NULL;
				root = root->rightSon;
				return true;
			}	
			get_biggest(actualNode);
			if (root->rightSon != NULL)
			{
				actualNode->rightSon = root->rightSon;
				root->rightSon->father = actualNode;
			}
			root = root->leftSon;
			root->father = NULL;
			
			return true;
		}
		bool remove(int elem)
		{
			if (isEmpty()) 
				return false;
			return remove_if_not_empty(elem);
		}
		bool search(int elem)
		{
			if (isEmpty()) 
				return false;
			return search_if_not_empty(elem);	
		}
		bool insert(int element)
		{
		if (isEmpty()) 
			return insert_if_empty(element);
		return insert_if_not_empty(element);
		}

		void print_dot_null(int value, int nullcount, FILE* stream)
		{
    		fprintf(stream, "    null%d [style=invisible][fontcolor=white];\n", nullcount);
		}
		void print_dot_aux(Node* node, FILE* stream)
		{
    		static int nullcount = 0;

		    if (node->leftSon)
    		{
        		fprintf(stream, "    %d -> %d;\n", node->value, node->leftSon->value);
        		print_dot_aux(node->leftSon, stream);
    		}
    		else
        		print_dot_null(node->value, nullcount++, stream);

    		if (node->rightSon)
    		{
        		fprintf(stream, "    %d -> %d;\n", node->value, node->rightSon->value);
        		print_dot_aux(node->rightSon, stream);
    		}
    		else
        		print_dot_null(node->value, nullcount++, stream);
		}
		void print_dot(Node* tree, FILE* stream)
		{
    		fprintf(stream, "digraph Splay {\n");
    		if (!tree)
        		fprintf(stream, "\n");
    		else if (!tree->rightSon && !tree->leftSon)
        		fprintf(stream, "    %d;\n", tree->value);
    		else
        		print_dot_aux(tree, stream);
    		fprintf(stream, "}\n");
		}
		void print_n()
		{
    		FILE * pFile;
    		pFile = fopen ("archivo.dot","w+");
    		print_dot(root,pFile);
    		fclose (pFile);
		}
};

void ejecutar()
{
    const char* comando="dot -Tpng archivo.dot -o grafico.png";
    system(comando);
}

int main(int argc, char const *argv[])
{
	SplayTree s;
	s.insert(1);
	s.insert(2);
	s.insert(31);
	s.insert(100);
	s.search(100);
	s.insert(20);
	s.insert(10);
	s.insert(5);
	s.print_n();
	ejecutar();
	return 0;
}
