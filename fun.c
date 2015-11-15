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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "haider.h"
#define MINI 10
#define RACK 100
void linit(list *l) {
	l->head = l->tail = NULL;
	l->length = 0;
}
void rinit(rlist *m){
	m->length = 0;
	m->head = m->tail = NULL;	               
}
void tinit(tlist *n) {
	n->head = n->tail = NULL;
}
void traverse(list *l) {
	node *p = l->head;
	while(p) {
		printf(" [ ");
		printf("%s %s %d %d", 
				p->name,
				p->brand,
				p->quantity,
				p->rackno);	
		printf(" ]\n");
		p = p->next;
	}
}
void rtraverse(rlist *m) {
	rack *q = m->head;
	while(q) {
		printf("Rack no. %d\n", q->rackno);
		printf("Total number of medicines in the rack: %d\n", q->count);
		printf(" [ ");
		node *r = q->n.head;
		while(r) {
			printf("%s %s %d ", 
					r->name,
					r->brand,
					r->quantity);
			
			r = r->rnext;
		}		
		printf("]\n");
		q = q->next;
	}
}
void buy(list *l, rlist *m){
	rack *q = m->head;
	int gotit;
	char c;
	node *temp = (node *)malloc(sizeof(node));
	printf("Name of product: ");
	scanf("%s", temp->name);
	printf("Manufacturing company: ");
	scanf("%s", temp->brand);
	printf("Quantity of product: ");
	scanf("%d", &temp->quantity);
	printf("Date of manufacture(mm/yyyy): ");
	scanf("%s", temp->mandate);
	printf("Date of expiry(mm/yyyy): ");
	scanf("%s", temp->expdate);
	printf("Cost Price per unit: ");
	scanf("%f", &temp->cp);
	printf("Selling Price per unit: ");
	scanf("%f", &temp->sp);
	while(1) {
		gotit = 0;
	        printf("Rack number: ");
	        while(scanf("%d", &temp->rackno)) {
		        if(temp->rackno > RACK && temp->rackno < 0) { 
 		        	printf("Rack number does not exist...Enter again\nRack number: ");	
		        	continue;
		        }
		        else
		        	break;
	        }
	        while(q) {
	        	if(temp->rackno == q->rackno) {
	        		gotit = 1;
	        		break;		
	        	}
	        	q = q->next;
	        }
	        if(gotit == 0) {
	        	rack *demp = (rack *)malloc(sizeof(rack));
	        	if(m->head == NULL) 
	        		m->head = m->tail = demp;
	        	else {
	        		m->tail->next = demp;
	        		m->tail = demp;
	        	}	
	        	demp->next = NULL;
	        	m->length++;
	        	demp->count = 0;
	        	demp->rackno = temp->rackno;
	        	tinit(&(demp->n));
	        	demp->n.head = demp->n.tail = temp;
	        	demp->count += temp->quantity;
	        	if(l->head == NULL) 
	        		l->head = l->tail = temp;
	        	else {
	        		l->tail->next = temp;
	        		l->tail = temp;
	        	}
	        	temp->next = temp->rnext = NULL;
	        	l->length++;
	        	break;
	        }
	        else {
        		if(!rackfull(q, temp->quantity)) {	        	
	 	       		node *r = q->n.tail;
	 	       		r->rnext = temp;
	 	       		q->n.tail = temp;
	 	       		q->count += temp->quantity;
	 	       		if(l->head == NULL) 
	        			l->head = l->tail = temp;
	       	 		else {
	        			l->tail->next = temp;
	        			l->tail = temp;
	        		}
	        		temp->next = NULL;
	        		l->length++;
	 	       		break;
	       		}		
                	else {
                	        printf("Cannot accomodate given number of tablets\n");
				printf("Do you want to exit? [Y/n] ");
				getchar();
				scanf("%c", &c);
				if(c == 'y') {
					save(l);
					exit(0);
				}
			}
		}
	}
}
int rackfull(rack *q, int quantity){
        if(q->count + quantity >= 1000)
                return 1;
        return 0;
}
void sell(list *l, rlist *m){
	float tbill = 0, disc;
	char c = 'y';
	while(c == 'y') {
		node *p = l->head;
		rack *q = m->head;
		char *name;
		int qnt, gotit = 0;
		name = (char *)malloc(16 * sizeof(char));
		printf("Name of medicine: ");
		scanf("%s", name);
		printf("Quantity: ");
		scanf("%d", &qnt);
		while(p) {
			if(!strcmp(name, p->name)){
				if(p->quantity >= qnt) {
					p->quantity -= qnt;
					printf("Discount : ");
					scanf("%f", &disc);
					tbill += qnt * p->sp * (1 - disc / 100);	
					while(q) {
						if(p->rackno == q->rackno) {
							q->count -= qnt;
							break;
						}
						q = q->next;
					}
					gotit = 1;
					break;			
				}
				printf("Available quantity: %d\n", p->quantity);	
				printf("Davaai kam hai...\n");	
				gotit = 1;		
				break;
			}
			p = p->next;
		}
		if(gotit == 0)
			printf("Not Found\n");
		free(name);	
		printf("Bill: %f\n", tbill);
		c = contsell();
	}		
}
char contsell() {
	char c;
	printf("Sell more[y/n] ? \n");
	getchar();
	scanf("%c", &c);
	return c;
}
void remov(list *l, rlist *m, char *name) {
	node *p = l->head;
	rack *q = m->head;
	node *r, *temp1 = p, *temp2;
	int gotit = 0;
	char c;
	while(p) {
		if(!strcmp(p->name, name)){		
			if(p == temp1) 
				l->head = p->next;
			else if(p == l->tail) {
				l->tail = temp1;
				temp1->next = NULL;
			}
			else
				temp1->next = p->next;
			l->length--;
			while(q) {
				if(q->rackno == p->rackno) {
					r = q->n.head;
					temp2 = r;
					q->count -= p->quantity;
					while(r) {
						if(!strcmp(r->name, name)) {
							if(r == temp2) 
								q->n.head = r->rnext;
							else if(r == q->n.tail) 
								temp2->rnext = NULL;
							else 
								temp2->rnext = r->rnext;
							free(r);
							break;
						}
						temp2 = r;
						r = r->rnext;
					}
					gotit = 1;
					break;				
				}
				q = q->next;
			}
			gotit = 1;
			break;
		}
		temp1 = p;
		p = p->next;
		if(gotit == 0 && !p) {
			printf("Not found!!\nTry again\n");
			printf("Do you want to exit? [Y/n] ");
			getchar();
			scanf("%c", &c);
			if(c == 'y') {
				save(l);
				exit(0);
			}
			printf("Enter name:");
			scanf("%s", name);
		}
	}
}
void save(list *l) {
	FILE *fp = fopen("mybackup.dat", "w");
	if(fp == NULL) {
		perror("Save failed");
		exit(0);
	}
	node *p = l->head;
	while(p) {
		fwrite(p, sizeof(node), 1, fp);
		p = p->next;	
	}
	fclose(fp);
}
void retrieve(list *l, rlist *m) {
	FILE *fp = fopen("mybackup.dat", "a+");
	if(fp == NULL) {
		perror("Retrieve failed");
		exit(0);
	}
	node *p = l->head;
	rack *q = m->head;
	node *r;
	int flag = 0;
	while(1) {
		node *temp = (node *)malloc(sizeof(node));
		if(!fread(temp, sizeof(node), 1, fp)) {
			if(flag == 0)
				return;
			l->tail = p;
			break;
		}
		if(flag == 0) {
			l->head = p = temp;
			p->next = NULL;
			l->length++;
			flag = 1;
			continue;
		}	
		p->next = temp;
		temp->next = NULL;
		l->length++;	
		p = p->next;
	}
	p = l->head;
	while(p) {
		flag = 0;
		q = m->head;
		while(q) {
			if(p->rackno == q->rackno) {
				flag = 1;
				r = q->n.head;
				p->rnext = r;
				q->n.head = p;
				q->count += p->quantity;
			}
			q = q->next;
		}
		if(flag == 0) {
			rack *demp = (rack *)malloc(sizeof(rack));
			if(m->head) {
				m->tail->next = demp;
				m->tail = demp;
			}
			else 
				m->head = m->tail = demp;
			demp->rackno = p->rackno;
			demp->next = NULL;
			m->length++;
			tinit(&(demp->n));
			demp->n.head = demp->n.tail = p;
			p->rnext = NULL;
			demp->count = p->quantity;
		}
		p = p->next;
	}
}
void destroy(list *l, rlist *m) {
	node *y, *p = l->head;
	while(p) {
		y = p;
		p = p->next;
		free(y);
	}
	rack *z, *q = m->head;
	while(q) {
		z = q;
		q = q->next;
		free(z);
	}
}
void expalert(list *l,rlist *m, char *date) {
	node *p;
	char c;
	p = l->head;
	int a = atoi(date), b;
	while(p) {
		b = atoi(p->expdate);
		if(b == a) {
			printf("Going to Expire...\n");
			printf("%s %s %d %d\n", p->name, p->brand,
						p->quantity, p->rackno);
			printf("Do you want to remove?[y/n]");
			scanf("%c", &c);			
			if(c == 'y') 
				remov(l, m, p->name);				
		}
		p = p->next;
	}
}
void minalert(list *l) {
	node *p;
	p = l->head;
	int flag = 0;
	while(p) {
		if(p->quantity <= MINI) {
			if(flag == 0)
				printf("Less qunatity alert...\n");
			printf("Name: %s\n", p->name);
			printf("Brand: %s\n", p->brand);
	  		printf("remaining quantity: %d\n",p->quantity);
			printf("Rack no,: %d\n", p->rackno);
			flag = 1;
		}						
		p = p->next;
	}
}
void changepos(list *l, rlist *m, char *name) {
	node *r, *temp;
	rack *q;
	node *p = l->head;
	int newp, gotit = 0;
	while(p) {
		if(!strcmp(name, p->name)) {
			gotit = 1;
			printf("Current Position: rack no. %d\n", p->rackno);
			while(1) {	
				printf("New Position: ");
				getchar();
				scanf("%d", &newp);
				q = m->head;
				while(q) {
					if(q->rackno == newp)
						break;
					q = q->next;
				}
				if(!rackfull(q, p->quantity) && (newp > 0 && newp <= RACK)) {
					q = m->head;
					while(q) {
						if(p->rackno == q->rackno) {
							r = q->n.head;
							temp = r;
							while(r) {
								if(!strcmp(name, r->name)) {
									if(temp == r) {
										q->n.head = r->rnext;
									}	
									else if(r == q->n.tail) {
										q->n.tail = temp;
										temp->rnext = NULL;
									}
									else {
										temp->rnext = r->rnext;
									}
									break;
								}
								temp = r;
								r = r->rnext;	
							}
							q->count -= r->quantity;
							break;
						}
						q = q->next;	
					}
					q = m->head;
					while(q) {
						if(newp == q->rackno) {
							temp = q->n.head;
							r->rnext = temp->rnext;
							temp->rnext = r;
							q->count += r->quantity;
							r->rackno = newp;
							break;
						}
						q = q->next;
					}
					break;
				}
				else 
					printf("rack is full. \n");				
			}
		}
		p = p->next;
	}
	if(gotit == 0) 
		printf("Not Found\n");		
}
void search(list *l, char *name) {
	node *p = l->head;
	int gotit = 0;
	while(p) {
		if(!strcmp(name, p->name)) {
			gotit = 1;
			printf("Found :)\n");
			printf("%s %s %d %d %f\n", p->name, p->brand, p->rackno, p->quantity, p->sp);
		}	
		p = p->next;
	}
	if(gotit == 0)
		printf("Not Found :(\n");
}
void networth(list *l) {
	float net = 0;
	node *p = l->head;
	while(p) {
		net += p->quantity * p->sp;
		p = p->next;
	}
	printf("Net worth of our shop is %f\n", net);
}
void deletemptynode(list *l, rlist *m) {
	node *p, *temp;
	p = temp = l->head;
	while(p) {
		if(p->quantity == 0) {
			if(p == temp) {
				l->head = p->next;
				del(p, m);
				p = temp = l->head;
				l->length--;
				continue;
			}
			else if(p == l->tail) {
				temp->next = NULL;
				l->tail = temp;
				del(p, m);
				l->length--;
				break;	
			}
			else {
				temp->next = p->next;
				del(p, m);
				p = temp;
				l->length--;
			}
			
		}
		temp = p;
		p = p->next;
	}	
}
void del(node *p, rlist  *m) {
	rack *q = m->head;
	node *r, *temp;
	while(q) {
		if(p->rackno == q->rackno) {
			r = q->n.head;
			temp = r;
			while(r) {
				if(!strcmp(p->name, r->name)) {
					if(r == temp) {
						q->n.head = r->rnext;
						free(temp);
						r = temp = q->n.head;
					}
					else if(r == q->n.tail) {
						temp->rnext = NULL;
						q->n.tail = temp;
						free(r);
						break;			
					}
					else {
						temp->rnext = r->rnext;
						free(r);
						r = temp;
					}
				}
				temp = r;
				r = r->rnext;
			}	
		}
		q = q->next;
	}
}
void deletemptyrack(rlist *m) {
	rack *q = m->head;
	rack *temp = q;
	while(q) {
		if(q->count == 0) {
			if(q == temp) {
				m->head = q->next;
				free(temp);
				q = temp = m->head;
				m->length--;
				continue;
			}	
			else if(q == m->tail) {
				temp->next = NULL;
				m->tail = temp;
				free(q);
				m->length--;
				break;
			}
			else {
				temp->next = q->next;
				free(q);
				q = temp;	
				m->length--;			
			}
			
		}
		temp = q;
		q = q->next;
	}
}
char *getdate() {
	time_t today;
	struct tm * tm_today;
	char buff[32];
	today = time(NULL);
	tm_today = localtime(&today);
	strftime(buff, sizeof(buff), "%a %d-%m-%Y", tm_today);
	strcpy(date, buff);
	return date;
}
char *getdatexp() {
	time_t today;
	struct tm * tm_today;
	char buff[32];
	today = time(NULL);
	tm_today = localtime(&today);
	strftime(buff, sizeof(buff), "%m%Y", tm_today);
	strcpy(date, buff);
	return date;
}
