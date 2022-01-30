#ifndef __KEY_H
#define __KEY_H
#include "gd32f1x0.h"

enum KEY_PRESS
{
    KEY1_S =0x01,       //�̰�
    KEY2_S,
    KEY3_S,
    KEY4_S,
    KEY1_L = 0x10,      //����
    KEY2_L,
    KEY3_L,
    KEY4_L,
    KEY_IDLE=0xFF
};

enum MENU_STATE
{
    DESK =1,    //������
    MENU,      //�˵����� 
    INFO,       //�豸��Ϣ���棨��Ȩ����Ϣ��
    INFO2,     //�豸�ײ���Ϣ���棨����ײ���Ϣ��
	  WARNING,   //�豸��������嵥�б�
    UNCONNECTER,      //���豸����
    SETUP,
	  WIFI_INFORMATION,//������Ϣ����
	  WIFI_INFORMATION_NAME,//����������ʾ����
	  WIFI_INFORMATION_Password,//����������ʾ����
	  WIFI_INFORMATION_IP,//����IP��ʾ����
	  AskDesk,//�û�ѯ�ʽ���
	  CREAD_WIFI,//�������߽���
	  CREAD_WIFI_NAME,//�����������ƽ���
	  CREAD_WIFI_PASSWORD,//���������������
	  SEND_WIFI_DATA,//ȷ�Ϸ�����������
	  SEND_DATA,//�������ݼ��ؽ���
	  TIME_SET,//ʱ�����ý���
	  TIME_SET_CHECK,//ʱ������ȷ�Ͻ���
};





void bsp_key_init(void);

#endif /*end of key.h*/
