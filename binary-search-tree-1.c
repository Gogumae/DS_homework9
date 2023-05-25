/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
void freeNode(Node* ptr);  //����� �޸𸮸� ��ȯ�ϴ� �Լ�
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
        printf("              [----- [������] [2019068057] -----]                \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

//����� �ݺ��� ���� Ʈ�� ���

void inorderTraversal(Node* ptr)
{
    if(ptr) {
        inorderTraversal(ptr->left);
        printf(" [%d] ", ptr->key);
        inorderTraversal(ptr->right);
    }
}

void preorderTraversal(Node* ptr)
{
    printf(" [%d] ", ptr->key);
    preorderTraversal(ptr->left);
    preorderTraversal(ptr->right);
}

void postorderTraversal(Node* ptr)
{
    postorderTraversal(ptr->left);
    postorderTraversal(ptr->right);
    printf(" [%d] ", ptr->key);
}


int insert(Node* head, int key)
{
    Node* new = (Node*)malloc(sizeof(Node));  //key���� ���� ���ο� ��� new �޸� �Ҵ�
    new->key = key;
    new->left = NULL;
    new->right = NULL;

    if(head->left == NULL) {  //���� Ʈ���� ����־����� ������� left�� new�� ����Ű�� ���� = new�� root�� ����
        head->left = new;
        return 0;
    }

    Node* now = head->left;  //Ʈ���� Ÿ�� �ٴ� now
    Node* parent = NULL;  //now�� ����ٴ� parent

    while(now != NULL) {
        if(new->key == now->key) {
            return 1;
        }
        parent = now;  //now�� ���� parent �̵�

        if(new->key < now->key) {  //�Է��� key�� ���� ����� key���� ������ ���� child�� �̵�
            now = now->left;
            }
        else {  //�Է��� key�� ���� ����� key���� ũ�� ���� child�� �̵�
            now = now->right;
            }
    }

    if(new->key < parent->key) {  //key ���� ���� parent�� child�� new ��ġ
        parent->left = new;
    }
    else {
        parent->right = new;
    }

    return 1;

}

int deleteLeafNode(Node* head, int key)
{
	if(head == NULL) {  //Ʈ�� ��ü�� root�� ������ ���� �޽��� ���
		printf("nothing to delete");
		return 0;
	}

	if(head->left == NULL) {
		printf("nothing to delete");
		return 0;
	}
	
	Node* now = head->left;  //Ʈ���� Ÿ��ٴ� now
	Node* parent = head;  //now�� �ڵ���ٴ� parent

	while(now != NULL) {  //now�� NULL�� �ƴҶ����� �ݺ�
		if(now->key == key) {  //�Է��� key�� ���� now�� ã���� ��
			if(now->left == NULL && now->right == NULL) {  //���� now�� ���� ��忴�ٸ�
				if(parent == head) {  //���� now�� root���ٸ�
					head->left = NULL;  //head��忡�� root�� ���´�
				}

				if(parent->left == now) {  //parent�� ���� child�� now���ٸ�
					parent->left = NULL;  //parent�� ���� child�� ���� ������
				}
				else {  //������ child�� now������ ������ child�� ���� ������
					parent->right = NULL;
				}
				free(now);  //now �޸� ��ȯ
			}
			else {
				printf("node is not a leaf node");  //���� ��尡 �ƴ϶�� �����޽��� ���
			}
			return 1;
		}

		parent = now;  //parent�� now�� ���� �� ĭ �̵�

		if(now->key < key) {  //now�� key�� �Էµ� key���� ���� ����, ������ child�� �̵�
			now = now->right;
		}
		else {
			now = now->left;
		}
	}

	printf("cannot find the node for key");  //now�� NULL, �� �Է��� key�� ���� ��� �߰� ���� �� �����޽��� ���
	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) {
		return NULL;
	}

	if(ptr->key < key) {  //�Էµ� ����� key���� �Է��� key�� �� ũ��
		ptr = searchRecursive(ptr->right, key);  //���� child�� ����� Ž��
	}
	else if(ptr->key > key) {  //�ݴ��� ��� ���� child�� ����� Ž��
		ptr = searchRecursive(ptr->left, key);
	}
	else {
		return 0;
	}
}

Node* searchIterative(Node* head, int key)
{
	Node* now = head->left;  //Ʈ���� Ÿ��ٴ� now

	while(now != NULL) {
		if(now->key == key) {  //now�� key�� �Է��� key�� ���ٸ� now ����
			return now;
		}
		if(now->key < key) {  //now�� key�� �Է��� key���� �۴ٸ� ������ child��, �ݴ�� ���� child�� �̵�
			now = now->right;
		}
		else {
			now = now->left;
		}
	}
	return NULL;
}

void freeNode(Node* ptr) {  //����� �޸𸮸� ��ȯ�ϴ� �Լ� ����
	if(ptr) {
		freeNode(ptr->left);  //����, ���� child�� ���� ��������� ���� ��ȯ
		freeNode(ptr->right);
		free(ptr);  //�Էµ� ��� ��ȯ
	}
}


int freeBST(Node* head)
{
	if(head->left == head) {  //���� Ʈ���� ����ִٸ� head��带 �޸� ��ȯ
		free(head);
		return 1;
	}

	Node* root = head->left;  //root ���
	freeNode(root);

	return 1;
}