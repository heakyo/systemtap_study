/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/07/2016 08:08:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define BUF_SIZE (512 * 1024 * 1024)

int g_test = 9;

void display()
{
	int test1 = 6;
	test1 = 8;
	sleep(2);
	printf("display: %d\n", g_test);
}

int main(int argc, char *argv[])
{
	int fd = 0;
	void *buf_w;
	void *buf_r;
	int size = 0;
	int ret = 0;

	display();

	ret = posix_memalign(&buf_w, 512, BUF_SIZE);
	if (ret) {
		printf("alloc write buf memory error\n");
		return -1;
	}
	ret = posix_memalign(&buf_r, 512, BUF_SIZE);
	if (ret) {
		printf("alloc read buf memory error\n");
		return -1;
	}
	memset(buf_w, 0xA5, BUF_SIZE);

	//fd = open("/dev/sdb", O_RDWR | O_DIRECT);
	fd = open("/dev/sdb", O_RDWR);
	//fd = open("test", O_RDWR);
	if (fd == -1) {
		perror("open file error.");
		return -1;
	}

#if 1
	size = write(fd, buf_w, BUF_SIZE);
	if (size < 0) {
		perror("write file error.");
		return -1;
	}
	//printf("write content: %s, write size: %d\n", buf_w, size);
#endif

#if 0
	lseek(fd, 0, SEEK_SET);
	size = read(fd, buf_r, BUF_SIZE);
	if (size < 0) {
		perror("read file error.");
		return -1;
	}
	//printf("read content: %s, read size: %d\n", buf_r, size);
#endif
	close(fd);
	return 0;
}
