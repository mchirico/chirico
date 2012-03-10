#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
  int i, j, k, p;          /* For loops */
  int pNum;                /* Page number */
  int pGraphs;             /* Paragraphs per page */
  char paragraph[4][256];  /* Our paragraphs */
  char ***Book = NULL;     /* Our book */

  /* Copy data to string */
  strcpy(paragraph[0], "Pointers are awesome!");
  strcpy(paragraph[1], "Now that I have learned 3-dimensional arrays,");
  strcpy(paragraph[2], "I can use this knowledge");
  strcpy(paragraph[3], "to write my own programs!");

  /* Initialize loop variables */
  j = p = 0;
  pNum = 2;    /* 2 pages */
  pGraphs = 4; /* 2 paragraphs per page */

  /* Allocate memory */
  Book = malloc(pNum * sizeof *Book);
  if (Book != NULL) {
    for (i = 0; i < pNum; i++) {
      /* Allocate memory */
      Book[i] = malloc(pGraphs * sizeof *Book);

      /* If allocation failed */
      if (Book[i] == NULL) {
	/* Free any memory that was previously used */
	for (k = i; k >= 0; k--) {
	  if (Book[k] != NULL) {
	    free(Book[k]);
	    Book[k] = NULL;
	  }
	}
	/* Free any memory that was previously used from beginning */
	if (Book != NULL) {
	  free(Book);
	  Book = NULL;
	}

	/* Terminate program */
	return 0;
      }

      for (j = 0; j < pGraphs; j++) {
	/* Allocate memory */
	Book[i][j] = malloc(strlen(paragraph[j]) + 1);

	/* If allocation failed */
	if (Book[i][j] == NULL) {
	  /* Free any memory that was previously used */
	  for (k = j; k >= 0; k--) {
	    if (Book[i][k] != NULL) {
	      free(Book[i][k]);
	      Book[i][k] = NULL;
	    }
	  }
	  /* Free any memory that was previously used in previous loop */
	  for (k = i; k >= 0; k--) {
	    if (Book[k] != NULL) {
	      free(Book[k]);
	      Book[k] = NULL;
	    }
	  }
	  /* Free any memory that was previously used from beginning */
	  if (Book != NULL) {
	    free(Book);
	    Book = NULL;
	  }

	  /* Terminate program */
	  return 0;
	}

	/* Copy data to pointer */
	strcpy(Book[i][j], paragraph[j]);
      }
    }
  }else {
    return 0;
  }

  /* Print data */
  p = 0;
  printf("My two page book\n");
  for (i = 0; i < pNum; i++) {
    printf("\nPage: %i\n", i);
    for (j = p; j < (p + 2); j++) {
      printf("%s\n", Book[i][j]);
    }
    p = j;
  }

  /* Free Memory */
  for (i = 0; i < pNum; i++) {
    for (j = 0; j < pGraphs; j++) {
      free(Book[i][j]);
      Book[i][j] = NULL;
    }
    free(Book[i]);
    Book[i] = NULL;
  }
  free(Book);
  Book = NULL;

  /* End program */
  return 0;
}
