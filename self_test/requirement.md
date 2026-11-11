Handsome Jeff finds the course network too complicated to understand. He wants to arrange an
ordering to all courses, such that if there is a prerequisite relationship A → B, course A must
appear before course B in the order. After constructing this order, Jeff assigns an ordering
number to each course. The first course in the order has ordering number 1, the second course
has ordering number 2, and so on.
To make the order unique and easier to check, Jeff decides that whenever there are ties, the
course with the smaller course id must be placed first.
For a given course s, Jeff wants to know the ordering number assigned to it.
Complete the file UniversityNumber-C.cpp to calculate the answer.
Input Format:
• The first line has two integers n and m. n denotes the number of courses available, m
denotes the number of unique prerequisite relationships between the courses.
• Each of the next m lines contains two integers a, b, where a and b are distinct course ids.
Course a is a prerequisite of course b.
• The last line contains an integer s, which denotes the target course id.
For all the input data, 1 ≤ n ≤ 100000; 0 ≤ m ≤ 300000; 0 ≤ a,b,s ≤ n−1. You can also
assume that the course ids must start from 0 and end at n−1.
Output Format:
Output an integer order, the ordering number assigned to course s.