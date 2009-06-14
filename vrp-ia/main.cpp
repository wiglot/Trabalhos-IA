/*
 * main.cpp
 * This file is part of VRP-IA
 *
 * Copyright (C) 2009 - Wagner
 *
 * VRP-IA is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * VRP-IA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VRP-IA; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */
 
 

#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "point.h"
#include "instancevrp.h"
#include "read.h"

int main(int argc, char **argv){
	Read le = Read();
	
	if (argc > 1)
		le.setFile(string(argv[1]));
	
	le.readVRP();
	return 0;
}

