// Polygon Clipping (normalized)

#include <vector>
#include "Matrix.h"

// Point class stores coordinates
// and has methods for the Sutherland-Hodgeman
// clipping algorithm
class Point {
  public:
	int x,y;

	Point(int _x, int _y) : x(_x), y(_y) { }
	Point(Matrix a) : x(a(0,0)), y(a(1,0)) { }

	Matrix matrix() {
		Matrix m(4,1);	
		m(0,0) = x;
		m(1,0) = y;
		m(2,0) = 1;
		m(3,0) = 1;
	}

	// check if a point is within clip region
	bool inside(int clip) {
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
	Point moveIn(Point r,int clip) {
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
				q.y = r.y + (-1 - r.x) * m;
				return q;
			case 3: // left
				q.x = -1;
				q.y = r.y + (1 - r.x) * m;
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
 * Clip the polygon with vertex count in and verticies inx and iny against
 * the rectangular clipping region specified by lower left corner (x0, y0) 
 * and upper right corner (x1, y1).  The resulting vertices are places in
 * outx, and outy with the vertex count places in out.
 */
void clipPolygon (const vector<Matrix>& inv) {
  /* provide your implementation here */
	vector<Matrix> outv;
	int in = (int)inv.size();
	if(in==0) return;
	Point S(inv.at(in-1));
	
	for(int clip=0;clip<4;clip++) {
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
	}
}
