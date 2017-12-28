#include <iostream>

template <typename T>
struct node{
    T elmnt;
    node* nxt;
};

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
void sort(node<T>* first, node<T>* last, uint64_t size) {
    if (size > 1) {
        node<T>* mid1 = first;
        int64_t c = 1;
        while (c < size / 2) {
            c++;
            mid1 = mid1->nxt;
        }
        node<T>* mid2 = mid1->nxt;
        sort(first, mid1, size / 2);
        sort(mid2, last, size - size / 2);
        merge(first, mid1, mid2, last);
    }
}

template <typename T>
void merge(node<T>* first1, node<T>* last1, node<T>* first2, node<T>* last2) {
    List<T> result;
    node<T>* part1_iter = first1, * part2_iter = first2;
    while (part1_iter != first2 && part2_iter != last2->nxt) {
        if (part1_iter->elmnt <= part2_iter->elmnt) {
            result.add(part1_iter->elmnt);
            part1_iter = part1_iter->nxt;
        } else {
            result.add(part2_iter->elmnt);
            part2_iter = part2_iter->nxt;
        }
    }
    while (part1_iter != first2) {
        result.add(part1_iter->elmnt);
        part1_iter = part1_iter->nxt;
    }
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
    sort(arr.begin(), arr.rbegin(), n);
    for (auto i = arr.begin(); i != nullptr; i = i->nxt)
        std::cout << i->elmnt << " ";
    arr.~List();
}
