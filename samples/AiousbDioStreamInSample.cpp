#include <iostream>
#include <array>
#include <signal.h>

#include "aiousb.h"

#include "AiousbSamples.inc"


#define STREAM_RATE 1E3

aiousb_device_handle Device;

void signal_handler (int sig)
{
  std::cout<<"Enter signal handler" << std::endl << std::flush;

  aiousb_abort_pipe(Device);
}

int main (int argc, char **argv)
{
  int Status;


  std::cout << "ACCES AIOUSB-Linux DIO Stream sample" << std::endl;

  aiousb_init();

  //Try to get a device handle.
  Status = SampleGetDeviceHandle(argc, argv, &Device);

  if ( 0 != Status )
  {
    std::cout << "Unable to get device handle" << std::endl;
    SampleUsage(argc, argv);
    exit (-1);
  }

  uint32_t nameSize = 255;
  char name[nameSize];

  aiousb_query_device_info(Device, nullptr, &nameSize, name, nullptr, nullptr);

  std::cout << name << " detected." << std::endl;

  // std::cout << "Opening a stream for output" << std::endl;
  // Status = aiousb_dio_stream_open(Device, false);

  double WriteFrequency = STREAM_RATE;
  double ReadFrequency = STREAM_RATE;

  std::cout << "Setting streaming rate to " << STREAM_RATE << "hz" << std::endl;
  aiousb_dio_stream_set_clocks(Device, &ReadFrequency, &WriteFrequency);
  std::cout << "Actual read rate " << ReadFrequency << "hz" << std::endl;
  std::cout << "Actual write rate " << WriteFrequency << "hz" << std::endl;

  signal(SIGINT, signal_handler);  std::array<uint16_t, 1024 * 10> DioData;
  DioData.fill(0x55aa);
  uint32_t Transferred = 0;

  // std::cout << "Streaming " << DioData.size() << " points" << std::endl;
  // aiousb_dio_stream_frame(Device, DioData.size(), DioData.data(), &Transferred);
  // std::cout << "Transferred " << Transferred << " bytes" << std::endl;

  // std::cout <<"Closing stream" << std::endl;
  // aiousb_dio_stream_close(Device);

  std::cout << "Opening a stream for input" << std::endl;
  aiousb_dio_stream_open(Device, true);

  std::cout << "Streaming " << DioData.size() << "points" << std::endl;
  aiousb_dio_stream_frame(Device, DioData.size(), DioData.data(), &Transferred);
  std::cout << "Transferred " << Transferred << " bytes" << std::endl;

  std::cout << "Closing stream" << std::endl;
  aiousb_dio_stream_close(Device);


  return 0;
}