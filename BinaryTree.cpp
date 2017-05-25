#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
#include <vector>
#include <cmath>
using namespace std;

template <typename T>
class Tree{
public:
	Tree() : high(0), root(NULL){};
	~Tree();
	struct Leaf{
		T element;
		Leaf *Right;
		Leaf *Left;
		Leaf *parent;
	};
	Leaf *root;
	int high;
	int len(Leaf *current);
    void swap(Leaf *one, Leaf *two);
	void Del(Leaf *kot);
	void insert(T& d);
	void print_inorder();
	void beginascendinground();
	void beginSymmetricOrder();
	T* findtheleast();
	void popelem();
	bool isEmpty() const { return root == NULL; }
	void copy(Tree<T>&);
	void where(Tree<T>&, bool(*)(T&), Leaf*);
	bool Find();
	int heightOfTree(Leaf* root);
	void ArithMean(Leaf* root,int &element,int &counter);
	void delete_note(T& k);
    
protected:
	void ascendinground(Leaf* L);
private:
	void inorder(Leaf*, int);
	void SymmetricOrder(Leaf*);
	void _copy(Leaf* cpy, Leaf* orig);
	void private_delete_note(T& k, Leaf* note);

};

template <typename T>
void Tree<T>::swap(Leaf *one, Leaf *two){
    if (one != NULL and two != NULL) {
        T temp = two->element;
        two->element = one->element;
        one->element = temp;
    }
    else {
        cout << "Can't swap with NULL." << endl;
    }
}

template <typename T>
int Tree<T>::len(Leaf *current){
    int x = 0;
    if (current == NULL) {
    	return 0;
    }
    else {
    	x+=1;
    	if (current->Left != NULL) {
    		x+=len(current->Left);
    	    }
    	if (current->Right != NULL) {
    		x+=len(current->Right);
    	}
    return x;
    }
}

template <class T>
void Tree<T>::insert(T& d)
{
	Leaf* t = new Leaf;
	t->element = d;
	t->Left = NULL;
	t->Right = NULL;
	t->parent = NULL;
	//
	if (isEmpty())
	{
		root = t;
	}
	else
	{
		Leaf* curr;
		curr = root;
		while (curr)
		{
			t->parent = curr;
			if (t->element > curr->element) curr = curr->Right;
			else curr = curr->Left;
		}

		if (t->element < t->parent->element)
			t->parent->Left = t;
		else
			t->parent->Right = t;
	}
}
template <class T>
void Tree<T>::ArithMean(Leaf *root,int &value, int &counter) ///Среднее арифметическое
{
       if (root) // если узел существует
        {
            value += root->element; // записываем значение узла
            ++counter; // увеличиваем счетчик
            ArithMean(root->Left, value, counter); // обходим левое поддерево
            ArithMean(root->Right, value, counter); // обходим правое поддерево
        }
}
template <class T>
T* Tree<T> ::findtheleast()
{
	if (root == NULL)
		return NULL;

	Leaf* ptr = root;
	while (ptr->Left != NULL)
	{
		ptr = ptr->Left;
	}
	return &ptr->element;
}
template <typename T>
void Tree <T> ::Del(Leaf *kot){
	if (kot != NULL)
	{
		Del(kot->Left);
		Del(kot->Right);
		delete kot;
	}
}

template <class T>
void Tree<T> :: popelem()
{
    if(root != NULL){
        Leaf* ptr = root;
        while(ptr!=NULL)
        {
            int i,j=0,a[10]={0,0,0,0,0,0,0,0,0,0};
            for (i=ptr->element; i!=0;)
            {
                j=i%10;
                i=i/10;
                a[j]=a[j]+1;}
            for(i=0;i<10;i++)
                if(a[i]>a[j]) j=i;
            ptr->element=j;
            for(i=0;i<10;i++)
                a[i]=0;
            if(ptr!=NULL)ptr=ptr->Right;
        }
    }
}

template<class T>
void Tree<T>::print_inorder()
{
	inorder(root, 0);
}
template<class T>
void Tree<T>::inorder(Leaf* p, int deep)
{
	if (p){
		for (int i = 0; i <= deep; i++)
			cout << "--";
		cout << p->element << endl;
		inorder(p->Left, deep + 1);
		inorder(p->Right, deep + 1);

	}
	else{
		for (int i = 0; i <= deep; i++)
			cout << "--";
		cout << "NULL" << endl;
	}
}

template <class T>
void Tree <T>::beginascendinground()
{
	if (root)
	{
		ascendinground(root);
	}
	else
		cout << "  Tree is empty" << endl;
}

template <class T>
void Tree <T>::ascendinground(Leaf* L)
{
	if (L->Left)
		ascendinground(L->Left);
	if (L->Right)
		ascendinground(L->Right);
	cout << " " << L->element;
}

template <class T>
void Tree <T>::beginSymmetricOrder()
{
	if (root)
	{
		SymmetricOrder(root);
	}
	else
		cout << "  Tree is empty" << endl;
}


template <class T>
void Tree <T>::SymmetricOrder(Leaf* L)
{
	if (L != NULL)
	{
		SymmetricOrder(L->Left);
		cout << " " << L->element << endl;
		SymmetricOrder(L->Right);
	}
}

bool more_then_five(int& num){ return num>5; }

template <typename T>
void Tree<T>::where(Tree<T>&Tr, bool(*cmp)(T&), Leaf*L){
	if (!L) return;
	if (cmp(L->element))
		Tr.insert(L->element);
	where(Tr, cmp, L->Left);
	where(Tr, cmp, L->Right);
}
template <typename T>
bool Tree<T>::Find(){
	Leaf *pv = root, *prev;
	T element1;
	cout << "Enter the student/professor to search for:" << endl;
	cin >> element1;
	while (pv)
	{
		prev = pv;
		if (element1 == pv->element) return true;
		if (element1 < pv->element) pv = pv->Left;
		else pv = pv->Right;
	}
	return false;
}


template <typename T>
int Tree<T>::heightOfTree(Leaf* root){//передаем указатель на корень дерева

    Leaf* p = root;

    if(p == NULL)
    {
        cout<<" "<<endl;
        return 0;
    }
    else{

    return max(heightOfTree(p->Left),heightOfTree(p->Right))+1;
    }
}



class Student{
public:
	string surname;
	string name;
	string patronymic;
	string group;
	bool operator<(Student& p1)
	{
		if (strcmp(surname.c_str(), p1.surname.c_str())<0) return 1;
		else return 0;
	}
	bool operator>(Student& p1)
	{
		if (strcmp(surname.c_str(), p1.surname.c_str())>0)return 1;
		else return 0;
	}
	bool operator==(Student& p1){
		if (strcmp(surname.c_str(), p1.surname.c_str()) == 0) return 1;
		else return 0;
	}

	friend ostream& operator<<(ostream& os, Student& petr){
		os << petr.surname << " " << petr.name << " " << petr.patronymic << " " << petr.group << endl;
		return os;
	}
	friend istream& operator>>(istream& is, Student& petr){
		is >> petr.surname;
		is >> petr.name;
		is >> petr.patronymic;
		is >> petr.group;
		return is;
	}
};
class Professors{
public:
	string surname;
	string name;
	string patronymic;
	string subject;
	bool operator<(Professors& p1){
		if (strcmp(surname.c_str(), p1.surname.c_str())<0)return 1;
		else return 0;
	}
	bool operator>(Professors& p1){
		if (strcmp(surname.c_str(), p1.surname.c_str())<0)return 0;
		else return 1;
	}

	friend ostream& operator<<(ostream& os, Professors& petr){
		os << petr.surname << " " << petr.name << " " << petr.patronymic << " " << petr.subject << endl;
		return os;
	}
	friend istream& operator>>(istream& is, Professors& petr){
		is >> petr.surname;
		is >> petr.name;
		is >> petr.patronymic;
		is >> petr.subject;
		return is;
	}

};

template <typename T>
Tree <T> :: ~Tree(){
	this->Del(root);
}

template<typename T>
void Tree<T>::_copy(Leaf* cpy, Leaf* orig){
	cpy->element = orig->element;
	cpy->Left = NULL;
	cpy->Right = NULL;
	if (orig->Left){
		cpy->Left = new Leaf;
		cpy->parent = cpy;
		_copy(cpy->Left, orig->Left);
	}
	else{
		cpy->Left = NULL;
	}
	if (orig->Right){
		cpy->Right = new Leaf;
		cpy->parent = cpy;
		_copy(cpy->Right, orig->Right);
	}
	else{
		cpy->Left = NULL;
	}
}

template <typename T>
void Tree<T>::copy(Tree<T>& new_tree)
{
	new_tree.Del(new_tree.root);
	if (this->root){
		new_tree.root = new Leaf;
		_copy(new_tree.root, this->root);
		new_tree.high = this->high;
	}
}

template <typename T>
void Tree<T>::delete_note(T& k){ private_delete_note(k, this->root); }

template <typename T>
void Tree<T>::private_delete_note(T& k, Leaf* note){
	if (note == NULL)
		return;
	if (note->element == k){
		Leaf* P = note->parent;
		if (P->Left == note)
			P->Left = NULL;
		else
			P->Right = NULL;
		Del(note);
		return;
	}
	else{
		private_delete_note(k, note->Left);
		private_delete_note(k, note->Right);
	}
}

/*
int main(){
    Tree <int> Stud1;
    for (int i = 0; i<10; i++){
        Stud1.insert(i);
    }
    Stud1.print_inorder();
    Tree <int> Stud2;
    //Stud1.copy(Stud2);
    Stud2.print_inorder();
    Stud1.where(Stud2, more_then_five, Stud1.root);
    Stud2.print_inorder();
}*/


int main(){
Tree <Student> Stud1;
Tree <int> Int_Tree;
int ch;
Student petr;
while(1)
{
   cout<<endl<<endl;
   cout<<" Binary Search Tree Operations "<<endl;
   cout<<" ----------------------------- "<<endl;
   cout<<" 1. Insertion/Creation "<<endl;
   cout<<" 2. Show In-Order "<<endl;
   cout<<" 3. Find the least element"<<endl;
   cout<<" 4. Ascending bypass"<<endl;
   cout<<" 5. Find for the entry" << endl;
     cout<<" 6. Height of the tree" << endl;
   cout<<" 7. Convert elements to maximum number "<<endl;
   cout<<" 8. Total number of leaves "<<endl;
   cout<<" 9.The arithmetic mean of elements(only for int and float)"<<endl;
cout << "10. Delete node " << endl;
cout<<"11. Exit "<<endl;
cout<<" Enter your choice : ";
cin>>ch;
switch(ch)
{
case 1 : cout<<" Enter data to be inserted : ";
cin.ignore(1);
cin >> petr;
Stud1.insert(petr);
break;
case 2 : cout<<endl;
cout<<" In-Order Traversal "<<endl;
cout<<" -------------------"<<endl;
Stud1.print_inorder();
break;
case 3 : cout<<endl;
{
Student* minStud = Stud1.findtheleast();
if ( minStud == NULL)
cout<<"Tree is empty"<<endl;
else
{
   cout<<"The least element is";
   cout<<"	"<<*minStud<<endl;
}
break;
}
case 4 : cout<<endl;
cout<<" ascending bypass "<<endl;
cout<<" *****************"<<endl;
Stud1.beginascendinground();
break;
case 5: cout << endl;
	if (Stud1.Find()){
		cout << "The student was found";
	}
	else cout << "The student is not found";
	break;
case 6:cout << endl;

cout<<endl;
cout<<"Height:"<<endl;
cout << Stud1.heightOfTree(Stud1.root);
break;
/*case 7 : cout << endl;
	Stud1.popelem();
	break;*/
case 8 : system("pause");
case 9 : cout << endl;
    int value=0;
    int counter=0;
	Int_Tree.ArithMean(Int_Tree.root, value, counter);
	cout << "The arithmetic mean of elements= " << (double)value / counter << endl;
break;
case 10:
cout << endl;
int k;
cout << "Enter the value of the node you want to delete: ";
cin >> k;
Int_Tree.delete_note(k);
break;
}
}
return 0;
}
