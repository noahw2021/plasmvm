//
//  term_sdl.c
//  plasmvm
//
//  Created by Noah Wooten on 2/4/22.
//

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdlib.h>
#include <string.h>

#include "term.h"
#include "../kb/kb.h"
#include "../scd/scd.h"

SDL_Window* Window;
SDL_Renderer* Renderer;
TTF_Font* Font;
termctx_t* termctx;

#ifdef _WIN32
int __stdcall MessageBeep(int Type);
#endif

void term_init(void) {
	termctx = malloc(sizeof(termctx_t));
	memset(termctx, 0, sizeof(termctx_t));
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	
	Window = SDL_CreateWindow("PlasmVM", 10, 10, 640, 400, 0);
	Renderer = SDL_CreateRenderer(Window, 1, SDL_RENDERER_ACCELERATED);
	
	Font = TTF_OpenFont("plasmvga.ttf", 16);
	
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_Rect Rectangle;
	Rectangle.x = 0;
	Rectangle.y = 0;
	Rectangle.w = 640;
	Rectangle.h = 400;
	SDL_RenderDrawRect(Renderer, &Rectangle);
	SDL_RenderPresent(Renderer);
	termctx->Color = 0xFFFFFFFF;
	
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
	char* RealData = malloc(4);
	RealData[0] = Data;
	RealData[1] = 0x00;
	
	SDL_Color RealColor;
	RealColor.r = (termctx->Color & 0xFF000000) >> 24;
	RealColor.g = (termctx->Color & 0x00FF0000) >> 16;
	RealColor.b = (termctx->Color & 0x0000FF00) >> 8;
	RealColor.a = (termctx->Color & 0xFF0000FF) >> 0;
	
	SDL_Surface* Rendered = TTF_RenderText_Solid(Font, RealData, RealColor);
	SDL_Texture* NewTexture = SDL_CreateTextureFromSurface(Renderer, Rendered);
	SDL_FreeSurface(Rendered);
	
	SDL_Rect TargetRect;
	TargetRect.x = (int)termctx->CursorX * 8;
	TargetRect.y = (int)termctx->CursorY * 16;
	TargetRect.w = 8;
	TargetRect.h = 16;
	
	termctx->CursorX++;
	
	SDL_RenderCopy(Renderer, NewTexture, NULL, &TargetRect);
	SDL_RenderPresent(Renderer);
	free(RealData);
}

void termi_bigdata(u32 Data) {
	termctx->BigData = Data;
}

void termi_sendcc(byte Code) {
	switch (Code) {
		case CC_NEWLINE:
			termctx->CursorY++;
			break;
		case CC_RETURN:
			termctx->CursorX = 0;
			break;
		case CC_BEEP:
#ifdef _WIN32
			MessageBeep(0); // 0 = default exclamation
#else
			fputc('\a', stdout);
			fflush(stderr);
#endif
			break;
		case CC_SETCOLOR:
			termctx->Color = termctx->BigData;
			break;
		case CC_CLRCOLOR:
			termctx->Color = 0xFFFFFFFF;
			break;
		case CC_SETCURX:
			termctx->CursorX = termctx->BigData;
			break;
		case CC_SETCURY:
			termctx->CursorY = termctx->BigData;
			break;
		case CC_CLEAR:
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_Rect Rectangle;
			Rectangle.x = 0;
			Rectangle.y = 0;
			Rectangle.w = 640;
			Rectangle.h = 400;
			SDL_RenderDrawRect(Renderer, &Rectangle);
			SDL_RenderPresent(Renderer);
			termctx->CursorX = 0;
			termctx->CursorY = 0;
			break;
	}
}
