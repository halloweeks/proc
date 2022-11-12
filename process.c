#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main() {
  DIR *dir = NULL;
  struct dirent *ptr = NULL;
  FILE *fp = NULL;
  char filepath[256];
  char filetext[128];
  dir = opendir("/proc");
  if (NULL != dir) {
    while ((ptr = readdir(dir)) != NULL) {
  	  if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0)) {
  			continue;
  		}
  		if (ptr->d_type != DT_DIR) {
  		  continue;
  		}
  		sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
  		fp = fopen(filepath, "r");
  		if (NULL != fp) {
  		  fgets(filetext, sizeof(filetext), fp);
  		  printf("Process Name: '%s' Process Id: '%d'\n", filetext, atoi(ptr->d_name));
  			fclose(fp);
  		}
  	}
  }
  closedir(dir);
  return 0;
}