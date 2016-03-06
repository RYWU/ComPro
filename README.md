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

## 3. Rabbit House (Time Limit: 1s)

### Description

Kokoa is a coffee shop clerk of Rabbit House. Since Rabbit House is a famous coffee shop, it earns lots of money per day. Kokoa records the total income si everyday, and checks whether it matches the cash Rabbit House has now. To prevent malicious modification, she also records ci, which is the checksum of si.

As a normal high school girl, she doesn't know the complicate message digest algorithms like MD5 or SHA-1. Instead, she just calculate the digit sums of si. The digit sum of a given integer is the sum of all its digits. For example, if s=[302,1000,2011], the checksums will be c=[5,1,4].

But this algorithm is too naive. It's easy to construct a different s with same checksums. For instance, if s=[5,10,13], the checksums will also be c=[5,1,4]. To show how unreliable is digit sum, please construct a valid s for a given c, such that the last element of s is as small as possible. If there are more than one possible s, choose the one with smallest sn−1, where n is the length of s. If there are still more than one possible s, choose the one with smallest sn−2, and so on.

### Input Format

The first line contains an integer T indicating the total number of test cases. Each test case starts with an integer n in one line, indicating the number of days, followed by a line of n integers c1,c2,…,cn.

* 1≤T≤10
* 1≤n,ci≤1000

### Output Format

For each test case, please output n integers s1,s2,…,sn in one line. Note that s should be strictly increasing since Rabbit House is famous and has income everyday.

### Sample Input

2
3
5 1 4
10
3 1 4 1 5 9 2 6 5 3
### Sample Output

5 10 13
3 10 13 100 104 108 110 114 122 201

## 4. MUST (Time Limit: 2s)

### Description

HH just learned MST (Minimum Spanning Tree) in the ADA course. To practice, he wants to find a MST of an undirected graph GG. But he notices that there may be more than one possible MST of GG. To make his life easier, he tries to choose the edges exist in every MST first. We call such edges MUST edges since you must choose them in MST. However, finding MUST edges is a hard task, can you help him?

### Input Format

The first line contains an integer TT indicating the total number of test cases. Each test case starts with a line contains two integers n,mn,m, denoting the number of nodes and edges in the undirected graph GG. Each of the following mm lines contains three integers ai,bi,ciai,bi,ci, which means there is an edge (ai,bi)(ai,bi) with weight cici in GG.

* 1≤T≤101≤T≤10
* 3≤n≤500003≤n≤50000
* n−1≤m≤100000n−1≤m≤100000
* 1≤ai,bi≤n1≤ai,bi≤n and ai≠biai≠bi
* 1≤ci≤1071≤ci≤107
* GG is connected

### Output Format

For each test case, please output the number of MUST edges and the sum of weight of MUST edges in one line.

### Sample Input
3
3 3
1 2 3
2 3 3
3 1 2
3 3
1 2 3
2 3 3
3 1 3
3 3
1 2 3
2 3 3
3 1 4

### Sample Output
1 2
0 0
2 6

## 5. Plagiarism (Time Limit: 2s)

### Description

HanHan is the chief urban designer of HyperHacker city. This city is known for its beautiful urban design. To simplify this problem, we treat HyperHacker city as an undirected graph, G1G1.

HugeHammer, the lazy and evil urban designer of HappyHippo City, is too lazy to create his own design. He decides to just copy HanHan’s design, and randomly rename the vertices in the graph. We call the renamed graph G2G2.

To simplify this problem again, we assume that the vertices of G1G1 and G2G2 are labelled as 1,2,…n1,2,…n. The renaming can be viewed as a random permutation ππ of 1,2,…,n1,2,…,n, so an edge (u,v)(u,v) in G1G1 would be an edge (π(u),π(v))(π(u),π(v)) in G2G2.

For example, if there are three vertices and two edges in G1G1 and G2G2. The edges in G1G1 are (1,2)(1,2) and (2,3)(2,3). The edges in G2G2 are (2,3)(2,3) and (1,3)(1,3). A possible permutation is π=⟨1,3,2⟩π=⟨1,3,2⟩. Since we can map edge (1,2)(1,2) in G1G1 to (π(1),π(2))=(1,3)(π(1),π(2))=(1,3) in G2G2, and (2,3)(2,3) in G1G1 to (π(2),π(3))=(3,2)(π(2),π(3))=(3,2) in G2G2. Note that the graphs are undirected, so (2,3)(2,3) and (3,2)(3,2) are interchangeable.

Please help HanHan to find the permutation ππ as the evidence of plagiarism.


### Input Format

The first line contains an integer TT indicating the total number of test cases. Each test case starts with a line containing two integers n,mn,m, denoting the number of nodes and edges in the undirected graphs G1,G2G1,G2. Each the following mm lines contains two integers ai,biai,bi, denoting an edge (ai,bi)(ai,bi) in G1G1. Each the following mm lines contains two integers ci,dici,di, denoting an edge (ci,di)(ci,di) in G2G2.

* 1≤T≤101≤T≤10
* 3≤n≤100003≤n≤10000
* 0≤m≤1000000≤m≤100000
* 1≤ai,bi,ci,di≤n1≤ai,bi,ci,di≤n
* There be self-loops and/or multi-edges in the graphs.

### Output Format

For each test case, please output the permutation ππ in one line as π(1),π(2),…π(n)π(1),π(2),…π(n) separated by a space. If there are more than one possible permutation, you can output any one of them.

### Sample Input
3
3 2
1 2
2 3
2 3
1 3
3 3
1 2
2 3
3 1
1 3
3 2
1 2
3 3
1 1
2 3
3 2
2 2
3 1
1 3

### Sample Output
1 3 2
1 2 3
2 1 3

### Hint
* There are two bonus tests (3 points each) in this problem. The condition n≤1000n≤1000 and m≤10000m≤10000 holds for the first 10 tests.
* The top secret of HanHan is that he just random generated a graph as his design.
