# Novel-Approach-of-Parallel-Radix-Sort
COUNTING SORT
	Sorting technique based on keys between a specific range.It counts the number of objects within a given range(basically hashing).Then does some addition operations to calculate the position of each element.
		Counting sort has been implemented in countsort Program.
	Time Complexity:O(n+k) where n:array size and k:fixed range of elements
		Suppose k=n^2 Counting sort becomes O(n^2) complexity.
	Space Complexity:O(n) 
		Because we will use count array and output array for holding intermediate values.
		
		
RADIX SORT
	Sort the array using digits of numbers from LSD to MSD.For each digit call the countingsort procedure.
	Time COmplexity:O(d*(n+b)) where d:maximum number of digits n:array size b:base d=log (k) to the base b where k:maximum possible value of input array
	Implies O(logb k*(n+b)) For large k, k<=n^c Runtime=O(nlogb n) which doesnt improve complexity.
	But if b=n? Time=O(n)
	Space Complexity:O(n) 
		Same as counting sort.
		
		
PARALLEL APPROACH OF RADIX SORT WITH BUCKET PARTITION PREPROCESS
	Due to the long execution time of the loop body of radix sort.We go for a approach based on parallelism idea.For each iteration of loop there can be thousands of threads.It is a scalable algorithm since the performance can be linearly improved with increase in the number of cores of modern processors.
	
	To resolve large number of data dependency(when the execution of a statement in a program is dependent on the data of the previous statement..studied in Computer Hardware), we can use a large number of mutex operations(mutual exclusion).But if we have to maintain mutual exclusion(i.e one process is not allowed to execute while the other is executing),we ll be reducing the degree of parallelism thus limiting the scalability.Another approach is to use privitisation..in this method size of the histogram bins used will increase on the number of processing elements and it is impossible to determine the size beforehand therefore may lead to excessive memory usage.Another disadvantage of privatisation is reduction operation used to combine the private histogram bins.
	
	Solution presented in this paper-
		*It converts the original data array "input" to
		*Preprocess array obtained by bucket partition "pinput"
		*Apply counting sort on pinput(includes histogram keys and rank-and-permute subprocedure).
		*At each iteration there is one element coming from each interval(all elements are different),i.e data will be accessed from different positions of histogram bins without any access conflict.  
		*Property of bucket partition preprocess is that all elements in ith bucket are smaller than the elements in the jth bucket when i<j.
