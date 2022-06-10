#include <stdio.h>
#include <stdlib.h>     // srand, rand 함수가 포함되어 있는 헤더파일
#include <stdbool.h>
#include <Windows.h>
//#include <time.h>       // time 함수가 포함되어 있는 헤더파일
#include "Btree.h"

// 검색
int search(struct BTreeNode* node, int val) {
    if (!node) {
        return 0;
    }
    struct BTreeNode* level = node;
    while (true) {
        int pos;
        for (pos = 0; pos < level->count_key; pos++) {
            if (val == level->key[pos])
                return 1;
            else if (val < level->key[pos])
                break;
        }
        if (level->leaf)
            break;
        level = level->child[pos];
    }
    return 0;
}

// 데이터를 받아 노드 생성
struct BTreeNode* create_node(int val) {
    struct BTreeNode* new_node;
    new_node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    new_node->leaf = false;
    new_node->key[0] = val;    // 생성한 노드의 첫번째 key값 : 받은 데이터 val
    new_node->count_key = 1;   // 노드의 정보 초기화
    new_node->count_child = 0;
    return new_node;
}

// 노드의 데이터를 분리하여 다른 노드에 분배
struct BTreeNode* split(int pos, struct BTreeNode* node, struct BTreeNode* parent) {
    int mid;    // 중앙값 (분리 기준)
    mid = node->count_key / 2;
    struct BTreeNode* right;    // 분리한 값을 새로 넣을 오른쪽 노드 생성

    right = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    right->leaf = node->leaf;   // 현재 노드와 분리된 오른쪽 노드의 리프 여부 같음
    right->count_key = 0;       // 오른쪽 노드 정보 초기화
    right->count_child = 0;

    int num = node->count_key;
    for (int i = mid + 1; i < num; i++) { // 분리할 노드에 키 담기
        right->key[i - (mid + 1)] = node->key[i];
        right->count_key++;
        node->count_key--;
    }

    if (!node->leaf) {   // 현재 노드가 리프가 아닐 경우 자식노드 담기
        num = node->count_child;
        for (int i = mid + 1; i < num; i++) { // 오른쪽 노드에 현재 노드의 자식노드 절반 담기
            right->child[i - (mid + 1)] = node->child[i];
            right->count_child++;   // 자식 노드 개수 정리
            node->count_child--;
        }
    }

    // 분리할 때 부모노드 처리
    if (node == root) {  // 루트노드 : 부모노드 새로 만들기
        struct BTreeNode* new_parent_node;
        new_parent_node = create_node(node->key[mid]);  // 새 부모노드 생성 (중앙값 이용)
        node->count_key--;
        new_parent_node->child[0] = node;   // 새 부모노드의 왼쪽 자식노드는 현재 노드
        new_parent_node->child[1] = right;  // 오른쪽 자식노드는 오른쪽노드

        new_parent_node->count_child = 2;
        return new_parent_node;
    }
    else {   // 루트노드가 아닐 경우 : 기존 부모노드 활용
        for (int i = parent->count_key; i > pos; i--) { // 키 배치
            parent->key[i] = parent->key[i - 1];
            parent->child[i + 1] = parent->child[i];
        }

        parent->key[pos] = node->key[mid];  // 부모노드에 값 넣기
        parent->count_key++;    // 키 개수 정리
        node->count_key--;
        parent->child[pos + 1] = right; // 왼쪽노드는 그대로, 오른쪽노드는 부모노드에 연결
        parent->count_child += 1;
    }
    return node;
}

// 노드에 값 삽입
struct BTreeNode* insert_node(int parent_pos, int val, struct BTreeNode* node, struct BTreeNode* parent) {
    int pos;    // 현재 노드에서 키의 위치
    for (pos = 0; pos < node->count_key; pos++) {
        if (val == node->key[pos]) {    // 노드의 pos번 째 키와 val이 같으면
            return node;
        }
        else if (val < node->key[pos]) {    // val이 노드의 pos번 째 키보다 작으면
            break;
        }
    }
    if (!node->leaf) {  // leaf가 아니면
        node->child[pos] = insert_node(pos, val, node->child[pos], node);
        if (node->count_key == max_keys + 1) {  // 현재 노드의 키 개수가 규칙에 맞지 않으면
            node = split(parent_pos, node, parent); // 위로 분리
        }
    }
    else {  // leaf이면
        for (int i = node->count_key; i > pos; i--) { // 노드를 뒤로 한칸 씩 옮김
            node->key[i] = node->key[i - 1];    // 키도 뒤로 한칸 씩
            node->child[i + 1] = node->child[i];    // 자식노드도 뒤로 한칸 씩
        }

        node->key[pos] = val;   // pos 위치에 val 삽입
        node->count_key++;      // 키 개수 정리
        if (node->count_key == max_keys + 1) {  // leaf 노드가 꽉 차면
            node = split(parent_pos, node, parent); // 분리
        }
    }
    return node;
}

// 삽입 함수!! //
void insert(int val) {
    if (!root) {                    // root가 없으면
        root = create_node(val);    // 생성
        root->leaf = true;          // 생성된 노드는 root이자 leaf
        return;
    }
    else {  // root가 있으면
        root = insert_node(0, val, root, root); // root가 부모이자 leaf 노드
    }
}

// 병합
void merge(struct BTreeNode* parent_node, int pos, int merge_pos) {
    int merge_idx = parent_node->child[merge_pos]->count_key;   // merge의 주체 노드 쪽에 merge될 키 위치 지정
    parent_node->child[merge_pos]->key[merge_idx] = parent_node->key[merge_pos];    // 부모노드의 키를 merge
    parent_node->child[merge_pos]->count_key++;

    for (int i = 0; i < parent_node->child[pos]->count_key; i++) {
        parent_node->child[merge_pos]->key[merge_idx + 1 + i] = parent_node->child[pos]->key[i];
    }

    int merge_child_index = parent_node->child[merge_pos]->count_child; // 남은 키를 merge한 노드로 옮기기
    for (int i = 0; i < parent_node->child[pos]->count_child; i++) {
        parent_node->child[merge_pos]->child[merge_child_index + i] = parent_node->child[pos]->child[i];
        parent_node->child[merge_pos]->count_child++;
    }

    free(parent_node->child[pos]);  // merge된 후 반대편 노드 해제

    for (int i = merge_pos; i < (parent_node->count_key) - 1; i++) {    // 부모노드의 키 재정비
        parent_node->key[i] = parent_node->key[i + 1];
    }
    parent_node->count_key--;

    for (int i = merge_pos + 1; i < (parent_node->count_child) - 1; i++) {  // merge한 노드 뒷 노드부터 재배열
        parent_node->child[i] = parent_node->child[i + 1];
    }
    parent_node->count_child--;
}

// 왼쪽에서 빌리는 함수
void borrow_from_left(struct BTreeNode* parent_node, int current) {
    int index = 0;  // 빌리는 주체노드에 빌려주는 키가 들어가야 할 위치

    // 노드 한칸씩 뒤로 이동
    for (int i = 0; i < parent_node->child[current]->count_key; i++) {
        parent_node->child[current]->key[i + 1] = parent_node->child[current]->key[i];
    }
    parent_node->child[current]->key[index] = parent_node->key[current - 1];    // 빌리는 키는 부모로부터 빌림
    parent_node->child[current]->count_key++;

    int sibling_index_top = (parent_node->child[current - 1]->count_key) - 1;   // 형제노드 중 마지막 키 부모로 올리기
    parent_node->key[current - 1] = parent_node->child[current - 1]->key[sibling_index_top];    // 부모노드는 빌려준 왼쪽 형제노드의 키를 가져옴
    parent_node->child[current - 1]->count_key--;

    // 자식노드 위치 정리
    if (parent_node->child[current - 1]->count_child > 0) { // 형제노드 자식이 있는 경우
        int child_index = (parent_node->child[current - 1]->count_child) - 1;
        // 자식노드 위치 정리
        for (int i = parent_node->child[current]->count_child; i > 0; i--) {
            parent_node->child[current]->child[i] = parent_node->child[current]->child[i - 1];
        }

        parent_node->child[current]->child[0] = parent_node->child[current - 1]->child[child_index];
        parent_node->child[current]->count_child++;

        parent_node->child[current - 1]->count_child--;
    }
}
// 오른쪽에서 빌리는 함수
void borrow_from_right(struct BTreeNode* parent_node, int current)
{
    int index = parent_node->child[current]->count_key; // 빌리는 주체노드에 빌려주는 키가 들어가야 할 위치
    parent_node->child[current]->key[index] = parent_node->key[current];    // 빌리는 키는 부모로부터 빌림
    parent_node->child[current]->count_key++;

    int sibling_index_top = 0;
    parent_node->key[current] = parent_node->child[current + 1]->key[sibling_index_top];    // 부모노드는 빌려준 형제노드의 키를 가져옴

    // 키 위치 정리
    for (int i = 0; i < (parent_node->child[current + 1]->count_key) - 1; i++) {
        parent_node->child[current + 1]->key[i] = parent_node->child[current + 1]->key[i + 1];
    }
    parent_node->child[current + 1]->count_key--;

    int sibling_index = 0;
    // 자식노드 위치 정리
    if (parent_node->child[current + 1]->count_child > 0) {
        int child_index = parent_node->child[current]->count_child;
        parent_node->child[current]->child[child_index] = parent_node->child[current + 1]->child[sibling_index];
        parent_node->child[current]->count_child++;

        for (int i = 0; i < parent_node->child[current + 1]->count_child - 1; i++) {
            parent_node->child[current + 1]->child[i] = parent_node->child[current + 1]->child[i + 1];
        }
        parent_node->child[current + 1]->count_child--;
    }
}


void balance(struct BTreeNode* node, int child_pos) {
    if (child_pos == 0) {   // 자식노드의 키 위치가 가장 왼쪽일 경우, 오른쪽 부모와 형제 봄
        if (node->child[child_pos + 1]->count_key > min_keys) {
            borrow_from_right(node, child_pos);
        }
        else {
            merge(node, child_pos + 1, child_pos);
        }
        return;
    }

    else if (child_pos == (node->count_key)) {  // 자식노드의 키 위치가 가장 오른쪽일 경우, 왼쪽 부모와 형제 봄
        if (node->child[child_pos - 1]->count_key > min_keys) {
            borrow_from_left(node, child_pos);
        }
        else {
            merge(node, child_pos, child_pos - 1);
        }
        return;
    }
    else {  // 나머지 위치일 경우
        if (node->child[child_pos - 1]->count_key > min_keys) {
            borrow_from_left(node, child_pos);
        }
        else if (node->child[child_pos + 1]->count_key > min_keys) {
            borrow_from_right(node, child_pos);
        }
        else {
            merge(node, child_pos, child_pos - 1);
        }
        return;
    }
}

// 내부노드 기준으로 자식들을 merge
int merge_child(struct BTreeNode* parent_node, int current) {
    int merge_index = parent_node->child[current]->count_key;

    int val_parent_node = parent_node->key[current];
    parent_node->child[current]->key[merge_index] = parent_node->key[current];
    parent_node->child[current]->count_key++;

    // 합치려는 노드에 형제 노드 값 가져옴
    for (int i = 0; i < parent_node->child[current + 1]->count_key; i++) {
        parent_node->child[current]->key[merge_index + 1 + i] = parent_node->child[current + 1]->key[i];
        parent_node->child[current]->count_key++;
    }
    // 형제노드의 자식노드 가져옴
    for (int i = 0; i < parent_node->child[current + 1]->count_child; i++) {
        parent_node->child[current]->child[merge_index + 1 + i] = parent_node->child[current + 1]->child[i];
        parent_node->child[current]->count_child++;
    }
    // 부모노드(내부노드), 자식노드 재배열
    for (int i = current; i < parent_node->count_key; i++) {
        parent_node->key[i] = parent_node->key[i + 1];
        parent_node->count_key--;
    }
    for (int i = current + 1; i < parent_node->count_child; i++) {
        parent_node->child[i] = parent_node->child[i + 1];
        parent_node->count_child--;
    }
    return val_parent_node;
}

// predecessor 찾기
int find_predecessor(struct BTreeNode* current_node) {
    int predecessor;
    if (current_node->leaf) {
        return current_node->key[current_node->count_key - 1];
    }
    return find_predecessor(current_node->child[(current_node->count_child) - 1]);
}
// 내부노드에 덮어씌우기
int override_predecessor(struct BTreeNode* parent_node, int pos_search) {
    int predecessor = find_predecessor(parent_node->child[pos_search]);
    parent_node->key[pos_search] = predecessor;
    return predecessor;
}

// successor 찾기
int find_successor(struct BTreeNode* current_node) {
    int successor;
    if (current_node->leaf) {
        return current_node->key[0];
    }
    return find_successor(current_node->child[0]);
}
// 내부노드에 덮어씌우기
int override_successor(struct BTreeNode* parent_node, int pos_search) {
    int successor = find_successor(parent_node->child[pos_search + 1]);
    parent_node->key[pos_search] = successor;
    return successor;
}

// 내부노드의 값 지우기
void delete_inner(struct BTreeNode* current_node, int current) {
    int cessor = 0;
    int deleted_for_merge = 0;

    if (current_node->child[current]->count_key >= current_node->child[current + 1]->count_key) {
        if (current_node->child[current]->count_key > min_keys) {
            cessor = override_predecessor(current_node, current);
            delete_value(cessor, current_node->child[current]);
        }
        else {
            deleted_for_merge = merge_child(current_node, current);
            delete_value(deleted_for_merge, current_node->child[current]);
        }
    }
    else {
        if (current_node->child[current + 1]->count_key > min_keys) {
            cessor = override_successor(current_node, current);
            delete_value(cessor, current_node->child[current + 1]);
        }
        else {
            deleted_for_merge = merge_child(current_node, current);
            delete_value(deleted_for_merge, current_node->child[current]);
        }
    }
}

// 노드와 값 지우기
int delete_value(int val, struct BTreeNode* node) {
    int pos;
    int flag = false;
    for (pos = 0; pos < node->count_key; pos++) {
        if (val == node->key[pos]) {
            flag = true;
            break;
        }
        else if (val < node->key[pos]) {
            break;
        }
    }
    if (flag) {
        if (node->leaf) {
            for (int i = pos; i < node->count_key; i++) {
                node->key[i] = node->key[i + 1];
            }
            node->count_key--;
        }
        else {
            delete_inner(node, pos);
        }
        return flag;
    }
    else {
        if (node->leaf) {
            return flag;
        }
        else {
            flag = delete_value(val, node->child[pos]);
        }
    }
    if (node->child[pos]->count_key < min_keys) {
        balance(node, pos);
    }

    return flag;
}

// 삭제 함수!! //
void delete (struct BTreeNode* node, int val) {
    if (!node) {
        return;
    }
    int flag = delete_value(val, node);
    if (!flag) {
        return;
    }
    if (node->count_key == 0) {
        node = node->child[0];
    }
    root = node;
}

// 랜덤으로 삽입하기 위해 섞기
void shuffle(int* arr, int num) {
    srand((unsigned)time(NULL));
    int temp;
    int ran;
    for (int i = 0; i < num - 1; i++) {
        ran = rand() % (num - i) + i;
        temp = arr[i];
        arr[i] = arr[ran];
        arr[ran] = temp;
    }
}


int main(void) {

    static int value[10000];
    int random_value[1000];
    int delete_index = rand() % 500;
    int count = 0;
    double start, end, insert_time, delete_time;

    //printf("Minimum degree t = %d\n", min_degree);

    for (int i = 0; i < 10000; i++) {   // 배열 초기화
        value[i] = i;
    }
    shuffle(value, 10000);
    for (int i = 0; i < 1000; i++) {    // 랜덤값 1000개
        random_value[i] = value[i]; 
    }
    // 삽입
    start = (double)clock() / CLOCKS_PER_SEC;   // 시작 시간
    for (int i = 0; i < 1000; i++) {
        insert(random_value[i]);
    }

    // 삭제
    for (int i = delete_index; i < delete_index + 500; i++) {
        delete (root, random_value[i]);
    }
    end = (double)clock() / CLOCKS_PER_SEC;     // 종료 시간

    // 총 수행 시간
    printf("Insert Time + Delete Time : %lf\n", end - start);   // 총 수행시간

    return 0;
}
