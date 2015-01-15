// Primo - Cubetto Playset
//    Bare-bones code for the Cubetto Robot

// Responds to a sequence of movement commands sent by radio.

// This code includes a mechanism for Interface/Cubetto Robot to pair.
// When a Cubetto Robot is powered-on, it is unpaired and will accept input from
// any Interface.  When an Interface is powered on, it generates a 32-bit random
// number to use as its session Unique ID (UID).
// Every radio message that an Interface sends includes this UID.
// A Cubetto Robot, on receiving its first radio message, records this UID,
// and subsequently ignores messages from any other UID.
// A devices's UID is forgotten when it is powered off.

// Normal usage of Interface/Cubetto Robot:
// 1. Power-on Cubetto Robot.
// 2. Send a message from the Interface.
// 3. These devices are now paired.
// (4). Repeat 1 & 2 for any other Interfaces & Cubetto Robots.
// (5). Power-off a Cubetto Robot to un-pair (the Interface is unaware of
//      pairings, so no need to power-off).

////////////////////////////////////////////////////////////////////////////////

#include <AccelStepper.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#include "Primo.h"
#include "sound.h"


// Remove // comments from following line to enable debug tracing.
#define PRIMO_DEBUG_MODE 1

#ifdef PRIMO_DEBUG_MODE
#define debugPrintf printf
#else
#define debugPrintf(...) ((void) 0)
#endif


#define PRIMO_STEPPER_MAX_SPEED    1000   // Pulses per second.
#define PRIMO_STEPPER_ACCELERATION 500    // Pulses per second.

#define PRIMO_STEPPER_FORWARD_STEPS 2700   // Total pulses.
#define PRIMO_STEPPER_TURN_STEPS    1170   // Total pulses.


//
// Hardware configuration
//

#define PRIMO_LEFT_STEPPER_PIN_1 12
#define PRIMO_LEFT_STEPPER_PIN_2 10
#define PRIMO_LEFT_STEPPER_PIN_3 11
#define PRIMO_LEFT_STEPPER_PIN_4 9

#define PRIMO_RIGHT_STEPPER_PIN_1 6
#define PRIMO_RIGHT_STEPPER_PIN_2 4
#define PRIMO_RIGHT_STEPPER_PIN_3 5
#define PRIMO_RIGHT_STEPPER_PIN_4 3

//int on1Pin = 6;
//int on2Pin = 5;
//int on3Pin = 4;
//int on4Pin = 3;


// Define a stepper and the pins it will use
AccelStepper leftStepper(AccelStepper::HALF4WIRE, PRIMO_LEFT_STEPPER_PIN_1, PRIMO_LEFT_STEPPER_PIN_2, PRIMO_LEFT_STEPPER_PIN_3, PRIMO_LEFT_STEPPER_PIN_4);
AccelStepper rightStepper(AccelStepper::HALF4WIRE, PRIMO_RIGHT_STEPPER_PIN_1, PRIMO_RIGHT_STEPPER_PIN_2, PRIMO_RIGHT_STEPPER_PIN_3, PRIMO_RIGHT_STEPPER_PIN_4);

static bool leftStepperIsMoving = 0;
static bool rightStepperIsMoving = 0;


// Set up nRF24L01 radio on SPI bus plus pins 7 (CE) & 8 (CSN).
RF24 radio(7, 8);


//
// Topology
//

// Flag to signal between interrupt handler and main event loop.
volatile bool rx_event_handler_pending = 0;

// Interrupt handler, check the radio because we got an IRQ
void checkRadio(void);

// play a happy tune to indicate successful completion of a command sequence
void playHappyTune(void);

////////////////////////////////////////////////////////////////////////////////

void setup (void)
{
  pinMode(PRIMO_LEFT_STEPPER_PIN_1, OUTPUT);
  pinMode(PRIMO_LEFT_STEPPER_PIN_2, OUTPUT);
  pinMode(PRIMO_LEFT_STEPPER_PIN_3, OUTPUT);
  pinMode(PRIMO_LEFT_STEPPER_PIN_4, OUTPUT);

  pinMode(PRIMO_RIGHT_STEPPER_PIN_1, OUTPUT);
  pinMode(PRIMO_RIGHT_STEPPER_PIN_2, OUTPUT);
  pinMode(PRIMO_RIGHT_STEPPER_PIN_2, OUTPUT);
  pinMode(PRIMO_RIGHT_STEPPER_PIN_4, OUTPUT);

  leftStepper.setMaxSpeed(PRIMO_STEPPER_MAX_SPEED);
  rightStepper.setMaxSpeed(PRIMO_STEPPER_MAX_SPEED);
  leftStepper.setAcceleration(PRIMO_STEPPER_ACCELERATION);
  rightStepper.setAcceleration(PRIMO_STEPPER_ACCELERATION);

  // IMPORTANT stepper outputs are disabled here to minimise power usage whilst stationary,
  // as they are automatically enabled in the class constructor.
  leftStepper.disableOutputs();
  rightStepper.disableOutputs();


  //
  // Print preamble
  //

  Serial.begin(57600);
  printf_begin();

  //while (Serial.read()== -1)
  debugPrintf("Cubetto Playset - Cubetto Robot - Version %s\n\r", PRIMO_CUBETTO_PLAYSET_VERSION);


  //
  // Setup and configure rf radio
  //

  radio.begin();

  // We will be using the Ack Payload feature, so please enable it
  radio.enableAckPayload();

  // Open pipes to other nodes for communication
  radio.openReadingPipe(1, pipe);

  // Start listening
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();

  // Attach interrupt handler to interrupt #0 (using pin 2)
  // on BOTH the sender and receiver
  attachInterrupt(1, checkRadio, CHANGE);

  playHappyTune();
  playHappyTune();

  delay(100);
}

////////////////////////////////////////////////////////////////////////////////

void loop (void)
{
  // Check if there is an Rx event to handle.
  if (rx_event_handler_pending == 1)
  {
    int i;
    long packet_id = 0;
    long packet_random = 0;

    debugPrintf("Event Handler start\n\r");

    debugPrintf("packet");
    for (i = 0; i < 32; i++)
    {
      debugPrintf(" %x", packet[i]);
    }
    debugPrintf("\n\r");

    memcpy(&packet_id, (const long*) &packet[0], 4);
    memcpy(&packet_random, (const long*) &packet[4], 4);

    // Check the packet is valid.
    if (packet_id == PRIMO_ID)
    {
      debugPrintf("PRIMO_ID good\n\r");

      if (sessionId == 0)
      {
        // (The UID could be used to set the packet address in the radio, but this would
        // make it necessary to un-pair Primo/Cubetto at BOTH ends).
        sessionId = packet_random;
        debugPrintf("PRIMO_RANDOM set\n\r");
      }

      if (sessionId == packet_random)
      {
        debugPrintf("PRIMO_RANDOM good\n\r");

        // Carry out movement instructions here.
        // IMPORTANT stepper outputs are enabled/disabled to minimise power usage whilst stationary.
        leftStepper.enableOutputs();
        rightStepper.enableOutputs();
        move();
        leftStepper.disableOutputs();
        rightStepper.disableOutputs();
      }
    }

    debugPrintf("Event Handler end\n\r");

    // Finally clear the event flag, so that the next interrupt event can register.
    rx_event_handler_pending = 0;

    // FIXME Would it be better to disable the radiointerrupt in the interrupt handler,
    // and re-enable it here?
  }
}
