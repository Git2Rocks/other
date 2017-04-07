## -*- Makefile -*-
##
## �û���ems
## ʱ�䣺2010-4-22 16:16:03
## �� Sun Studio ������ Makefile��
##
## ���ļ����Զ����ɵġ�
##


#### ����������Ŀ�깲��ı������͹��߶��� #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC


# ����Ŀ��Ŀ¼��
TARGETDIR_dl476_client_recv.dxe=.


all: $(TARGETDIR_dl476_client_recv.dxe)/dl476_client_recv.dxe

## Ŀ�꣺dl476_client_recv.dxe
OBJS_dl476_client_recv.dxe =  \
	$(TARGETDIR_dl476_client_recv.dxe)/dl476_app_fun.o \
	$(TARGETDIR_dl476_client_recv.dxe)/dl476_client_recv.o \
	$(TARGETDIR_dl476_client_recv.dxe)/dl476_fun.o
SYSLIBS_dl476_client_recv.dxe = -lm -lsocket -lnsl -lthread 
USERLIBS_dl476_client_recv.dxe = ../../../dps/v4.0a/lib/ipclib.lib ../../../lan/v4.0a/lib/lan.lib ../../../dps/v4.0a/lib/dpslib.lib ../../../dms/v4.0a/lib/dblib.lib $(SYSLIBS_dl476_client_recv.dxe) 
DEPLIBS_dl476_client_recv.dxe =      
LDLIBS_dl476_client_recv.dxe = $(USERLIBS_dl476_client_recv.dxe)


# ���ӻ�鵵
$(TARGETDIR_dl476_client_recv.dxe)/dl476_client_recv.dxe: $(TARGETDIR_dl476_client_recv.dxe) $(OBJS_dl476_client_recv.dxe) $(DEPLIBS_dl476_client_recv.dxe)
	$(LINK.c) $(CFLAGS_dl476_client_recv.dxe) $(CPPFLAGS_dl476_client_recv.dxe) -o $@ $(OBJS_dl476_client_recv.dxe) $(LDLIBS_dl476_client_recv.dxe)


# ��Դ�ļ�����Ϊ .o �ļ�
$(TARGETDIR_dl476_client_recv.dxe)/dl476_app_fun.o: $(TARGETDIR_dl476_client_recv.dxe) dl476_app_fun.c
	$(COMPILE.c) $(CFLAGS_dl476_client_recv.dxe) $(CPPFLAGS_dl476_client_recv.dxe) -o $@ dl476_app_fun.c

$(TARGETDIR_dl476_client_recv.dxe)/dl476_client_recv.o: $(TARGETDIR_dl476_client_recv.dxe) dl476_client_recv.c
	$(COMPILE.c) $(CFLAGS_dl476_client_recv.dxe) $(CPPFLAGS_dl476_client_recv.dxe) -o $@ dl476_client_recv.c

$(TARGETDIR_dl476_client_recv.dxe)/dl476_fun.o: $(TARGETDIR_dl476_client_recv.dxe) dl476_fun.c
	$(COMPILE.c) $(CFLAGS_dl476_client_recv.dxe) $(CPPFLAGS_dl476_client_recv.dxe) -o $@ dl476_fun.c



#### ����Ŀ�꽫��ɾ���������ɵ��ļ� ####
clean:
	rm -f \
		$(TARGETDIR_dl476_client_recv.dxe)/dl476_client_recv.dxe \
		$(TARGETDIR_dl476_client_recv.dxe)/dl476_app_fun.o \
		$(TARGETDIR_dl476_client_recv.dxe)/dl476_client_recv.o \
		$(TARGETDIR_dl476_client_recv.dxe)/dl476_fun.o
# ����������ϵ���
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-sparc-Solaris

