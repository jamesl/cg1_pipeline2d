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
	double x,y;

	Point(double _x, double _y) : x(_x), y(_y) { }
	Point(Matrix a) : x(a(0,0)), y(a(1,0)) { }

	Matrix matrix() {
		Matrix m(4,1);	
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
		Point q(x,y);
		bool vert = (x == r.x);
		float m;
		if(!vert) m = (y - r.y) / (x - r.x);
		// we know r is in clip window, we must move
		// q so that it is also.
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

ostream& operator<<(ostream& os, const Point &p) {
	os << "(" << p.x << "," << p.y << ")";
}


/**
 * Clip the polygon with vertex count in and verticies inx and iny against
 * the rectangular clipping region specified by lower left corner (x0, y0) 
 * and upper right corner (x1, y1).  The resulting vertices are places in
 * outx, and outy with the vertex count places in out.
 */

vector<Matrix> clipAgainst (vector<Matrix> inv,enum clip_plane clip) {
	vector<Matrix> outv;
	cout << " inv.size: " << inv.size() << endl;
	cout << " outv.size: " << outv.size() << endl;

	int in = inv.size();
	if(in<=0) return outv;
	Point S(inv.at(inv.size()-1));

	cout << "Clipping against edge " << clip << endl;
	for(int i=0;i<in;i++) {
		Point P(inv[i]);
		if(P.inside(clip)) { // right edge
			if(!(S.inside(clip))) { 
				// compute intersection S, P
				Point Q = S.moveIn(P,clip);
				cout << "\tMoved " << P << " into " << Q << endl;
				outv.push_back(Q.matrix());
			}
			// output P
			outv.push_back(P.matrix());
			cout << "\tUsing " << P << " unchanged." << endl;
		} else if(S.inside(clip)) {
			// compute intersection P, S
			Point Q = P.moveIn(S,clip);
			outv.push_back(Q.matrix());
			cout << "\tMoved " << S << " into " << Q << endl;
		}
		S = P;
	}
	inv = outv;

	cout << " outv.size: " << outv.size() << endl;
	return outv;
}

vector<Matrix> clipper(vector <Matrix> v) {
	v = clipAgainst(v,RIGHT);
	v = clipAgainst(v,TOP);
	v = clipAgainst(v,BOTTOM);
	v = clipAgainst(v,LEFT);
	return v;
}

