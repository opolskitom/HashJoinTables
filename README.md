# HashJoinTables
Using basic input and console outputs to hash join a table in C++

# Program Overview
In this assignment, you will have a chance to implement the hash-join algorithm for a DBMS. You can use C, C++, Java or any other
high-level programming language to write the program. However, your program should include sufficient comments to make it
readable. You need to turn in (1) a brief report/description about your program design and implementation (e.g., high-level program
diagram and data/file structures) and program usage; (2) your program source code; (3) proof of compilation (e.g., the screen
snapshot of a successful compilation); and (4) sample execution outputs. Please assemble all the above required contents in a
single Word or PDF file for your submission. The program specification is given as follows.
Let R1(a1, a2, a3) and R2(b1, b2, b3, b4) be two relations with all integer attributes. Tuples in these two relations are sequentially
stored in two data files, respectively.
• Use the hash-join algorithm to implement a join (equijoin) of R1 and R2. Assume that the hash function is f(k) = k mod N,
where N is the number of buckets allowed in your hash structure/table.
• Your program should allow a user to choose the joining attributes from the two relations, i.e., performing R1
./R1.ai=R2.bj R2 for any chosen pair of ai and bj , where ai is the i-th attribute in R1 (1 ≤ i ≤ 3) and bj is the jth attribute in R2 (1 ≤ j ≤
4). For example, a user may want to perform R1 ./R1.a2=R2.b3 R2.
• Your program should display the join result and output the selectivity of the join.
• You may request a user to interactively input the necessary parameters, such as the data file names for R1 and R2, the
number of tuples in each relation, and the joining attributes (e.g., 1 for the 1st attribute, 3 for the 3rd attribute).
• Use your program to perform several joins for different relation instances of R1 and R2.

# Sample Inputs
R1(a1, a2, a3):
2   3   5
4   5   6
3   3   7

R2(b1, b2, b3, b4):
4   5   6   1
2   4   5   3
4   2   3   2
1   2   2   3

# Sample Output
a1    a2    a3    b1    b2    b3    b4
2     3     5     4     2     3     2
3     3     7     4     2     3     2
4     5     6     2     4     5     3    
