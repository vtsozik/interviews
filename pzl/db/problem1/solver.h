#pragma once
#define problem1 ecc5a3ff-5646-4460-bddb-19305fe936d7

template<class It, class T>
// iterator and value_type of *It
// out.first  - starting stop number or -1
// out.second - ending stop number or -1
void solver(It begin, It end, std::pair<int, int> &out) {
    // begining of implementation:
    // Due to "positive sum" restriction, fastest algorithm will have linear complexity 
    T sum = 0, max_sum = 0; // Init sum and max_sum variables to 0
    int start_stop = 1, end_stop = start_stop + 1; // Init start and stop iterators
    out.first = out.second = -1; // Init first and last stops to no cycling state
    for(It iter = begin; iter != end; ++iter, ++end_stop) { // Iterate ratings and increment end stop too
        sum += *iter; // sum up ratings
        if(sum < 0) { // If sum became negative floor it to 0, reset start stop to next interval
            sum = 0;
            start_stop = end_stop;
        } else if(sum > max_sum) { // use first solution only, that's why >= condition is not used
            max_sum = sum;
            out.first = start_stop;
            out.second = end_stop;
        } else if(sum == max_sum && out.first == start_stop) { // extend continuous route segment for the same, first solution maximal rating
            out.second = end_stop;
        }
    }
    // end of implementation:
}
