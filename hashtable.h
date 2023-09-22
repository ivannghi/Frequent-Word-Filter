typedef struct lnode * NodePtr;
typedef struct lnode {
        char * word;
        int frequency;
        NodePtr next;
} node;
