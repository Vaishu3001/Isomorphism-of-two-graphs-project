# Isomorphism-of-two-graphs-project

This project implements an algorithm to determine whether two graphs are isomorphic.

Overview

An isomorphism between two graphs is a one-to-one correspondence between the vertices of the two graphs such that any two vertices are adjacent in one graph if and only if their corresponding vertices are adjacent in the other graph.
The algorithm implemented in this project works by first checking whether the two graphs have the same number of vertices and edges. If they do, the algorithm then checks whether the two graphs have the same degree sequence. If they do, the algorithm then generates all possible permutations of the vertices of the first graph and checks each permutation to see if it produces an isomorphic graph.
Usage

To use the algorithm, first compile the code by running the following command:
gcc isomorphism.c -o isomorphism

Then, run the program with two filenames as arguments, one for each graph to be checked. For example, to check the isomorphism of the graphs in the files graph1.txt and graph2.txt, run the following command:

./isomorphism graph1.txt graph2.txt

If the two graphs are isomorphic, the program will print a message to the console. Otherwise, the program will print a message indicating that the two graphs are not isomorphic.

Example

The following code shows how to use the algorithm to check the isomorphism of the graphs in the files graph1.txt and graph2.txt:

#include <stdio.h>

int main() 
{ 

// Read the graphs from the files

FILE *graph1 = fopen("graph1.txt", "r");

FILE *graph2 = fopen("graph2.txt", "r");

// Check the isomorphism of the graphs 

isomorphism(graph1, graph2);

// Close the files

fclose(graph1); 

fclose(graph2);

return 0; 

}

Code snippet:
//To run this code, first compile it by running the following command:

gcc isomorphism.c -o isomorphism


Code snippet
//Then, run the program by typing the following command at the command line:

./isomorphism graph1.txt graph2.txt


If the two graphs are isomorphic, the program will print a message to the console. Otherwise, the program will print a message indicating that the two graphs are not isomorphic.

