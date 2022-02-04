//
//  sdl.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include <SDL.h>


#include "term.h"
#include "../kb/kb.h"
#include "../scd/scd.h"

SDL_Window* Window;
SDL_Renderer* Renderer;

void term_init(void) {
	SDL_Init(SDL_INIT_VIDEO);
	
	Window = SDL_CreateWindow("PlasmVM", 10, 10, 640, 400, 0);
	Renderer = SDL_CreateRenderer(Window, 1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_Rect Rectangle;
	Rectangle.x = 0;
	Rectangle.y = 0;
	Rectangle.w = 640;
	Rectangle.h = 400;
	SDL_RenderDrawRect(Renderer, &Rectangle);
	SDL_RenderPresent(Renderer);
	return;
}

void term_clock(void) {
	SDL_Event Event;
	SDL_PollEvent(&Event);
	if (Event.type == SDL_KEYDOWN)
		kbi_keydown(Event.key.keysym.scancode);
	if (Event.type == SDL_KEYUP)
		kbi_keyup(Event.key.keysym.scancode);
	if (Event.type == SDL_QUIT)
		scdi_sendevent(SCD_SHUTDOWN);
	return;
}

void term_shutdown(void) {
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	return;
}

void termi_print(char Data) {
	
}
void termi_sendcc(byte Code) {
	
}
