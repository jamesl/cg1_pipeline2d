// used for storing colors

typedef struct {
	float r;
	float g;
	float b;
} color;

color getcolor();
color getclearcolor();
void setcolor(float,float,float);
void setclearcolor(float,float,float);

void setPixel(int,int);
