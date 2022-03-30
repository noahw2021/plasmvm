//
//  cpuf.h
//  plasmvm
//
//  Created by Noah Wooten on 2/1/22.
//

#ifndef cpuf_h
#define cpuf_h
#include "../../ctx.h"

typedef struct _cpufctx {
	u32 TimerMs;
	u32 LocalOffset;
	byte Interrupt;
	union {
		u32 Flags;
		struct {
			byte Active : 1;
			byte Skip : 1;
			byte Wait : 1;
			byte Repeat : 1;
			byte Interrupt : 1;
			byte TimerAvailable : 1;
			byte PowerAvailable : 1;
			byte HasPowerInterrupt : 1;
			byte PowerActive : 1;
			byte PowerShuttingDown : 1;
			byte Restarting : 1;
			byte Sleeping : 1;
			byte Asleep : 1;
		};
	}Flags;
	struct {
		byte Interrupt;
		u32 Ms;
		byte Mode;
	}Waiting;
	byte PowerInterrupt;
	byte PowerState;
	u64 PowerBackupTimer;
	u32 PowerTimerTargetTicks;
}cpufctx_t;
extern cpufctx_t* cpuf;

void cpuf_init(void);
void cpuf_shutdown(void);
byte cpuf_query(byte Device);
void cpuf_send(byte Device, int Count, u64 Data);
u64 cpuf_get(byte Device, int Count);
void cpuf_genset(byte Device);
void cpuf_genclr(byte Device);

void cpuf_timer_set(void);
void cpuf_timer_clear(void);
void cpuf_timer_wait(u32 ms);
void cpuf_timer_setint(byte Vector, u32 ms);
void cpuf_timer_clrint(byte Vector);

void cpuf_power_set(void);
void cpuf_power_clear(void);
void cpuf_power_shutdown(void);
void cpuf_power_sleep(void);
void cpuf_power_restart(void);
void cpuf_power_handle(byte Interrupt);
void cpuf_power_unhandle(void);
void cpuf_power_wakeup(void);

#define CPUFENUM_TIMER 0x01
#define CPUFENUM_POWER 0x02

#define CPUFTMR_CMD_SET      0x01  // SEND Command (No Data Recievable)
#define CPUFTMR_CMD_CLEAR    0x02  // SEND Command (No Data Recievable)
#define CPUFTMR_CMD_SETMS    0x03  // SEND Command (No Data Recievable)
#define CPUFTMR_CMD_SETINT   0x04  // SEND Command (No Data Recievable)
#define CPUFTMR_CMD_SETMODE  0x05  // SEND Command (No Data Recievable)
#define CPUFTMR_CMD_CLRMODE  0x06  // SEND Command (No Data Recievable)
#define CPUFTMR_CMD_GO       0x07  // SEND Command (No Data Recievable)

#define CPUFPWR_CMD_SET      0x01 // SEND Command (No Data Recievable)
#define CPUFPWR_CMD_CLR		 0x02 // SEND Command (No Data Recievable)
#define CPUFPWR_CMD_SHUTDOWN 0x03 // SEND Command (No Data Recievable)
#define CPUFPWR_CMD_SLEEP    0x04 // SEND Command (No Data Recievable)
#define CPUFPWR_CMD_RESTART  0x05 // SEND Command (No Data Recievable)
#define CPUFPWR_CMD_HANDLE   0x06 // SEND Command (No Data Recievable)
#define CPUFPWR_CMD_UNHANDLE 0x07 // SEND Command (No Data Recievable)

#define CPUFPWR_DATA_SHUTTINGDOWN500000TICKS  0x1000000000000100
#define CPUFPWR_DATA_SHUTTINGDOWN5000TICKS    0x1000000000000200
#define CPUFPWR_DATA_RESTART				  0x2000000000000100
#define CPUFPWR_DATA_SLEEP                    0x3000000000000000
#define CPUFPWR_DATA_WAKEUP                   0x3100000000000000

#endif /* cpuf.h */