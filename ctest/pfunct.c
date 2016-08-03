#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000		/* max # of lines to be sorted */

char *lineptr[MAXLINES];	/* pointers to text lines */
int readlines (char *lineptr[], int nlines);
void writelines (char *lineptr[], int nlines);

void myqsort (void *lineptr[], int left, int right, int (*cmp) (void *, void *) );

int numcmp (char *, char *);

/* sort input lines */
int main (int argc, char *argv[]){
	int nlines;		/* number of input line read */
	int numeric = 0; /* 1 if numeric sort */

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if ( (nlines = readlines(lineptr, MAXLINES)) >= 0 ){
		myqsort ((void**) lineptr, 0, nlines - 1,
				(int (*) (void *, void *)) (numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf ("input too big to sort\n");
		return 1;
	}
}
/* myqsort */

void myqsort (void *v[], int left, int right, int (*cmp) (void *, void *) ){
	int i, last;

	void swap (void *v[], int, int);

	if (left >= right)
		return;
	swap (v, left, (left + right) /2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ( (*cmp)(v[i], v[left]) < 0 )
			swap(v, ++last, i);
	swap(v, left, last);
	myqsort(v, left, last - 1, cmp);
	myqsort(v, last + 1, right, cmp);
}

/* numcmp */
int numcmp (char *s1, char *s2){
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* swap */
void swap (void *v[], int i, int j){
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* readlines */

int readlines (char *lineptr[], int maxlines){
	FILE *fp;
	size_t len = 0;
	ssize_t readlen;
	char *buf = NULL; 
	char *p;
	int nlines = 0;

	fp = fopen("input.txt", "r");

	if (fp == NULL)
		return -1;

	while( (readlen = getline(&buf, &len, fp)) > 0){
		if (nlines > maxlines || (p = malloc(len)) == NULL){
			printf("AAA\n");
			return -1;
		}
		else {
			buf[len - 1] = '\0';
			strcpy(p, buf);
			lineptr[nlines++] = p;	
		}
	}
	return nlines;
}

/* writelines */
void writelines (char *lineptr[], int nlines){
	int i;

	for(i = 0; i < nlines; i++){
		printf("%s",lineptr[i]);
	}
}
