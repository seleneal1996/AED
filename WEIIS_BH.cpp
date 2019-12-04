#include<iostream>
#include<vector>
#include <stdexcept>
#include<fstream>
using namespace std;

template <class Comparable>
class BinaryHeap
{
    public:
    BinaryHeap(int capacity =100);
    BinaryHeap(const vector<Comparable> & items):
	array(items.size()),cantidadElementos{items.size()}
	{
		for(int i=0;i<items.size();++i)
		{
			array[i+1]=items[i];
			
		}
		buildHeap();
	}

    bool isEmpty( ) const;
    bool isFull( ) const;
    const Comparable & findMin( ) const;
    void insert( const Comparable & x );
    void inserta(Comparable x);
    void deleteMin( );
    void deleteMin( Comparable & minItem );
    void makeEmpty( );
    void mostrar()
 	{
		for(int i=1;i<=array.size();i++)
		{
			cout<<array[i]<<" ";
		}
		cout<<endl;
	}
	
	//MOSTRANDO EL BINARY HEAP :,V 
	
	/**
	Si 2i <= n entonces A[2i] contiene al hijo izquierdo del
	elemento en A[i] y si 2i + 1 <= n entonces A[2i + 1]
	contiene al hijo derecho de A[i]
	
	
	Si i >= 2 entonces A[i=2] contiene al padre de A[i]
	*/
	
	void print_dot()
    {   
        string text="digraph BHeap{\n";
        for(int i=1;i<this->array.size();i++)
            {
				if(i*2<=this->array.size())
                {
                    text=text+to_string(this->array[i])+" -> "+to_string(this->array[2*i])+";\n";
                }
                
                if((2*i)+1<=this->array.size())
                {
                	text=text+to_string(this->array[i])+" -> "+to_string(this->array[2*i+1])+";\n";
				}
			
                if(i>=2)
                {
					text=text+to_string(this->array[i])+" -> "+to_string(this->array[i/2])+";\n";
				}
            }
        text=text+"}";
        ofstream archivo;  // objeto de la clase ofstream
        archivo.open("binaryHeap.dot");
        archivo <<text;
        archivo.close();    
    }
    
    
    private:
    int cantidadElementos;  
    vector<Comparable> array;        // El arreglo heap 

    void buildHeap( );
    void percolateDown( int hole );

    
};

template <class Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity)
  : cantidadElementos(0), array(capacity + 1)
{
}
/*
Inserta el elemento x en la cola de prioridad, manteniendo el orden de almacenamiento dinámico.
* Se permiten duplicados.
* Lanzar desbordamiento si el contenedor está lleno.

*/
template <class Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & x)
{
    if( isFull( ) )
        throw std::out_of_range("Error!");

                // Percolate up
    int hole = ++cantidadElementos;
    Comparable copy=x;
    array[0]=std::move(copy);
	for(;x<array[hole/2];hole/=2)
	{
		array[hole]=std::move(array[hole/2]);
	}
	array[hole]=std::move(array[0]);
}

template <class Comparable>
void BinaryHeap<Comparable>::inserta(const Comparable x)
{
   inserta(x);
}
/*
* Encuentra el elemento más pequeño en la cola de prioridad.
* Devuelva el elemento más pequeño o arroja Underflow si está vacío.
*/
      
template <class Comparable>
const Comparable & BinaryHeap<Comparable>::findMin( ) const
{
    if( isEmpty( ) )
       throw std::out_of_range("EL heap esta vacio");
    return array[ 1 ];
}
/*Remueve el elemento mas peque de la cola de prioridad o manda trow*/
      
template <class Comparable>
void BinaryHeap<Comparable>::deleteMin( )
{
    if( isEmpty( ) )
        throw std::out_of_range("EL heap esta vacio");
	
    array[1] = array[ cantidadElementos-- ];
    percolateDown( 1 );
}

        /**
         * Remueve el elemento mas peque de la cola de prio 
         * y reemplaza con el minItem. Si esta vacia envia trow.
         */
template <class Comparable>
void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
{
    if(isEmpty())
        throw std::out_of_range("El heap esta vacio");

    minItem = array[1];
    array[1] = array[cantidadElementos--];
    percolateDown(1 );
}

        /**
         * Establece propiedad de orden de almacenamiento dinámico de una
         * disposición arbitraria de los elementos. Se ejecuta en tiempo lineal.
         */
template <class Comparable>
void BinaryHeap<Comparable>::buildHeap( )
{
    for( int i = (cantidadElementos / 2); i > 0; --i )
        percolateDown( i );
}

        /**
         * Prueba si la cola de prioridad está lógicamente vacía.
         * Devuelve verdadero si está vacío, falso de lo contrario.
         */
template <class Comparable>
bool BinaryHeap<Comparable>::isEmpty( ) const
{
    return cantidadElementos == 0;
}

        /**
         *Pruebe si la cola de prioridad está lógicamente llena.
         * Devuelve verdadero si está lleno, falso de lo contrario.
         */
template <class Comparable>
bool BinaryHeap<Comparable>::isFull( ) const
{
    return cantidadElementos == array.size( ) - 1;
}

        /**
         * Hace que la cola de prioridad esté lógicamente vacía.
         */
template <class Comparable>
void BinaryHeap<Comparable>::makeEmpty( )
{
    cantidadElementos = 0;
}


/*
Método interno para filtrarse en el montón.
agujero es el índice en el que comienza el percolado.
*/

template <class Comparable>
void BinaryHeap<Comparable>::percolateDown( int hole )
{
	int child;
	Comparable tmp =std::move(array[hole]);

	for( ; hole * 2 <= cantidadElementos; hole = child )
    {
		child = hole * 2;
	    if( child != cantidadElementos && array[child + 1] < array[child] )
		    child++;
		if( array[ child ] < tmp )
	        array[ hole ] = std::move(array[child]);
        else
			break;
    }
    array[hole] =std::move(tmp);
}

void ejecutar()
{
    const char* comando="dot -Tpng binaryHeap.dot -o BinHeap.png";
    system(comando);
}


int main()
{
	vector<int> x;
	for(int i=31;i>0;i--)
	{
		x.push_back(i);
	}

	BinaryHeap<int> a(x);
	a.mostrar();
//	a.deleteMin();
//	a.mostrar();
	a.print_dot();
	ejecutar();
	system("BinHeap.png");
	
}	

