#ifndef __WT16C_H__
#define __WT16C_H__

#include "struct_typedef.h"

#define WT61C_DATA_READY 0
#define WT61C_FINED_SOF 1


#define WT61C_DATA_SOF 0x55 
#define WT61C_ACCEL_ID 0x51
#define WT61C_GYRO_ID 0x52
#define WT61C_ANGLE_ID 0x53


typedef struct
{
    fp32 gyro[3];
    fp32 accel[3];
    fp32 angle[3];

}wt61c_data_t;

extern void wt16c_data_process(uint8_t rx_buff);

#endif
