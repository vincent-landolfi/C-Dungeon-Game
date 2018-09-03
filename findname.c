#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int searchDir(char *file, char *directory) {
	DIR *dp;
	struct dirent *p;
	int length = 2000;
	struct stat statbuf;

	if((dp = opendir(directory)) == NULL) {
		perror(directory);
		return(1);
	}
	while ((p = readdir(dp))) {
		char path[length];
        strcpy(path,directory);
        strcat(path,"/");
        strcat(path,p->d_name);
        if (sizeof(path) > length) {
            fprintf (stderr, "Path too long\n");
            return(1);
        }
		if (strcmp(file,p->d_name) == 0){
			printf("%s\n", path);
		}
		if (lstat(path, &statbuf)) {
			perror(path);
			return(1);
		}else {
			if (S_ISDIR(statbuf.st_mode)) {
				if (strcmp(p->d_name,"..") != 0 &&
					strcmp(p->d_name,".") != 0 ) {
					searchDir(file,path);
				}
			}
		}
	}
	closedir(dp);
	return(0);
}

int main(int argc,char **argv){
	int i;
	int status;
	if (argc < 3) {
		printf("usage: findname FILE DIR...\n");
		return(2);
	}
	for(i=2;i<argc;i++){
		status = searchDir(argv[1],argv[i]);
	}
	return(status);
}