
Karl Bayer, ksb2153
COMS W4995, HW1

Approach:
A sparce adjacency matrix is computed with the vector indices from the faces matrix. This adjacency matrix represents all directed edges. Since the surface is a topologically valid (no boundaries/max of 2 triangles per edge), the adjacency matrix is symmetric across the diagonal. That is, in order to retreive only the undirected edges, we need only the indices on one side of the diagonal.

Challenges:
By far the most difficult part of the assignment was figuring out how to compute the unique list of edges in an elegent/efficient manner. The naiive implementation is a double nested loop that requires checking the entire list of found edges for every new potential edge. Just the thought of coding this is disgusting to me. 

I know this isn't ideal, but I did finally (after several hours) look at the igl::edges() function and discovered that they used a sparce adjacency matrix. This was the only idea I had that made sense and so I incorporated it into this assignment.

Finally, I was never able to get the assigment to run on my own .off files. I tested with both absolute and relative file paths using cube.off copied from the OFF(file format) wikipedia page.
