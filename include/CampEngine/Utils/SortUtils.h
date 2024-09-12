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
    static std::vector<T> quickSort(std::vector<T>& list, const std::function<bool(T t1, T t2)>& compare_func) {
        int low = 0;
        int high = list.size() - 1;

        return qsIter(list, compare_func, low, high);
    }

private:
    static std::vector<T> qsIter(std::vector<T>& list, const std::function<bool(T t1, T t2)>& compare_func, int low, int high) {
        if(low < high) {
            int pv = list[high];
            int pos = divide(list, low, high, pv);
        }
    }

    static void swap(std::vector<T>& list, int i, int j) {
        int temp = list[i];
        list[i] = list[j];
        list[j] = temp;
    }

    static int divide(std::vector<T>& list, int low, int high, int pv) {
        int i = low;
        int j = low;

        while(i <= high) {
            if(list[i] > pv) {
                i++;
            } else {
                swap(list, i, j);
                i++;
                j++;
            }
        }
        return j-1;
    }
};

#endif
