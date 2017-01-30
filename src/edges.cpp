#include "edges.h"

#include <Eigen/SparseCore>
//#include <iostream>
//#include <algorithm>
#include "igl/adjacency_matrix.h"

Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
	Eigen::MatrixXi E;
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
	
	//std::cout << "Faces: " << F.rows() << " Vertices: " << nv << std::endl;

	// Best way to remove duplicate edges is probably an adjacency matrix
	// I know this isn't ideal, but I got this idea from igl::edges()
	Eigen::SparseMatrix<int> A(nv, nv);
	igl::adjacency_matrix(F,A);
	
	//std::cout << "A.numZeros: " << A.nonZeros() << " nv^2: " << nv*nv << std::endl;
	//std::cout << A.rows() << " , " << A.cols() << std::endl;	

	//Resize E to number of edges
	int ne = A.nonZeros()/2;
	//std::cout << "NumEdges: " << ne << std::endl;
	E.resize(ne,2);
	
	// To prevent duplicates, take only the top diagonal of the adjacency matrix
	/* Ineficient to itterate Sparce matrix this way.
	int i = 0;
	for (int r=0; r<A.rows(); ++r) {
		for (int c=A.cols()-r; c>0; --c) {
			if (A.coeffRef(r,c) != 0) {
				E(i,0) = r;
				E(i,1) = c;
				i = i+1;
			}
		}
	}*/


	//Taken from https://eigen.tuxfamily.org/dox-devel/group__TutorialSparse.html
	//SparseMatrix<double> mat(rows,cols);
	int i = 0;
	for (int k=0; k<A.outerSize(); ++k) {
		for (Eigen::SparseMatrix<int>::InnerIterator it(A,k); it; ++it)
		{
			if (it.row() > it.col()) {
				E(i,0) = it.row();
				E(i,1) = it.col();
				i = i+1;
			}
			//it.value();
			//it.row();   // row index
			//it.col();   // col index (here it is equal to k)
			//it.index(); // inner index, here it is equal to it.row()
		}
	}


/*

	// Get number of Vertices. 
	int m = 0;	
	for (int f=0; f<F.rows(); ++f) {
		for (int i=0; i<3; ++i) {
			if ( F(f,i) > m )
				m = F(f,i);
		}
	}
	int nv = m+1; //NumVertices
	int ne = F.rows()+1;
	std::cout << "len of faces: " << ne << std::endl;
	
	Eigen::MatrixXi A (ne, ne);
	//for (int f=0; f<F.rows(); ++f) {
	//	int v1 = F(f,0);
	//	int v2 = F(f,1);
	//	int v3 = F(f,2);
	//	
	//	A(v1,v2) = 1;
	//	A(v2,v3) = 1;
	//	A(v3,v1) = 1;
	//}

	// Resize the Edges matrix
	E.resize(ne,2);

	//There should be 2*ne 1's
	assert(A.nonZeros() == 2*ne);
	std::cout << "nonZeros: " << A.nonZeros() << std::endl;

	// To prevent duplicates, take only the top diagonal of the adjacency matrix
	int i = 0;
	for (int r=0; r<A.rows(); ++r) {
		for (int c=A.cols()-r; c>0; --c) {
			if (A(r,c) == 1) {
				E(i,0) = r;
				E(i,1) = c;
				i = i+1;
			}
		}
	}
*/
	
	return E;
}
