	var CShow	=	"show";	//��ʾ״̬
	var CNew	=	"new";		//����״̬
	var CDel	=	"delete";  //ɾ��״̬
	var apk = 0;			   //Left UP DOWN by Max
	var Position=18;
	//���ڱ�����״̬����
	function dBuffer()
	{
		this.nodes=new Array();
		this.Add= dAddNode;
		this.Delete = dDelNode;
	}

	//����һ���ڵ�
	function dAddNode(a_func_id,a_zone,a_status,a_Title,a_Position,a_modu_id,a_modu_Title)
	{
		//alert('operator=new');
		var oNode = new pNode(a_func_id,a_zone,a_status,a_Title,a_Position,a_modu_id,a_modu_Title);
		var oNode1;
		//����һ���ӵ��ʱ���жϸýӵ��Ƿ��������Ѿ�����
		//���������״̬ΪCDel�͸ı���״̬ΪCShow�����������״̬ΪCShow��CNew��
		//���κδ���,�������������ӡ�
		oNode1 = this.nodes[a_func_id];

		if (oNode1==null)
			{
				//�����ڵĴ���

				this.nodes[a_func_id]=oNode;
				return 1;
			}
		else
			{
				if (this.nodes[a_func_id].Status==CDel)
				{
					this.nodes[a_func_id].Status==CShow;
					return 2;
				}
				else
				{
					return 3;
				}
			}
		return 1;
	}

	//ɾ��һ���ڵ�
	function dDelNode(a_func_id)
	{
		//alert('operator=del');
		var newnodes = new Array();
		var l_s;

		if (this.nodes[a_func_id]==null)
			{
				alert("�ڵ�Ϊ��");
				return -1 ;
				}
		if (this.nodes[a_func_id].Status==CNew)
			{
			for (l_s in this.nodes)
				{
					if (l_s!=a_func_id)
						{
							newnodes[l_s]=this.nodes[l_s];
						}
				}
			this.nodes = newnodes;
			return true;
			}
		else
			{
				//����ýڵ��״̬����"new"��ı�ýڵ��״̬Ϊ"delete"
				this.nodes[a_func_id].UpdateStatus(CDel);
				return true;
			}
	}

	//ҳ�湦�ܽڵ���
	function pNode(a_func_id,a_zone,a_status,a_Title,a_Position,a_modu_id,a_modu_Title)
	{
		this.Func_id	= a_func_id;
		this.modu_id	= a_modu_id;
		this.modu_Title = a_modu_Title;
		this.Zone		= a_zone;
		//״̬Ϊ����:1--show 2--new 3--deleted
		this.Status		= a_status;
		this.Title		= a_Title;
		this.Position   = a_Position;
		this.UpdateStatus		= pNodeUpdateStatus;
		this.UpdateZone = pNodeUpdateZone;
	}

	//�Խڵ�����޸�,�ı�״̬
	//����: true �ɹ� false ʧ��
	function pNodeUpdateStatus(a_Status)
	{
        //alert('state=' + a_Status);
		this.Status = a_Status;
		return true;
	}

	//�Խڵ�����޸ģ��ı�λ��
	function pNodeUpdateZone(a_Zone)
	{
		this.Zone=a_Zone;
		return true;
	}




	//�����ڴ�����е�ģ�鹦��
	function cAllFunc()
	{
		this.nodes = new Array();
		this.Add = AllFuncAdd;  //����һ��ģ��Ԫ��
		this.AddCell = FuncAddCell;
		this.Del = DelAllFunc;
		this.DelCell=DelCellAllFunc;
		this.Find=FindFunc;
	}

	//�ҵ�ָ����Ԫ��
	function FindFunc(a_func_id)
	{
		var l_s,l_func;
		for (l_s in this.nodes)
		{
			for (l_func in this.nodes[l_s].nodes)
			{
				if (l_func==a_func_id)
				{
					return this.nodes[l_s].nodes[l_func];
				}
			}
		}
	}
	//�Ӷ���cAllFunc��ֱ��ɾ��һ��function�ڵ�
	function DelCellAllFunc(a_func_id)
	{
		var l_s,l_func;

		for (l_s in this.nodes)
		{
			for (l_func in this.nodes[l_s].nodes)
			{
				if (l_func==a_func_id)
				{
					this.nodes[l_s].Delete(a_func_id);
					return true;
				}
			}
		}
		return false;
	}

	function DelAllFunc(a_modu_id)
	{
		var newnodes = new Array();
		var l_s;

		if (this.nodes[a_func_id]==null)
			{
				alert("�ڵ�Ϊ��");
				return -1 ;
			}

			for (l_s in this.nodes)
				{
					if (l_s!=a_func_id)
						{
							newnodes[l_s]=this.nodes[l_s];
						}
				}
			this.nodes = newnodes;
			return true;
	}

	function AllFuncAdd(a_modu_id,a_modu_Title)
	{
		var oNode;
		oNode = new cModuFunc(a_modu_id,a_modu_Title);
		this.nodes[a_modu_id] = oNode;
	}

	//����һ���ڵ�
	function FuncAddCell(a_modu_id,a_modu_Title,a_func_id,a_Title,a_ary)
	{
		var oNode;

		//���жϽڵ����Ƿ��Ѿ�������Ӧ�Ľڵ�
		if (this.nodes[a_modu_id]==null)
		{
			//����һ���ڵ�
			oNode = new cModuFunc(a_modu_id,a_modu_Title);
			this.nodes[a_modu_id] = oNode;
		}

		//�ж�ģ��ڵ����Ƿ���ڣ���������������
		if (this.nodes[a_modu_id].nodes[a_func_id]==null)
		{
			this.nodes[a_modu_id].Add(a_func_id,a_modu_id,a_Title,a_modu_Title,a_ary)
		}

	}

	//�����ڴ��ÿ��ģ�����еĹ���
	function cModuFunc(a_Modu_id,a_modu_Title)
	{
		this.nodes = new Array();
		this.moduid = a_Modu_id;
		this.moduTitle=a_modu_Title;
		this.Add=ModuFuncAdd;
		this.Delete=ModuFuncDel;
	}

	//��function���ڴ�Ÿ�Ԫ�ص�����
	function cfunc(a_func_id,a_modu_id,a_Title,a_modu_Title,a_ary)
	{
		this.func_id=a_func_id;
		this.modu_id=a_modu_id;
		this.modu_Title=a_modu_Title
		this.Title=a_Title;
		this.other=a_ary;
	}

	//����һ��Ԫ��
	function ModuFuncAdd(a_func_id,a_modu_id,a_Title,a_modu_Title,a_ary)
	{
		var ofunc;

		ofunc = new cfunc(a_func_id,a_modu_id,a_Title,a_modu_Title,a_ary);
		this.nodes[a_func_id] = ofunc;
	}

	//ɾ��һ��Ԫ��
	function ModuFuncDel(a_func_id)
	{
		var newnodes = new Array();
		var l_s;

		if (this.nodes[a_func_id]==null)
			{
				alert("�ڵ�Ϊ��");
				return -1 ;
			}

			for (l_s in this.nodes)
				{
					if (l_s!=a_func_id)
						{
							newnodes[l_s]=this.nodes[l_s];
						}
				}
			this.nodes = newnodes;
			return true;
	}

//--------------------------------��������-------------------------------------------
	//�õ���ǰϵͳ������Щģ��
	function GetModu()
	{
		var l_s;
		var l_option;
		var l_i,l_CurrModu;

		if (oAllFunc==null) {return false;}

		l_i = 0
		l_option="<SELECT class='Select' ID='moduSelect' name='moduSelect' onclick='javascript:moduSelect_Changed();'>";
		for (l_s in oAllFunc.nodes)
		{
			l_option = l_option + "<OPTION value=" + l_s
			if (l_i == 0)
			{l_option = l_option + " Selected ";
			 l_CurrModu = l_s;
			 }

			l_option = l_option + "> " + oAllFunc.nodes[l_s].moduTitle + "</OPTION> "
			l_i = l_i + 1;
		}
		if (l_i==0)
		{
		return "";
		}

		l_option = l_option + "</SELECT>"
		return l_option;

	}

	//�õ�ָ��ģ���δʹ�ù��ܵ���ʵ
	function GetFunction(a_modu_id)
	{
		var l_s;
		var l_StrTop;

		l_StrTop="";
		for (l_s in oAllFunc.nodes[a_modu_id].nodes)
		{
			l_StrTop = l_StrTop + "<Table border = '0' CELLSPACING='1' CELLPADDING='0' CLASS='LayoutWebPartFrame' ID='" + l_s + "' >"
			l_StrTop = l_StrTop + "<tr><td CLASS='LayoutWebPart' >" + oAllFunc.nodes[a_modu_id].nodes[l_s].Title + "</td></tr> "
			l_StrTop = l_StrTop + "</TABLE>"

		}

		return l_StrTop;
	}



//-------------------------������--------------------------------------
function ChangeBuffer(a_prtSrc,a_prtTarget)
	{
		var l_zone;
		var l_Srcid;
		var oNode;

		if (a_prtSrc==null) {return;}

		if (a_prtSrc.id==null){return;}

		l_Srcid = a_prtSrc.id
		l_zone=-1;
		//�ж��ƶ���λ��
		if (a_prtTarget!=null)
			//�ж�Target������Ҫ���Ĵ���
			switch (a_prtTarget.className)
				{
					case 'LayoutDelZone':
						//ɾ���Ĵ���
						l_zone = 0;

						oNode = oBuffer.nodes[l_Srcid];

						if (oNode==null){
							a_prtTarget.innerText=' ';
							moduSelect_Changed();
							return;
								}

						//��oAllFunc���������
						oAllFunc.AddCell(oNode.modu_id	,oNode.modu_Title,oNode.Func_id,oNode.Title);

						//oBuffer�Ӷ�����ɾ����
						oBuffer.Delete(l_Srcid);
						a_prtTarget.innerText=" ";
						moduSelect_Changed();
						break;
						return;
					case 'LayoutZoneTop':
						//�Ƶ������Ĵ���
						l_zone = 4;
						break;
					case 'LayoutZoneLeft':
						//�Ƶ���ߵĴ���
						l_zone = 1;
						break;
					case 'LayoutZoneCenter':
						//�Ƶ��м�Ĵ���
						l_zone = 3;
						break;
					case 'LayoutZoneRight':
						//�Ƶ��ұߵĴ���
						l_zone = 2;
						break;
					case 'LayoutZoneBottom':
						//�Ƶ��ײ��Ĵ���
						l_zone = 5;
						break;
					default:
						l_zone = -1;
						break;
				}

			//�������ɾ�����ڶ���oAllFunc���������ǰ�Ľڵ�
			//����oBuffer���������һ���µĽڵ�
			/*
			if ((l_zone!=-1) && (l_zone!=0))
			{
				oNode = oAllFunc.Find(a_prtSrc.id);
				if (oNode==null) {return;}

				oBuffer.Add(a_prtSrc.id,l_zone,CNew,oNode.Title,0,oNode.modu_id,oNode.modu_Title);
				oAllFunc.DelCell(a_prtSrc.id);
			}
			*/

		}

	//���л�ģ��ʱ���Ĵ���
	function moduSelect_Changed()
	{
		var l_modu_id,l_return;

		if (moduSelect==null) {return;}

		l_modu_id = moduSelect.options(moduSelect.selectedIndex).value;
		if (l_modu_id==null){return;}

		l_return = GetFunction(l_modu_id);
		document.all.item("LeftBar").innerHTML=l_return;

	}

//------------------div�Ĺ���-------------
setTimeout('ini()',300);

//function doOnresize()
//{
//    ini();
//}

function ini(){
    //maxy =425
    maxy=500
    scrollicon = 40*(Math.round(Math.round(document.body.offsetHeight/2.5)/25));
          if ((apk+document.body.offsetHeight) < maxy){
              //down2.style.display = '';
          }
          else {
              //down2.style.display = 'none';
          }
    //up2.style.pixelLeft = document.body.offsetWidth - 700
    //down2.style.pixelLeft = document.body.offsetWidth - 700
    //up2.style.pixelTop = 200
    //down2.style.pixelTop = document.body.offsetHeight - 25
}

function addy(){
   ik = apk;
    addygo();
}

	function addygo()
	{
	 if(inFloder.clientHeight <= 260){
    maxHeight=-10;
    }
    if(inFloder.clientHeight > 260 && inFloder.clientHeight <= 900){
    maxHeight=inFloder.clientHeight/1.8;
    }
    if(inFloder.clientHeight > 900 && inFloder.clientHeight <= 1150){
    maxHeight=inFloder.clientHeight/1.6;
    }
    if(inFloder.clientHeight > 1150){
    maxHeight=inFloder.clientHeight/1.4;
    }

    k = apk;

    inFloder.style.clip = 'rect(' + (k) + ' 100% ' + (k+270) + ' 0)';
    inFloder.style.top = (0 - k) + Position;

    //inFloder.style.top = (0 - 200)
    if ((k < ik + scrollicon) && k<(maxHeight)){
        apk = (k + 10);
        setTimeout('addygo()',20);
    }
    if ((k+document.body.offsetHeight)-25>=500){
    }
    }


function miny(){
    ih = apk;
    minygo();
}

function minygo(){
    h = apk
    inFloder.style.clip = 'rect(' + (h) + ' 100% ' + (h+270) + ' 0)';

    inFloder.style.top = (0 - h) + Position;

    if ((h > ih - scrollicon) && ( h >= 0)){
        apk = (h - 10);
        setTimeout('minygo()',20);
    }
    if (apk <= 0){
    }
}
