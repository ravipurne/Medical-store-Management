/*****************************************************************************
 * Copyright (C) Ravishankar Purne purnerb14.comp@coep.ac.in
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
 
 
#include <stdio.h>
#include "haider.h"
#include <stdlib.h>

void printmenu() {
	printf("\t\tMenu \n\
		1. sell product to costumer \n\
		2. buy a product\n\
		3. remove from shop\n\
		4. print all products\n \
		5. print rack wise\n \
		6. change position of product\n\
		7. calculate shop worth\n \
		8. search a product \n\
		9. exit\n");
}

int main() {
	system("clear");
	printf("****************The Medical Store******************\n");
	int choice;
	list l;
	rlist m;
	linit(&l);
	rinit(&m);
	char *name;
	printf("\t\t\t\tDate: %s\n", getdate());
	retrieve(&l, &m);
	expalert(&l, &m, getdatexp());
	minalert(&l);
	while(1) {
		printmenu();
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				sell(&l, &m);
				deletemptynode(&l, &m);
				deletemptyrack(&m);
				system("clear");
				break;
				
			case 2:
				buy(&l, &m);	
				system("clear");
				break;
			
			case 3:
				name = (char *)malloc(sizeof(char) * 16);
				printf("Name: ");
				scanf("%s", name);
				remov(&l, &m, name);
				deletemptynode(&l, &m);
				deletemptyrack(&m);
				system("clear");
				break;
			
			case 4:
				traverse(&l);
				break;
			
			case 5:
				rtraverse(&m);
				break;
			
			case 6:
				name = (char *)malloc(sizeof(char) * 16);
				printf("Name: ");
				scanf("%s", name);
				changepos(&l, &m, name);
				free(name);
				deletemptynode(&l, &m);
				deletemptyrack(&m);
				break;
			
			case 7:
				networth(&l);
				break;
			
			case 8:
				name = (char *)malloc(sizeof(char) * 16);
				printf("Name: ");
				scanf("%s", name);
				search(&l, name);
				free(name);
				break;
				
			case 9:
				save(&l);
				destroy(&l, &m);
				system("clear");
				exit(0);
				break;
			
			default:
				printf("Invalid Option\n");	
				break;
			
		}
	}
	return 0;
}
