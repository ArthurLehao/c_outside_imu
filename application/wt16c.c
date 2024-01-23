#include "wt16c.h"

wt61c_data_t wt61c_data;    //wt61c数据
uint8_t wt61c_data_buff[11];
uint8_t wt61c_process_flag = WT61C_DATA_READY;

static int8_t wt61c_data_length = 0;
static int16_t wt61c_buff[3];
unsigned char crc_sum_check(const unsigned char *buf, int len);	//校验和

void wt16c_data_process(uint8_t rx_buff)    //wt61c数据处理与归档
{
    wt61c_data_buff[wt61c_data_length] = rx_buff;
		wt61c_data_length++;
	
    switch (wt61c_process_flag)
    {
        case WT61C_DATA_READY:
            if(rx_buff == WT61C_DATA_SOF)
            {
	            wt61c_process_flag = WT61C_FINED_SOF;
            }
            else
            {
                wt61c_data_length = 0;
            }
        break;

        case WT61C_FINED_SOF:
            if(wt61c_data_length >= 11)
            {
                if(crc_sum_check(wt61c_data_buff,10) == wt61c_data_buff[10]) //校验
                {
                    switch (wt61c_data_buff[1]) //根据帧头数据
                    {
                        case WT61C_ACCEL_ID:
													for(int8_t i = 0; i < 3; i++)
													{
															wt61c_buff[i] = (wt61c_data_buff[3+2*i] << 8 | wt61c_data_buff[2+2*i]);
															wt61c_data.accel[i] = (fp32)wt61c_buff[i] / 32768 * 156.8;
													}                
                           break;
                        case WT61C_GYRO_ID:
													for(int8_t i = 0; i < 3; i++)
													{
															wt61c_buff[i] = (wt61c_data_buff[3+2*i] << 8 | wt61c_data_buff[2+2*i]);
															wt61c_data.gyro[i] = (fp32)wt61c_buff[i] / 32768 * 2000.0;
													}     
                            break;
                        case WT61C_ANGLE_ID:
													for(int8_t i = 0; i < 3; i++)
													{
															wt61c_buff[i] = (wt61c_data_buff[3+2*i] << 8 | wt61c_data_buff[2+2*i]);
															wt61c_data.angle[i] = (fp32)wt61c_buff[i] / 32768 * 180.0;
													} 

                            break;
                        default:
                            break;
                    }
										
										wt61c_data_length = 0;
                    wt61c_process_flag = WT61C_DATA_READY;
									}
									else
									{
                    wt61c_data_length = 0;
                    wt61c_process_flag = WT61C_DATA_READY;
									}
            }
        break;

        default:
        break;
    }
}

unsigned char crc_sum_check(const unsigned char *buf, int len)  
{  
    int iSum = 0; 
    for (int i = 0;i < len;i++)  
    {  
        iSum += buf[i];  
    }  
    iSum %= 0x100;   //也可以&0xff
    return (unsigned char)iSum;  
} 

