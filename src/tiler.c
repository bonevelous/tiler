/*******************************************************************************

    tiler - Tests the tilability of an image file.
    Copyright (C) 2023	Matthew Gobbi
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*******************************************************************************/

#include <tiler.h>

#define WINX SDL_WINDOWPOS_CENTERED
#define WINY SDL_WINDOWPOS_CENTERED
#define WINF SDL_WINDOW_RESIZABLE

int winw = 800;
int winh = 600;

int tilex = 1;
int tiley = 1;

int offsetx = 0;
int offsety = 0;

int mvspd = 1;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;
SDL_Texture *tileimg = NULL;
SDL_Rect img_src = {0, 0, 16, 16};
SDL_Rect img_dst = {0, 0, 16, 16};
SDL_Event event;

int tiler_init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("%s\n", SDL_GetError());
		return -1;
	}

	win = SDL_CreateWindow("tiler", WINX, WINY, winw, winh, WINF);
	if (win == NULL) {
		printf("%s\n", SDL_GetError());
		return 1;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		printf("%s\n", SDL_GetError());
		return 1;
	}

	tileimg = load_tile("./src/data/tile0.bmp");
	if (tileimg == NULL) return 1;
	SDL_QueryTexture(tileimg, NULL, NULL, &img_src.w, &img_src.h);
	SDL_QueryTexture(tileimg, NULL, NULL, &img_dst.w, &img_dst.h);

	printinst();

	return 0;
}

SDL_Texture *load_tile(const char *filename) {
	SDL_Texture *_tex = NULL;
	SDL_Surface *temp = NULL;

	temp = SDL_LoadBMP(filename);
	if (temp == NULL) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	_tex = SDL_CreateTextureFromSurface(ren, temp);
	if (_tex == NULL) {
		printf("%s\n", SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(temp);
	temp = NULL;
	return _tex;
}

void tiler_keyboard() {
	const uint8_t *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LSHIFT]) {
		mvspd = 8;
	} else {
		mvspd = 1;
	}

	if (keystate[SDL_SCANCODE_RIGHT]) offsetx += mvspd;
	if (offsetx >= img_src.w) offsetx = 0 + (offsetx % img_src.w);

	if (keystate[SDL_SCANCODE_LEFT]) offsetx -= mvspd;
	if (offsetx < 0) offsetx = img_src.w - 1 + (offsetx % img_src.w);

	if (keystate[SDL_SCANCODE_DOWN]) offsety += mvspd;
	if (offsety >= img_src.h) offsety = 0 + (offsety % img_src.h);

	if (keystate[SDL_SCANCODE_UP]) offsety -= mvspd;
	if (offsety < 0) offsety = img_src.h - 1 + (offsety % img_src.h);

}

void tiler_render() {
	SDL_GetWindowSize(win, &winw, &winh);

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	tilex = winw / img_src.w;
	tiley = winh / img_src.h;
	for (int i = -1; i <= tilex; i++) {
		img_dst.x = (i * img_src.w) + offsetx;
		for (int j = -1; j <= tiley; j++) {
			img_dst.y = (j * img_src.h) + offsety;
			SDL_RenderCopy(ren, tileimg, &img_src, &img_dst);
		}
	}

	SDL_RenderPresent(ren);
}

void tiler_pollevent() {
	while (SDL_PollEvent(&event) != 0) {
		switch(event.type) {
			case SDL_QUIT:
				tiler_quit(0);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE:
						tiler_quit(0);
						break;
					case SDLK_SPACE:
						printf("\x1b[1;32mTILE INFO\x1b[0m:\n"
							"\t\x1b[0;36mSIZE\x1b[0m: %ix%i\n"
							"\t\x1b[0;36mOFFSET\x1b[0m: %ix%i\n\n", \
							img_src.w, img_src.h, offsetx, offsety);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void tiler_clean() {
	SDL_DestroyTexture(tileimg);
	tileimg = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	SDL_DestroyWindow(win);
	win = NULL;

	SDL_Quit();
}
