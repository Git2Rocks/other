## -*- Makefile -*-
##
## �û���ems
## ʱ�䣺2010-4-22 17:04:45
## �� Sun Studio ������ Makefile��
##
## ���ļ����Զ����ɵġ�
##


#### ����������Ŀ�깲��ı������͹��߶��� #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC


# ����Ŀ��Ŀ¼��
TARGETDIR_dl476_client_send.dxe=.


all: $(TARGETDIR_dl476_client_send.dxe)/dl476_client_send.dxe

## Ŀ�꣺dl476_client_send.dxe
OBJS_dl476_client_send.dxe =  \
	$(TARGETDIR_dl476_client_send.dxe)/dl476_app_fun.o \
	$(TARGETDIR_dl476_client_send.dxe)/dl476_client_send.o \
	$(TARGETDIR_dl476_client_send.dxe)/dl476_fun.o
SYSLIBS_dl476_client_send.dxe = -lm -lsocket -lnsl -lthread 
USERLIBS_dl476_client_send.dxe = ../../../dps/v4.0a/lib/ipclib.lib ../../../lan/v4.0a/lib/lan.lib ../../../dps/v4.0a/lib/dpslib.lib ../../../dms/v4.0a/lib/dblib.lib $(SYSLIBS_dl476_client_send.dxe) 
DEPLIBS_dl476_client_send.dxe =      
LDLIBS_dl476_client_send.dxe = $(USERLIBS_dl476_client_send.dxe)


# ���ӻ�鵵
$(TARGETDIR_dl476_client_send.dxe)/dl476_client_send.dxe: $(TARGETDIR_dl476_client_send.dxe) $(OBJS_dl476_client_send.dxe) $(DEPLIBS_dl476_client_send.dxe)
	$(LINK.c) $(CFLAGS_dl476_client_send.dxe) $(CPPFLAGS_dl476_client_send.dxe) -o $@ $(OBJS_dl476_client_send.dxe) $(LDLIBS_dl476_client_send.dxe)


# ��Դ�ļ�����Ϊ .o �ļ�
$(TARGETDIR_dl476_client_send.dxe)/dl476_app_fun.o: $(TARGETDIR_dl476_client_send.dxe) dl476_app_fun.c
	$(COMPILE.c) $(CFLAGS_dl476_client_send.dxe) $(CPPFLAGS_dl476_client_send.dxe) -o $@ dl476_app_fun.c

$(TARGETDIR_dl476_client_send.dxe)/dl476_client_send.o: $(TARGETDIR_dl476_client_send.dxe) dl476_client_send.c
	$(COMPILE.c) $(CFLAGS_dl476_client_send.dxe) $(CPPFLAGS_dl476_client_send.dxe) -o $@ dl476_client_send.c

$(TARGETDIR_dl476_client_send.dxe)/dl476_fun.o: $(TARGETDIR_dl476_client_send.dxe) dl476_fun.c
	$(COMPILE.c) $(CFLAGS_dl476_client_send.dxe) $(CPPFLAGS_dl476_client_send.dxe) -o $@ dl476_fun.c



#### ����Ŀ�꽫��ɾ���������ɵ��ļ� ####
clean:
	rm -f \
		$(TARGETDIR_dl476_client_send.dxe)/dl476_client_send.dxe \
		$(TARGETDIR_dl476_client_send.dxe)/dl476_app_fun.o \
		$(TARGETDIR_dl476_client_send.dxe)/dl476_client_send.o \
		$(TARGETDIR_dl476_client_send.dxe)/dl476_fun.o
	rm -f -r $(TARGETDIR_dl476_client_send.dxe)


# ����Ŀ��Ŀ¼�������Ҫ��
$(TARGETDIR_dl476_client_send.dxe):
	mkdir -p $(TARGETDIR_dl476_client_send.dxe)


# ����������ϵ���
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-sparc-Solaris

