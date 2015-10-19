# ComPro
My Competitive Programming Repo

## 1. Queue (Time Limit: 3s)
### Description
In computer science, a queue is a particular kind of abstract data type or collection in which the entities in the collection are kept in order and the principal (or only) operations on the collection are the addition of entities to the rear terminal position, known as enqueue, and removal of entities from the front terminal position, known as dequeue.

We all should have learned how queues work before. But today we are considering a queue in the real world instead of a queue in computer science. There are n people queueing up for the tickets of the ADA course, numbered from 1 to n respectively. Since the ADA course is very popular, some of them may even fight for a better place in the queue.

The fights in the ADA course is very special. When person i is fighting against person j, person i wins if and only if c(i−j)(i+j)emodp>p2, where c,e,p are numbers predefined by TAs. We say a queue is stable if the first person in the queue can beat the second person in the queue, the second person can beat the third, and so on. Please help us arrange a stable queue.

### Input Format
The first line contains an integer T indicating the total number of test cases. Each test case contains four integers n,c,e,p in one line.

* 1≤T≤10
* 2≤n≤200000
* 1≤c<p
* 0≤e≤1018
* 2n<p≤2×109
* p is a prime.
* There is at least one stable arrangement.

### Output Format
For each test case, please output n integers which form a stable queue from first to last in one line.

### Sample Input
3
2 1 0 5
3 5 8 13
8 5 3 37

### Sample Output
1 2
1 2 3
7 3 8 6 2 5 4 1

### Hint
* In the first sample, person 1 beats person 2 since 1(1−2)(1+2)0=−1, and −1mod5=4>52.
* There are two bonus tests (3 points each) in this problem. The condition n≤100000 holds for the first 10 tests.
