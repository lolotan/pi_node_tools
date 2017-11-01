typedef struct __attribute__((packed))
{
  char nodeAddr[5]; // Node address
  char gwAddr[5];   // Gateway address
} addr_t;

typedef struct __attribute__((packed))
{
  char sensorID[2];  // Sensor ID, in ASCII from 00 to 99
  char hwVersion[2]; // Hardware version, in ASCII from 00 to 99
  char swVersion[2]; // Software version, in ASCII from 00 to 99
} header_t;

typedef struct __attribute__((packed))
{
  header_t  header;       // Frame header
  char      rfChannel;    // RF CHANNEL, in binary
  char      rfPower;      // PA, in binary
  addr_t    addresses;    // Node and gateway addresses, in ASCII  
} configFrame_t;

typedef struct __attribute__((packed))
{
  header_t  header;       // Frame header
  char      batteryLvl;   // Battery level, in binary
  char      xferStats;    // Transfer statistics
  short     sensVal[2];   // Sensor raw values
} sensorFrame_t;
