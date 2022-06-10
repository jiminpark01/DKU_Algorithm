#define min_degree 9    // 5, 7, 9  (차수 t)
#define max_children min_degree * 2     // 최대 자식노드 수 (2t)
#define max_keys max_children - 1       // 노드의 최대 key 수 (t-1)
#define min_keys min_degree - 1         // 노드의 최소 key 수 (2t-1)

// 노드 구조체
struct BTreeNode
{
    bool leaf;              // leaf 여부
    int key[max_keys + 1];  // key 배열
    int count_key;          // key 개수
    struct BTreeNode* child[max_children + 1];  // 자식노드 포인터배열
    int count_child;        // 자식노드 개수
};

struct BTreeNode* root;     // 루트 노드


// 필요한 함수 정의
int search(struct BTreeNode* node, int val);
struct BTreeNode* create_node(int val);
struct BTreeNode* split(int pos, struct BTreeNode* node, struct BTreeNode* parent);
struct BTreeNode* insert_node(int parent_pos, int val, struct BTreeNode* node, struct BTreeNode* parent);
void insert(int val);
void merge(struct BTreeNode* parent_node, int pos, int merge_pos);
void borrow_from_left(struct BTreeNode* parent_node, int current);
void borrow_from_right(struct BTreeNode* parent_node, int current);
void balance(struct BTreeNode* node, int child_pos);
int merge_child(struct BTreeNode* parent_node, int current);
int find_predecessor(struct BTreeNode* current_node);
int override_predecessor(struct BTreeNode* parent_node, int pos_search);
int find_successor(struct BTreeNode* current_node);
int override_successor(struct BTreeNode* parent_node, int pos_search);
void delete_inner(struct BTreeNode* current_node, int current);
int delete_value(int val, struct BTreeNode* node);  //
void delete (struct BTreeNode* node, int val);
void shuffle(int* arr, int num);
