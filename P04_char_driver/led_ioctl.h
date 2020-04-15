#ifndef _LED_IOCTL_H

#define _LED_IOCTL_H

#include <linux/ioctl.h>

#define GPIO_SELECT_LED _IOW('l', 1, int)

//TODO 2: Define the IOCTLS
#define GPIO_SET_LED	1
#define GPIO_GET_LED	1

#endif /* _LED_IOCTL_H */
