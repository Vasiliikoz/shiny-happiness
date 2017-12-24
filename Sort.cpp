#include <iostream>
#include <iomanip>

using namespace std;

struct node{
    int64_t elmnt;
    node* nxt;
};

class List{
private:
    int64_t size;
    node* first;
    node* last;
public:
    List() {
        size = 0;
        first = nullptr;
        last = nullptr;
    }
    List(node* element,int64_t nsize,node* lastelement) {
        first = element;
        last = lastelement;
        size = nsize;
    }
    void add(int64_t a) {
        if (size == 0) {
            node* element = new node;
            element->elmnt = a;
            element->nxt = nullptr;
            first = element;
            last = element;
        } else {
            node* element = new node;
            last->nxt = element;
            element->elmnt = a;
            element->nxt = nullptr;
            last = element;
        }
        size++;
    }
    void inpart(node* element, int64_t val) {
        last = element;
        last->nxt = nullptr;
        size = val;
    }
    node* begin() {
        return first;
    }
    node* rbegin() {
        return last;
    }
    int64_t asize() {
        return size;
    }
};

void merge(node* a, node* b, int64_t sizenow) {
    if (sizenow == 2) {
        if (a->elmnt > b->elmnt) {
            auto c = a->elmnt;
            a->elmnt = b->elmnt;
            b->elmnt = c;
        }
    }
    if (sizenow > 2) {
        auto mid1 = a;
        int64_t c = 1;
        while (c < sizenow / 2) {
            c++;
            mid1 = mid1->nxt;
        }
        auto mid2 = mid1->nxt;
        merge(a, mid1, sizenow / 2);
        merge(mid2, b, sizenow - sizenow / 2);
        List result;
        auto l1 = a;
        auto l2 = mid2;
        while (result.asize() < sizenow) {
            if (l1->elmnt <= l2->elmnt) {
                result.add(l1->elmnt);
                if (l1 != mid1) {
                    l1 = l1->nxt;
                } else {
                    while (l2 != b) {
                        result.add(l2->elmnt);
                        l2 = l2->nxt;
                    }
                    result.add(l2->elmnt);
                }
            } else {
                result.add(l2->elmnt);
                if (l2 != b) {
                    l2 = l2->nxt;
                } else {
                    while (l1 != mid1) {
                        result.add(l1->elmnt);
                        l1 = l1->nxt;
                    }
                    result.add(l1->elmnt);
                }
            }
        }
        auto it1 = a;
        auto it2 = result.begin();
        for (int i = 1; i <= sizenow; ++i) {
            it1->elmnt = it2->elmnt;
            it1 = it1->nxt;
            it2 = it2->nxt;
        }
    }
}

int main() {
    int64_t n;
    List arr;
    cin >> n;
    for (int64_t i = 1; i <= n; ++i) {
        int64_t a;
        cin >> a;
        arr.add(a);
    }
    merge(arr.begin(), arr.rbegin(), arr.asize());
    for (auto i = arr.begin(); i != nullptr; i = i->nxt)
        cout << i->elmnt << " ";
}
