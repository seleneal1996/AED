//ARBOL B

/*REGLAS

	


*/

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <string>
#include<fstream>
#include<windows.h>
#include <sstream>
using namespace std;

class Pagina
{
    int *claves;  
    int t;      //grdo minimo de la pagina
    Pagina **C; //arreglo de punteros a hijos
    int n;     // numero actual de claves
    bool leaf; 
public:
    Pagina(int t1, bool leaf1)
    {
    	t = t1;
	    leaf = leaf1;
	    claves = new int[2*t-1];
	    C = new Pagina *[2*t];
	    n = 0;
    } 

    //PRIMER CASO  INSERTA UNA CLAVE EN UN PAGINA VALIDA 
    void insertNonFull(int k)
    {
	    int i = n-1; // numero maximo de claves en una pagina
	  
	    if (leaf == true)
	    {
	 
	        while (i >= 0 && claves[i] > k)
	        {
	            claves[i+1] = claves[i];
	            i--;
	        }
	       
	        claves[i+1] = k;
	        n = n+1;
	    }
	    else 
	    {
	        //SEGUNDO CASO : INSERTA UNA CLAVE QUE CORRESPONDE A UNA PAGINA LLENA
	        while (i >= 0 && claves[i] > k)
	            i--;
	     
	        if (C[i+1]->n == 2*t-1)
	        {
	            splitChild(i+1, C[i+1]);
	    
	            if (claves[i+1] < k)
	                i++;
	        }
	        C[i+1]->insertNonFull(k);
	    }
    }

  
  
    void splitChild(int i, Pagina *y)
    {
	    Pagina *z = new Pagina(y->t, y->leaf);
	    z->n = t - 1;
	    
	    for (int j = 0; j < t-1; j++)
	        z->claves[j] = y->claves[j+t];
	  
	    if (y->leaf == false)
	    {
	        for (int j = 0; j < t; j++)
	            z->C[j] = y->C[j+t];
	    }
	    
	    y->n = t - 1;
	    
	    for (int j = n; j >= i+1; j--)
	        C[j+1] = C[j];
	 
	    C[i+1] = z;
	    
	    for (int j = n-1; j >= i; j--)
	        claves[j+1] = claves[j];
	    
	    claves[i] = y->claves[t-1];
	    
	    n = n + 1;
    }
  
    void traverse()
    {
	    int i;
	    for (i = 0; i < n; i++)
	    {
	        if (leaf == false)
	            C[i]->traverse();
	        cout << " " << claves[i];
	    }
	    
	    if (leaf == false)
	        C[i]->traverse();

    }
   
    Pagina *search(int k)
    {
 
	    int i = 0;
	    while (i < n && k > claves[i])
	        i++;
	    if (claves[i] == k)
	        return this;
	    if (leaf == true)
	        return NULL;
	    return C[i]->search(k);
    }
   
    friend class BTree;
};

class BTree
{
    Pagina *root;
    int t;  
public:
    BTree(int _t)
    {  
    	root = NULL;  
    	t = _t; 
    }

    void Cargar(string Name){
       ifstream is(Name);
       if (is){
           string linea;
           // Mientras se pueda leer una linea del archivo ...
           while (getline(is, linea)){
                stringstream ss(linea);
                long valor;
                ss >> valor;
                insert(valor);
            }
            is.close();
        }
    }
    void traverse()
    {  if (root != NULL) 
    	root->traverse();
    }
    
    Pagina* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }
  
    void insert(int k)
    {
	    
	    if (root == NULL)
	    {
	        root = new Pagina(t, true);
	        root->claves[0] = k; 
	        root->n = 1;  
	    }
	    else
	    {
	        if (root->n == 2*t-1)
	        {
	          
	            Pagina *s = new Pagina(t, false);
	            
	            s->C[0] = root;
	       
	            s->splitChild(0, root);
	         
	            int i = 0;
	            if (s->claves[0] < k)
	                i++;
	            s->C[i]->insertNonFull(k);
	            
	        
	            root = s;
	        }
	        else  
	            root->insertNonFull(k);
	    }
    }


    void print_dot_null(int *claves, int nullcount, FILE* stream)
	{
    	fprintf(stream, "    null%d [style=invisible][fontcolor=white];\n", nullcount);
    	fprintf(stream, "    %d -> null%d;\n", *claves, nullcount);
	}
	void print_dot_aux(Pagina* node, FILE* stream)
	{
    	static int nullcount = 0;
		if (true)
		{
		 
		    traverse();

		    fprintf(stream, "    %d -> %d;\n",Pagina->claves);
            //print_dot_aux(node->claves, stream);
		}

	}

    void print_dot(Pagina* tree, FILE* stream)
    {
        fprintf(stream, "digraph ArbolB{\n");
    	if (!tree)
        	fprintf(stream, "\n");
    	else if(tree!=NULL)
        	fprintf(stream, "    %d;\n", tree->claves);
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
    BTree t(3);
    t.Cargar("test.txt");
    t.traverse();
    t.print_n();
    ejecutar();
    int k = 6;
    (t.search(k) != NULL)? cout << "\nEncontrado" : cout << "\n No se Encuentra";
    k = 15;
    (t.search(k) != NULL)? cout << "\nEncontrado" : cout << "\nNo se Encuentra";
     
    return 0;
}



















































































/*#include<iostream>
#include<conio.h>
using namespace std;
int d;
struct btnode
{
	int *key;
	btnode **child;
};
void print(btnode* t)
{
	if(t==NULL) return;
	int i;
	for(i=0;i<2*d;i++)
	{
		print(t->child[i]);
		if(t->key[i]!=-1)
		cout<<t->key[i]<<" ";
	}
    print(t->child[2*d]);
}
bool check_leaf(btnode* T)
{
	int flag=0;
	for(int i=0;i<2*d+1;i++)
	if(T->child[i]!=NULL)
	flag=1;
	if(flag==0)
	return (1);
	else
	return (0);
}
void add_to_node(btnode* old_node,int k,btnode* &new_node,int pos)
{
	int i,j;
	for(i=0;i<2*d&&old_node->key[i]!=-1;i++);
	for(j=i-1;j>=pos&&old_node->key[j]>k;j--)
	{
		old_node->key[j+1]=old_node->key[j];
		old_node->child[j+2]=old_node->child[j+1];
	}
	old_node->key[pos]=k;
	old_node->child[pos+1]=new_node;
}
void create_newnode(btnode* &T)
{
	int i;
	T=new btnode;
	T->key=new int[2*d];
	T->child=new btnode*[2*d+1];
	for(i=0;i<2*d;i++) T->key[i]=-1;
	for(i=0;i<2*d+1;i++) T->child[i]=NULL;
}
void nodesplit(btnode* old_node,btnode* &new_node,int &k,int pos)
{
	btnode* N=NULL;
	create_newnode(N);
	if(pos<=d)
	{
		for(int i=d;i<2*d;i++)
		{
			N->key[i-d]=old_node->key[i];
			N->child[i-d+1]=old_node->child[i+1];
			old_node->key[i]=-1;
			old_node->child[i+1]=NULL;
		}
		N->child[0]=old_node->child[d];
		add_to_node(old_node,k,new_node,pos);
	}
	else
	{
		for(int i=d+1;i<2*d;i++)
		{
			N->key[i-(d+1)]=old_node->key[i];
			N->child[i-d]=old_node->child[i+1];
			old_node->key[i]=-1;
			old_node->child[i+1]=NULL;
		}
		N->child[0]=old_node->child[d+1];
        old_node->child[d+1]=NULL;
		add_to_node(N,k,new_node,pos-(d+1));
	}
	k=old_node->key[d];
	old_node->key[d]=-1;
	new_node=N;
}
int setflag(btnode* T,int &k,btnode* &new_node)
{
	int pos;
	if(T==NULL)
	{
		return (1);
	}
	for(pos=0;pos<2*d&&T->key[pos]!=-1;pos++)
	{
		if(k<T->key[pos]) break;
	}
	if(check_leaf(T))
	{
		if(T->key[2*d-1]==-1)
		{
			add_to_node(T,k,new_node,pos);
			return (0);
		}
		else
		{
			nodesplit(T,new_node,k,pos);
			return (1);
		}
	}
	else
	{
		int flag=setflag(T->child[pos],k,new_node);
		if(flag==1)
		{
			if(T->key[2*d-1]==-1)
			{
				add_to_node(T,k,new_node,pos);
				return (0);
			}
		    else
		    {
			    nodesplit(T,new_node,k,pos);
			    return (1);
		    }
		}
	}
}
btnode* create_root(btnode* T,btnode* new_node,int k)
{
	btnode* root=NULL;
        create_newnode(root);
	    root->key[0]=k;
		root->child[0]=T;
		root->child[1]=new_node;
		return (root);
}
void insert(btnode* &T,int k,btnode* new_node)
{
	btnode* root=NULL;
	int flag=setflag(T,k,new_node);
	if(flag) T=create_root(T,new_node,k);
}
int main()
{
	btnode *root=NULL;
	cout<<"enter d\n";
	cin>>d;
	cout<<"enter elements to be inserted \n";
	int next;
	while(cin>>next)
	{
		if(next==-1) break;
		else insert(root,next,NULL);
	}
	print(root);
	getch();
	return (0);
}*/