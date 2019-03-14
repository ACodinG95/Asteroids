#ifndef DISPLAY_H
#define DISPLAY_H
#include <string>

#include <SDL2\SDL.h>
#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <iostream>





class Display
{
public:
	Display(int width, int height, const std::string title);
	virtual ~Display();

	void Update();
	void Clear(float r,float g,float b,float a);


	bool isClosed();

private:

	Display(const Display& other) {};
	Display& operator=(const Display& other) {};

	SDL_Window *m_window;
	SDL_GLContext m_glContext;

	bool m_isClosed;
};

#endif