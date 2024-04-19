#include <utils/conversions.h>

template<class T>
T* listToArray(std::list<T> ls) {
    T arr[ls.size()];
    std::copy(ls.begin(), ls.end(), arr);
    return arr;
}
