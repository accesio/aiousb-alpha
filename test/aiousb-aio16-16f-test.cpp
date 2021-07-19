#include "aiousb.h"
#include "AiousbSamples.inc"

#include <array>

#define START_CHANNEL 0
#define END_CHANNEL 15

AIOUSB::aiousb_device_handle Device;
double Readings[16];

void GetAndPrintScan()
{
  int status;
  std::array<double, END_CHANNEL - START_CHANNEL + 1> Voltages;
  status = AIOUSB::ADC_SetScanLimits(Device, START_CHANNEL, END_CHANNEL);

  status = AIOUSB::ADC_SetOversample(Device, 5);

  status = AIOUSB::ADC_GetScanV(Device, Voltages.data());

  for (int i = 0 ; i <= END_CHANNEL - START_CHANNEL ; i++)
  {
    printf("%d: %f\n", i, Voltages[i]);
  }

}

int main (int argc, char **argv)
{
  int Status;

  AIOUSB::AiousbInit();

  Status = SampleGetDeviceHandle(argc, argv, &Device);

  if (Status)
  {
    std::cout << "Unable to open device" << std::endl;
    exit(-1);
  }
  AIOUSB::ADC_SetCal(Device, ":NONE:");

  GetAndPrintScan();

    AIOUSB::ADC_SetCal(Device, ":NORM:");

  GetAndPrintScan();

  AIOUSB::ADC_SetCalAndSave(Device, ":AUTO:", "outtest.bin");
  GetAndPrintScan();
}
