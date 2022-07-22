#include "mbed.h"
#include "USBSerial.h"
#include "helloWorldConfig.h"

#define UART_EVENT      (1UL << 25)

USBSerial serial(false);
EventFlags mainEvent("mainEvent");

void SerialReceiveISR()
{
    mainEvent.set(UART_EVENT);
}

void onSerialReceived()
{
  char serialRxBuf[1];

  while(serial.readable()){
    serial.read(serialRxBuf, 1);
    printf("%c", serialRxBuf[0]);
  }
  //The "\n" will trigger the actual output
  printf("@(%p)\n", ThisThread::get_id());
}

int main()
{
  uint32_t flags_read = 0;

  printf("\nMbed OS version - %d.%d.%d\n\nHello World! (V%d.%d)\n",
	 MBED_MAJOR_VERSION,
	 MBED_MINOR_VERSION,
	 MBED_PATCH_VERSION,
	 HELLOWORLD_VERSION_MAJOR,
	 HELLOWORLD_VERSION_MINOR);

  printf("Starting in context %p\n", ThisThread::get_id());
  serial.connect();
  serial.attach(SerialReceiveISR);

  while(true){
    flags_read = mainEvent.wait_any(UART_EVENT);
    printf("(%p) Got: 0x%08lx\n", ThisThread::get_id(), flags_read);
    if(flags_read & UART_EVENT)
      onSerialReceived();
  }

  //Thread worker_thread;
  //
  //worker_thread.start(mbed::callback(onSerialReceived));
  //
  //// Wait for the thread to terminate
  //worker_thread.join();
}
