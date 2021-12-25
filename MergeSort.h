#pragma once
#include <iostream>
#include <algorithm>

template<typename FirstInputIt, typename SecondInputIt, typename OutputIt, typename Comparer>
void Merge(FirstInputIt first_begin, FirstInputIt first_end,
           SecondInputIt second_begin, SecondInputIt second_end,
           OutputIt output_it,
           Comparer comparer) {

    for (; first_begin != first_end; ++output_it) {
        if (second_begin == second_end) {
            std::move(first_begin, first_end, output_it);
            return;
        }
        if (comparer(*second_begin, *first_begin)) {
            *output_it = std::move(*second_begin);
            ++second_begin;
        } else {
            *output_it = std::move(*first_begin);
            ++first_begin;
        }
    }

    std::move(second_begin, second_end, output_it);
}


template<typename FirstInputIt, typename SecondInputIt, typename OutputIt>
void Merge(FirstInputIt first_begin, FirstInputIt first_end,
           SecondInputIt second_begin, SecondInputIt second_end,
           OutputIt output_it) {

    for (; first_begin != first_end; ++output_it) {
        if (second_begin == second_end) {
            std::move(first_begin, first_end, output_it);
            return;
        }
        if (*second_begin < *first_begin) {
            *output_it = std::move(*second_begin);
            ++second_begin;
        } else {
            *output_it = std::move(*first_begin);
            ++first_begin;
        }
    }

    std::move(second_begin, second_end, output_it);
}

template<typename RandomAccessIt, typename Comparer>
void MergeSort(RandomAccessIt begin, RandomAccessIt end, Comparer comparer) {
    size_t part_size = std::distance(begin, end);
    if (part_size < 2) {
        return;
    }

    RandomAccessIt split = std::next(begin, part_size / 2);
    MergeSort(begin, split, comparer);
    MergeSort(split, end, comparer);

    std::vector<typename std::iterator_traits<RandomAccessIt>::value_type> buffer;
    Merge(begin, split, split, end, std::back_inserter(buffer), comparer);

    std::swap_ranges(begin, end, buffer.begin());
}


template<typename RandomAccessIt>
void MergeSort(RandomAccessIt begin, RandomAccessIt end) {
    size_t part_size = std::distance(begin, end);
    if (part_size < 2) {
        return;
    }

    RandomAccessIt split = std::next(begin, part_size / 2);
    MergeSort(begin, split);
    MergeSort(split, end);

    std::vector<typename std::iterator_traits<RandomAccessIt>::value_type> buffer;
    Merge(begin, split, split, end, std::back_inserter(buffer));

    std::swap_ranges(begin, end, buffer.begin());
}
