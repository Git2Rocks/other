<SCRIPT language=JavaScript>

function showdate(syear,smon,sdate,sday){

var enabled = 0;

today = new Date();

var day;

var date;

date = '';



if(today.getDay()==0) day = "������"

if(today.getDay()==1) day = "����һ"

if(today.getDay()==2) day = "���ڶ�"

if(today.getDay()==3) day = "������"

if(today.getDay()==4) day = "������"

if(today.getDay()==5) day = "������"

if(today.getDay()==6) day = "������"

if(syear){



if(today.getYear()>90){

date = today.getYear();

}else{

date = '20' + today.getYear();

}



date = date + "��";

}

if(smon){

date = date + (today.getMonth() + 1 ) + "��";

}

if(sdate){

date = date + today.getDate() + "��, ";

}

if(sday){

date = date + day +"";

}

document.write( date );

}

</SCRIPT>