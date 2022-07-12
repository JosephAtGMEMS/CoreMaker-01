#include "mbed.h"
#include "helloWorldConfig.h"

int main()
{
  printf("\nMbed OS version - %d.%d.%d\n\nHello World! (V%d.%d)\n",
	 MBED_MAJOR_VERSION,
	 MBED_MINOR_VERSION,
	 MBED_PATCH_VERSION,
	 HELLOWORLD_VERSION_MAJOR,
	 HELLOWORLD_VERSION_MINOR);    
}
