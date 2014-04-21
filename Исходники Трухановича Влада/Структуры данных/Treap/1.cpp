#include <iostream>
#include <stdio.h>

// ��� �����
#include <algorithm>
#include <vector>
#include <memory.h>

using namespace std;

// ��� ������, ������������ ���������� ������
#define N 111111
struct cell {
    // ����, ���������
    int key,prior;
    
    // ������ ������ � ������� ����. 0 - ������ � ������
    int ls,rs;
} tree[N];

// ���������� ����������� ������, ����� ����� ������
int kv,root;

// ���������, ������� ����� ������ � ������ � ������� x
// �� ��� ������, ��� ��� ���������� ����� ����� ������ ������
// � ���������� left_tree, � ������� � right_tree
// � ����� ������ ��� ����� < key
void split(int x, int key, int& left_tree, int& right_tree) {
    // ���� �� ������ � 0, �.� ���, ��� ������ �� ����������
    if (!x) {
	// ����� ��� ������ - ���������
	left_tree = right_tree = 0;
	return;
    }
    if (key < tree[x].key) {
	// ���� �� ������ ����, �� ������ �������� ��������� -
	// �� ������ ��������� ������ ���� � right_tree, ����
	// ��� ����� � �� �������� ������ key.
	// � ��� � ����� ��������� ����� ������ �������, �������
	// � ������� ����� ������������ ������ �����������
	
	
	// ������� ��������� ��������� �������. ������� ����� ���������
	// ������������ ������ �� �����
	// ��������� ����� ������ - ��� ���������
	// ����� ������ ���������� - ������ ��, ��� ��� �����, ������� ��� ������ �� ������
	// � ��� � ������ ���������� �������, ���� ��� ������� � �� ������ ����� ������ � �� ������
	// ������� ���� ��������� x. �� ��� ��� ����������� ������ ��� ������������� ��������� �����
	// �� �� �������� ����� �����: ������ right_tree ������� x. ��� ����� ����� - ���������, �������
	// ����� ��� ����� split. ����������, ��� ��� �������� �������� ���������
	split(tree[x].ls, key, left_tree, tree[x].ls); 
	right_tree = x;
    } else {
	// ������������ ������
	
	split(tree[x].rs, key, tree[x].rs, right_tree);
	left_tree = x;
    }
}

// ��������� ���������� ��� ������ � ������ left_tree � right_tree
// � ����, ������ �������� ����� �������� ���������� x
void merge(int& x, int left_tree, int right_tree) {
    // ���� ���� �� �������� �� ����������
    if (!left_tree || !right_tree) {
	// �� �� �������, ����� ���������� � ������ ��� �� ����� x
	if (left_tree) x = left_tree;
	else x = right_tree;
	return;
    }
    
    // ������� ������ ������ ������ ������������. �� � ����� ������ ������ ������
    if (tree[left_tree].prior > tree[right_tree].prior) { 
	// ����� ��������� left_tree ���������� ��� ��, � ��� ������
	// ����� ������������ ����������� ������ ������� ��������� left_tree
	// � ������ right_tree
	merge(tree[left_tree].rs, tree[left_tree].rs, right_tree);
	x = left_tree;
    } else {
	// ������������ ������
	
	merge(tree[right_tree].ls, left_tree, tree[right_tree].ls);
	x = right_tree;
    }
}

// ��������� ������� ������� � ������ � ������ � x
// new_item - ��� ����� �������������� �������
void insert(int& x, int new_item) {
    // ���� ������ ������
    if (!x) {
	// ������ ����� ������� ������ ������
	x = new_item;
	return;
    }
    // ���� � ��� ����� ��� ����� �������� �������
    if (tree[new_item].prior > tree[x].prior) {
	// ����� �� ������ �������� ������� ��������� �� ��� �� ����� ������ ������ ��������
	// ��������� ��������� (��� ������) ����� ��������� ����� �������
	// ���� ����� ������� ������ ���������
	split(x, tree[new_item].key, tree[new_item].ls, tree[new_item].rs);
	x = new_item;
    } else {
	// ���� ��������� ��� ����, ������� � ����� ��������� ������ ���� ���� �������
	if (tree[new_item].key < tree[x].key) insert(tree[x].ls, new_item);
	else insert(tree[x].rs, new_item);
    }
}

// ���������, ������� ��������� ����� x
// �.� ��� ������ ����������� �������� � ���������� � ������� insert
// ��-�������� ��� ������ ���� ��������, ��� ��� ���������� ������
// �� rand() �������� ����� ��������
void insert(int x) {
    tree[++kv] = (cell) {x, rand(), 0, 0};
    insert(root, kv);
}

// �������� ������� � �������� ������
void erase(int& x, int key) {
    // ���� ������ �� �����, ������������ �� � ���
    if (!x) return;
    // ���� ����� ������ �������, ������ ���������� ��� � ���������-����
    // � �������� ����������� ������� �������
    if (tree[x].key == key) merge(x, tree[x].ls, tree[x].rs);
    else {
	// ����� �������, � ����� ��������� ������
	if (key < tree[x].key) erase(tree[x].ls, key);
	else erase(tree[x].rs, key);
    }
}

vector<int> b;
// ����� ������ (��� �����)
void print(int x) {
    if (!x) return;
    print( tree[x].ls );
    b.push_back(tree[x].key);
    print( tree[x].rs );
}

int n;

// ���������, ��������� �� �������� ������������������ (��� �����)
bool check(int n, int cur_rand) {
    vector<int> a(n),c;
    for (int i=0;i<n;i++) a[i] = i;
    c = a;
    
    root = kv = 0; memset(tree,0,sizeof(tree));
    b.clear();
    
    srand(cur_rand);
    random_shuffle(c.begin(),c.end());
    for (int i=0;i<n;i++) insert(c[i]);
    
    print(root);
    
    bool ans = (a == b);
    if (ans) printf("%d : OK\n",cur_rand);
    else printf("%d: WA\n",cur_rand);
    return ans;
}

int main() {
    cin >> n;
    int lim = 1 << 12;
    for (int i=0;i<lim;i++) 
	if (!check(n,i)) break;
    
    return 0;
}