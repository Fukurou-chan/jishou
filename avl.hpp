#ifndef AVL_H
#define AVL_H
#include "tree.hpp"
#include <string>
#include <queue>
#include <iostream>


using namespace std;
class AVL:public Tree
{
 private:
		int size;
		Tree *root;
	public:
		AVL()
		{
			this->root = NULL;
			this->size = 0;
			this->count = 0;
		}
		~AVL()                   
		{
			if(root == NULL) return;	
			queue<Tree*> q;
			q.push(root);
			while(!q.empty())
			{
				if(q.front()->left != NULL)  q.push(q.front()->left);
				if(q.front()->right != NULL) q.push(q.front()->right);
				free(q.front());
				q.pop();
			} 
		}
			int count;
			//int getSize();
			int max(int a,int b);
			int getHeightDif(Tree*);
			//Tree* getRoot();
			Tree* avl_newNode(string word, string value);
			Tree* rotateRight(Tree*);
			Tree* rotateLeft(Tree*);
			void insert(Tree*);
			void remove();
			void search();
};



int AVL::max(int a, int b)
{
	if(a>=b)
		return a;
	else
		return b;
}

int AVL::getHeightDif(Tree *t)
{
	if(t == NULL)
		return 0;
	else if( t->left == NULL && t->right == NULL)
		return 0;
	else if(t->left == NULL)
		return (-1-(t->right->height));
	else if(t->right == NULL)
		return (t->left->height+1);
	else
		return (t->left->height - t->right->height);
}


Tree* AVL::avl_newNode(string word, string value)
{
	Tree *ptr = new Tree(word, value);
	return ptr;
}

Tree* AVL::rotateRight(Tree* y)
{
	Tree *x = y->left; 
	Tree *T2 = x->right; 

 	 x->right = y; 
 	 y->left = T2;
	if(T2!=NULL)
		T2->parent = y;
	y->parent = x;
  
	if(y->left != NULL && y->right != NULL)
			y->height = 1 + max(y->left->height, y->right->height);
	else if(y->left != NULL)
			y->height = 1 + y->left->height;
	else if(y->right !=NULL)
			y->height = 1 + y->right->height;
	else
			y->height = 0;
  if(x->left != NULL && x->right != NULL)
			x->height = 1 + max(x->left->height, x->right->height);
	else if(x->left != NULL)
			x->height = 1 + x->left->height;
	else if(x->right !=NULL)
			x->height = 1 + x->right->height;
	else
			x->height = 0;
  
  return x; 
}

Tree* AVL::rotateLeft(Tree* y)
{
  Tree *x = y->right; 
  Tree *T2 = x->left; 
  
    x->left = y; 
    y->right = T2;
		if(T2!=NULL)
			T2->parent = y;
		y->parent = x;
  
	if(y->left != NULL && y->right != NULL)
			y->height = 1 + max(y->left->height, y->right->height);
	else if(y->left != NULL)
			y->height = 1 + y->left->height;
	else if(y->right !=NULL)
			y->height = 1 + y->right->height;
	else
			y->height = 0;
  if(x->left != NULL && x->right != NULL)
			x->height = 1 + max(x->left->height, x->right->height);
	else if(x->left != NULL)
			x->height = 1 + x->left->height;
	else if(x->right !=NULL)
			x->height = 1 + x->right->height;
	else
			x->height = 0;
  
    return x; 
}

void AVL::insert(Tree *t)
{
	string word; string value; 
        cout << "Enter new word"<<endl;
        cin >> word;
        cout << "Enter value for word"<<endl;
        cin >> value;
	Tree *node = root;
	this->size++;
    Tree_add(t, word, value);

	// увеличение высоты
	node = t->parent;
	while(node != NULL)
	{
		if(node->left != NULL && node->right != NULL)
			node->height = 1 + max(node->left->height, node->right->height);
		else if(node->left != NULL)
			node->height = 1 + node->left->height;
		else if(node->right != NULL)
			node->height = 1 + node->right->height;
		else
			node->height = 0;
		node = node->parent;
	}

	// балансировка высоты
	Tree *z,*y,*x,*p;
	z = t->parent;
	y = t;
	x = NULL;
	int heightDiff;
	while(z != NULL){
		heightDiff = getHeightDif(z);
		if((heightDiff > 1) || (heightDiff<(-1)))
		{
			p = z->parent;
			if(z->left == y && y->left == x)
				node = rotateRight(z);
			else if(z->left == y && y->right == x)
			{
				node = rotateLeft(y);
				node->parent = z;
				z->left = node;
				node = rotateRight(z);
			}
			else if(z->right == y && y->right == x)
				node = rotateLeft(z);
			
			else
			{
				node = rotateRight(y);
				node->parent = z;
				z->right = node;
				node = rotateLeft(z);
			}
			if(p!=NULL)
			{
				node->parent = p;
				if(p->right == z)
					p->right = node;
				else
					p->left = node;
			}
			else
			{
				root = node;
				node->parent = NULL;
			}
			node = node->parent;
			while(node != NULL)
			{
				if(node->left != NULL && node->right != NULL)
					node->height = 1 + max(node->left->height, node->right->height);
				else if(node->left != NULL)
					node->height = 1 + node->left->height;
				else if(node->right != NULL)
					node->height = 1 + node->right->height;
				else
					node->height = 0;
				node = node->parent;
			}
		}
		x=y;
		y=z;
		z=z->parent;
	}
}


void AVL::remove()
{
	string word;
	cout << "Enter the word to delete"<<endl;
    cin>>word;
	Tree* p, *t = find(word);
	if (t == NULL)
		cout << endl << "No such word found in dictionary" << endl;
	else {
		this->size--;

		//Deleting Node 
		if (t->left == NULL && t->right == NULL)
		{
			p = t->parent;
			if (p != NULL)
			{
				if (p->left == t)
					p->left = NULL;
				else
					p->right = NULL;
			}
			else
				root = NULL;
			free(t);
		}
		else if (t->left == NULL)
		{
			p = t->parent;
			if (p != NULL)
			{
				if (p->left == t)
					p->left = t->right;
				else
					p->right = t->right;
			}
			else
				root = t->right;
			free(t);
		}
		else if (t->right == NULL)
		{
			p = t->parent;
			if (p != NULL)
			{
				if (p->left == t)
					p->left = t->left;
				else
					p->right = t->left;
			}
			else
				root = t->left;
			free(t);
		}
		else {
			Tree* temp = findpresuc(word);
			t->word = temp->word;
			t->value = temp->value;
			p = temp->parent;
			if (temp->left == NULL && temp->right == NULL)
			{
				if (p != NULL)
				{
					if (p->left == temp)
						p->left = NULL;
					else
						p->right = NULL;
				}
				else
					root = NULL;
				free(temp);
			}
			else if (temp->left != NULL)
			{
				if (p != NULL)
				{
					if (p->left == temp)
						p->left = temp->left;
					else
						p->right = temp->left;
				}
				else
					root = temp->left;
				free(temp);
			}
			else if (temp->right != NULL)
			{
				if (p != NULL)
				{
					if (p->left == temp)
						p->left = temp->right;
					else
						p->right = temp->right;
				}
				else
					root = temp->right;
				free(temp);
			}
		}
	}
	Tree *z,*y,*x;
	int h, hDiff;

	while(p != NULL)
	{
		h = p->height;
		if(p->left != NULL && p->right != NULL)
				p->height = 1 + max(p->left->height, p->right->height);
				else if(p->left != NULL)
					p->height = 1 + p->left->height;
				else if(p->right != NULL)
					p->height = 1 + p->right->height;
				else
					p->height = 0;
			hDiff = getHeightDif(p);
			if(h == p->height)
				break;
			else if(hDiff <=1 && hDiff>= (-1))
				p = p->parent;
			
			else{
				z = p;
				p = p->parent;
				if(z->left != NULL && z->right != NULL)
				{
					if(z->left->height >= z->right->height)
						y = z->left;
					else
						y = z->right;  
				}
				else if(z->left != NULL)
					y = z->left;
				else
					y = z->right;
				if((y->left != NULL) && (y->right != NULL))
				{
					if(y->left->height >= y->right->height)
						x = y->left;
					else
						x = y->right;  
				}
				else if(y->left != NULL)
					x = y->left;
				else if(y->right != NULL)
					x = y->right;
				else
					x = NULL;
				Tree *node;
				if(z->left == y && y->left == x)
				{
					node = rotateRight(z);
				}
				else if(z->left == y && y->right == x)
				{
					node = rotateLeft(y);
					node->parent = z;
					z->left = node;
					node = rotateRight(z);
				}
				else if(z->right == y && y->right == x)
					node = rotateLeft(z);
				else{
					node = rotateRight(y);
					node->parent = z;
					z->right = node;
					node = rotateLeft(z);
				}
				if(p!=NULL)
				{
					node->parent = p;
					if(p->right == z)
						p->right = node;
					else
						p->left = node;
				}
				else{
					root = node;
					node->parent = NULL;
				}
			}
		}
		cout<<" Word Removed !\n";
	}


void AVL::search()
{
    string word;
	cout<<"Enter the word to be searched for"<<endl;
	cin>>word;
	find(word);
}

#endif

