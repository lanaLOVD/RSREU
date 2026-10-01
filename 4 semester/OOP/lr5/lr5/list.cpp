#include "list.h"

// Явная инстанциация для всех используемых типов
template class BoundedSinglyLinkedList<int, 10>;
template class BoundedSinglyLinkedList<float, 5>;
template class BoundedSinglyLinkedList<const char*, 5>;
template class BoundedSinglyLinkedList<Vec2, 10>;
