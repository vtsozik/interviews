/*
1) Q: Print first non-duplicated letter found in a word, e.g.
 TOTAL->O, TEETER->R?
   A: Put letters in a hashtable storing their count as value.
 Iterate letters second time looking up count in the created
 hashtable. Print first letter with single count (totaloteeterr.cpp).

2) Q: Find sum of two elements from unsorted array of n elements
 which equals to given number S?
   A1: Sort array and put one pointer to the beginning pb and 
 another to the end pe. Compute sum of first and last element
 to S. If S > (*pb + *pe) then ++pb else if S < (*pb + *pe)
 then --pe else print pb and pe and break from loop before 
 pb >= pe (sumoftwo.cpp).
   A2: Insert first element in hash. Starting from second element
 check if (S - element[i->2,n]) is present in hashtable. If it is
 print element[i] and (S - element[i]) and exit, continue otherwise.
 (sumoftwo.cpp)

3) Q: Find sum of four elements from unsorted array of n elements
 which equals to given number S?
   A1: Create an array of n * (n - 1) sums of 2 unique elements, 
 sort it and run binary search on it as described in Q2-A1.
   A2: Create an array of n * (n - 1) sums of 2 unique elements,
 then insert first element of this array into hashtable and proceed
 as described in Q2-A2.
   N: Note in both cases additinal checking is necessary to avoid finding
 a pair that contains element that is also part of first pair, e.g.
 {1,2} and {2,3}.
*/
