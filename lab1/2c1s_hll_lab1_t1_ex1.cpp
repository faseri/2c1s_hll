#include "SDL2/SDL.h"
#include <cstdlib>
#include <iostream>

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char**){
	std::cout<<"Begin main"<< std::endl;
	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 0, 20, 640, 480, SDL_WINDOW_SHOWN);
	if(win == 0){
	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
	system("PAUSE");
	SDL_Quit();
	return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(win == 0){
	SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
	SDL_Quit();
	return 1;
	}

	std::string imagePath = ".\\hello.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if(bmp == 0){
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
	SDL_Quit();
	return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	if(tex == 0){
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
	SDL_Quit();
	return 1;
	}

		SDL_Window *win2 = SDL_CreateWindow("Hello World! 2", 900,480,640,480, SDL_WINDOW_SHOWN);
		if(win2 == 0){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("PAUSE");
		SDL_Quit();
		return 1;
		}
		SDL_Renderer *ren2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(win2 == 0){
		SDL_DestroyWindow(win2);
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			system("PAUSE");
		SDL_Quit();
		return 1;
		}
		imagePath = ".\\hello2.bmp";
		bmp = SDL_LoadBMP(imagePath.c_str());
			if(bmp == 0){
				SDL_DestroyWindow(win2);
				SDL_DestroyRenderer(ren2);
				std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
				system("PAUSE");
			SDL_Quit();
			return 1;
			}
		SDL_Texture *tex2 = SDL_CreateTextureFromSurface(ren2, bmp);
		SDL_FreeSurface(bmp);
		if(tex2 == 0){
			SDL_DestroyWindow(win2);
			SDL_DestroyRenderer(ren2);
			std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
			system("PAUSE");
		SDL_Quit();
		return 1;
		}

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = 640;
	dst.h = 480;
	SDL_Rect dst2;
	dst2.x = 0;
	dst2.y = 0;
	dst2.w = 640;
	dst2.h = 480;
	for(int i = 0; i < 20; i++){
		SDL_RenderClear(ren);
		dst.x = 10*i;
		dst.y = 5*i;
		SDL_RenderCopy(ren, tex, NULL, &dst);
		SDL_RenderPresent(ren);

		SDL_RenderClear(ren2);
		dst2.x = -10*i;
		dst2.y = -5*i;
		SDL_RenderCopy(ren2, tex2, NULL, &dst2);
		SDL_RenderPresent(ren2);

		SDL_Delay(100);
	}
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	std::cout<<"End main before SDL_Quit"<< std::endl;
	SDL_Quit();
	std::cout<<"End main after SDL_Quit"<< std::endl;
//	system("PAUSE");
	return EXIT_SUCCESS;
}
