#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MAX(x,y) ((x) > (y) ? (x) : (y))

typedef struct ELEMENT {
	int id_num;
	char name[10];
}element;
typedef struct TreeNode {
	element std;
	struct TreeNode* left, * right;
} TreeNode;

// ================ ����ť �ڵ� ���� =================
#define MAX_QUEUE_SIZE 100
typedef TreeNode* qdata;
typedef struct { // ť Ÿ��
	qdata  data[MAX_QUEUE_SIZE];
	int  level[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ���� ���� ���� �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType* q, qdata item,int num)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
	q->level[q->rear] = num;
}

// ���� �Լ�
qdata dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
int peek(QueueType* q) {
	return q->level[q->front+1];
}

void level_order(TreeNode* ptr)
{
	QueueType q;
	int num = 0;
	int peek_num = 0;

	init_queue(&q);	 // ť �ʱ�ȭ

	if (ptr == NULL) {
		printf("���� Ʈ���Դϴ�.");
		return;
	}
	enqueue(&q, ptr, 1);
	while (!is_empty(&q)) {
		peek_num = peek(&q);
		if (peek_num != num) {
			putchar('\n');
			printf("Level%d ", peek_num);
		}
		num = peek_num;
		ptr = dequeue(&q);
		printf("[%d] ", ptr->std.id_num);
		if (ptr->left)
			enqueue(&q, ptr->left,num+1);
		if (ptr->right)
			enqueue(&q, ptr->right,num+1);
	}
}


TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->std = item;
	temp->left = temp->right = NULL;

	return temp;
}


TreeNode* insert_node(TreeNode* node, element key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) {

		return new_node(key);
	}

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key.id_num < node->std.id_num) {
		node->left = insert_node(node->left, key);
	}
	else if (key.id_num > node->std.id_num) {
		node->right = insert_node(node->right, key);
	}


	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->std.id_num)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->std.id_num)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// �� ��° ���
		TreeNode* temp = min_value_node(root->right);

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->std = temp->std;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->std.id_num);
	}

	return root;
}

// ���� ��ȸ
inorder(TreeNode* root) {
	if (root) {
		inorder(root->left);	// ���ʼ���Ʈ�� ��ȸ
		printf(" [%d] ", root->std.id_num); 	// ��� �湮
		inorder(root->right);	// �����ʼ���Ʈ�� ��ȸ
	}
}



//��ȯ���� Ž�� �Լ�
TreeNode* search(TreeNode * node, int  key)
{
	if (node == NULL)  return NULL;
	if (key == node->std.id_num) return node;     // (1)
	else if (key < node->std.id_num)
		return  search(node->left, key);   // (2)
	else
		return  search(node->right, key);  // (3)
}


int get_node_count(TreeNode* root) {

	int count = 0;

	if (root != NULL) {
		count = 1 + get_node_count(root->left) + get_node_count(root->right);
	}
	return count;
}


int get_leaf_count(TreeNode* root) {
	int count = 0;
	if (root != NULL) {
		if (root->left == NULL && root->right == NULL)
			return 1;
		else {
			count = get_leaf_count(root->left) + get_leaf_count(root->right);
		}
	}
	return count;
}

int get_height(TreeNode* root) {
	int h = 0;
	if (root != NULL) {
		h = 1 + MAX(get_height(root->left), get_height(root->right));

	}
	return h;
}


// ���� ��ȸ
TreeNode* delete_tree(TreeNode* root) {

	if (root) {
		delete_tree(root->left);	// ���� ���� Ʈ�� ��ȸ
		delete_tree(root->right);	// ������ ���� Ʈ�� ��ȸ
		printf(" [%d] ", root->std.id_num); 	// ��� �湮
		free(root);
	}

}


int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element item;
	item.id_num = 2021006; strcpy_s(item.name, 6,"name6");
	root = insert_node(root, item);
	item.id_num = 2021001; strcpy_s(item.name, 6, "name1");
	root = insert_node(root, item);
	item.id_num = 2021009; strcpy_s(item.name, 6, "name9");
	root = insert_node(root, item);
	item.id_num = 2021007; strcpy_s(item.name, 6, "name7");
	root = insert_node(root, item);
	item.id_num = 2021003; strcpy_s(item.name, 6, "name3");
	root = insert_node(root, item);
	item.id_num = 2021002; strcpy_s(item.name, 6, "name2");
	root = insert_node(root, item);
	item.id_num = 2021005; strcpy_s(item.name, 6, "name5");
	root = insert_node(root, item);
	item.id_num = 2021004; strcpy_s(item.name, 6, "name4");
	root = insert_node(root, item);
	item.id_num = 2021008; strcpy_s(item.name, 6, "name8");
	root = insert_node(root, item);
	item.id_num = 2021010; strcpy_s(item.name, 7, "name10");
	root = insert_node(root, item);
	printf("���� Ž�� Ʈ���� ��� ��, leaf��� ��, ���� ���ϱ�\n");
	printf("��� �� = %d \nleaf ��� �� = %d \n���� = %d \n\n", get_node_count(root), get_leaf_count(root), get_height(root));
	printf("���� Ž�� Ʈ�� ���� Ž�� ��ȸ ���\n");
	level_order(root);
	printf("\n\n");
	printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n���� Ž�� Ʈ������ 2021010 �˻�\n");
	tmp = search(root, 2021010);
	if (tmp != NULL)
		printf("�˻� ���� : �й� %d, �̸� %s \n", tmp->std.id_num,
			tmp->std.name);
	else
		printf("���� Ž�� Ʈ������ �˻� �л��� �߰߸��� \n");
	printf("\n���� Ž�� Ʈ������ 2021006 ����\n");
	delete_node(root, 2021006);
	printf("\n\n���� Ž�� Ʈ������ 2021006 �˻�\n");
	tmp = search(root, 2021006);
	if (tmp != NULL)
		printf("�˻� ���� : �й� %d, �̸� %s \n", tmp->std.id_num,
			tmp->std.name);
	else
		printf("���� Ž�� Ʈ������ �˻� �л��� �߰߸��� \n");
	printf("\n\n���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n");
	printf("\n\n���� Ž�� Ʈ�� ��ü ���� \n");
	printf("��� ���� ���� : ");
	root = delete_tree(root);
	printf("\n\n���� Ž�� Ʈ�� ���� Ž�� ��ȸ ���\n");
	level_order(root);
	printf("\n\n");
	return 0;
}
