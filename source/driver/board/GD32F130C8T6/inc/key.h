#ifndef __KEY_H
#define __KEY_H
#include "gd32f1x0.h"

enum KEY_PRESS
{
    KEY1_S =0x01,       //短按
    KEY2_S,
    KEY3_S,
    KEY4_S,
    KEY1_L = 0x10,      //长按
    KEY2_L,
    KEY3_L,
    KEY4_L,
    KEY_IDLE=0xFF
};

enum MENU_STATE
{
    DESK =1,    //主界面
    MENU,      //菜单界面 
    INFO,       //设备信息界面（授权类信息）
    INFO2,     //设备底层信息界面（其余底层信息）
	  WARNING,   //设备警告代码清单列表
    UNCONNECTER,      //无设备连接
    SETUP,
	  WIFI_INFORMATION,//无线信息界面
	  WIFI_INFORMATION_NAME,//无线名称显示界面
	  WIFI_INFORMATION_Password,//无线密码显示界面
	  WIFI_INFORMATION_IP,//无线IP显示界面
	  AskDesk,//用户询问界面
	  CREAD_WIFI,//创建无线界面
	  CREAD_WIFI_NAME,//创建无线名称界面
	  CREAD_WIFI_PASSWORD,//创建无线密码界面
	  SEND_WIFI_DATA,//确认发送无线数据
	  SEND_DATA,//发送数据加载界面
	  TIME_SET,//时间设置界面
	  TIME_SET_CHECK,//时间设置确认界面
};





void bsp_key_init(void);

#endif /*end of key.h*/
