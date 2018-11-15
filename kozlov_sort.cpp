#include <iostream>
#include <utility>


template <typename T>
struct node{
    T elmnt;
    node* nxt;
};

template <typename T>
void swap(node<T>*& first, node<T>*& second) {
    node<T>* newnode = first;
    first = second;
    second = newnode;
}

template <typename T>
class List{
 private:
    node<T>* first;
    node<T>* last;

 public:
    List() {
        first = nullptr;
        last = nullptr;
    }
    ~List() {
        node<T>* now = first;
        node<T>* next = nullptr;
        if (last != first)
            next = now->nxt;
        while (next != nullptr) {
            delete now;
            now = next;
            next = next->nxt;
        }
        delete(now);
    }
    void add(T a) {
        node<T>* element = new node<T>;
        element->elmnt = a;
        element->nxt = nullptr;
        if (first == nullptr) {
            first = element;
        } else {
            last->nxt = element;
        }
        last = element;
    }
    node<T>* begin() {
        return first;
    }
    node<T>* rbegin() {
        return last;
    }
};

template <typename T>
void sort(node<T>* first, node<T>* last) {
    if (first != last) {
        node<T>* newlast = first;
        node<T>* ptr = first;
        while (ptr != last) {
            ptr = ptr->nxt;
            if (ptr != last) {
                newlast = newlast->nxt;
                ptr = ptr->nxt;
            }
        }
        node<T>* newfirst = newlast->nxt;
        sort(first, newlast);
        sort(newfirst, last);
        merge(first, newlast, newfirst, last);
    }
}

template <typename T>
void merge(node<T>* first1, node<T>* last1, node<T>* first2, node<T>* last2) {
    List<T> result;
    node<T>* part1_iter = first1, * part2_iter = first2;
    node<T>* last = last2->nxt;
    last1->nxt = nullptr;
    last2->nxt = nullptr;
    while (part1_iter != nullptr || part2_iter != nullptr) {
        if (part1_iter == nullptr) {
            swap(part1_iter, part2_iter);
        } else {
            if (part2_iter != nullptr) {
                if (part2_iter->elmnt < part1_iter->elmnt) {
                    swap(part1_iter, part2_iter);
                }
            }
        }
        result.add(part1_iter->elmnt);
        part1_iter = part1_iter->nxt;
    }
    last1->nxt = first2;
    last2->nxt = last;
    node<T>* iter = first1;
    for (node<T>* i = result.begin(); i != nullptr; i = i->nxt) {
        iter->elmnt = i->elmnt;
        iter = iter->nxt;
    }
}

int main() {
    int64_t n;
    List<int64_t> arr;
    std::cin >> n;
    for (int64_t i = 1; i <= n; ++i) {
        int64_t a;
        std::cin >> a;
        arr.add(a);
    }
    sort(arr.begin(), arr.rbegin());
    for (auto i = arr.begin(); i != nullptr; i = i->nxt)
        std::cout << i->elmnt << " ";
    arr.~List();
}
