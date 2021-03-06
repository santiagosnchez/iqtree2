/*

BOOSTER: BOOtstrap Support by TransfER: 
BOOSTER is an alternative method to compute bootstrap branch supports 
in large trees. It uses transfer distance between bipartitions, instead
of perfect match.

Copyright (C) 2017 Frederic Lemoine, Jean-Baka Domelevo Entfellner, Olivier Gascuel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#define _GNU_SOURCE
#include <stdlib.h>

#ifndef _SORT_H
#define _SORT_H

int comp_double(const void * elem1, const void * elem2);
int comp_indexes(const void * elem1, const void * elem2, void * other_array);
int comp_indexes_apple(void * other_array, const void * elem1, const void * elem2);

void sort_double(double * tab, int size);
void sort_indexes_double(int * indexes, int size, double * values);

#endif
