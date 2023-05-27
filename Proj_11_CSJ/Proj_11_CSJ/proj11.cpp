
#include <stdio.h>



// 포인터로 이진트리 구성
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
// 배열로 이진트리 구성
typedef struct NODE { int data; int leaf; } node;
// Full Binary Tree node number 1~15(root 1, left child n*2, right child n*2+1
node arr[] = { {0,0}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,0}, {9,0}, {10,0}, {11,0},
{12,0}, {13,0}, {14,0}, {15,0} };

// 중위 순회(배열)
void inorder_rec_arr(node* root, int number) {
	if (root[number].leaf) {
		inorder_rec_arr(root, number * 2);	// 왼쪽서브트리 순회
		printf("[%d] ", root[number].data); 	// 노드 방문
		inorder_rec_arr(root,number * 2 + 1);	// 오른쪽서브트리 순회
	}
	else {
		printf("[%d] ", root[number].data); 	// 노드 방문
	}
}

// 전위 순회(배열)
void preorder_rec_arr(node* root, int number) {
	if (root[number].leaf) {
		printf("[%d] ", root[number].data); 	// 노드 방문
		preorder_rec_arr(root, number * 2);	// 왼쪽서브트리 순회
		preorder_rec_arr(root, number * 2 + 1);	// 오른쪽서브트리 순회
	}
	else {
		printf("[%d] ", root[number].data); 	// 노드 방문
	}

}

// 후위 순회(배열)
void postorder_rec_arr(node* root, int number) {
	if (root[number].leaf) {
		postorder_rec_arr(root, number * 2);	// 왼쪽서브트리 순회
		postorder_rec_arr(root, number * 2 + 1);	// 오른쪽서브트리 순회
		printf("[%d] ", root[number].data); 	// 노드 방문

	}
	else {
		printf("[%d] ", root[number].data); 	// 노드 방문
	}

}

// 중위 순회
void inorder_rec(TreeNode* root) {
	if (root) {
		inorder_rec(root->left);	// 왼쪽서브트리 순회
		printf("[%d] ", root->data); 	// 노드 방문
		inorder_rec(root->right);	// 오른쪽서브트리 순회
	}
}


// 전위 순회
void preorder_rec(TreeNode* root) {
	if (root) {
		printf("[%d] ", root->data); 	// 노드 방문
		preorder_rec(root->left);	// 왼쪽서브트리 순회
		preorder_rec(root->right);	// 오른쪽서브트리 순회
	}
}

void postorder_rec(TreeNode* root) {
	if (root) {
		postorder_rec(root->left);	// 왼쪽 서브 트리 순회
		postorder_rec(root->right);	// 오른쪽 서브 트리 순회
		printf("[%d] ", root->data); 	// 노드 방문
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
	printf("중위 순회(rec) =");
	inorder_rec(root);
	printf("\n");
	printf("중위 순회(itr) =");
	inorder_iter(root);
	printf("\n");
	printf("배열 중위 순회(rec)=");
	inorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("전위 순회(rec) =");
	preorder_rec(root);
	printf("\n");
	printf("전위 순회(itr) =");
	preorder_iter(root);
	printf("\n");
	printf("배열 전위 순회(rec)=");
	preorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("후위 순회(rec) =");
	postorder_rec(root);
	printf("\n");
	printf("후위 순회(itr) =");
	postorder_iter(root);
	printf("\n");
	printf("배열 후위 순회(rec)=");
	postorder_rec_arr(arr, 1);
	printf("\n\n");
	return 0;
}