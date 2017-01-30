#include "euler_characteristic.h"

#include <edges.h>

int euler_characteristic(const Eigen::MatrixXi &F)
{
	int Chi;
	// ADD YOUR CODE HERE
	
	// Get number of Vertices. 
	int m = 0;	
	for (int f=0; f<F.rows(); ++f) {
		for (int i=0; i<3; ++i) {
			if ( F(f,i) > m )
				m = F(f,i);
		}
	}
	int nv = m+1; //NumVertices

	// Get the number of edges
	Eigen::MatrixXi E = edges(F);
	int ne = E.rows();

	// Get the number of faces
	int nf = F.rows();

	// Compute Euler's Characteristic
	Chi = nv - ne + nf;

	return Chi;
}
