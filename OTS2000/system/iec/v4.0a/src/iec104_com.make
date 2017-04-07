## -*- Makefile -*-
##
## �û��� ems
## ʱ�䣺 2009-12-24 17:24:02
## �� Sun Studio ������ Makefile��
##
## ���ļ����Զ����ɵġ�
##


#### ����������Ŀ�깲��ı������͹��߶��� #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC


# ����Ŀ��Ŀ¼��
TARGETDIR_iec104_com.dxe=.


all: $(TARGETDIR_iec104_com.dxe)/iec104_com.dxe

## Ŀ�꣺ iec104_com.dxe
OBJS_iec104_com.dxe =  \
	$(TARGETDIR_iec104_com.dxe)/iec104_app_fun.o \
	$(TARGETDIR_iec104_com.dxe)/iec104_com.o \
	$(TARGETDIR_iec104_com.dxe)/iec104_fun.o
SYSLIBS_iec104_com.dxe = -lm -lsocket -lnsl -lthread 
USERLIBS_iec104_com.dxe =../../../../dps/v4.0a/lib/dpslib.lib  ../../../../lan/v4.0a/lib/lan.lib ../../../../dms/v4.0a/lib/dblib.lib ../../../../dps/v4.0a/lib/ipclib.lib $(SYSLIBS_iec104_com.dxe) 
DEPLIBS_iec104_com.dxe =      
LDLIBS_iec104_com.dxe = $(USERLIBS_iec104_com.dxe)


# ���ӻ�鵵
$(TARGETDIR_iec104_com.dxe)/iec104_com.dxe: $(TARGETDIR_iec104_com.dxe) $(OBJS_iec104_com.dxe) $(DEPLIBS_iec104_com.dxe)
	$(LINK.c) $(CFLAGS_iec104_com.dxe) $(CPPFLAGS_iec104_com.dxe) -o $@ $(OBJS_iec104_com.dxe) $(LDLIBS_iec104_com.dxe)


# ��Դ�ļ�����Ϊ .o �ļ�
$(TARGETDIR_iec104_com.dxe)/iec104_app_fun.o: $(TARGETDIR_iec104_com.dxe) iec104_app_fun.c
	$(COMPILE.c) $(CFLAGS_iec104_com.dxe) $(CPPFLAGS_iec104_com.dxe) -o $@ iec104_app_fun.c

$(TARGETDIR_iec104_com.dxe)/iec104_com.o: $(TARGETDIR_iec104_com.dxe) iec104_com.c
	$(COMPILE.c) $(CFLAGS_iec104_com.dxe) $(CPPFLAGS_iec104_com.dxe) -o $@ iec104_com.c

$(TARGETDIR_iec104_com.dxe)/iec104_fun.o: $(TARGETDIR_iec104_com.dxe) iec104_fun.c
	$(COMPILE.c) $(CFLAGS_iec104_com.dxe) $(CPPFLAGS_iec104_com.dxe) -o $@ iec104_fun.c



#### ����Ŀ�꽫��ɾ���������ɵ��ļ� ####
clean:
	rm -f \
		$(TARGETDIR_iec104_com.dxe)/iec104_com.dxe \
		$(TARGETDIR_iec104_com.dxe)/iec104_app_fun.o \
		$(TARGETDIR_iec104_com.dxe)/iec104_com.o \
		$(TARGETDIR_iec104_com.dxe)/iec104_fun.o
# ����������ϵ���
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

