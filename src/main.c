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
#include <tmesg.h>

static struct option longopt[] = {
	//{"file", 1, 0, 'f'},
	{"help", 0, 0, 'h'},
	{"version", 0, 0, 'v'},
	{0, 0, 0, 0}
};

int gameloop = 1;
const int framerate = 50000000;

void printinst() {
	printf("%s\n", INSTRUCTIONS);
}

int main (int argc, char **argv) {
	int curind = 0;

	//int curopt = getopt_long(argc, argv, "f:hv", longopt, &curind);
	int curopt = getopt_long(argc, argv, "hv", longopt, &curind);
	switch (curopt) {
		case 'h':
			printf("%s\n", HELPMSG);
			printinst();
			return 0;
			break;
		case 'v':
			printf("tiler version %i.%i %s\n", tiler_VERSION_MAJOR, tiler_VERSION_MINOR, WARNING);
			return 0;
			break;
		default:
			break;
	}

	FILE *test = NULL;

	if (argc > 1) {
		for (int i = 1; i < argc; i ++) {
			test = fopen(argv[i], "r");
			if (test == NULL) {
				printf("File %s does not exist.\n", argv[i]);
			} else {
				printf("File %s found.\n", argv[i]);
				fclose(test);
				test = NULL;
			}
		}
	}

	if (tiler_init() != 0) return -1;

	while (gameloop == 1) {
		for (int i = 0; i < framerate; i++) {
			if (i == 0) {
				tiler_pollevent();
				tiler_keyboard();
				tiler_render();
			}
		}
	}

	return 0;
}

void tiler_quit (int status) {
	tiler_clean();

	switch (status) {
		case 0:
			printf("CODE %i: Exited without issue\n", status);
			break;
		default:
			printf("UNRECOGNIZED ERROR.\n");
			break;
	}

	gameloop = 0;
}
