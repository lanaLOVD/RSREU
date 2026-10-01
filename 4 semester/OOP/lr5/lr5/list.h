#ifndef BOUNDED_SINGLY_LINKED_LIST_H
#define BOUNDED_SINGLY_LINKED_LIST_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <stdexcept>

using namespace std;

struct Vec2 {
    float x, y;
    //Вычисление длины по формуле
    float length() const {
        return sqrt(x * x + y * y);
    }
    //Перегрузка оператора == для сравнения
    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }
    // Перегрузка оператора
    bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }
};

template<typename T, int MaxVal>
class BoundedSinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    Node* head = nullptr;
    size_t length = 0;
    //проверка
    bool canAdd(const T& elem) const;

public:
    BoundedSinglyLinkedList();
    BoundedSinglyLinkedList(const BoundedSinglyLinkedList& other);
    BoundedSinglyLinkedList& operator=(const BoundedSinglyLinkedList& other);
    ~BoundedSinglyLinkedList();

    void clear();//удаление

    size_t getLength() const;// возращение текущего количества
    bool isExist(const T& elem) const;//проверка на наличие
    bool insert(const T& elem, size_t n);//вставка в n
    bool remove(size_t n);// удалить из n

    BoundedSinglyLinkedList& operator+(const T& elem);
    BoundedSinglyLinkedList& operator-(const T& elem);
    BoundedSinglyLinkedList& operator--();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    template<typename U, int MV>
    friend ostream& operator<<(ostream& os, const BoundedSinglyLinkedList<U, MV>& list);
};

// Проверка возможности добавления элемента в зависимости от типа T
template<typename T, int MaxVal>
bool BoundedSinglyLinkedList<T, MaxVal>::canAdd(const T& elem) const {
    if constexpr (is_same_v<T, int> || is_same_v<T, float>) {
        return abs(elem) <= MaxVal;
    } else if constexpr (is_same_v<T, const char*>) {
        return strlen(elem) <= static_cast<size_t>(MaxVal);
    } else if constexpr (is_same_v<T, Vec2>) {
        return elem.length() <= MaxVal;
    }
    return false;
}
//Конструктор по умолчанию
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>::BoundedSinglyLinkedList() = default;
//копирующий конструктор
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>::BoundedSinglyLinkedList(const BoundedSinglyLinkedList& other) {
    *this = other;
}
// Оператор присваивания
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>& BoundedSinglyLinkedList<T, MaxVal>::operator=(const BoundedSinglyLinkedList& other) {
    if (this == &other) return *this;
    clear();

    Node* curr = other.head;
    Node** tail = &head;
    while (curr) {
        *tail = new Node(curr->data);
        tail = &((*tail)->next);
        curr = curr->next;
        ++length;
    }
    return *this;
}
// Деструктор
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>::~BoundedSinglyLinkedList() {
    clear();
}
// Полная очистка списка
template<typename T, int MaxVal>
void BoundedSinglyLinkedList<T, MaxVal>::clear() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    length = 0;
}
// Проверка наличия элемента в списке
template<typename T, int MaxVal>
size_t BoundedSinglyLinkedList<T, MaxVal>::getLength() const { return length; }

template<typename T, int MaxVal>
bool BoundedSinglyLinkedList<T, MaxVal>::isExist(const T& elem) const {
    Node* curr = head;
    while (curr) {
        if constexpr (is_same_v<T, const char*>) {
            if (strcmp(curr->data, elem) == 0) return true;
        } else if (curr->data == elem) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}
// Удаление элемента по позиции
template<typename T, int MaxVal>
bool BoundedSinglyLinkedList<T, MaxVal>::insert(const T& elem, size_t n) {
    if (!canAdd(elem)) {
        cout << "Ошибка: элемент превышает лимит (" << MaxVal << ")\n";
        return false;
    }
    if (n > length) n = length;

    Node* newNode = new Node(elem);
    if (n == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* curr = head;
        for (size_t i = 1; i < n; ++i) curr = curr->next;
        newNode->next = curr->next;
        curr->next = newNode;
    }
    ++length;
    return true;
}

template<typename T, int MaxVal>
bool BoundedSinglyLinkedList<T, MaxVal>::remove(size_t n) {
    if (n >= length) return false;
    if (n == 0) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    } else {
        Node* curr = head;
        for (size_t i = 1; i < n; ++i) curr = curr->next;
        Node* tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
    }
    --length;
    return true;
}
//добавнение в начало
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>& BoundedSinglyLinkedList<T, MaxVal>::operator+(const T& elem) {
    insert(elem, 0);
    return *this;
}
//- все вхождения
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>& BoundedSinglyLinkedList<T, MaxVal>::operator-(const T& elem) {
    Node* curr = head;
    Node* prev = nullptr;
    while (curr) {
        bool match = false;
        if constexpr (is_same_v<T, const char*>) {
            match = (strcmp(curr->data, elem) == 0);
        } else {
            match = (curr->data == elem);
        }
        if (match) {
            Node* tmp = curr;
            if (prev) prev->next = curr->next;
            else head = curr->next;
            curr = curr->next;
            delete tmp;
            --length;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return *this;
}
//удаляет первый элемент списка
template<typename T, int MaxVal>
BoundedSinglyLinkedList<T, MaxVal>& BoundedSinglyLinkedList<T, MaxVal>::operator--() {
    if (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        --length;
    }
    return *this;
}
// доступ к индексу
template<typename T, int MaxVal>
T& BoundedSinglyLinkedList<T, MaxVal>::operator[](size_t index) {
    if (index >= length) throw out_of_range("Index out of range");
    Node* curr = head;
    for (size_t i = 0; i < index; ++i) curr = curr->next;
    return curr->data;
}
// доступ к индексу конст

template<typename T, int MaxVal>
const T& BoundedSinglyLinkedList<T, MaxVal>::operator[](size_t index) const {
    if (index >= length) throw out_of_range("Index out of range");
    Node* curr = head;
    for (size_t i = 0; i < index; ++i) curr = curr->next;
    return curr->data;
}
// Вывод списка
template<typename T, int MaxVal>
ostream& operator<<(ostream& os, const BoundedSinglyLinkedList<T, MaxVal>& list) {
    os << "Список (длина = " << list.length << "): [";
    typename BoundedSinglyLinkedList<T, MaxVal>::Node* curr = list.head;
    bool first = true;
    while (curr) {
        if (!first) os << ", ";
        if constexpr (is_same_v<T, const char*>) {
            os << "\"" << curr->data << "\"";
        } else if constexpr (is_same_v<T, Vec2>) {
            os << "(" << curr->data.x << ", " << curr->data.y << ")";
        } else {
            os << curr->data;
        }
        first = false;
        curr = curr->next;
    }
    os << "]";
    return os;
}

#endif
