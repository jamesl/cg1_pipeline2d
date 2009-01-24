
typedef struct {
	float r;
	float g;
	float b;
} color;

color getcolor();
color getclearcolor();
void setcurrentcolor(float,float,float);
void setclearcolor(float,float,float);

void setPixel(int,int);
