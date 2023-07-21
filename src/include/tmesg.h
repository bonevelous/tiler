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

#ifndef TMESG_H
#define TMESG_H

const char *HELPMSG = "Usage: imgtiletest [OPTIONS]... [FILES]... \n"
		"-h, --help\tDisplay this help and exit\n"
		"-v, --version\toutput version information and exit\n"
		"---------------------------------------------------\n";

const char *INSTRUCTIONS = "When running tiler, use the arrow keys to change\n"
		"the offset of the tiles, and hit space to print\n"
		"the tile size and offset to the terminal.\n";

const char *WARNING = "Copyright (C) 2023 Matthew Gobbi\n\n"
		"This program is copyrighted under GPL3\n"
		"and comes with ABSOLUTELY NO WARRANTY.\n"
		"Read LICENSE.txt for more details.\n";

#endif //TMESG_H
