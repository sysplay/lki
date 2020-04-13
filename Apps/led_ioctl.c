#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include "led_ioctl.h"


int main(int argc, char *argv[])
{
	char *file_name;
	int choice;
	int fd = -1;
	unsigned int c;
	int cnt = 1;
	int i;
	int led_num;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <device file name>\n", argv[0]);
		return 1;
	}
	else
	{
		file_name = argv[1];
	}


	do
	{
		printf("1: Open\n");
		printf("2: Get LED Status\n");
		printf("3: Set LED Status\n");
		printf("4: Set LED Number\n");
		printf("5: Close\n");
		printf("0: Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
			case 0: 
				break;
			case 1:
				fd = open(file_name, O_RDWR);
				if (fd == -1)
				{
					perror("led_ops open");
				}
				break;
			case 2:
				if (fd == -1)
				{
					printf("File not open\n");
					break;
				}
				cnt = ioctl(fd, GPIO_GET_LED, (unsigned long)&c);
				if (cnt == -1)
				{
					perror("led_ops read");
				}
				else
				{
					printf("\nLED Value is %d", c);
				}
				printf("\n");
				break;
			case 3:
				if (fd == -1)
				{
					printf("File not open\n");
					break;
				}
				printf("Enter your choice [0 - Turn Off, 1- Turn On] :\n");
				scanf("%u", &c);

				cnt = ioctl(fd, GPIO_SET_LED, c);
				if (cnt == -1)
				{
					perror("led_ops write");
					break;
				}
				break;
			case 4:
				printf("Enter the LED Number (1 to 4): ");
				scanf("%d", &led_num);
				getchar();
				if (ioctl(fd, GPIO_SELECT_LED, led_num) == -1)
				{
					perror("led_ops ioctl");
					break;
				}
				break;
			case 5:
				if (fd == -1)
				{
					printf("File not open\n");
					break;
				}
				close(fd);
				fd = -1;
				break;
			default:
				printf("Invalid Choice\n");
				break;
		}
	} while (choice != 0);

	return 0;
}
