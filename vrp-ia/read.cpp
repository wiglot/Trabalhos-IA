
/**
  * class Read
  * Read.cpp
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
  * 
  * This will open a file and read a instance from VRP
  */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "point.h"
#include "instancevrp.h"
#include "read.h"




// Constructors/Destructors
//  

Read::Read ( ):file("") {  }

Read::~Read ( ){ }


InstanceVRP Read::readVRP ( ){
	InstanceVRP *vrp;
	string line;
	size_t pos, newpos;
	int numTrucks, j, i;
	Point* point;

	if (this->file == "" )
		throw (string("Deve indicar um nome de arquivo anter de ler a instância\n"));
		
	fstream file_ptr(file.c_str(), fstream::in);
	if (!file_ptr.is_open())
		throw (string("Erro ao abrir arquivo " + this->file + "\n"));
	
	
	vrp = new InstanceVRP;
	//Nome Instancia
	getline (file_ptr, line);
	pos = line.find_last_of(" ");
	if (pos != string::npos)
		vrp->setName(line.substr(pos+1));
	else
		vrp->setName(this->file);	
	cout << "Reading: "<< vrp->getName() << " Instance."<< endl;
	
	getline (file_ptr, line);	
	getline (file_ptr, line);

	getline (file_ptr, line);	
	//Num veiculos
	pos = line.find_first_of(":");
	numTrucks = Read::str2int(line.substr(pos+1));
	
	getline (file_ptr, line);	
	//Capacidade
	getline (file_ptr, line);	
	pos = line.find_first_of(":");
	vrp->setCapacity(Read::str2int(line.substr(pos+1)));

	getline (file_ptr, line);
	//Lista de pontos
	for (i = 0; i < numTrucks; i++){
	    point = new Point;
		getline (file_ptr, line);
		//Number
		pos = 0;
		newpos = line.find_first_of(" ", pos+1);
		point->setNumber(Read::str2int(line.substr(pos, newpos-pos) ));
		//X
		pos = newpos  + 1;
		newpos = line.find_first_of(" ", pos+1);
		point->setX( Read::str2int(line.substr(pos, newpos-pos)));
		//Y
		pos = newpos  + 1;
		newpos = line.find_first_of(" ", pos+1);
		point->setY(Read::str2int(line.substr(pos, newpos-pos)));
		vrp->addPoint(point);
	}
	
	getline (file_ptr, line);
	//Lista de Demandas
	for (i = 0; i < numTrucks; i++){
		
		getline (file_ptr, line);
		//Number
		pos = 0;
		newpos = line.find_first_of(" ", pos+1);
		j = Read::str2int(line.substr(pos, newpos-pos));
		//Demanda
		pos = newpos  + 1;
		newpos = line.find_first_of(" ", pos+1);
		vrp->getPoint(j = 1)->setDemand( Read::str2int(line.substr(pos, newpos-pos)));
	}
	
	getline (file_ptr, line);
	//Lê Deposito
	getline (file_ptr, line);
	vrp->setDeposit(Read::str2int(line)-1);
	for (i = 0; i < vrp->getNumPoints(); i++)
	cout << vrp->getPoint(i)->getNumber() << endl;
	
	file_ptr.close();
	
	return *vrp;
}
    
