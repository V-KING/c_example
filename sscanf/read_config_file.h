
/* read_config_file.h */

#ifndef __INICFG_H__
#define __INICFG_H__

#define  MEMBER_OFFSET(type, member)     (((unsigned long)(&((type*)0)->member)))

typedef unsigned char   tU08;   /*unsigned 8 bit definition */
typedef unsigned short    tU16;   /*unsigned 16 bit definition*/
typedef unsigned long   tU32;   /*unsigned 32 bit definition*/
typedef signed char     tS08;   /*signed 8 bit definition */
typedef signed short	    tS16;   /*signed 16 bit definition*/
typedef long int    	  tS32;   /*signed 32 bit definition*/
typedef long long llong;


#define	UINT8	tU08			/* unsigned 8-bit */	
#define	UINT16	tU16			/* unsigned 16-bit */
#define	UINT32	tU32			/* unsigned 32-bit */
#define	INT8	tS08			/* signed 8-bit */
#define	INT16	tS16			/* signed 16-bit */
#define	INT32	tS32			/* signed 32-bit */


typedef enum tagDataTypeEn
{
	EN_TYPE_STR=1,
	EN_TYPE_UCHAR,
	EN_TYPE_USHORT,
	EN_TYPE_IP,
	EN_TYPE_BLANK
} DataTypeEnDef;


typedef struct tagINIFileFmt
{
	char	*pszFmt;           		// 格式字符串
	DataTypeEnDef	enDataType;     // 所获取的字段数据类型
	unsigned int	lOffSet;        // 偏移量
} INIFileFmtDef;


/* 网络参数结构体定义 */
struct net_parameter
{
	UINT8	DHCP_switch;			// 自动IP开关
	UINT32	ip_addr;   				// 读写器IP地址
	UINT32	netmask;   				// 读写器子网掩码
	UINT32	gateway;       			// 读写器网关
};



#endif

