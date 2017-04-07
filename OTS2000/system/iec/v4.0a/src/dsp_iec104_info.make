## -*- Makefile -*-
##
## �û��� ems
## ʱ�䣺 2009-12-25 15:53:01
## �� Sun Studio ������ Makefile��
##
## ���ļ����Զ����ɵġ�
##


#### ����������Ŀ�깲��ı������͹��߶��� #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC


# ����Ŀ��Ŀ¼��
TARGETDIR_iec104info.dxe=.


all: $(TARGETDIR_iec104info.dxe)/iec104info.dxe

## Ŀ�꣺ iec104info.dxe
OBJS_iec104info.dxe =  \
	$(TARGETDIR_iec104info.dxe)/dsp_iec104_info.o
SYSLIBS_iec104info.dxe = -lm -lsocket -lnsl 
USERLIBS_iec104info.dxe = ../../../../dps/v4.0a/lib/ipclib.lib ../../../../dps/v4.0a/lib/dpslib.lib ../../../../dms/v4.0a/lib/dblib.lib $(SYSLIBS_iec104info.dxe) 
DEPLIBS_iec104info.dxe =     
LDLIBS_iec104info.dxe = $(USERLIBS_iec104info.dxe)


# ���ӻ�鵵
$(TARGETDIR_iec104info.dxe)/iec104info.dxe: $(TARGETDIR_iec104info.dxe) $(OBJS_iec104info.dxe) $(DEPLIBS_iec104info.dxe)
	$(LINK.c) $(CFLAGS_iec104info.dxe) $(CPPFLAGS_iec104info.dxe) -o $@ $(OBJS_iec104info.dxe) $(LDLIBS_iec104info.dxe)


# ��Դ�ļ�����Ϊ .o �ļ�
$(TARGETDIR_iec104info.dxe)/dsp_iec104_info.o: $(TARGETDIR_iec104info.dxe) dsp_iec104_info.c
	$(COMPILE.c) $(CFLAGS_iec104info.dxe) $(CPPFLAGS_iec104info.dxe) -o $@ dsp_iec104_info.c



#### ����Ŀ�꽫��ɾ���������ɵ��ļ� ####
clean:
	rm -f \
		$(TARGETDIR_iec104info.dxe)/iec104info.dxe \
		$(TARGETDIR_iec104info.dxe)/dsp_iec104_info.o
# ����������ϵ���
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

