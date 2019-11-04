#include<iostream>

using namespace std;

enum Color{RED,BLACK};

template<class T>
class RB{
	public:
		class nodo{
		public:
			T dato;
			nodo* left;
			nodo* right;
			nodo* padre;
			int color;
			public:
				nodo(T valor){
					dato=valor;
					left=nullptr;
					right=nullptr;
					padre=nullptr;
					color=RED;
				}
		
			
		};
		nodo *root;		
		void add(nodo *&r){
			nodo *q=nullptr;
			nodo *p=root;
			while(p)
			{
				q=p;
				if (r->dato < p->dato){
					p=p->left;
				}
				else{
					p=p->right;
				}
			}
			r->padre=q;
			if(q == nullptr){
				root=r;
			}
			else if(r->dato<q->dato){
				q->left=r;
			}
			else{
				q->right=r;
			}
			r->left=nullptr;
			r->right=nullptr;
			r->color=RED;
		}
		void setColor(nodo *&p,int color){
			if(p==NULL){
				return; 
			}
			p->color=color;
		}
		int getColor(nodo *&p){
			if(p==NULL)
				return BLACK;
			return p->color;
		}
		nodo* insertar(nodo *&p,nodo *&q){
			if(p==NULL) return q; 
			if(p->dato ==q->dato) return NULL;
			if(p->dato<q->dato){
				p->right=insertar(p->right,q);
				p->right->padre=p;
			}
			else{
				p->left=insertar(p->left,q);
				p->left->padre=p;
			}
			return p;
			
		}
		
		void acomodar(nodo *&p){
			nodo *padre;
			nodo *abuelo;
			while(p!=root && getColor(p)==RED && getColor(p->padre)==RED){
				padre=p->padre;
				abuelo=padre->padre;
				if(padre==abuelo->left){
					nodo *tio=abuelo->right;
					if(getColor(tio)==RED){
						setColor(tio,BLACK);
						setColor(padre,BLACK);
						setColor(abuelo,RED);
						p=abuelo;
					}
					else{
						if(p==padre->right){
							RI(padre);
							p=padre;
							padre=p->padre;
						}
						RD(abuelo);
						swap(padre->color,abuelo->color);
						p=padre;
					}
					
					}
					else{
						nodo *tio=abuelo->left;
						if(getColor(tio)==RED){
							setColor(tio,BLACK);
							setColor(padre,BLACK);
							setColor(abuelo,RED);
							p=abuelo;
						}
						else{
							if(p==padre->left){
								RD(padre);
								p=padre;
								padre=p->padre;
							}
							RI(abuelo);
							swap(padre->color,abuelo->color);
							p=padre;
						}
					}
				}
				setColor(root,BLACK);
			}
		
		void RI(nodo *&p){
			nodo *q=p->right;
			p->right=q->left;
			
			if(p->right != nullptr){
				p->right->padre=p;
			}
			q->padre=p->padre;
			if(p->padre==nullptr){
				root=q;
			}
			else if(p==p->padre->left){
				p->padre->left=q;
			}
			else{
				p->padre->right=q;
			}
			q->left=p;
			p->padre=q;
		}
		void RD(nodo *&p){
			nodo *q=p->left;
			p->left=q->right;
			
			if(p->left!=nullptr){
				p->left->padre=p;
			}
			q->padre=p->padre;
			
			if(p->padre==nullptr){
				root=q;
			}
			else if(p==p->padre->left){
				p->padre->left=q;
			}
			else{
				p->padre->right=q;
			}
			q->right=p;
			p->padre=q;
		}
		void print(nodo *&p){
			if(p!=NULL) {
			cout<<p->dato<<" color: ";
			cout<<p->color<<endl;
			print(p->left);
			print(p->right);
			}
		}

		void mostrar(){
			print(root);
		}
		void agregar(T d){
			nodo *q=new nodo(d);
			add(q);
			acomodar(q);
			
		}
		
		
		nodo *ArbolMin(nodo *&x)
		{
			nodo *a=x;
			while(a->left != nullptr)
				a=a->left;
			return a;
		}
		void transplant(nodo*& a, nodo*& b) {
			if (a->padre == NULL)
				root = b;
			else if (a == a->padre->left)
				a->padre->left = b;
			else
				a->padre->right = b;
			b->padre = a->padre;
		}

		nodo* search( T key ){
			nodo* x = root;
			while( x != nullptr && key != x->dato ){
				if( key < x->dato )
					x = x->left;
				else
					x = x->right;
			}
			return x;
		}
		
		void borrar(T d)
		{
//			nodo *z=search(d);
			nodo *z=rbdelete(root,d);
//			rbDelete(z);
			deletefix(z);
			
		}
		nodo* rbdelete(nodo *&root, int data) {
    	if (root == nullptr)
        	return root;

    	if (data < root->dato)
	        return rbdelete(root->left, data);

    	if (data > root->dato)
        	return rbdelete(root->right, data);

    	if (root->left == nullptr || root->right == nullptr)
        	return root;

    	nodo *temp = ArbolMin(root->right);
    	root->dato = temp->dato;
    	return rbdelete(root->right, temp->dato);
		}
//		void rbDelete( nodo *&z ){
//			nodo * x = nullptr;
//			nodo * y = nullptr;
//			if( z->left == nullptr || z->right == nullptr )
//				y = z;
//			else
//				y = ArbolMin( z->right );
//			if( y->left != nullptr )
//				x = y->left;
//			else
//				x = y->right;
//			x->padre = y->padre;
//			if( y->padre == nullptr )
//				root = x;
//			else{
//				if( y == y->padre->left )
//					y->padre->left = x;
//				else
//					y->padre->right = x;
//			}
//			if( y != z )
//				z->dato = y->dato;
//			if( y->color == BLACK )
//				rbDeleteFixup( x );
//			delete y;
//		}
		
		
		void deletefix(nodo* ip) {
	if (ip==nullptr)
	{
		return;
	}
	if (ip==root)
	{
		root=nullptr;
		return;
	}
	if (getColor(ip)==RED || getColor(ip->left)==RED || getColor(ip->right)==RED)
	{
		nodo *hijo=ip->left !=nullptr ? ip->left:ip->right;

		if(ip==ip->padre->left){
			ip->padre->left=hijo;
			if(hijo != nullptr)
				hijo->padre=ip->padre;
			setColor(hijo,BLACK);
			delete(ip);
		}else{
			ip->padre->right=hijo;
			if (hijo != nullptr)
			{
				hijo->padre=ip->padre;
			}
			setColor(hijo,BLACK);
			delete(ip);
		}
	}else{
		nodo *padre=nullptr;
		nodo *ptr=ip;
		while (ptr != root && getColor(ptr) == BLACK) {
			padre=ptr->padre;
			if (ptr == padre->left) {		//if ip is the left child of its parent
				nodo* par = padre->right;
				if (getColor(par) == RED) {
					setColor(par,BLACK);
					setColor(padre,RED);
					RI(padre);
					// par = padre->right;
				}else
				{
					if (getColor(par->left) == BLACK && getColor(par->right) == BLACK) {
						setColor(par,RED);
						if(getColor(padre)==RED)
							setColor(padre,BLACK);
						ptr = padre;
					}
					else {
						if (getColor(par->right) == BLACK) {
							setColor(par->left,BLACK);
							setColor(par,RED);
							RD( par);
							par = padre->right;
						}
						setColor(par,padre->color);
						setColor(padre,BLACK);
						setColor(par->right,BLACK);
						RI(padre);
						// ip = root;
						break;
						}
					}
				}
			else {		//if ip is the right child of its parent
				nodo* par = padre->left;
				if (getColor(par)== RED) {
					setColor(par,BLACK);
					setColor(padre,RED);
					RD(padre);
					// par = padre->left;
				}else{
				if (getColor(par->left) == BLACK && getColor(par->right) == BLACK) {
					setColor(par,RED);
					if(getColor(padre)==RED)
						setColor(padre,BLACK);
					ptr = padre;
				}
				else {
					if (getColor(par->left)== BLACK) {
						setColor(par->right,BLACK);
						setColor(par,RED);
						RI( par);
						par = padre->left;
					}
					setColor(par,padre->color);
					setColor(padre,BLACK);
					setColor(par->left,BLACK);
					RD( padre);
					// ip = root;
					break;
					}
				}
			}
		}

		if(ip==ip->padre->left)
			ip->padre->left=nullptr;
		else
			ip->padre->right=nullptr;
		delete(ip);
		setColor(ip,BLACK);
	}
}


//////////////////////////////////7
//		void rbDeleteFixup(nodo *& x){
//			nodo * w =nullptr;
//			nodo *aux=x;
//			while( aux != root && getColor(aux) == BLACK){
//				
//				if( aux==aux->padre->left){
//					w = aux->padre->right;
//				if( w->color == RED ){
//					setColor(w,BLACK);
//					setColor(aux->padre,RED);
//					RI( aux->padre);
////					w = x->padre->right;
//				}
//				if( getColor(w->left) == BLACK && getColor(w->right) == BLACK ){
//					setColor(w,RED);
//					aux = aux->padre;
//				}
//				else{
//					if( getColor(w->right) == BLACK ){
//						setColor(w->left,BLACK);
//						setColor(w,RED);
//						RD( w );
//						w = aux->padre->right;
//					}
//					setColor(w,aux->padre->color);
//					setColor(aux->padre,BLACK);
//					setColor(w->right,BLACK);
//					RI( aux->padre );
//					break;
////					x = root;
//				}
//			}
//			else{
//				w = aux->padre->left;
//				if( getColor(w)==RED ){
//					setColor(w,BLACK);
//					setColor(aux->padre,RED);
//					RD( aux->padre );
////					w = x->padre->left;
//				}
//				if( getColor(w->left)==BLACK && getColor(w->right) == BLACK ){
//					setColor(w,RED);
//					aux = aux->padre;
//				}
//				else{
//					if(getColor(w->left) == BLACK ){
//						setColor(w->right,BLACK);
//						setColor(w,RED);
//						RI( w );
//						w = aux->padre->left;
//					}
//					setColor(w,aux->padre->color);
//					setColor(aux->padre,BLACK);
//					setColor(w->left,BLACK);
//					RD( aux->padre );
//					break;
////					x = root;
//				}
//			}
//		}
//		if(x==x->padre->left){
//			x->padre->left=nullptr;
//		}
//		else{
//			x->padre->right=nullptr;
//		}
//		delete(x);
//		setColor(root,BLACK);
//	}
		
		void print_dot_null(int dato, int nullcount, FILE* stream)
		{
    		fprintf(stream, "    null%d [style=filled][fillcolor=black][fontcolor=white];\n", nullcount);
    		fprintf(stream, "    %d -> null%d;\n", dato, nullcount);
		}
////////////////////////////////////////////

		void print_dot_aux(nodo* node, FILE* stream)
		{
		    static int nullcount = 0;
			if(node)
			{
				if(getColor(node)==RED)
				{
					fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=red][fontcolor=white];\n",node->dato);
				}
				else{
					fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=black][fontcolor=white];\n",node->dato);
				}
				
				fprintf(stream, "    %d;\n", node->dato);
			}
			
    		if (node->left)
    		{
    			if(getColor(node->left)==BLACK)
    			{
    				fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=black][fontcolor=white];\n",node->left->dato);
        			
				}
				else
				{
					fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=red][fontcolor=white];\n",node->left->dato);
					
				}
				fprintf(stream, "    %d -> %d;\n", node->dato, node->left->dato);
        		print_dot_aux(node->left, stream);
      			//  cout<<"imprimiendo"<<endl;
    		}
    		else
        		print_dot_null(node->dato, nullcount++, stream);

    		if (node->right)
    		{
    			if(getColor(node->right)==RED)
    			{
    				fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=red][fontcolor=white];\n",node->right->dato);
				}
				else{
					fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=black][fontcolor=white];\n",node->right->dato);
				}
        		fprintf(stream, "    %d -> %d;\n", node->dato, node->right->dato);
        		print_dot_aux(node->right, stream);
       			// cout<<"imprimiendo"<<endl;
    		}
    		else
        		print_dot_null(node->dato, nullcount++, stream);
			
		}
		void print_dot(nodo* tree, FILE* stream)
		{
    		fprintf(stream, "digraph BST {\n");
    		//fprintf(stream, "    node [fontname=\"Arial\"];\n");

   			if (!tree)
        		fprintf(stream, "\n");
    		else if (!tree->right && !tree->left){
    			fprintf(stream," %d [width=.6][fontname=Helvetica][fontsize=24][fixedsize=true][style=filled][fillcolor=black][fontcolor=white];\n",tree->dato);
        		fprintf(stream, "    %d;\n", tree->dato);
    		}
    		else
        		print_dot_aux(tree, stream);
    		fprintf(stream, "}\n");
		}
////////////////////////////

		void print_n()
		{
    		FILE * pFile;
    		pFile = fopen ("redB.txt","w+");
    		print_dot(root,pFile);
    		fclose (pFile);
		}
		

};
void ejecutar()
{
    const char* comando="dot -Tpng redB.txt -o redB.png";
    system(comando);

}


int main(){
	RB<int> a;
	a.agregar(5);
	a.agregar(10);
	a.agregar(12);
	a.agregar(28);
	a.agregar(16);
	a.agregar(22);
	a.agregar(3);
	a.mostrar();
	int x;
	a.print_n();
	ejecutar();
	system("redB.png");
	/*while(cin>>x)
	{
		a.borrar(x);
		a.mostrar();
		a.print_n();
		ejecutar();
		system("redB.png");
	}*/


	
//	a.mostrar();

}


