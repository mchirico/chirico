/*  Left Node Right (LNR) linked list.


*/


#include <stdio.h>
#include <stdlib.h>

struct linked_list {
	double item;
	struct linked_list *left;
	struct linked_list *right;
};

void insert_left(struct linked_list **main_list, double item_to_insert)
{
	struct linked_list *new_item;
	new_item = malloc(sizeof(struct linked_list));
	if (new_item == NULL) {
		fprintf(stderr, "Out of memory: insert_left\n");
		exit(1);
	}
	new_item->item = item_to_insert;
	if (*main_list == NULL) {
		new_item->left = NULL;
		new_item->right = NULL;
		*main_list = new_item;
	} else {
		new_item->left = (*main_list)->left;
		new_item->right = NULL;
		(*main_list)->left = new_item;
	}
}

void insert_right(struct linked_list **main_list, double item_to_insert)
{
	struct linked_list *new_item;
	new_item = malloc(sizeof(struct linked_list));
	if (new_item == NULL) {
		fprintf(stderr, "Out of memory: insert_right\n");
		exit(2);
	}
	new_item->item = item_to_insert;
	if (*main_list == NULL) {
		new_item->left = NULL;
		new_item->right = NULL;
		*main_list = new_item;
	} else {
		new_item->left = NULL;
		new_item->right = (*main_list)->right;
		(*main_list)->right = new_item;
	}

}

void print_LNR(struct linked_list *main_list)
{
	if (main_list == NULL)
		return;
	print_LNR(main_list->left);
	printf("%f\n", main_list->item);
	print_LNR(main_list->right);

}

void print_NLR(struct linked_list *main_list)
{
	if (main_list == NULL)
		return;
	printf("%f\n", main_list->item);
	print_NLR(main_list->left);
	print_NLR(main_list->right);
}

void print_LRN(struct linked_list *main_list)
{
	if (main_list == NULL)
		return;
	print_LRN(main_list->left);
	print_LRN(main_list->right);
	printf("%f\n", main_list->item);
}


void free_LRN(struct linked_list *main_list)
{
	if (main_list == NULL)
		return;
	free_LRN(main_list->left);
	free_LRN(main_list->right);
	/*  printf("%f\n",main_list->item);   */
	free(main_list);
	main_list = NULL;

}




int main()
{
	struct linked_list *main_list = NULL;
	insert_right(&main_list, 0.0);
	insert_left(&main_list, -5);
	insert_right(&main_list, 5);


	print_LRN(main_list);


	free_LRN(main_list);

	return 0;

}
