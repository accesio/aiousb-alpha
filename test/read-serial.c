#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "accesio_usb_ioctl.h"


int generic_vendor_read(int fd, unsigned char request, unsigned short value,
                        unsigned short index, unsigned long size, void *data)
{
        struct  accesio_usb_control_transfer context = {0};
        int status;

        context.request = request;
        context.value = value;
        context.index = index;
        context.size = size;
        context.data = data;
        context.read = 1;

        status = ioctl (fd, ACCESIO_USB_CONTROL_XFER, &context);

        if (status)
        {
                printf("%s: ioctl returned %d\n", __FUNCTION__, status);
        }
        return status;
}

int generic_vendor_write(int fd, unsigned char request, unsigned short value,
                        unsigned short index, unsigned long size, void *data)
{
        struct accesio_usb_control_transfer context = {0};
        int status;

        context.request = request;
        context.value = value;
        context.index = index;
        context.size = size;
        context.data = data;
        context.read = 0;

        status = ioctl (fd, ACCESIO_USB_CONTROL_XFER, &context);

        if (status)
        {
                printf("%s: ioctl returned %d\n", __FUNCTION__, status);
        }

        return status;
}


int main (int argc, char **argv)
{
        int fd = open (argv[1], O_RDWR);
        long long serial_num = 0;
        unsigned long size = sizeof(serial_num);
        int status;

        if (fd < 0)
        {
                printf("fd = %d\n", fd);
                exit(1);
        }

        {
        status = generic_vendor_read(fd, 0xa2, 0x1df8, 0, size, &serial_num);

        printf("status = %d, serial_num = %llx\n", status, serial_num);
        }

        {
        unsigned char data[6] = {0};
        data[0] = 0xff;
        data[4] = 0xff;
        status = generic_vendor_write (fd, 0x12, 0, 0, sizeof(data), data);
        printf("status after write = %d\n", status);
        }

        close(fd);
        return 0;
}