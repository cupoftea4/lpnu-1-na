#include <iostream>

class A {
public:
    int num;
}

template<class T, int n>
class Array {
    T * array = new T[n];
public:
    T GetValue(int index) { return array[index]; }
}

template<int n>
class Array<int *> {
    int ** array = new int*[n];
public:
    int GetValue(int index) { return *array[index]; }
}

template<int n>
class Array<A> {
    A * array = new A[n];
public:
    int GetValue(int index) { return array[index].num; }
}
