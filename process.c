#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>

int main() {
	int id, fd;
	DIR *dir;
	char data[128] = {0};
	struct dirent* entry;
	
	if ((dir = opendir("/proc")) == NULL) {
		printf("Failed to open proc\n");
		exit(EXIT_FAILURE);
	}
	
	while ((entry = readdir(dir)) != NULL) {
		sscanf(entry->d_name, "%d", &id);
		if (id != 0) {
			snprintf(data, 127, "/proc/%d/cmdline", id);
			if ((fd = open(data, O_RDONLY)) != -1) {
				read(fd, data, 127);
				printf("[%d] %s\n", id, data);
				close(fd);
            }
		}
	}
	
	closedir(dir);
	exit(EXIT_SUCCESS);
}
