
#include<string>
#include<SDL2-2.0.12/SDL.h>

class Display
{
	SDL_Window* m_window;
	SDL_GLContext m_glContext;

	bool m_isClosed;

public:
	Display(int width, int height, const std::string& title);
	~Display();

	void Clear(float r, float g, float b,float a);

	void update();

	bool IsClosed();

};

