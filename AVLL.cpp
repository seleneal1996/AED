#include <iostream>
#include <stdio.h>
#include "time.h"
#include <cstdlib>

using namespace std;

template<class Comparable>
class AVL{
	private:
		struct AvlNode
		{
		Comparable element;
		AvlNode *left;
		AvlNode *right;
		int height;
	
		AvlNode(const Comparable & ele,AvlNode *lt,AvlNode *rt,int h=0)
		:element{ele},left{lt},right{rt},height{h}{}
	
		AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
		:element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
		};
		
		AvlNode *root;
		
		//ENCUENTRA EL MINIMO
		AvlNode * findMin( AvlNode *t ) const
 		{
 			if(t==nullptr)
 				return nullptr;
 			if(t->left== nullptr)
 				return t;
 			return findMin(t->left);
		}
		//FUNCION PARA INSERTAR
		void insert( const Comparable & x, AvlNode * & t )
		{
			if( t == nullptr )
				t =	new AvlNode{ x, nullptr, nullptr };
			else if( x < t->element )
				insert( x, t->left );
			else if( t->element < x )
 				insert( x, t->right );
//			cout<<x<<endl;
			balance( t );
		}
		//IMPRESION EN PRE-ORDEN
		void print_pre(AvlNode *p)
		{
    		if(!p)return;
    		cout<<p->element<<" ";
    		print_pre(p->left);
    		print_pre(p->right);

		}
		//FUNCION PARA ELIMINAR
		void remove( const Comparable & x, AvlNode * & t )
		{
			if( t == nullptr )
				return; // Item not found; do nothing
			if( x < t->element )
				remove( x, t->left );
			else if( t->element < x )
				remove( x, t->right );
			else if( t->left != nullptr && t->right != nullptr ) // Two children
			{
				t->element = findMin( t->right )->element;
				remove( t->element, t->right );
			}
			else
			{
				AvlNode *oldNode = t;
				t = ( t->left != nullptr ) ? t->left : t->right;
				delete oldNode;
			}
			balance(t);
		}
	public:
		//METODO DE INSERCION 
		void insert(const Comparable x){
			insert(x,root);
		}
		//METODO PARA CALCULAR EL PESO DE UN NODO
		int height(AvlNode *t) const{
			return t == nullptr ? -1 : t->height;
		}

		static const int ALLOWED_IMBALANCE = 1;
		
		//BALANCEO
		void balance( AvlNode * & t )
		{
			if( t == nullptr )
				return;
			if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
				if( height( t->left->left ) >= height( t->left->right ) )
					rotateWithLeftChild( t );
				else
					doubleWithLeftChild( t );
			else
			if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
				if( height( t->right->right ) >= height( t->right->left ) )
					rotateWithRightChild( t );
				else
					doubleWithRightChild( t );
				
				
			t->height = max( height( t->left ), height( t->right ) ) + 1; 
		}
		
		
		//ROTACION SIMPLE 
		void rotateWithLeftChild( AvlNode * & k2){
			AvlNode *k1 = k2->left;
			k2->left = k1->right;
			k1->right = k2;
			k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
			k1->height = max( height( k1->left ), k2->height ) + 1;
			k2 = k1;
		}
		
		//ROTACION SIMPLE  
		void rotateWithRightChild(AvlNode *& k2){
			AvlNode *k1 = k2->right;
			k2->right= k1->left;
			k1->left=k2;
			k2->height= max( height( k2->left ), height( k2->right ) ) + 1;
			k1->height= max( height( k1->right ), k2->height ) + 1;
			k2=k1;
		}
		//ROTACION DOBLE (ID)
		void doubleWithLeftChild( AvlNode * & k3 )
		{
			rotateWithRightChild( k3->left );
			rotateWithLeftChild( k3 );
		}
		
		//ROTACION DOBLE (DI)
		void doubleWithRightChild(AvlNode *& k3){
			rotateWithLeftChild(k3->right);
			rotateWithRightChild(k3);
		}
		//IMPRIMIR EN PRE-ORDEN
		void print_pre()
		{    		 
			this->print_pre(root);
		}
		
		//FUNCION REMOVE
		void remove(const Comparable &x){
			this->remove(x,root);
		}
		///CODIGO PARA MOSTRAR EL AVL EN UNA IMAGEN
		void print_dot_null(Comparable dato, int nullcount, FILE* stream)
		{
    		fprintf(stream, "    null%d [style=dotted][fontcolor=white];\n", nullcount);
    		fprintf(stream, "    %d -> null%d;\n", dato, nullcount);
		}
		void print_dot_aux(AvlNode* node, FILE* stream)
		{
    		static int nullcount = 0;

		    if (node->left)
    		{
        		fprintf(stream, "    %d -> %d;\n", node->element, node->left->element);
        		print_dot_aux(node->left, stream);
      		//  cout<<"imprimiendo"<<endl;
    		}
    		else
        		print_dot_null(node->element, nullcount++, stream);

    		if (node->right)
    		{
        		fprintf(stream, "    %d -> %d;\n", node->element, node->right->element);
        		print_dot_aux(node->right, stream);
       			// cout<<"imprimiendo"<<endl;
    		}
    		else
        		print_dot_null(node->element, nullcount++, stream);
		}
		void print_dot(AvlNode* tree, FILE* stream)
		{
    		fprintf(stream, "digraph BST {\n");
    		//fprintf(stream, "    node [fontname=\"Arial\"];\n");

    		if (!tree)
        		fprintf(stream, "\n");
    		else if (!tree->right && !tree->left)
        		fprintf(stream, "    %d;\n", tree->element);
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




int main()
{
	AVL<int> a;
	int x,i;
	i=0;
	srand(time(NULL));
	a.insert(50);
	a.insert(100);
	a.insert(200);
	a.insert(300);
	a.insert(150);
	a.insert(175);
	a.insert(180);
	a.remove(50);	
	a.print_pre();
	a.print_n();
	ejecutar();
	
	
}

