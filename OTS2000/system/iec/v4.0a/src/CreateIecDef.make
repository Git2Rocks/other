## -*- Makefile -*-
##
## �û��� ems
## ʱ�䣺 2010-2-2 15:47:06
## �� Sun Studio ������ Makefile��
##
## ���ļ����Զ����ɵġ�
##


#### ����������Ŀ�깲��ı������͹��߶��� #####
CC = cc
BASICOPTS = -g
CFLAGS = $(BASICOPTS) -xCC


# ����Ŀ��Ŀ¼��
TARGETDIR_CreateIecDef.dxe=.


all: $(TARGETDIR_CreateIecDef.dxe)/CreateIecDef.dxe

## Ŀ�꣺ CreateIecDef.dxe
OBJS_CreateIecDef.dxe =  \
	$(TARGETDIR_CreateIecDef.dxe)/IecDef.o
SYSLIBS_CreateIecDef.dxe = -lm -lsocket -lnsl -lthread -lpthread 
USERLIBS_CreateIecDef.dxe = ../../../../lan/v4.0a/lib/lan.lib ../../../../dps/v4.0a/lib/ipclib.lib ../../../../dps/v4.0a/lib/dpslib.lib ../../../../dms/v4.0a/lib/dblib.lib $(SYSLIBS_CreateIecDef.dxe) 
DEPLIBS_CreateIecDef.dxe =      
LDLIBS_CreateIecDef.dxe = $(USERLIBS_CreateIecDef.dxe)


# ���ӻ�鵵
$(TARGETDIR_CreateIecDef.dxe)/CreateIecDef.dxe: $(TARGETDIR_CreateIecDef.dxe) $(OBJS_CreateIecDef.dxe) $(DEPLIBS_CreateIecDef.dxe)
	$(LINK.c) $(CFLAGS_CreateIecDef.dxe) $(CPPFLAGS_CreateIecDef.dxe) -o $@ $(OBJS_CreateIecDef.dxe) $(LDLIBS_CreateIecDef.dxe)


# ��Դ�ļ�����Ϊ .o �ļ�
$(TARGETDIR_CreateIecDef.dxe)/IecDef.o: $(TARGETDIR_CreateIecDef.dxe) IecDef.c
	$(COMPILE.c) $(CFLAGS_CreateIecDef.dxe) $(CPPFLAGS_CreateIecDef.dxe) -o $@ IecDef.c



#### ����Ŀ�꽫��ɾ���������ɵ��ļ� ####
clean:
	rm -f \
		$(TARGETDIR_CreateIecDef.dxe)/CreateIecDef.dxe \
		$(TARGETDIR_CreateIecDef.dxe)/IecDef.o
	rm -f -r $(TARGETDIR_CreateIecDef.dxe)


# ����Ŀ��Ŀ¼�������Ҫ��
$(TARGETDIR_CreateIecDef.dxe):
	mkdir -p $(TARGETDIR_CreateIecDef.dxe)


# ����������ϵ���
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.Sun-x86-Solaris

