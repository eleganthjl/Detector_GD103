

#ifndef _FLASH_H
#define _FLASH_H

#define SECTOR_SIZE ((uint32_t)0x00000400)//块大小1K

#define FLASH_SIZE 	0x10000                            //FLASH大小
#define PARA_SIZE   1           //参数大小1个块
#define PARA_ADDR_START   (0x08000000+FLASH_SIZE-PARA_SIZE*SECTOR_SIZE)    //参数存储地址
#define PARA_ADDR_END   (0x08000000+FLASH_SIZE-2)    //参数存储地址

extern char WriteParaToFlash(u32 addr, u16 *data , u16 N);
extern char ReadParaFromFlash(u32 addr, u16 *data, u16 N);
/*
32F103C8
flash 64K   0x10000  0x8000000-0x800ffff
ram   20K   0x500    0x2000000-0x2004fff

md块大小为1K

最后1k空间用来存储参数  0x800FC00-0x800ffff

*/


#endif



