#include <iostream>

#define VALUE_SZ 10

struct Segment {
    Segment() : value(NULL), next(NULL) {}
    Segment(const char *val, Segment *n);
    char *value;
    Segment *next;
};

class Hash {
public:
    ~Hash() {makeNull();}
    Hash &insertValue(const char *val);
    Hash &deleteValue(const char *val);
    int member(const char *val);
    void makeNull();
    void print();
private:
    static const int SZ = 10;
    Segment arr[SZ];
    int calculateHash(int sum);
    int sumValue(const char *val);
    Segment *searchCollision(const char *val, int _hash);
    void deleteHead(int _head);
};

Segment::Segment(const char *val, Segment *n) {
    value = new char[VALUE_SZ];
    value = strcpy(value, val);
    next = n;
}

Hash &Hash::insertValue(const char *val) {
    int _hash = calculateHash(sumValue(val));
    
    if (!arr[_hash].value) {
        arr[_hash].value = new char[VALUE_SZ];
        strcpy(arr[_hash].value, val);
        return *this;
    }
    
    if (!strcmp(arr[_hash].value, val))
        return *this;
    
    if (!searchCollision(val, _hash)) {
        Segment *temp = new Segment(val, arr[_hash].next);
        arr[_hash].next = temp;
        return *this;
    }
    
    return *this;
}

void Hash::deleteHead(int _hash) {
    delete [] arr[_hash].value;
    arr[_hash] = *(arr[_hash].next);
}

int Hash::sumValue(const char *val) {
    int size = 0;
    
    for (int i = 0; i < VALUE_SZ && val[i] != '\0'; i++)
        size += (int)val[i];
    
    return size;
}

int Hash::calculateHash(int sum) {
    return sum % SZ;
}

Segment *Hash::searchCollision(const char *val, int _hash) { // возвращает указатель на предыдущий
    Segment *temp = arr[_hash].next, *prev = &arr[_hash];
    
    while (temp) {
        if (!strcmp(temp->value, val))
            return prev;
        
        prev = temp;
        temp = temp->next;
    }
    
    return NULL;
}

Hash &Hash::deleteValue(const char *val) {
    int _hash = calculateHash(sumValue(val));
    
    if (!arr[_hash].value)
        return *this;
    
    if (!strcmp(arr[_hash].value, val)) {
        if (arr[_hash].next) {
            deleteHead(_hash);
            return *this;
        }
        delete [] arr[_hash].value;
        arr[_hash].value = NULL;
        return *this;
    }
    
    Segment *collision = searchCollision(val, _hash);
    if (collision) {
        Segment *temp = collision->next;
        collision->next = temp->next;
        delete [] temp->value;
        delete temp;
        
        return *this;
    }
    
    return *this;
}

int Hash::member(const char *val) {
    int _hash = calculateHash(sumValue(val));
    
    if (!arr[_hash].value)
        return 0;
    if (!strcmp(arr[_hash].value, val))
        return 1;
    
    return searchCollision(val, _hash) != NULL;
}

void Hash::makeNull() {
    Segment *curr, *prev;
    
    for (int i = 0; i < SZ; i++) {
        curr = arr[i].next;
        prev = &arr[i];
        while (curr) {
            deleteHead(i);
            prev = curr;
            curr = curr->next;
        }
        
        delete [] arr[i].value;
        arr[i].value = NULL;
    }
}

void Hash::print() {
    for (int i = 0; i < SZ; i++) {
        Segment *p = &arr[i];
        //std::cout << "i = " << i << ":" << std::endl;
        while (p != NULL) {
            if (p->value)
                std::cout << p->value << std::endl;
            p = p->next;
        }
    }
}

int main(){
    Hash T;
    
    T = T.insertValue("George");
    T = T.insertValue("Alex");
    T = T.insertValue("Alfx");
    T = T.insertValue("Alfz");
    T = T.insertValue("Blfy");
    T = T.insertValue("Vova");
    T = T.insertValue("Anya");
    T.print();
    
    std::cout << "member?" << T.member("George");
    T.deleteValue("George");
    T.deleteValue("Blfy");
    
    std::cout << std::endl << std::endl;
    T.print();
}
