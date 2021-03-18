#include "RF24.h"
#include "mbed.h"

// Let these addresses be used for the pair
uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false; // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
uint32_t payload = 0;

static RF24 radio(PA_7, PA_6, PA_5, PB_0, PB_1);

void setup()
{

    // initialize the transceiver on the SPI bus
    if (!radio.begin()) {
        printf("radio begin fail\r\n");
        while (1) {
        } // hold in infinite loop
    }

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit a float
    radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

    // set the TX address of the RX node into the TX pipe
    radio.openWritingPipe(address[radioNumber]); // always uses pipe 0

    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

    // additional setup specific to the node's role
    if (role) {
        radio.stopListening(); // put radio in TX mode
    } else {
        radio.startListening(); // put radio in RX mode
    }

    // For debugging info
    // printf_begin();             // needed only once for printing details
    // radio.printDetails();       // (smaller) function that prints raw register values
    radio.printPrettyDetails(); // (larger) function that prints human readable data

} // setup

void loop()
{
    if (role) {
        // This device is a TX node
        bool report = radio.write(&payload, sizeof(float)); // transmit & save the report

        printf("Tx: %d\r\n", payload);
        if (report) {
            payload += 1; // increment float payload
        } else {
            printf("Transmission failed or timed out\r\n"); // payload was not delivered
        }
        ThisThread::sleep_for(1000);
    } else {
        uint8_t pipe;
        if (radio.available(&pipe)) { // is there a payload? get the pipe number that recieved it
            uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
            radio.read(&payload, bytes); // fetch payload from FIFO
            printf("Payload read: %u\r\n", payload);
        }
    }
}

int main()
{
    puts("=====\r\n");

    setup();
    DigitalOut led(PC_13);
    while (true) {
        led = !led;
        loop();
    }
}
