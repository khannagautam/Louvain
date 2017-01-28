# Louvain
Louvain method for bipartite graphs
Input syntax: 1. Enter the number of vertices in the graph
	      2. Enter the number of edges in the graph
	      3. Enter the colour of n vertices, i.e., n times enter either 1(if the vertex is red), 0(if it is blue)
	      4. Enter the egde list: The edge list should contain exactly m lines, each line containing 2 integers i,j which signinfies an undirected edge between the vertices i and j.

Sample input: For K3,3 the input file should be as follows
		6 9
		1 1 1 0 0 0 
		1 4
		1 5
		1 6
		2 4
		2 5
		2 6
		3 4
		3 5
		3 6


Output: The output will contain k lines, where k is the final number of communities formed.
	Each line will contain v integers, where the ith integer v(i) will be the vertex number of the vertices in the community

Sample Output:  For K3,3 the output should be as follows
		1 
		2 
		3 
		4 
		5 
		6 

