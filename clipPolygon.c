// Polygon Clipping (against a rectangle)

// Point class stores coordinates
// and has methods for the Sutherland-Hodgeman
// clipping algorithm
class Point {
  public:
	int x,y;

	Point(int _x, int _y) : x(_x), y(_y) { }

	// check if a point is within clip region
	bool inside(int clip, Point ll, Point ur) {
		switch(clip) {
			case 0: // right
				return x < ur.x;
			case 1: // top
				return y < ur.x;
			case 2: // bottom
				return y > ll.y;
			case 3: // left
				return x > ll.x;
		}
	}

	// move this point into the clip region. this point is
	// outside the clip region, and point r is within the clip
	// region. 
	Point moveIn(Point r,int clip, Point ll, Point ur) {
		Point q(x,y);
		bool vert = (x == r.x);
		float m;
		if(!vert) m = (y - r.y) / (x - r.x);
		// we know r is in clip window, we must move
		// q so that it is also.
		switch(clip) {
			// move in x
			case 0: // right
				q.x = ur.x;
				q.y = r.y + (ll.x - r.x) * m;
				return q;
			case 3: // left
				q.x = ll.x;
				q.y = r.y + (ur.x - r.x) * m;
			// move in y
			case 1: // top
				q.y = ur.y;
				if(vert) 
					q.x = r.x;
				else
					q.x = r.x + (ur.y - r.y)/m;
				return q;
			case 2: // bottom
				q.y = ll.y;
				if(vert) 
					q.x = r.x;
				else
					q.x = r.x + (ll.y - r.y)/m;
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
void clipPolygon (int in, int inx[], int iny[], int *out, int outx[],
		  int outy[], int x0, int y0, int x1, int y1)
{
  /* provide your implementation here */
	Point S(inx[in-1],iny[in-1]);
	Point P(0,0);
	Point ll(x0,y0);
	Point ur(x1,y1);
	
	*out=0;
	
	for(int clip=0;clip<4;clip++) {
	for(int i=0;i<in;i++) {
		P.x = inx[i]; P.y = iny[i];
		if(P.inside(clip,ll,ur)) { // right edge
			if(!(S.inside(clip,ll,ur))) { 
				// compute intersection S, P
				Point Q = S.moveIn(P,clip,ll,ur);
				outx[*out] = Q.x; outy[*out] = Q.y;   
				*out++;
			}
			// output P
			outx[*out] = P.x; outy[*out] = P.y;   
			*out++;
		} else if(S.inside(clip,ll,ur)) {
			// compute intersection P, S
			Point Q = P.moveIn(S,clip,ll,ur);
			outx[*out] = Q.x; outy[*out] = Q.y;   
			*out++;
		}
		S = P;
	}
	}
}
