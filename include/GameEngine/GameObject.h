#include "GameEngine/GameEngine.h"
#include "GameEngine/Renderer.h"

class GameObject{
public:
	GameObject(int x, int y, int w, int h);
	GameObject(int x, int y, int w, int h, int r, int g, int b);
	GameObject(int x, int y, int w, int h, float r, float g, float b);
	virtual ~GameObject();
	
	void update();
	void draw(Renderer* r);
	void setColor(int r, int g, int b);
	void setColor(float r, float g, float b);
	
	void printColor(){ std::cout << "r: " << r <<
					"g: " << g <<
					"b: " << b << endl; }
	int getX(){ return x; }
	int getY(){ return y; }
	int getWidth(){ return w; }
	int getHeight(){ return h; }	 
	

protected:
	int x;
	int y;
	int w;
	int h;
	int r;
	int g;
	int b;
private:
	void init(int x, int y, int w, int h, int r, int g, int b);
};
