function LockControl(a_tag,a_style,a,a_IDs)
{
	var x,i,tag,type,IDs,IDName;
	IDs = (a_IDs != null) ? a_IDs + ',' : null;
	if (!a)
		a = document.all;
	if (!a_style)
		a_style = 'readonly';
	tag = a_tag.toLowerCase();
	type = '';
	switch(tag)
	{
	case 'textarea':
		break;
	case 'select':
		break;
	case 'checkbox':
	case 'password':
	case 'radio':
	case 'button':
	case 'text':
		type = tag;
		tag = 'input';
	default:
	}
	x = a.tags(tag);
	for (i=0;i<x.length;i++)
	{
		if (x[i].id)
			IDName = x[i].id;
		else if (x[i].name)
			IDName = x[i].name;
		else IDName = null;

		if (tag == 'input' && x[i].type != type)
			continue;

		if (IDName && IDs && IDs.indexOf(IDName + ',') >= 0 )
			continue;

		switch (a_style.toLowerCase())
		{
		case 'disabled':
			x[i].disabled = true;
			break;
		case 'readonly':
			x[i].readOnly = true;
			if ( x[i].onclick )
				x[i].onclick = null;
			break;
		default:
			break;
		}
		x[i].style.backgroundColor = '#c0c0c0';
	}
}

/*
function LockControls(a_IDs)
������ҳ�������text��checkbox��password��radio��textarea��selectҳ��ؼ�
���������ó�ֻ�����߽�ֹʹ��
���룺
	a_IDs����ѡ�������Զ��ŷָ����ַ�������¼��ҳ�治�뱻��ס��ҳ��ؼ���id����nameֵ
�����
*/
function LockControls(a_IDs)
{
	var d,a;
	d = document;
	a = d.all;
	if (a)
	{
		LockControl('text','readonly',a,a_IDs);
		LockControl('checkbox','disabled',a,a_IDs);
		LockControl('password','readonly',a,a_IDs);
		LockControl('radio','disabled',a,a_IDs);
		LockControl('textarea','readonly',a,a_IDs);
		LockControl('select','disabled',a,a_IDs);
		LockControl('button','disabled',a,a_IDs);
		return;
	}
}
