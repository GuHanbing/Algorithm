#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;

#define AVL 
typedef struct Node* link;
struct Node
{
	int val;
	int height;
	link left;
	link right;
};

link insert(link & T, int val);
void L_Rotate(link & root);
void R_Rotate(link & root);
void freeTree(link T);
int getHeight(link T);
void updateHeight(link T);
int getBalanceFactor(link T);
void orderTraversal(link T, vector<int> & V);
int test_main()
{
	int N, temp;
	scanf("%d", &N);
	link root = NULL;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &temp);
		insert(root, temp);
	}
	vector<int> output;
	orderTraversal(root, output);
	vector<int>::iterator it = output.begin();
	cout << *it;
	it++;
	while (it != output.end())
	{
		printf(" %d", *it);
		it++;
	}
	printf("%d", root->val);
	return 0;
}

void orderTraversal(link T, vector<int> & V)
{
	if (T)
	{
		V.push_back(T->val);
		orderTraversal(T->left, V);
		orderTraversal(T->right, V);
	}

}


void R_Rotate(link & root)
{
	link A, B, C;
	A = root;
	B = A->left;
	C = B->right;
	A->left = C;
	B->right = A;
	root = B;
}

void L_Rotate(link & root)
{
	link A, B, C;
	A = root;
	B = A->right;
	C = B->left;
	A->right = C;
	B->left = A;
	root = B;
}
link insert(link & T, int val)
{

	if (T == NULL)          //如果该结点为空则创立新结点，结束递归
	{
		T = new Node;
		T->val = val;
		T->left = NULL;
		T->right = NULL;
		T->height = 1;             //插入的新结点高度为1
		return T;

	}


	if (val > T->val)                                 //插入右边  
	{
		T->right = insert(T->right, val);
		updateHeight(T);
#if defined(AVL)              //如果是AVL树，完成插入操作后要检查平衡因子
		if (getBalanceFactor(T) == -2)
		{
			if (getBalanceFactor(T->right) == -1)    //RR
			{
				L_Rotate(T);
			}
			else if (getBalanceFactor(T->right) == 1)  //LR
			{
				R_Rotate(T->right);
				L_Rotate(T);
			}

		}
#endif
	}
	else
	{
		T->left = insert(T->left, val);
		updateHeight(T);
#if defined(AVL)              //如果是AVL树，完成插入操作后要检查平衡因子
		if (getBalanceFactor(T) == 2)
		{
			if (getBalanceFactor(T->left) == 1)    //RR
			{
				R_Rotate(T);
			}
			else if (getBalanceFactor(T->left) == -1)  //LR
			{
				L_Rotate(T->left);
				R_Rotate(T);
			}
		}
#endif
	}

	return T;
}



void freeTree(link T)
{
	if (T->right)
		freeTree(T->right);
	if (T->left)
		freeTree(T->left);
	delete T;
}

int getHeight(link T)
{
	if (T == NULL)
		return 0;
	else
		return T->height;
}

int getBalanceFactor(link T)
{
	return getHeight(T->left) - getHeight(T->right);
}

void updateHeight(link T)
{
	T->height = max(getHeight(T->left), getHeight(T->right)) + 1;
}