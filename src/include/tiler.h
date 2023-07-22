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

#ifndef TILER_H
#define TILER_H


#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <getopt.h>
#include <magic.h>

#include <tconf.h>

#include <SDL.h>

int tiler_init(const char *_tilefile);
void tiler_render_main();
void tiler_render_term();
void tiler_pollevent();
void tiler_clean();
void tiler_keyboard();
void tiler_quit(int status);
void printinst();
SDL_Texture *load_tile(const char *filename);

#endif //TILER_H
