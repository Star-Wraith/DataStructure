
#include <stdio.h>



// �����ͷ� ����Ʈ�� ����
typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
// Full Binary Tree node number 1~15(root : 1)
TreeNode n15 = { 15, NULL, NULL };
TreeNode n14 = { 14, NULL, NULL };
TreeNode n13 = { 13, NULL, NULL };
TreeNode n12 = { 12, NULL, NULL };
TreeNode n11 = { 11, NULL, NULL };
TreeNode n10 = { 10, NULL, NULL };
TreeNode n9 = { 9, NULL, NULL };
TreeNode n8 = { 8, NULL, NULL };
TreeNode n7 = { 7, &n14, &n15 };
TreeNode n6 = { 6, &n12, &n13 };
TreeNode n5 = { 5, &n10, &n11 };
TreeNode n4 = { 4, &n8, &n9 };
TreeNode n3 = { 3, &n6, &n7 };
TreeNode n2 = { 2, &n4, &n5 };
TreeNode n1 = { 1, &n2, &n3 };
TreeNode* root = &n1;
// �迭�� ����Ʈ�� ����
typedef struct NODE { int data; int leaf; } node;
// Full Binary Tree node number 1~15(root 1, left child n*2, right child n*2+1
node arr[] = { {0,0}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,0}, {9,0}, {10,0}, {11,0},
{12,0}, {13,0}, {14,0}, {15,0} };

// ���� ��ȸ(�迭)
void inorder_rec_arr(node* root, int number) {
	if (root[number].leaf) {
		inorder_rec_arr(root, number * 2);	// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root[number].data); 	// ��� �湮
		inorder_rec_arr(root,number * 2 + 1);	// �����ʼ���Ʈ�� ��ȸ
	}
	else {
		printf("[%d] ", root[number].data); 	// ��� �湮
	}
}

// ���� ��ȸ(�迭)
void preorder_rec_arr(node* root, int number) {
	if (root[number].leaf) {
		printf("[%d] ", root[number].data); 	// ��� �湮
		preorder_rec_arr(root, number * 2);	// ���ʼ���Ʈ�� ��ȸ
		preorder_rec_arr(root, number * 2 + 1);	// �����ʼ���Ʈ�� ��ȸ
	}
	else {
		printf("[%d] ", root[number].data); 	// ��� �湮
	}

}

// ���� ��ȸ(�迭)
void postorder_rec_arr(node* root, int number) {
	if (root[number].leaf) {
		postorder_rec_arr(root, number * 2);	// ���ʼ���Ʈ�� ��ȸ
		postorder_rec_arr(root, number * 2 + 1);	// �����ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root[number].data); 	// ��� �湮

	}
	else {
		printf("[%d] ", root[number].data); 	// ��� �湮
	}

}

// ���� ��ȸ
void inorder_rec(TreeNode* root) {
	if (root) {
		inorder_rec(root->left);	// ���ʼ���Ʈ�� ��ȸ
		printf("[%d] ", root->data); 	// ��� �湮
		inorder_rec(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}


// ���� ��ȸ
void preorder_rec(TreeNode* root) {
	if (root) {
		printf("[%d] ", root->data); 	// ��� �湮
		preorder_rec(root->left);	// ���ʼ���Ʈ�� ��ȸ
		preorder_rec(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}

void postorder_rec(TreeNode* root) {
	if (root) {
		postorder_rec(root->left);	// ���� ���� Ʈ�� ��ȸ
		postorder_rec(root->right);	// ������ ���� Ʈ�� ��ȸ
		printf("[%d] ", root->data); 	// ��� �湮
	}
}

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void push(TreeNode* p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}

TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}

void preorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left) {
			push(root);
			printf("[%d] ", root->data);
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}

void postorder_iter(TreeNode* root)
{
	int i = 0;
	int reverse[SIZE];
	push(root);
	while (1) {
		
		root = pop();
		if (!root) break;
		reverse[i++] = root->data;
		if (root->left != NULL)
			push(root->left);
		if (root->right != NULL)
			push(root->right);

	}
	for (i = i - 1; i >= 0; --i) {
		printf("[%d] ", reverse[i]);
	}
}


int main(void)
{
	printf("���� ��ȸ(rec) =");
	inorder_rec(root);
	printf("\n");
	printf("���� ��ȸ(itr) =");
	inorder_iter(root);
	printf("\n");
	printf("�迭 ���� ��ȸ(rec)=");
	inorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("���� ��ȸ(rec) =");
	preorder_rec(root);
	printf("\n");
	printf("���� ��ȸ(itr) =");
	preorder_iter(root);
	printf("\n");
	printf("�迭 ���� ��ȸ(rec)=");
	preorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("���� ��ȸ(rec) =");
	postorder_rec(root);
	printf("\n");
	printf("���� ��ȸ(itr) =");
	postorder_iter(root);
	printf("\n");
	printf("�迭 ���� ��ȸ(rec)=");
	postorder_rec_arr(arr, 1);
	printf("\n\n");
	return 0;
}