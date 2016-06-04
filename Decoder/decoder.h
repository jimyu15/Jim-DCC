//#define DEBUG

#define LOCO



#define SHUTDOWN_TIMEOUT 500
#define MICROS_PER_COUNT (128*1000000/F_CPU)


#define NSLEEP BIT0
#define LED BIT3
#define IN1 BIT4
#define IN2 BIT5

#ifdef DEBUG
#define PH BIT7
#define EN BIT6

#else
#define PH BIT1
#define EN BIT2
#endif

//CV
#define PRI_ADDR 1
#define VSTART 2
#define ACC_RATE 3
#define DEC_RATE 4
#define VHIGH 5
#define VMID 6
#define VERSION 7
#define MANU_ID 8
#define FUNC1 13
#define FUNC2 14
#define LOCK1 15
#define LOCK2 16
#define EXT_ADDR1 17
#define EXT_ADDR2 18
#define CONST_ADDR 19
#define CONST_ADDR_FUNC1 20
#define CONST_ADDR_FUNC2 21
#define CONFIG 29

