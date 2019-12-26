#include<iostream>
#include<string>
#ifndef TREE_H
#define TREE_H
using namespace std;

class Tree
{     
	 private:
		int size;
	    Tree *root;
            
	public:
		string word, value;
		Tree *parent,*left,*right;
		int height;
        Tree();
		Tree(string,string);
        Tree* find(string word);
        void Tree_remove(string word);
	    void Tree_add(Tree *t, string word, string value);
        Tree* newNode(string word, string value);
        Tree* findpresuc(string word);
};

Tree::Tree(string wordInp, string valueInp)
{
	for(int i=0; i < wordInp.size(); i++)
		this->word.push_back(wordInp[i]);
	for(int i=0; i < valueInp.size(); i++)
		this->value.push_back(valueInp[i]);
	this->height = 0;
	this->parent = NULL;
	this->right = NULL;
	this->left = NULL;
}

Tree* Tree::find(string word)
{
	if(root == NULL)
		return root;
	Tree *node = root;
	while(1)
	{
		if(node == NULL || node->word == word)
				return node;
		else if(node->word < word)
				node = node->right;
		else if(node->word > word)
				node = node->left;
	}
}

Tree* Tree::findpresuc(string word){
	Tree *t = find(word);
	if(t!= NULL){
		if(t->left !=NULL){
			t = t->left;
			while(t->right !=NULL)
				t = t->right;
			return t;
		}
		else if(t->right !=NULL){
			t = t->right;
			while(t->left !=NULL)
				t = t->left;
			return t;
		}
		else
			return t->parent;		
	}
	else
		return NULL;
}


/*void Tree::Tree_remove(string word)
{
	Tree *p, *t = find(word);
	if(t == NULL)
		cout<<endl<<"No such word found in dictionary"<<endl;
	else{
		this->size--;

		//Deleting Node 
		if(t->left == NULL && t->right == NULL)
		{
			p = t->parent;
			if(p!=NULL)
			{
				if(p->left == t)
					p->left = NULL;
				else
					p->right = NULL;
			}
			else
				root = NULL;
			free(t);
		}
		else if(t->left == NULL)
		{
			p = t->parent;
			if(p != NULL)
			{
				if(p->left == t)
					p->left = t->right;
				else
					p->right = t->right;
			}
			else
				root = t->right;
			free(t);
		}
		else if(t->right == NULL)
		{
			p = t->parent;
			if(p != NULL)
			{
				if(p->left == t)
					p->left = t->left;
				else
					p->right = t->left;
			}
			else
				root = t->left;
			free(t);
		}
		else{
			Tree *temp = findpresuc(word);
			t->word = temp->word;
			t->value = temp->value;
			p = temp->parent;
			if(temp->left == NULL && temp->right == NULL)
			{
				if(p!=NULL)
				{
					if(p->left == temp)
						p->left = NULL;
					else
						p->right = NULL;
				}
				else
					root = NULL;
				free(temp);
			}
			else if(temp->left != NULL)
			{
				if(p != NULL)
				{
					if(p->left == temp)
						p->left = temp->left;
					else
						p->right = temp->left;
				}
				else
					root = temp->left;
				free(temp);
			}
			else if(temp->right != NULL)
			{
				if(p != NULL)
				{
					if(p->left == temp)
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
//	return p;
}*/


void Tree::Tree_add(Tree *t, string word, string value)
{
	Tree *node = root;
	this->size++;
	if(root == NULL)
	{
		root = newNode(t->word, t->value);
		return;
	}
	int f =1;
	while(f){
			if(node->word < t->word){
				if(node->right == NULL)
				{
					t->parent = node;
					node->right = t;
					f=0;
				}
				else
					node = node->right;
			}
			else if(node->word > t->word)
			{
				if(node->left == NULL)
				{
					t->parent = node;
					node->left = t;
					f=0;
				}
				else
					node = node->left;
			}
			else
			{
				node->value = t->value;
				this->size--;
				return;
			}
	}

}


Tree* Tree::newNode(string word, string value)
{
	Tree *ptr = new Tree(word, value);
	return ptr;
}



#endif
