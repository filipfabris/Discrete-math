Every txt file contains adjacency matrix, of n elements.
n is defined in first line of txt file.

DFS has to transfer vector of visited vertex recusivly, if not we would not find all cycles in graph.
Smaller cycles would use some of vertex and bigger cycles could not be formed because vartex in vector visited would already be set to 1 / 2.
