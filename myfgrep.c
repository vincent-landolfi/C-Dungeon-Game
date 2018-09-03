#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char** argv) {
	char *word = argv[1];
	int index = 2;
	int optionl = 0;
	int optionh = 0;
	int optionm = 0;
	int printedFile = 1;
	if (argc < 2) {
	    printf("usage: myfgrep [-lh] [-m count] searchstring [file ..] \n");
	    return(2);
	}
	if (strcmp(word,"-l") || strcmp(word,"-h")){
		word = argv[2];
		index = 3;
	} else if (strcmp(word,"-m")){
		word = argv[3];
		index = 4;
	}
	int option;
	while ((option = getopt(argc, argv, "m:lh")) != -1) {
		switch (option) {
			case 'l' :
				optionl = 1;
				break;
			case 'h' :
				optionh = 1;
				break;
			case 'm' :
				optionm = 1;
				break;
		}
	}
	if (strcmp(argv[index],"-l") || strcmp(argv[index],"-h")){
		index++;
	} else if (strcmp(argv[index],"-m")){
		index = index + 2;
	}
	FILE* file = fopen(argv[index],"r");
	char line[256];
	while(file != NULL){
		while (fgets(line,sizeof(line),file)){
			if (strstr(line,word) != NULL){
				if (optionl){
					if (printedFile) {
					printf("%s",argv[index]);
					printedFile = 0;
					}
				} else {
					if (argc > 3 && !optionh){
						printf("%s:%s",argv[index],line);
					} else {
						printf("%s",line);
					}
				}
			}
		}
		fclose(file);
		printf("\n");
		index++;
		printedFile = 1;
		if (strcmp(argv[index],"-l") || strcmp(argv[index],"-h")){
			index++;
		} else if (strcmp(argv[index],"-m")){
			index = index + 2;
		}
		file = fopen(argv[index],"r");
	}
	return(0);
}
