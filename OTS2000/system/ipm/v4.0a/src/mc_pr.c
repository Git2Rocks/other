

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <winspool.h>
#include <commdlg.h>

#include "../inc/ipm.h"

#include "../inc/pr.h"
#include "../inc/scaler.h"
#include "../inc/text_edit_def.h"
#include "../inc/color_def.h"

BOOL	CreatePrtLogFont(float);

void Print ()
{
	int	 width, height, bgcolorsave;
	float	 xscalesave,yscalesave,xprtfontscale,yprtfontscale,fLogPelsX1,fLogPelsY1,fLogPelsX2,fLogPelsY2;
  	DOCINFO di;
	HDC		hdc;
	HANDLE	palsave;

  	SetMapMode (prtdc, MM_TEXT);

	bgcolorsave = canvas_bg_color;
  	xscalesave = xscale;
  	yscalesave = yscale;
	palsave = ghPal;
	ghPal = NULL;

	canvas_bg_color = WHITE;						//	��ɫ
 	width     = GetDeviceCaps (prtdc, HORZRES);		//	��ȡ�йظ����豸���豸�ض���Ϣ
  	height    = GetDeviceCaps (prtdc, VERTRES) - 200;
	xscale = (float)width/(float)OLDWIDTH;
	yscale = (float)height/(float)OLDHEIGHT;

	hdc = GetDC(ghWnd);						//	��ȡ����������ʾ�豸������	
	fLogPelsX1 = (float)GetDeviceCaps (hdc, LOGPIXELSX);
	fLogPelsY1 = (float)GetDeviceCaps (hdc, LOGPIXELSY);
	ReleaseDC(ghWnd, hdc);
	fLogPelsX2 = (float)GetDeviceCaps (prtdc, LOGPIXELSX);
	fLogPelsY2 = (float)GetDeviceCaps (prtdc, LOGPIXELSY);
	xprtfontscale = fLogPelsX2/fLogPelsX1;
	yprtfontscale = fLogPelsY2/fLogPelsY1;
	if(CreatePrtLogFont(yprtfontscale) == FALSE)	//	��������ָ���������߼�����	
	{
		 
		MessageBox (ghWnd, "Can't Create Fitable Printer font", "IPM", MB_OK);
	}		

	if(ghPal) 
	{
		SelectPalette (prtdc, ghPal, FALSE);
    	RealizePalette (prtdc);
	}

  	di.cbSize      = sizeof(DOCINFO);
  	di.lpszDocName = "print dsp";
  	di.lpszOutput  = NULL;

	toprint = TOPRINTON;

  	StartDoc  (prtdc, &di);		//	������ӡ��ҵ
  	StartPage (prtdc);			//	��ӡ����������׼����������
	Redraw(ghWnd, prtdc);

  	EndPage   (prtdc);			//	��ҳ��
  	EndDoc    (prtdc);			//	��ֹ��ӡ��ҵ
 // DeleteDC  (prtdc);
	toprint = TOPRINTOFF;
	canvas_bg_color = bgcolorsave;
	xscale = xscalesave;
	yscale = yscalesave;
	ghPal = palsave;
}


BOOL	CreatePrtLogFont(float yprtfontscale)
{
	int		font_id, height;
	
	for(font_id=0; font_id<MAX_FONTSET; font_id++)
	{
		height = (int)(font_size[font_id].height*yprtfontscale);
		prt_font_set[font_id] = CreateFont(height, 0,
										0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
										OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
										DEFAULT_QUALITY,
										VARIABLE_PITCH | FF_DONTCARE, "RS_Song");	//RS_Song  RS_FangSong RS_Kai ����

		if( prt_font_set[font_id] == NULL) 
		{
			
			MessageBox (ghWnd, "Create Printer font set error", "IPM", MB_OK);
            return(FALSE);
		}
	}
	return(TRUE);
}


