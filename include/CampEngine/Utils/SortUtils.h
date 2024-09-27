//
// Created by Noah Campagne on 31/08/2024.
//

#ifndef CE_SORTUTILS_H
#define CE_SORTUTILS_H

#include <functional>
#include <vector>

template<typename T>
class Sorter {
public:
    static void quickSort(std::vector<T>& list, const std::function<bool(T t1, T t2)>& compare_func) {
        int low = 0;
        int high = list.size() - 1;

        return qsIter(list, compare_func, low, high);
    }

private:
    static void qsIter(std::vector<T>& list, const std::function<bool(T t1, T t2)>& compare_func, int low, int high) {
        if(low < high) {
            int pv = list[high];
            int pos = divide(list, compare_func, low, high, pv);

            qsIter(list, compare_func, low, pos-1);
            qsIter(list, compare_func, pos+1, high);
        }
    }

    static void swap(std::vector<T>& list, int i, int j) {
        int temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }

    static int divide(std::vector<T>& list, const std::function<bool(T t1, T t2)>& compare_func, int low, int high, int pv) {
        int i = low - 1;
        for(int j = low; j < high; j++) {
            if(compare_func(list[j], pv)) {
                i++;
                swap(list, i, j);
            }
        }
        swap(list, i+1, high);
        return i+1;
    }
};

#endif
