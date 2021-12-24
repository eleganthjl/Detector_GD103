
/*
32F103C8
flash 64K   0x10000  0x8000000-0x800ffff
ram   20K   0x500    0x2000000-0x2004fff

md���СΪ1K

���1k�ռ������洢����  0x800FC00-0x800ffff

*/

#include "main.h"

/***************************************************************************************
**Function : ����д�뺯��
**Parameter: addr�������ĵ�ַ������Ϊż��ַ  data��2�ֽ� N����������
**Return   : 0 �ɹ�; 1 ʧ��
**Author   : 
**Time     : 
**--------------------------------------------------------------------------------------
**Modifier : 
**Time     : 
***************************************************************************************/

char WriteParaToFlash(u32 addr, u16 data[] , u16 N)//1k�ռ� 0x800FC00-0x800ffff 512������
{
	if(addr%2!=0)return 1;
	if(addr<PARA_ADDR_START)return 1;
	if((addr+2*(N-1))>PARA_ADDR_END)return 1;
	
	u16 flash_wdata[PARA_SIZE*SECTOR_SIZE/2];
  u16 flash_rdata[PARA_SIZE*SECTOR_SIZE/2];

	
	u16 i;
	u16 j;
	
	//������
	j=PARA_SIZE*SECTOR_SIZE/2;
	for(i=0;i<j;i++)
	{
		flash_wdata[i] = *(vu16*)(PARA_ADDR_START + i*2); 
	}
	
	//����Ҫд�Ĳ���
	j=(addr-PARA_ADDR_START)/2;
	for(i=0;i<N;i++)
	{
	  flash_wdata[j+i]=data[i];
	}
	
	//��һ��д��
	  FLASH_Unlock();                                          //����FLASH
		FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		while(FLASH_ErasePage(PARA_ADDR_START)!= FLASH_COMPLETE){};//����FLASH�����ռ�
	  j=PARA_SIZE*SECTOR_SIZE/2;
	  for(i=0;i<j;i++)              
		{
			while(FLASH_ProgramHalfWord(PARA_ADDR_START+2*i,flash_wdata[i])!=FLASH_COMPLETE);
		}
		FLASH_Lock();
	
	//check 
	j=PARA_SIZE*SECTOR_SIZE/2;	
  for(i=0;i<j;i++)
	{
		flash_rdata[i] = *(vu16*)(PARA_ADDR_START + i*2); 
	}
		
	for(i=0;i<j;i++)
	{
		if(flash_rdata[i] != flash_wdata[i])break ;
	}
		
	if(i==j)return 0;
	else return 1;
}


/***************************************************************************************
**Function : ����д�뺯��
**Parameter: addr�������ĵ�ַ  data��2�ֽڣ��ߵ�ַΪ��λ N����������
**Return   : **Return   : 0 �ɹ�; 1 ʧ��
**Author   : 
**Time     : 
**--------------------------------------------------------------------------------------
**Modifier : 
**Time     : 
***************************************************************************************/
char ReadParaFromFlash(u32 addr, u16 data[] , u16 N)
{
	if(addr%2!=0)return 1;
	if(addr<PARA_ADDR_START)return 1;
	if((addr+2*(N-1))>PARA_ADDR_END)return 1;
		
	u16 i;
	for(i=0;i<N;i++)
	{
		data[i] = *(vu16*)(addr + i*2); 
	}
	
	return 0;
	
}






