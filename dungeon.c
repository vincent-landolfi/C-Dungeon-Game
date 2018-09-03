#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUNGEONSIZE 10

int main(int argc,char **argv) {
	char *map[DUNGEONSIZE][DUNGEONSIZE];
	char *token;
	char src[50];
	int i = 0;
	int j = 0;
	int length = 0;
	if (argc != 2) {
		printf("usage: dungeon mapfile\n");
		return(2);
	}
	FILE* file;
	if ((file = fopen(argv[1],"r")) == NULL) {
		perror(argv[1]);
		return(1);
	}
	char line[256];

	while(fgets(line, sizeof(line), file) && i < DUNGEONSIZE) {
		if (line[strlen(line) - 1] == '\n') {
  			line[strlen(line) - 1] = '\0';
		}
		token = strtok(line," ");
		while(j < DUNGEONSIZE){
			if ((map[i][j] = malloc(strlen(src)+1)) == NULL) {
				fprintf(stderr, "out of memory\n");
				exit(1);
			}
			if (strlen(src) > length) {
				length = strlen(src);
			}
			if (token != NULL){
				strcpy(src,token);
				token = strtok(NULL," ");
			} else {
				strcpy(src,"pass");
			}
			strcpy(map[i][j],src);
			j++;
		}
		i++;
		j=0;
	}
	while (i<DUNGEONSIZE) {
		while(j<DUNGEONSIZE){
			if ((map[i][j] = malloc(strlen(src)+1)) == NULL) {
				fprintf(stderr, "out of memory\n");
				exit(1);
			}
			strcpy(map[i][j],"pass");
			j++;
		}
		i++;
		j=0;
	}
	char input[256];
	i = 0;
	j = 0;
	while (1) {
		printf("You are at: %s\n",map[i][j]);
		fgets(input,256,stdin);
		if (input[0] == 'n'){
			i--;
			if (i<0 || strcmp(map[i][j],"pass") == 0){
				while (i<0 || strcmp(map[i][j],"pass") == 0){
					i--;
					if (i<0){
						i = 9;
					}
				}
			}
		}else if (input[0] == 's'){
			i++;
			if (i>9 || strcmp(map[i][j],"pass") == 0){
				while (i>9 || strcmp(map[i][j],"pass") == 0){
					i++;
					if (i>9){
						i=0;
					}
				}
			}
		}else if (input[0] == 'e'){
			j++;
			if (j>9 || strcmp(map[i][j],"pass") == 0){
				while (i>9 || strcmp(map[i][j],"pass") == 0){
					j++;
					if (j>9){
						j=0;
					}
				}
			}
		}else if (input[0] == 'w'){
			j--;
			if (j<0 || strcmp(map[i][j],"pass") == 0){
				while (j<0 || strcmp(map[i][j],"pass") == 0){
					j--;
					if (j<0){
						j=9;
					}
				}
			}
		} else if (input[0] == 'm'){
			int k;
			int l;
			for (k = 0; k<DUNGEONSIZE;k++){
				for (l=0;l<DUNGEONSIZE;l++){
					printf("%-*s",length+3,map[k][l]);
				}
					printf("\n");
			}
		} else {
			printf("Type n, w, e, s, or m.\n");
		}
	}
	return(0);
}