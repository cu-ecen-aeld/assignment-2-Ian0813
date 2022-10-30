/*
 * =====================================================================================
 *
 *       Filename:  writer.c
 *
 *    Description:  Write a string to a specific file and introduce the logger functionality.
 *        Version:  1.0
 *
 *         Author:  Ian Chen
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>

#define FUN_FAILURE (-1)

int file_create(const char *file_name) {

    int fd;
	mode_t mode = S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH;

    fd = open(file_name, O_CREAT | O_WRONLY, mode);
	if (fd == FUN_FAILURE) {
        printf("func %s fail, errno: %d\n", __func__, errno);
		printf("error: %s\n", strerror(errno));
        syslog(LOG_USER | LOG_ERR, "%s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return fd;
}

void file_write(int fd, const char *str) {

    int retval;

	retval = write(fd, (const void *) str, strlen(str));
    if (retval == FUN_FAILURE) {
        printf("func %s fail, errno: %d\n", __func__, errno);
        printf("error: %s\n", strerror(errno));
        syslog(LOG_USER | LOG_ERR, "%s", strerror(errno));
        exit(EXIT_FAILURE);
	}
    return;	
}

void file_close(int fd) {

	if (close(fd) == FUN_FAILURE) {
        printf("func %s fail, errno: %d\n", __func__, errno);
        printf("error: %s\n", strerror(errno));
        syslog(LOG_USER | LOG_ERR, "%s", strerror(errno));
        exit(EXIT_FAILURE);
	}
    
	return;
}

int main(int argc, char *argv[]) {

    const char *file_name = NULL, *str = NULL;
	/* fd: File descriptor number */
	int fd;

    /* The default argc value is 1, but we will pass in two arguments so the argc will equal 3. */	
    if (argc < 3) {
        printf("Please pass in the correct arguments.\n");
        syslog(LOG_USER | LOG_ERR, "Please pass in the correct arguments.");
        exit(EXIT_FAILURE);
    } else {
       file_name = argv[1];
	   str = argv[2];
	   openlog(NULL, LOG_PID, LOG_USER);
	}

    fd = file_create(file_name);
	file_write(fd, str);
	syslog(LOG_USER | LOG_DEBUG, "Writing %s to %s", str, file_name);

    file_close(fd);
	closelog();
	return 0;
}
