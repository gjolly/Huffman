#include "list.h"
#include <stdio.h>
#include <assert.h>
#define limite 10*1000 - 1
#define logLimite 4

static void big_List(List list)
{
	for(int i = 0; i < limite; i++)
		add_List(list, &i);
}

//Tests List of int

void init_data(void** this)			//Be careful, only one parameter
{
	*this = malloc(sizeof(int));
}

void destroy_data(void* this)		//Free for default
{
	free(this);
}

void equal_data(void* a, void* b)	//Set first data to the second
{
	*(int*)a = *(int*)b;
}

int compar_data(void* a, void* b)
{
	return (*(int*)a < *(int*)b) ? -1 : (*(int*)a > *(int*)b);
}

void print_list(List list)
{
	Cell cell = list->cell;
	while (cell != NULL)
	{
		printf("%d\t|", *(int*)(cell->data));
		cell = cell->next;
	}
	printf("\n");
}

void unit_init()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	destroy_List(&list);
}

void unit_add()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);	
	
	int deux = 2;
	add_List(list, &deux);
	print_list(list);
	
	add_List(list, &deux);
	print_list(list);
	
	big_List(list);
	print_list(list);
	
	destroy_List(&list);
}

void unit_front_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);
	
	printf("Front : %d\n", *(int*)front_List(list));
	
	big_List(list);
	print_list(list);
	printf("Front : %d\n", *(int*)front_List(list));
	
	destroy_List(&list);
}

void unit_pop_front_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);
	
	printf("Front : %d\n", *(int*)front_List(list));
	
	pop_front_List(list);
	print_list(list);
	
	big_List(list);
	print_list(list);
	printf("Front : %d\n", *(int*)front_List(list));
	
	pop_front_List(list);
	pop_front_List(list);
	printf("Front : %d\n", *(int*)front_List(list));
	
	destroy_List(&list);
}

void unit_back_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);
	
	printf("Back : %d\n", *(int*)back_List(list));
	
	big_List(list);
	print_list(list);
	printf("Back : %d\n", *(int*)back_List(list));
	
	destroy_List(&list);
}

void unit_pop_back_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);
	
	printf("Back : %d\n", *(int*)back_List(list));
	
	pop_back_List(list);
	print_list(list);
	
	big_List(list);
	print_list(list);
	printf("Back : %d\n", *(int*)back_List(list));
	
	pop_back_List(list);
	pop_back_List(list);
	printf("Back : %d\n", *(int*)back_List(list));
	
	destroy_List(&list);
}

void unit_has_data_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);
	
	int unBis = 1;
	printf("Has : %d\n", has_data_List(list, &unBis));
	
	big_List(list);
	print_list(list);
	int troiscents = 300;
	printf("Has : %d\n", has_data_List(list, &troiscents));
	
	clear_List(list);
	printf("Has : %d\n", has_data_List(list, &troiscents));
	
	destroy_List(&list);
}

void unit_get_i_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	add_List(list, &un);
	print_list(list);
	printf("get : %d\n", *(int*)get_i_List(list, 0));
	
	big_List(list);
	print_list(list);
	printf("get : %d\n", *(int*)get_i_List(list, 300));
	
	clear_List(list);
	printf("Get hors liste : %p\n", get_i_List(list, 42));
	
	destroy_List(&list);
}

void unit_push_List()
{
	List list;
	init_List(&list, sizeof(int), init_data, destroy_data, equal_data, compar_data);
	
	int un = 1;
	push_back_List(list, &un);
	print_list(list);
	
	int deux = 2;
	push_back_List(list, &deux);
	print_list(list);
	
	int trois = 3;
	push_front_List(list, &trois);
	print_list(list);
	
	destroy_List(&list);
}

void tests()
{
	unit_init();
	unit_add();
	unit_front_List();
	unit_pop_front_List();
	unit_back_List();
	unit_pop_back_List();
	unit_has_data_List();
	unit_get_i_List();
	unit_push_List();
}

int main(int argc, char** argv)
{
	tests();
	return 0;
}
