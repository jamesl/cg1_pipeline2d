
#define SCR_HEIGHT screenHeight
#define SCR_WIDTH screenWidth
#include <cassert>
#include <vector>
#include <algorithm>
#include "Matrix.h"
#include "color.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

using namespace std;

extern int screenHeight;
extern int screenWidth;

// the same buckets as in class
class Bucket {
  public:
	Bucket(int _ymax, float _x, float _xinc) :
		ymax(_ymax), x(_x), xinc(_xinc), next(0) {
	}


	int ymax;
	// yuck, floating point
	float x;
	float xinc;
	Bucket *next;

}; 

// compare 2 buckets by dereferencing the pointers
bool cmpbucketptr(Bucket *a, Bucket *b) {
	assert(a!=0);
	assert(b!=0);
	return a->x < b->x;
}
	
// draw a polygon!
void drawPolygon(vector<Matrix> vertex) {
	int n = vertex.size();
	Bucket *edgetable[SCR_HEIGHT];
	for(int i=0;i<SCR_HEIGHT;i++) 
		edgetable[i] = 0; 
	// fill ET
	int y0,y1,x0,x1;
	for(int i=0;i<n;i++) {
		y0 = vertex[i](1,0);
		y1 = vertex[(i+1)%n](1,0);
		x0 = vertex[i](0,0);
		x1 = vertex[(i+1)%n](0,0);
		if(y1 < y0) { // swap points
			int swap;	
			swap = y0; y0 = y1; y1 = swap;	
			swap = x0; x0 = x1; x1 = swap;	
		}
		
		// toss out horizontal edges
		if(y1==y0) continue;
		
		// make a bucket for current edge
		Bucket *edge = new Bucket(
			y1,x0,(float)(x1-x0)/(float)(y1-y0));
		if(y0 < 0 || y0 >= screenHeight) {
			// now that this code is working,
			// we should never get here.
			cerr << "oops, y0=" << y0 << "!" << endl;
			continue; 
		}
		if(edgetable[y0] == 0) {
			// first edge bucket for this y
			edgetable[y0] = edge;
		} else {
			// current bucket is first in table
			Bucket *curbucket = edgetable[y0];
			// that if statement passed so this should...
			assert(curbucket!=0 && edge!=0);
			if(curbucket->x > edge->x) {
				// add this bucket first
				edgetable[y0] = edge;
				edge->next = curbucket;	
			} else {
				// add the bucket where it 
				// should be so that the edge table entries
				// remain sorted by x
				Bucket *prevbucket;
				do {
				prevbucket = curbucket;
				curbucket = curbucket->next;
				if(curbucket==0 || curbucket->x > edge->x) {
					prevbucket->next = edge;
					edge->next = curbucket;
					break;
				}
				assert(curbucket!=0);
				} while(1);
			}
		}

	}
	
	// the amazing active edge table
	vector<Bucket *> aet;

	for(int y=0;y<SCR_HEIGHT;y++) {
		for(vector<Bucket *>::iterator iter = aet.begin();
		    iter != aet.end();iter++) {
			if((*iter)->ymax <= y) {
				aet.erase(iter);
				iter--;
			}
		}
		while(edgetable[y] != 0) {
			aet.push_back(edgetable[y]);
			edgetable[y] = edgetable[y]->next;
		}
		sort(aet.begin(), aet.end(), cmpbucketptr);
		vector<Bucket *>::iterator iter = aet.begin();
		bool draw = false;
		for(int x=0;x<SCR_WIDTH;x++) {
			while(iter != aet.end() && 
			      *iter != 0 && 
			      int((*iter)->x) == x) { 
				draw = !draw; iter++; 
			}
			if(y >= 0 && y <SCR_HEIGHT)
				if(draw) setPixel(x,y);
		}	
		for(iter = aet.begin();iter!=aet.end();iter++) {
			(*iter)->x += (*iter)->xinc;
		}
	}
}
