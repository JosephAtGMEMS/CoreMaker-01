#include "mbed.h"
#include "USBSerial.h"
#include "helloWorldConfig.h"

#define EVENT_CMDPORT      (1UL << 25)

static USBSerial cmdPort(false);
static BufferedSerial debugPort(CONSOLE_TX, CONSOLE_RX);
EventFlags mainEvent("mainEvent");

void CmdPortReceiveISR()
{
    mainEvent.set(EVENT_CMDPORT);
}

// Task with blocking event waiting
void onCmdPortReceived()
{
  char serialRxBuf[1];

  while(true){
    uint32_t flags_read = mainEvent.wait_any(EVENT_CMDPORT);

    if(flags_read & EVENT_CMDPORT == 0) continue;
    
    while(cmdPort.readable()){
      cmdPort.read(serialRxBuf, 1);
      debugPort.write(serialRxBuf, 1);
    }
  }
}

// Task with blocking read
void onDebugPortReceived(){
  char buff[MBED_CONF_DRIVERS_UART_SERIAL_RXBUF_SIZE];
  while(true){
    int n = debugPort.read(&buff, MBED_CONF_DRIVERS_UART_SERIAL_RXBUF_SIZE);
    cmdPort.write(&buff, n);
  }
}

int main()
{
  uint32_t flags_read = 0;
  Thread cmdPortThread, debugPortThread;

  printf("\nMbed OS version - %d.%d.%d\n\nHello World! (V%d.%d)\n",
	 MBED_MAJOR_VERSION,
	 MBED_MINOR_VERSION,
	 MBED_PATCH_VERSION,
	 HELLOWORLD_VERSION_MAJOR,
	 HELLOWORLD_VERSION_MINOR);

  printf("(%p) main() starting\n", ThisThread::get_id());
  
  cmdPort.connect();
  cmdPort.attach(CmdPortReceiveISR);
  
  if(debugPort.is_blocking() == false){
    printf("Set debug port to blocking mode.\n");
    debugPort.set_blocking(true);
  }

  cmdPortThread.start(mbed::callback(onCmdPortReceived));
  debugPortThread.start(mbed::callback(onDebugPortReceived));

  // Wait for the thread to terminate
  cmdPortThread.join();
  debugPortThread.join();
}
