#include <libxml/tree.h>
#include <stdio.h>

typedef struct person{
	char *name;
	char *email;
	char *company;
	char *org;
	char *smail;
	char *webPage;
	char *phone;
}person, *personPtr;

/* parse function*/
personPtr parsePerson (xmlDocPtr doc, xmlNsPtr ns, xmlNodePtr cur) {
	personPtr ret = NULL;

	/*allocate the memory*/
	ret = (personPtr) malloc(sizeof(person));
	if(ret == NULL){
		fprintf(stderr, "Cannot allocate memory\n");
		return(NULL);
	}
	memset (ret, 0, sizeof(person));

	/*We don't care what the top element is*/
	cur = cur->xmlChildrenNode;
		
}

int main(){
	printf("End of program!\n");
	return 0;
}
