## DSA II Program #2 - Use Heap

For this assignment, a class called "heap" that provides programmers with the functionality of a priority queue using a binary heap (a.k.a. heap) was implemented.

To view the full details for this assignment, please refer to the link below. 
https://view.officeapps.live.com/op/view.aspx?src=http%3A%2F%2Ffaculty.cooper.edu%2Fsable2%2Fcourses%2Ffall2023%2Fece365%2Fheap%2Fece365_useHeap.docx&wdOrigin=BROWSELINK


Grade and Comments: 

Grade: 97

Comments:

The program works for all my tests.

This is not a logical bug, per se, but in heap's insert function, you should not be dynamically allocating a node, just to fill it in and copy it to the end of the vector. You could just fill the new vector slot directly, or at least declare a node directly, instead of declaring a pointer to a node and using "new". Also, you are not freeing the node, so that is a memory leak. -3 points

I won't take off again, and I hadn't noticed this before (that I recall), but you have a similar bug in the hash table's insert function (you dynamically allocate and never free each hashItem).

Mostly, the code looks good.
