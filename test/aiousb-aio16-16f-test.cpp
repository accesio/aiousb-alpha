#include "aiousb.h"
#include "AiousbSamples.inc"

int main (int argc, char **argv)
{
  int Status;
  AIOUSB::aiousb_device_handle Device;

  AIOUSB::AiousbInit();

  Status = SampleGetDeviceHandle(argc, argv, &Device);

  if (Status)
  {
    std::cout << "Unable to open device" << std::endl;
    exit(-1);
  }

  AIOUSB::ADC_SetCal(Device, ":AUTO:");
}