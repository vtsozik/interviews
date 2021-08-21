1) constructor initialization list order for member variables

2) Invalidation of vector iterators when push_back is called:
Iterators are only invalidated when capacity is reached:
"all iterators and references before the point of insertion are unaffected, unless the new container size is greater than the previous capacity (in which case all iterators and references are invalidated)"
http://kera.name/articles/2011/06/iterator-invalidation-rules/

3) parameter dependent lokup:
 order of variable resolution, function stack, class member, namespace member, global variable

4) size of cash line (register length)
POF (unknown term). Cache line size is equal to register size or 64 bytes.
Cache organization tutorial: https://www.scss.tcd.ie/Jeremy.Jones/CS3021/5%20caches.pdf

5) what is false sharing and how to prevent it.
https://software.intel.com/sites/default/files/m/d/4/1/d/8/3-4-MemMgt_-_Avoiding_and_Identifying_False_Sharing_Among_Threads.pdf

6) How HashMap is implemented.
HashMap and HashTable data structure wise are the same. Implementation wise there are the following differences in java:
http://javahungry.blogspot.com/2014/03/hashmap-vs-hashtable-difference-with-example-java-interview-questions.html

7) Can you write to file descriptor if file removed by another process.
Yes, according to Alex, you can, however close system call will return an error. "mktemp call unlinks file immediately, but you can still write to created temp file." This needs to be verified with a test program.
