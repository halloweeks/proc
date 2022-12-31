#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char **argv) {
	int id, fd;
	DIR *dir;
	char data[128];
	struct dirent* entry;
	
	dir = opendir("/proc");
	
	if (dir == NULL) {
		printf("Failed to open proc\n");
		exit(1);
	}
	
	while ((entry = readdir(dir)) != NULL) {
		sscanf(entry->d_name,"%d",&id);
		if (id != 0) {
			sprintf(data, "/proc/%d/cmdline", id);
			if ((fd = open(data, O_RDONLY)) != -1) {
            	read(fd, data, 127);
                printf("[%d] %s\n", id, data);
                close(fd);
            }
		}
	}
	
	closedir(dir);
	exit(0);
}
