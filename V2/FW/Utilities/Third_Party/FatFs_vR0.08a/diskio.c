/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */

#define ATA		0
#define MMC		1
#define USB		2
#define BLOCK_SIZE                 65536 /* Block Size in Bytes */


extern uint8_t mem_is_on;


/*-----------------------------------------------------------------------*/
/* Inicializes a Drive                                                    */

DSTATUS disk_initialize (BYTE drv)    /* Physical drive nmuber (0..) */
{
  DSTATUS stat = STA_NOINIT;
  
  if(mem_is_on)
  {  
    stat &= ~STA_NOINIT;
  }
  
  return stat;
  
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
  uint8_t result;

  switch (drv) 
  {
    case MMC :
      if(!mem_is_on)
        return STA_NOINIT;
      if(!Memory_is_here())
        return STA_NODISK;
      result = Memory_read_status();
      if(result&0x1C)
        return STA_PROTECT;
    default:
        return STA_NOINIT;
  }
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{

	switch (drv) {
	case MMC :
                Memory_read_sector(buff,sector);
		return RES_OK;
        default:
                return RES_PARERR;
	}
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	switch (drv) {
	case MMC :
                Memory_write_sector((uint8_t*)buff,sector);
		return RES_OK;
        default:
          return RES_PARERR;
	}
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  DRESULT res;
  switch (ctrl) 
  {
    case CTRL_SYNC :		/* Make sure that no pending write process */
      res = RES_OK;
      break;

    case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
      *(DWORD*)buff = (DWORD) 16;     
      res = RES_OK;
      break;

    case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
      *(WORD*)buff = 0x10000;
      res = RES_OK;
      break;

    case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
      *(DWORD*)buff = 1;
      break;
    default:
      res = RES_PARERR;
  }
}

