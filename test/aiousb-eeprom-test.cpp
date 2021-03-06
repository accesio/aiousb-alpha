#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "aiousb.h"

#define err_printf(fmt, ...) \
        do { printf ("%s:%d:%s(): \n" fmt, __FILE__, \
                                __LINE__, __func__, ##__VA_ARGS__); } while (0)


int main(int argc, char **argv)
{
	int status;

	status = AIOUSB::AiousbInit();

	if (status != 0)
	{
		printf("aiousb_init() failed: %d", status);
		return -1;
	}

	AIOUSB::aiousb_device_handle device;
	if (argc != 2)
	{
		printf("usage: aiousb-test <filename>\n");
		return -1;
	}

	status = AIOUSB::DeviceHandleByPath(argv[1], &device);

	if (status)
	{
		printf("Error opening device: %d\n", status);
		return -1;
	}

  {
    uint8_t data[40];
    memset(data, 0x40, sizeof(data));
    status = AIOUSB::CustomEEPROMWrite(device, 0, sizeof(data), data);
    printf("status after write = %d\n", status);
    memset(data, 0, sizeof(data));
    status = AIOUSB::CustomEEPROMRead(device, 0, sizeof(data), data);
    printf("status after read = %d\n", status);

    for (unsigned int count = 0; count < sizeof(data) ; count++)
    {
      printf("%x, ", data[count]);
      if (count && !(count % 8 )) printf("\n");
    }
    printf("\n");



  }
	return 0;
}