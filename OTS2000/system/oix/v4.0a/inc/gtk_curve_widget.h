#ifndef GTK_CURVE_WIDGET
#define GTK_CURVE_WIDGET

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#define G_ASSERT_NULL(p) g_assert(p != 0)

#define G_SAFE_FREE(p)	\
	if (p != 0)			\
	{					\
		g_free(p);		\
		p=0;			\
	}

#define COUNT_OF(p) sizeof(p)/sizeof(p[0])
#define M_PI	3.141592

#define MAX_STRING_LEN 256
#define MAX_USR_DATA	16

enum ECurveType		{eCurveLine=0, eCurveLadder, eCurveFill, eCurveDash, eCurveIndicator, eCurveTypeEnd};
enum ECurveTimeMode	{eModeNormal=0, eModeSec, eModeMin, eModeHour, eModeNormalAndNoSample, eModeEnd};
enum ECurveDataType	{eDataFloat, eDataInt, eDataTypeEnd};
enum ECurveLabelPos	
{
	eCurveNoLabel, 
	eCurveLabelStart, 
	eCurveLabelMid, 
	eCurveLabelEnd,
	eCurveLabelPosEnd
};

typedef struct
{
	gchar strText[MAX_STRING_LEN];

	GdkColor color;
	gint nCurveType;	//������ʾ����
	gint nDataType;		//��������
	gint nLabelPos;		//����������ʾλ��

	gint nTimeMode;		//pXAxis��ʾ���ݻ�����������ʼʱ��
	gdouble dStep;		//��ʱ��ģʽ���ü��ģʽʱ��ʱ����

	gint nNumPt;		//���ƶ�����������������ݻ�����ʱѭ����ʾ
	gint nLenBuf;		//���ݻ���������
	gint nOffset;		//��ʼ��ƫ����

	gdouble* pYAxis;	//���ݻ�����
	gdouble* pXAxis;	//���ݻ����������ڼ��ģʽ�µ���ʼʱ��

	gdouble dMin, dMax;	//�������޺�����

	gpointer usrData[MAX_USR_DATA];	//�û�����
}GCurve;

GCurve* gtk_curve_create(gint nLenBuf, gint nTimeMode);
void gtk_curve_destroy(GCurve* pCurve);
void gtk_curve_change_buf_size(GCurve* pCurve, gint nLenBuf, gint nTimeMode);
void gtk_curve_set_text(GCurve* pCurve, gchar* strText);
void gtk_curve_set_label_pos(GCurve* pCurve, gint pos);
GdkColor gtk_curve_get_color(GCurve* pCurve);
void gtk_curve_set_color(GCurve* pCurve, GdkColor* color);
void gtk_curve_set_rgb_color(GCurve* pCurve, guint8 r, guint8 g, guint8 b);
void gtk_curve_set_int_color(GCurve* pCurve, int color);
void gtk_curve_set_type(GCurve* pCurve, gint nType);
void gtk_curve_set_data(GCurve* pCurve, gdouble* pXAxis, gdouble* pYAxis, gint nLenBuf, 
						gint nOffset, gint nNumPt, gdouble dStep);
void gtk_curve_set_boundary(GCurve* pCurve, gboolean bMenual, gdouble dMin, gdouble dMax);
gdouble gtk_curve_get_max_range(GCurve* pCurve);
gdouble gtk_curve_get_min_range(GCurve* pCurve);
void gtk_curve_set_data_type(GCurve* pCurve, gint nDataType);
void gtk_curve_set_data_offset(GCurve* pCurve, gint nOffset);
void gtk_curve_set_data_points_num(GCurve* pCurve, gint nNumPt);

void gtk_curve_set_user_data(GCurve* pCurve, gpointer usrData, gint nIndex);
gpointer gtk_curve_get_user_data(GCurve* pCurve, gint nIndex);

gboolean gtk_curve_get_sample_value(GCurve* pCurve, gdouble dSample, gdouble dRange, gdouble dStep, gint* nNumPt,
								gdouble* dAxis, gint* nOffset, gdouble* dValue);

enum EColorType 
{
	eColorTitle=0,			//����
	eColorSubTitle,			//������
	eColorLabel,			//��������
	eColorAxisLabel,		//ʱ����
	eColorAxis,				//������
	eColorScale,			//�̱��
	eColorMajor,			//���������ǩ
	eColorMinor,			//���������ǩ
	eColorPositive,			//����������ǩ
	eColorZero,				//��ֵ0��ǩ
	eColorNegative,			//��ֵ������ǩ
	eColorChooseRect,		//����Ŵ�ѡ���
	eColorTrackLine,
	eColorTrackTime,
	eColorMessage,
	eColorCurvsMark,
	eColorEnd
};

enum ETimeType	{eTimeSec=0, eTimeMin, eTimeHour, eTimeDay, eTimeMon, eTimeYear, eTimeEnd};

enum EEnableStatus 
{
	eEnableAutoSubTitle=0,		//�Ƿ��Զ����ɸ�����	(Ĭ�Ϲر�)
	eEnableScale,				//�Ƿ��ṩ���Ź���	(Ĭ�Ϲر�)
	eEnableTrack,				//�Ƿ��ṩTrack��ʾ����	(Ĭ�Ͽ���)
	eEnableNegativeScale,		//�Ƿ���ʾ�����̣����Ա���������Ч	(Ĭ�Ͽ���)
	eEnableKeepZero,			//�����Ƿ��0��ʼ��������ֵ������Ч	(Ĭ�Ͽ���)
	eEnableMessage,				//��Ϣ��ʾ
	eEnableMessageClose,		//��Ϣ��ʾ�رհ�ť
	eEnableCurvesMark,			//�������߱�ʶ
	eEnableAutoLabel,			//�����������ǩ
	eEnableTimeAxis,			//X���Ƿ���ʱ����(Ĭ�Ͽ���)
	eEnableEnd
};

enum EFontDescType 
{
	eFontDescTitle=0, 
	eFontDescSubTitle, 
	eFontDescAxis, 
	eFontDescTrack,
	eFontDescMessage,
	eFontDescCurvesMark,
	eFontDescEnd
};

enum ECurveOpType 
{
	eCurveOpPointer=0, 
	eCurveOpHand, 
	eCurveOpZoomIn, 
	eCurveOpZoomOut,
	eCurveOpZoomRect,
	eCurveOpEnd
};

enum ETextType 
{
	eTextTitle=0, 
	eTextSubtitle, 
	eTextLabel, 
	eTextMessage,
	eTextXAxisLabel,	//����x��Ϊ��ʱ����ģʽʱ
	eTextEnd
};

enum ECalcType 
{
	eCalcScale=0,		//��������ʾ����������(-100.0��100.0��0��100.0)���������Զ���������(Ĭ��ֵ)
	eCalcScaleAuto,		//��������ʾ����������(-100.0��100.0��0��100.0)���Զ�������ֵ����
	eCalcScaleManual,	//��������ʾ����������(-100.0��100.0��0��100.0)����������ֵ����
	eCalcManual,		//����ֵ��ʾ������������
	eCalcAuto,			//����ֵ��ʾ���Զ���������
	eCalcEnd
};

#define MAX_NUM_CURVES	64

enum ECloseBtnStatus {eCloseBtnNormal=0, eCloseBtnAbove, eCloseBtnPressed, eCloseBtnDisAbled};

typedef struct 
{
	gchar strText[eTextEnd][MAX_STRING_LEN];

	gboolean bEnable[eEnableEnd];

	gint nCurveOpType;

	GdkCursor* pCursor[eCurveOpEnd];		//�����״

	GtkWidget	*pFrame;		//����
//	GdkGC		*pFrameGc;		//����gc

	GtkWidget	*pCanvas;		//����
//	GdkGC		*pCanvasGc;		//����gc

	GdkRectangle rectCanvas;

	PangoLayout* pPangoLayout;
	PangoFontDescription* pFontDesc[eFontDescEnd];

	gint nTimeType;
	gint nNumMajorCol;
	gdouble dTimeMin, dTimeMax, dTimeInterval;

	gdouble dYAixsMin, dYAxisMax, dYAxisInterval;

	gdouble dScaleTop, dScaleBottom;
	gdouble dScaleLeft, dScaleRight;

	gdouble dScaleRate;

	gboolean bPressed;
	gdouble dPtStartX, dPtStartY;
	gdouble dPtEndX, dPtEndY;

	GdkColor	color[eColorEnd];

	gint nSamplePixel;

	gint nCalc;
	gint nNext;
	GCurve* pCurves[MAX_NUM_CURVES];

	GdkRectangle rectMessage;
	GdkRectangle rectMessageClose;
	gint nCloseBtnStatue;

	GtkWidget* pToolBtn[eCurveOpEnd];
	int nToolType;
}GtkCurveWidget;

GtkWidget* gtk_curve_widget_create(GtkWidget* pTopWidget, GtkCurveWidget* pCurveWidget);

void gtk_curve_widget_set_text(GtkCurveWidget* pCurveWidget, gchar* str, gint nStrType);
void gtk_curve_widget_set_canvas_bg_color(GtkCurveWidget *pCurveWidget, GdkColor colorBg);
void gtk_curve_widget_set_canvas_bg_rgb_color(GtkCurveWidget* pCurveWidget, guint8 r, guint8 g, guint8 b);
void gtk_curve_widget_set_font_desc(GtkCurveWidget* pCurveWidget, PangoFontDescription* pFontDesc, gint nFontDescType);
void gtk_curve_widget_enable(GtkCurveWidget* pCurveWidget, gboolean bEnable, gint nType);
void gtk_curve_widget_set_color(GtkCurveWidget* pCurveWidget, GdkColor* color, gint nType);
void gtk_curve_widget_set_rgb_color(GtkCurveWidget* pCurveWidget, guint8 r, guint8 g, guint8 b, gint nType);
void gtk_curve_widget_set_current_operation(GtkCurveWidget* pCurveWidget, gint nCurveOp);
gint gtk_curve_widget_get_current_operation(GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_set_scale_rate(GtkCurveWidget* pCurveWidget, gdouble dRate);
void gtk_curve_widget_frame_redraw(GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_redraw(GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_zoom_100(GtkCurveWidget* pCurveWidget);
GtkWidget* gtk_curve_widget_get_frame(GtkCurveWidget* pCurveWidget);

void gtk_curve_widget_add_scale_toolbox(GtkCurveWidget* curvewidget, GtkWidget* box, GtkWidget * parent);

void gtk_curve_widget_tool_btn_manager(GtkCurveWidget* curvewidget, gint nToolType);
void gtk_curve_widget_toggled_btn_pointer(GtkWidget *widget, gpointer data);
void gtk_curve_widget_toggled_btn_hand(GtkWidget *widget, gpointer data);
void gtk_curve_widget_toggled_btn_zoom_in(GtkWidget *widget, gpointer data);
void gtk_curve_widget_toggled_btn_zoom_out(GtkWidget *widget, gpointer data);
void gtk_curve_widget_toggled_btn_zoom_rect(GtkWidget *widget, gpointer data);
void gtk_curve_widget_toggled_btn_zoom_100(GtkWidget *widget, gpointer data);

gint gtk_curve_widget_add_curve(GtkCurveWidget* pCurveWidget, GCurve* pCurve);
gboolean gtk_curve_widget_remove_curve(GtkCurveWidget* pCurveWidget, gint nIndex);
void gtk_curve_widget_clear_all_curve(GtkCurveWidget* pCurveWidget);
gboolean gtk_curve_widget_check_add_curve(GtkCurveWidget* pCurveWidget);
gint gtk_curve_widget_get_curve_count(GtkCurveWidget* pCurveWidget);
GCurve* gtk_curve_widget_get_curve(GtkCurveWidget* pCurveWidget, gint nIndex);

gboolean gtk_curve_widget_print(cairo_t* cr, GtkCurveWidget* pCurveWidget, 
								gdouble x, gdouble y, gdouble width, gdouble height);

void gtk_curve_widget_set_time_scale(GtkCurveWidget* pCurveWidget, gdouble dMin, gdouble dMax);
void gtk_curve_widget_set_data_scale(GtkCurveWidget* pCurveWidget, gint nCalcType, gdouble dMin, gdouble dMax);
void gtk_curve_widget_adjust_data_scale(GtkCurveWidget* curvewidget, double *min, double *max);

void gtk_curve_widget_set_sample_pixel_interval(GtkCurveWidget* pCurveWidget, gint nNumPixel);

void gtk_curve_widget_calculate_data_scale(GtkCurveWidget* pCurveWidget, GCurve* pCurve, gdouble* dMin, gdouble* dMax);

void gtk_curve_widget_adjust_axis(GtkCurveWidget* pCurveWidget);

void gtk_curve_widget_destroy(GtkWidget* pWidget, gpointer usr_data);
void gtk_curve_widget_frame_realize(GtkWidget *pWidget, gpointer usr_data);
void gtk_curve_widget_frame_allocate(GtkWidget *pWidget, GtkAllocation *pAlloc, gpointer usr_data);
void gtk_curve_widget_adjust_layout(GtkWidget *pWidget, GtkAllocation *pAlloc, gpointer usr_data);
void gtk_curve_widget_frame_expose_event(GtkWidget *pWidget,GdkEventExpose *pEvent, gpointer usr_data);
void gtk_curve_widget_frame_draw(GtkWidget *pWidget, gpointer usr_data);
void gtk_curve_widget_frame_draw_contents(cairo_t* cr, GtkCurveWidget* pCurveWidget, GdkRectangle rect);

void gtk_curve_widget_canvas_realize(GtkWidget* pWidget, gpointer usr_data);
void gtk_curve_widget_canvas_expose_event(GtkWidget *pWidget, GdkEventExpose *pEvent, gpointer usr_data);
void gtk_curve_widget_canvas_draw(GtkWidget *pWidget, gpointer usr_data);
void gtk_curve_widget_canvas_draw_contents(cairo_t* cr, GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_draw_grid(cairo_t* cr, GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_draw_choose_rect(cairo_t* cr, GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_draw_curves(cairo_t* cr, GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_draw_track(GtkWidget* pWidget, cairo_t* cr, GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_draw_message(cairo_t* cr, GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_canvas_draw_curves_mark(cairo_t* cr, GtkCurveWidget* pCurveWidget);

gboolean gtk_curve_widget_canvas_btn_press_event(GtkWidget *pWidget, GdkEventButton *pEvent, gpointer usr_data);
gboolean gtk_curve_widget_canvas_btn_release_event(GtkWidget *pWidget, GdkEventButton *pEvent, gpointer usr_data);
gboolean gtk_curve_widget_canvas_motion_notify_event(GtkWidget *pWidget, GdkEventButton *pEvent, gpointer usr_data);
gboolean gtk_curve_widget_canvas_key_release_event(GtkWidget *pWidget,GdkEventKey *pEvent, gpointer usr_data);

void gtk_curve_widget_draw_pango_layout(cairo_t* cr, GdkColor* color, gdouble x, gdouble y, PangoLayout* layout);
void gtk_curve_widget_draw_line(cairo_t* cr, gdouble x1, gdouble y1, gdouble x2, gdouble y2);
void gtk_curve_widget_draw_rectangle(cairo_t* cr, gdouble x, gdouble y, gdouble width, gdouble height, gboolean fill);
void gtk_curve_widget_draw_polygon(cairo_t* cr, gdouble* x, gdouble* y, int size);
void gtk_curve_widget_draw_indicator(cairo_t* cr, gdouble x, gdouble y);
void gtk_curve_widget_draw_pixpuf(cairo_t* cr, GdkPixbuf* pixbuf, 
								  gdouble sx, gdouble sy, gdouble sWidth, gdouble sHeight, 
								  gdouble x, gdouble y, gdouble width, gdouble height);

void gtk_curve_widget_canvas_hand_move(GtkCurveWidget* pCurveWidget, gdouble x, gdouble y);
void gtk_curve_widget_canvas_zoom_in(GtkCurveWidget* pCurveWidget, gdouble x, gdouble y);
void gtk_curve_widget_canvas_zoom_out(GtkCurveWidget* pCurveWidget, gdouble x, gdouble y);
void gtk_curve_widget_canvas_zoom_rect(GtkCurveWidget* pCurveWidget);

void gtk_curve_widget_canvas_set_zoom_rect(GtkCurveWidget* pCurveWidget, double dLeft, double dRight);

gint gtk_curve_widget_transform(gdouble dAxis, gdouble dMin, gdouble dMax, gint nLength, gboolean bRev);
gdouble gtk_curve_widget_invTransform(gdouble dPos, gdouble dMin, gdouble dMax, gdouble dLength, gboolean bInv);
gdouble gtk_curve_widget_scale_value(gdouble dScale, gdouble dMin, gdouble dMax);
gint gtk_curve_widget_sample(gdouble dMin, gdouble dMax, gint nWidth, gint nPixelInterval);

GdkCursor* create_cursor(GtkCurveWidget* pCurveWidget, GdkPixbuf* pPixBuf, gboolean bCenter);
void gtk_curve_widget_create_cursor(GtkCurveWidget* pCurveWidget);
void gtk_curve_widget_destroy_cursor(GtkCurveWidget* pCurveWidget);

void gtk_curve_widget_ref_cursor_pixbuf();
void gtk_curve_widget_unref_cursor_pixbuf();

void gtk_curve_widget_ref_pixbuf();
void gtk_curve_widget_unref_pixbuf();

void adjust_data_scale(gdouble* dMin, gdouble* dMax);
gint binary_find(gdouble* pData, gint nLenBuf, gint nOffset, gint nNumPt, gdouble dValue);
gint step_find(gint nLenBuf, gint nOffset, gint nNunPt, gdouble dStart, gdouble dStep, gdouble dValue, gboolean bNear);

GdkColor rgb2gdk(guint8 r, guint8 g, guint8 b);
gboolean gtk_rectangle_contains(GdkRectangle rect, gdouble x, gdouble y);

typedef struct  
{
	gint nPos;
	GdkColor* color;
}ColorStack;

typedef struct
{
	ColorStack colorUsed, colorUnused;
}GtkColorStack;

GtkColorStack* gtk_color_stack_create(GdkColor** pColors, gint nNum);
void gtk_color_stack_destroy(GtkColorStack* pStack);
GdkColor gtk_color_stack_pop_color(GtkColorStack* pStack);
void gtk_color_stack_push_color(GtkColorStack* pStack, GdkColor* color);
void gtk_color_stack_reset(GtkColorStack* pStack);

#endif
