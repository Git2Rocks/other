var listSelectTr=-1;

function initList(){
  //�����б��td�ı�ѡ�й���
  var listTable=document.all.item("listTable");
  if(listTable!=null){
    var allTdofList=listTable.all.tags("td");
    for(i=0;i<allTdofList.length;i++)
      allTdofList[i].unselectable = "on";
  }
}

//����б��ĳһtrʱ
function listTrClick(item){
  var hiddenCheckboxObj = document.all.item("hiddenCheckbox");
  if(hiddenCheckboxObj==null || hiddenCheckboxObj[item.index-1]==null)
    return;
  if(window.event.ctrlKey==false && window.event.shiftKey==false && (item.index-1)==listSelectTr){
    if(hiddenCheckboxObj.length==null){
      hiddenCheckboxObj.checked = false;
      hiddenCheckboxObj.parentElement.parentElement.className = "data_Tr1";
    }else{
      for(j=0;j<hiddenCheckboxObj.length;j++){
        hiddenCheckboxObj.item(j).checked = false;
        hiddenCheckboxObj.item(j).parentElement.parentElement.className = (j%2==0)?"data_Tr1":"data_Tr2";
      }
    }
    listSelectTr = -1;
    return;
  }
  if(hiddenCheckboxObj.length==null){
    hiddenCheckboxObj.checked = true;
    hiddenCheckboxObj.parentElement.parentElement.className = "select_Tr";
  }else{
    if(window.event.ctrlKey==false){
      if(listSelectTr<=-1){
        iStart = item.index-1;
        iEnd = item.index-1;
      }else{
        iStart = (listSelectTr<item.index)?listSelectTr:item.index-1;
        iEnd = (listSelectTr<item.index)?item.index-1:listSelectTr;
      }
      for(i=0;i<hiddenCheckboxObj.length;i++){
        hiddenCheckboxObj.item(i).checked = false;
        hiddenCheckboxObj.item(i).parentElement.parentElement.className = (i%2==0)?"data_Tr1":"data_Tr2";

        if(window.event.shiftKey && i>=iStart && i<=iEnd){
          hiddenCheckboxObj.item(i).checked = true;
          hiddenCheckboxObj.item(i).parentElement.parentElement.className = "select_Tr";
        }
      }
    }
    hiddenCheckboxObj.item(item.index-1).checked = true;
    hiddenCheckboxObj.item(item.index-1).parentElement.parentElement.className = "select_Tr";
  }
  listSelectTr = item.index-1;
}

//���б�û��ѡ���κ�һ��ʱ������true��
function listSelectNone(){
  var hiddenCheckboxObj = document.all.item("hiddenCheckbox");
  if(hiddenCheckboxObj==null)
    return true;
  else{
    if(hiddenCheckboxObj.length==null){
      return !hiddenCheckboxObj.checked;
    }else{
      var num=0;
      for(i=0;i<hiddenCheckboxObj.length;i++){
        if(hiddenCheckboxObj[i].checked){
          num=num+1;
          break;
        }
      }
      if(num>0)
        return false;
      else
        return true;
    }
  }
}

//���б�ѡ�г���һ�У����л��������ϣ�ʱ������true��
function listSelectMore(){
  var hiddenCheckboxObj = document.all.item("hiddenCheckbox");
  if(hiddenCheckboxObj==null || hiddenCheckboxObj.length==null)
    return false;
  else{
    var num=0;
    for(i=0;i<hiddenCheckboxObj.length;i++){
      if(hiddenCheckboxObj[i].checked)
        num=num+1;
    }
    if(num>1)
      return true;
    else
      return false;
  }
}

//�����б�ǰѡ��ֵ������ж����ֵ��ֵ֮����","�ָ�����hiddenCheckboxObj==null��û��ѡ���κμ�¼��ѡ����һ����¼����¼ֵȷʵΪ""ʱ������ֵ������""��
function listGetValue(){
  var hiddenCheckboxObj = document.all.item("hiddenCheckbox");
  var returnValue="";
  if(hiddenCheckboxObj.length==null){
    if(hiddenCheckboxObj.checked)
      returnValue=hiddenCheckboxObj.value;
  }else{
    for(i=0;i<hiddenCheckboxObj.length;i++){
      if(hiddenCheckboxObj[i].checked){
        if(returnValue=="")
          returnValue=hiddenCheckboxObj[i].value;
        else
          returnValue=returnValue+","+hiddenCheckboxObj[i].value;
      }
    }
  }
  return returnValue;
}