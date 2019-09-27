#include <iostream>
#include <cstdlib>
using namespace std;
template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root(NULL) {}
    BinarySearchTree( const BinarySearchTree & rhs ) : root(NULL) {makeEmpty();*this = rhs;}

    /**
     * Destructor para el arbol
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    const Comparable & findMin( ) const
    {
        return findMin(root)->element;
    }

    const Comparable & findMax( ) const 
    {
	   return findMax(root)->element;
    }

    bool contains( const Comparable & x ) const 
    {
	   return contains(x, root);
    }

    bool isEmpty( ) const 
    {
	   return root == NULL;
    }

    void printTree( ) const 
    {
	   printTree(root);
	   cout << endl;
    } 

    void makeEmpty( ) 
    {
	   makeEmpty(root);
    }

    void insert( const Comparable & x ) 
    {
	   insert(x, root);
    }

    void remove( const Comparable & x ) 
    {
	   remove(x, root);
    }

    /**
     * A veces es beneficioso proporcionar un clone()método explícito , especialmente para clases polimórficas.
     */
    const BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone( rhs.root );
        }
        return *this;
    }
    

  private:
    struct BinaryNode
    {
       Comparable element;
       BinaryNode *left;
       BinaryNode *right;

       BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
         : element( theElement ), left( lt ), right( rt ) { }
    };

    BinaryNode *root;

    /*
     * Método interno para insertar en un subárbol.
     * x es el elemento a insertar.
     * t es el nodo que arraiga el subárbol.
     * Establecer la nueva raíz del subárbol.
     * (SJS) Tenga en cuenta que este no es un método constante
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {

        if( t == NULL ) 
            t = new BinaryNode( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    /*
     * Método interno para eliminar de un subárbol.
     * x es el elemento a eliminar.
     * t es el nodo que arraiga el subárbol.
     * Establecer la nueva raíz del subárbol.
     * (SJS) Tenga en cuenta que este no es un método constante
     * El libro señala que esto es ineficiente debido a dos
     * pasa. Piensa en cómo corregirías esto.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == NULL )
            return;   // Objeto no encontrado; hacer nada
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != NULL && t->right != NULL ) // Dos hijos
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != NULL ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /*
     * Método interno para encontrar el elemento más pequeño en un subárbol t.
     * Nodo de retorno que contiene el item más pequeño.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
        if( t->left == NULL )
            return t;
        return findMin( t->left );
    }

    /*
     * Método interno para encontrar el elemento más grande en un subárbol t.
     * Nodo de retorno que contiene el item más grande.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != NULL )
            while( t->right != NULL )
                t = t->right;
        return t;
    }

    /*
     * Método interno para probar si un item está en un subárbol.
     * x es el elemento a buscar.
     * t es el nodo que arraiga el subárbol.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    /**
     * Método interno para hacer que el subárbol esté vacío..
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    void printTree( BinaryNode *t ) const 
    {
	// hacer un recorrido en orden
	if (t == NULL)
		return;
	else 
        {
		  printTree(t->left);
		  cout << t->element << ", ";
		  printTree(t->right);
	    }
    } 

    /**
     * Método interno para clonar subárbol.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == NULL )
            return NULL;
 
        return new BinaryNode( t->element, clone( t->left ), clone( t->right ) );
    }
};

int main() {
	BinarySearchTree<int> t1;
	t1.insert(11);
	t1.insert(5);
	t1.insert(3);
	t1.insert(6);
	cout << "Encontrado!" << endl;
	cout << "t1.findMin(): " << t1.findMin() << endl;
	cout << "t1.findMax(): " << t1.findMax() << endl;
	t1.insert(6);
	t1.remove(6);
	if (t1.contains(6))
		cout << "Árbol contiene 6" << endl;
	else
		cout << "El árbol no contiene 6" << endl;

	t1.printTree();
	cout << endl;

	BinarySearchTree<int> t2;
    t2.insert(13);
    t2.insert(5);
    t2.insert(1);
	t2.printTree();
	
}
