typedef void* voidPtr;
typedef struct node Node;
typedef Node * Node_ptr;
typedef struct linkedList LinkedList;
typedef char *string;

struct linkedList{
	Node_ptr head;
	Node_ptr tail;
	int count;
};

struct node {
    voidPtr data;
    Node *next;
};

LinkedList createList(void);
Node * create_node(void *);
int add_to_list(LinkedList *,Node *);
void *get_first_element(LinkedList);
void *get_last_element(LinkedList);
void traverse(LinkedList, void (*)(void *));
void * getElementAt(LinkedList, int );
int indexOf(LinkedList, void *);
void * deleteElementAt(LinkedList *, int);
int asArray(LinkedList, void **);
LinkedList * filter(LinkedList, int (*)(void *));