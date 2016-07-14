//#define DEBUG

#define MOTOR
//#define HEADLIGHT

#define SHUTDOWN_TIMEOUT 500
#define MICROS_PER_COUNT (128*1000000/F_CPU)


#define LED BIT3
#define IN1 BIT4
#define IN2 BIT5

#ifdef MOTOR
#define NSLEEP BIT0
#define PH BIT1
#define EN BIT2
#endif

#ifdef HEADLIGHT
#define EN1 BIT1
#define EN2 BIT2
#endif

//#define F1
//#define F2

//CV
#define CV_PRI_ADDR 0
#define CV_VSTART 1
#define CV_ACC_RATE 2
#define CV_DEC_RATE 3
#define CV_VHIGH 4
#define CV_VMID 5
#define CV_VERSION 6
#define CV_MANU_ID 7
#define CV_FUNC1 12
#define CV_FUNC2 13
#define CV_LOCK1 14
#define CV_LOCK2 15
#define CV_EXT_ADDR1 16
#define CV_EXT_ADDR2 17
#define CV_CONST_ADDR 18
#define CV_CONST_ADDR_FUNC1 19
#define CV_CONST_ADDR_FUNC2 20
#define CV_CONFIG 28

