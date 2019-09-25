#include <bits/stdc++.h>
#include "unorderedLinkedList.h"
#include <string.h>
using namespace std;

int main(){
	/*unorderedLinkedList<string> arr;
	arr.insertFirst("Selene");
	arr.print();
	cout<<arr.front();*/
	int cantidad;
	unorderedLinkedList<string> list1; //Line 5
	string num; //Line 6
	cout <<"N?"<<endl;
	cin >> cantidad;
	cout << "Ingrese tiempos:"<<endl; //Line 7
	cin >> num; //Line 8
	for(int i=0;i<cantidad;i++)
	{
		list1.insertFirst(num);
		cin >> num; 
	}
	cout << endl; //Line 14
	cout << "Line 15: list1: "; //Line 15
	list1.print(); //Line 16
	cout << endl; //
	return 0;
}
