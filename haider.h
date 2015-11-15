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
 
 
char date[32];

typedef struct node{
	char name[16];
	char brand[16];
	int quantity;
	float cp, sp;
	char expdate[9];
	char mandate[9];
	int rackno;
	struct node *next;
	struct node *rnext;
}node;
typedef struct list{
	node *head, *tail;
	int length;
}list;

typedef struct tlist {
	node *head, *tail;
}tlist;

typedef struct rack{
	int rackno;
	int count;		//no of tablets
	tlist n; 
	struct rack *next;   
}rack;
typedef struct rlist{
	rack *head, *tail;
	int length;
}rlist;

void linit(list *l);					//
void rinit(rlist *m);					//	
void buy(list *l, rlist *m);				//
int rackfull(rack *q, int quantity);			//
void sell(list *l, rlist *m);				//
char contsell(void);					//
void traverse(list *l);					//
void rtraverse(rlist *m);				//
void remov(list *l, rlist *m, char *name);		//
void networth(list *l);					//
void save(list *l);					//
void retrieve(list *l, rlist *m);			//
void search(list *l, char *name);			//
void minalert(list *l);					//
void expalert(list *l, rlist *m, char *date);		//
void printmenu(void);					//
void changepos(list *l, rlist *m, char *name);		//
void destroy(list *l, rlist *m);			//
char *getdate();
char *getdatexp();
void deletemptynode(list *l, rlist *m);			//
void deletemptyrack(rlist *m);				//
void del(node *p, rlist *m);				//
