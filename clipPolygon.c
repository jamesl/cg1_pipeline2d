// Polygon Clipping (normalized)

#include <vector>
#include "Matrix.h"
#include <cassert>

enum clip_plane {
	RIGHT=0,
	TOP=1,
	BOTTOM=2,
	LEFT=3
};

// Point class stores coordinates
// and has methods for the Sutherland-Hodgeman
// clipping algorithm
class Point {
  public:
	Matrix m;
	double x,y;
	
	// construct a point given 2 coordinates
	//Point(double _x, double _y) : x(_x), y(_y) { }
	// in the 2d pipeline, we are using a 4x1 matrix
	// to represent a vertex, so it is easier to construct
	// from a Matrix
	Point(Matrix a) : x(a(0,0)), y(a(1,0)), m(a) { }

	// create a Matrix representation of this point
	Matrix matrix() {
		m(0,0) = x;
		m(1,0) = y;
		m(2,0) = 1;
		m(3,0) = 1;
		return m;
	}

	// check if a point is within clip region
	bool inside(enum clip_plane clip) {
		switch(clip) {
			case 0: // right
				return x < 1;
			case 1: // top
				return y < 1;
			case 2: // bottom
				return y > -1;
			case 3: // left
				return x > -1;
		}
	}

	// move this point into the clip region. this point is
	// outside the clip region, and point r is within the clip
	// region. 
	Point moveIn(Point r,enum clip_plane clip) {
		Point q(matrix());
		bool vert = (x == r.x);
		float m;
		if(!vert) m = (y - r.y) / (x - r.x);
		// we know r is in clip window, we must move
		// q so that it is also.
		// now uses normalized clipping
		switch(clip) {
			// move in x
			case 0: // right
				q.x = 1;
				q.y = r.y + (1 - r.x) * m;
				return q;
			case 3: // left
				q.x = -1;
				q.y = r.y + (-1 - r.x) * m;
				return q;
			// move in y
			case 1: // top
				q.y = 1;
				if(vert) 
					q.x = r.x;
				else
					q.x = r.x + (1 - r.y)/m;
				return q;
			case 2: // bottom
				q.y = -1;
				if(vert) 
					q.x = r.x;
				else
					q.x = r.x + (-1 - r.y)/m;
				return q;
		}
	}
	
};

/** 
 * used for printing points 
 */
ostream& operator<<(ostream& os, const Point &p) {
	os << "(" << p.x << "," << p.y << ")";
}


/**
 * clip vertices in inv against edge clip
 */
vector<Matrix> clipAgainst (vector<Matrix> inv,enum clip_plane clip) {
	vector<Matrix> outv;

	int in = inv.size();
	if(in<=0) return outv;
	Point S(inv.at(inv.size()-1));

	for(int i=0;i<in;i++) {
		Point P(inv[i]);
		if(P.inside(clip)) { // right edge
			if(!(S.inside(clip))) { 
				// compute intersection S, P
				Point Q = S.moveIn(P,clip);
				outv.push_back(Q.matrix());
			}
			// output P
			outv.push_back(P.matrix());
		} else if(S.inside(clip)) {
			// compute intersection P, S
			Point Q = P.moveIn(S,clip);
			outv.push_back(Q.matrix());
		}
		S = P;
	}

	return outv;
}

/**
 * clip a polygon against all 4 edges,
 * 1 at a time.
 */
vector<Matrix> clipper(vector <Matrix> v) {
	v = clipAgainst(v,RIGHT);
	v = clipAgainst(v,TOP);
	v = clipAgainst(v,BOTTOM);
	v = clipAgainst(v,LEFT);
	return v;
}

