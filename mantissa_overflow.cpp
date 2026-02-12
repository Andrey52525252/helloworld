#include <iostream>
// ваш кот сюда
#include <climits>
struct subset_node {
    int key;
    subset_node *left;
    subset_node *right;
    unsigned int height = 0;
};

bool init (subset_node **tree) {
    if (tree == nullptr) {
        return false;
    }
    *tree = nullptr;
    return true;
}

bool insert (subset_node **tree, int x) {
    subset_node *new_leaf = new subset_node();
    new_leaf -> key = x;
    new_leaf -> left = nullptr;
    new_leaf -> right = nullptr;
    if (*tree == nullptr) {
        *tree = new_leaf;
        return true;
    }
    subset_node *current = *tree;

    while (true) {
        if (x < current -> key) {
            if (current -> left == nullptr) {
                current -> left = new_leaf;
                return true;
            }
            else current = current -> left;
        }
        if (x > current -> key) {
            if (current -> right == nullptr) {
                current -> right = new_leaf;
                return true;
            }
            else current = current -> right;
        }
        if (x == current -> key) {
            delete new_leaf;
            return false;
        }
    }
}

bool remove (subset_node **tree, int x) {

    if (*tree == nullptr) return false;

    subset_node *current = *tree;
    subset_node *parent = nullptr;
    bool parent_from_left = true;    //здесь буду хранить информацию в какой ветке предка лежит current
    while (true) {
        if (x < current -> key) {
            if (current -> left == nullptr) return false;
            else {
                parent = current;
                parent_from_left = true;
                current = current -> left;
            }
        }
        else if (x > current -> key) {
            if (current -> right == nullptr) return false;
            else {
                parent = current;
                parent_from_left = false;
                current = current -> right;
            }
        }
        else if (x == current -> key) {
            if (parent == nullptr) {
                if (current -> left == nullptr && current -> right == nullptr) {
                    delete current;
                    *tree = nullptr;
                }
                else if (current -> left != nullptr) {
                    subset_node *closest_left_child = current -> left; 
                    subset_node *parent_of_child = current;
                    while (closest_left_child -> right != nullptr) {
                        parent_of_child = closest_left_child;
                        closest_left_child = closest_left_child -> right;
                    }
                    current -> key = closest_left_child -> key;
                    parent_of_child -> right == closest_left_child? parent_of_child -> right = closest_left_child -> left : parent_of_child -> left = closest_left_child -> left;
                    delete closest_left_child;
                    }
                else {
                    *tree = current -> right;
                    delete current;
                }
            }
            else if (current -> left == nullptr && current -> right == nullptr) {
                (parent_from_left? parent -> left : parent -> right) = nullptr;
                delete current;
            }
            else if (current -> left != nullptr && current -> right == nullptr) {
                parent_from_left? parent -> left = current -> left: parent -> right = current -> left;
                delete current;
            }
            else if (current -> left == nullptr && current -> right != nullptr) {
                parent_from_left? parent -> left = current -> right : parent -> right = current -> right;
                delete current;
            }
            else if (current -> left != nullptr && current -> right != nullptr) {
                subset_node *closest_left_child = current -> left; 
                subset_node *parent_of_child = current;
                while (closest_left_child -> right != nullptr) {
                    parent_of_child = closest_left_child;
                    closest_left_child = closest_left_child -> right;
                }
                current -> key = closest_left_child -> key;
                parent_of_child -> right == closest_left_child? parent_of_child -> right = closest_left_child -> left : parent_of_child -> left = closest_left_child -> left;
                delete closest_left_child;

            }
            return true;
        }
    }
}

subset_node* find (subset_node *sn, int x) {
    subset_node *current = sn;
    while (true) {
        if (x < current -> key) {
            if (current -> left == nullptr) return NULL;
            else current = current -> left;
        }
        if (x > current -> key) {
            if (current -> right == nullptr) return NULL;
            else current = current -> right;
        }
        if (x == current -> key) {
            return current;
        }
    }
}
unsigned count = 0;
void recursion (subset_node *sn) {       //Вспомогательная функция, буду вызывать в size и считать количество вызовов
    if (sn != nullptr) {
        count ++;
        if (sn -> right != nullptr) recursion(sn -> right);
        if (sn ->left != nullptr) recursion(sn -> left);
    }
}


unsigned int size (subset_node *sn) {
    count = 0;
    recursion(sn);
    return(count);
}

unsigned int height (subset_node *sn) {
    if (sn == nullptr) return 0;
    int left_height = height(sn -> left);
    int right_height = height(sn -> right);
    if (left_height > right_height) return left_height + 1;
    else return right_height + 1;
}

void destructor (subset_node **sn) {
    subset_node *current = *sn;
    if (current -> left != nullptr) destructor(&(current -> left));
    if (current -> right != nullptr) destructor(&(current -> right));
    delete current;
}
void add_to_arr(int* arr, int x, int length) {
    int i = 0;
    while (i < length && arr[i] != INT_MIN) i ++;
    arr[i] = x;
}
void helper (subset_node *sn, int* arr, int length) {
    if (sn -> left != nullptr) helper(sn -> left, arr, length);
    add_to_arr(arr, sn -> key, length);
    if (sn -> right != nullptr) helper(sn -> right, arr, length);
}


int* DFS (subset_node *sn) {
    unsigned int length = size(sn);
    int* arr = new int[length];
    for (int i = 0; i < length; i ++) arr[i] = INT_MIN; 
    helper(sn, arr, length);
    return(arr);
}

#include <random>
#include <chrono>
#include <climits>
using std::cout;
using std::endl;
double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}
int rand_uns(int min, int max)
{
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        static std::default_random_engine e(seed);
        std::uniform_int_distribution<int> d(min, max);
        return d(e);
}
int main()
{
    unsigned int n = 10000;
    int *sequent_sequence = new int[n],
        *rand_sequence_10 = new int[n],
        *rand_sequence_100 = new int[n],
        *rand_sequence_n = new int[n],
        *rand_sequence_unique = new int[n],
        *sorted_sequence_unique = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);
//----------- Initialization
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sequent_sequence[i] = i;
        rand_sequence_10[i] = rand_uns(0, 10);
        rand_sequence_100[i] = rand_uns(0, 100);
        rand_sequence_n[i] = rand_uns(0, n);
    }
    for (unsigned int i = 0; i < n; i++)
    {
        rand_sequence_unique[i] = rand_uns(0, INT_MAX);
        for (unsigned int j = 0; j < i; j++)
            if (rand_sequence_unique[i] == rand_sequence_unique[j])
            {
                i--;
                break;
            }
    }
    for (unsigned int i = 0; i < n; i++)
        sorted_sequence_unique[i] = rand_sequence_unique[i];
    for (unsigned int i = 0; i < n; i++)
        for (unsigned int j = 0; j < n - i - 1; j++)
            if (sorted_sequence_unique[j] > sorted_sequence_unique[j + 1])
            {
                int tmp = sorted_sequence_unique[j];
                sorted_sequence_unique[j] = sorted_sequence_unique[j + 1];
                sorted_sequence_unique[j + 1] = tmp;
            }

    finish = get_time();
    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
    subset_node *sn;
    init(&sn);
//----------- Test 000 Insert of a sequent sequence
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, sequent_sequence[i]);
    }
    finish = get_time();
    if (size(sn) != n)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, wrong number of elements !!! ---" << endl;
        return 0;
    }
    if (height(sn) != n)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, wrong height !!! ---" << endl;
        return 0;
    }
    cout << "000 Insert of a sequent sequence: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 001 Finding of a sequent sequence
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, sequent_sequence[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "001 Finding of a sequent sequence: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 002 Remove of a sequent sequence
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, sequent_sequence[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "002 Remove of a sequent sequence: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 003 Insert of a random sequence (0 - 10)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_10[i]);
    }
    finish = get_time();
    auto content = DFS(sn);
    auto size_content = size(sn);
    for (unsigned int i = 0; i < size_content - 1; i++)
        if (content[i] >= content[i + 1])
        {
            cout <<endl <<"--- !!! Failed content order, the left is larger than the right !!! ---" << endl;
            return 0;
        }
    delete[] content;
    cout << "003 Insert of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 004 Finding of a random sequence (0 - 10)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_10[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "004 Finding of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 005 Remove of a random sequence (0 - 10)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, rand_sequence_10[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "005 Remove of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 006 Insert of a random sequence (0 - 100)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_100[i]);
    }
    finish = get_time();
    content = DFS(sn);
    size_content = size(sn);
    for (unsigned int i = 0; i < size_content - 1; i++)
        if (content[i] >= content[i + 1])
        {
            cout <<endl <<"--- !!! Failed content order, the left is larger than the right !!! ---" << endl;
            return 0;
        }
    delete[] content;
    cout << "006 Insert of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 007 Finding of a random sequence (0 - 100)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_100[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "007 Finding of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 008 Remove of a random sequence (0 - 100)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, rand_sequence_100[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "008 Remove of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 009 Insert of a random sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_n[i]);
    }
    finish = get_time();
    cout << "009 Insert of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 010 Finding of a random sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_n[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "010 Finding of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 011 Remove of a random sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, rand_sequence_n[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "011 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 012 Insert of an unique sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_unique[i]);
    }
    finish = get_time();
    cout << "012 Insert of an unique sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 013 Finding of an unique sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_unique[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "013 Finding of an unique sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 014 Checking the searchiness of the tree
    content = DFS(sn);
    size_content = size(sn);
    if (size_content != n)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, wrong number of elements !!! ---" << endl;
        return 0;
    }
    for (unsigned int i = 0; i < size_content; i++)
    {
        if (content[i] != sorted_sequence_unique[i])
        {
            cout <<endl <<"--- !!! Failed order, DFS is supposed to sort the data !!! ---" << endl;
            return 0;
        }
    }
    delete[] content;
    cout << "014 Checking the searchiness of the tree: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 015 Remove of an unique sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, sorted_sequence_unique[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "015 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;

//----------- End of tests
//
    cout << "-----------" << endl <<"Alltests finished, total time: \t" << total << endl;
    delete[] sequent_sequence;
    delete[] rand_sequence_10;
    delete[] rand_sequence_100;
    delete[] rand_sequence_n;
    delete[] rand_sequence_unique;
    delete[] sorted_sequence_unique;
    return 0;
}