# ComPro
RYUW's Competitive Programming Repo

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

## 2. Lucky Number (Time Limit: 1s)
### Description
We all know that digit 7 is lucky and digit 4 is unlucky. For example, you can win a jackpot if you get 777 on a casino slot machine, and elevators often be missing the 4th floor or any floor whose number contains the digit 4. Even a special term Tetraphobia is created to describe the fear of the digit 4.

In this problem, we say an integer n is a lucky number if:

* The integer n is divisible by 7.
* The decimal representation of n contains at least three digits 7.
* The decimal representation of n contains more digits 7 than digits 4.
For example, 777 and 774746 are lucky numbers; but 7771, 77, and 747474 are not. Can you tell us how many lucky numbers are in range [l,r]?

### Input Format
The first line contains an integer T indicating the total number of test cases. Each test case contains two integers l,r in one line.

* 1≤T≤100000
* 1≤l≤r≤10^18

### Output Format
For each test case, please output an integer indicating how many lucky numbers are in range [l,r] in one line.

### Sample Input
3
1 10000
1 1000
1000 10000

### Sample Output
5
1
4

### Hint
* All lucky numbers in [1,10000] are 777, 7077, 7707, 7770, 7777.
* There are two bonus tests (3 points each) in this problem. The condition T≤300 holds for the first 10 tests.