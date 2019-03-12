// JavaScript Document

function toCompileName(sn)
{
	if (sn == "VC") return "Microsoft Visual C";
	if (sn == "VCPP") return "Microsoft Visual C++";
	if (sn == "BC") return "Borland C";
	if (sn == "BCPP") return "Borland C++";
	if (sn == "JAVA") return "Java";
	if (sn == "DC") return "Dev-CPP (C语言)";
	if (sn == "DCPP") return "Dev-CPP (C++语言)";
	if (sn == "C") return "Dev-CPP (C语言)";
	if (sn == "CPP") return "Dev-CPP (C++语言)";
	return "";
}

function isRequireLang(tp)
{
	var tmp = (""+tp).toLowerCase();
	if (!tp) tmp = "";
	return !(tmp=="" || tmp=="-" || tmp=="result");
}

function two(x){return (x>=10?"":"0")+x;}
function leftTimeStr(svnow)
{
	svnow = Math.floor(svnow);
	var old = svnow;
	pn = "";
	if (svnow>=3600)
	{
		var hours = Math.floor(svnow / 3600);
		pn += hours + "小时";
		svnow = svnow - hours * 3600;
	}
	if (old>=60)
	{
		var minutes = Math.floor(svnow / 60);
		if (pn!="" && minutes<10)
			pn += "0";
		pn += minutes + "分";
		svnow = svnow - minutes * 60;
	}
	var seconds = Math.floor(svnow);
	if (pn!="" && seconds<10)
		pn += "0";
	pn += seconds + "秒";
	return pn;
}
function onticktime()
{
	var svst = parseInt(currentInfo["time"]);
	var now=new Date();var ns=now.getHours()*3600+now.getMinutes()*60+now.getSeconds();
	var timepassed = Math.floor((new Date().getTime()-currentInfo.timec)/1000);
	var svnow=svst+timepassed;
	var curtime = two(Math.floor(svnow/3600)%24)+":"+two(Math.floor(svnow/60)%60)+":"+two(svnow%60);
	e('info1').innerHTML = currentInfo["cdate"];// + " " + curtime;
	if (e('info4'))
		e('info4').innerHTML = curtime;//tpstr;
	if (currentInfo["timeleft"]!="no")
	{
		var tleft = parseInt(currentInfo["timeleft"]) - timepassed;
		var aleft = parseInt(currentInfo["extratime"]);
		var tpast = parseInt(currentInfo["timepast"]) + timepassed;
		var tlstr =  "", alstr = "", tpstr = "";
		for (var i=0; i<10; ++i) {
			if (parseInt(currentInfo["alerttime"+i]+"")>0)
			{
				if (tleft<=parseInt(currentInfo["alerttime"+i]+""))
				{
					alert(currentInfo["alertinfo"+i]);
					for (var j=0; j<10; ++j)
						currentInfo["alerttime"+i] = "0";
				}
			}
		}
		if (tleft<=0)
		{
			aleft += tleft;
			tleft = 0;
		}
		if (aleft < 0)
			aleft = 0;
		if (tleft>0) tlstr = leftTimeStr(tleft); else tlstr = "已结束";
		if (aleft>0) alstr = leftTimeStr(aleft); else alstr = "已结束";
		tpstr = leftTimeStr(tpast);
		if (currentInfo["extratime"]=="no") alstr = "无";
		if (e('info2'))
			e('info2').innerHTML = tlstr;
		if (currentInfo["extratime"]!="no")
		{
			if (e('info3'))
				e('info3').innerHTML = "<span style='color:red;'><b>考试补时：</b>" + alstr + "</span>";
		}
		else
		{
			if (e('info3'))
				e('info3').innerHTML = "";
		}
	}
	else
	{
		if (e('info2'))
			e('info2').innerHTML = "";
		if (e('info3'))
			e('info3').innerHTML = "";
	}
}

function gotoUrl(url)
{
	location.href = url;
}
function checkUState()
{
	var stat = ""+currentInfo["userid"];
	var curl = location.pathname;
	if (stat=="") { if (curl!="/"&&curl!="/index.page"&&curl!="/index.html") gotoUrl("/"); }
	//else if (stat=="wait") { if (curl!="/unstart.page"&&curl!="/unstart.html") gotoUrl("/unstart.page"); }
	//else if (stat=="end") { if (curl!="/over.page"&&curl!="/over.html") gotoUrl("/over.page"); }
	//else if (stat=="complete") { if (curl!="/complete.page"&&curl!="/complete.html") gotoUrl("/complete.page"); }
	//else if (curl=="/unstart.page" || curl=="/unstart.html" || curl=="/over.page" || curl=="/over.html") { gotoUrl("/"); }
}
function setTitle(tit, hideret, retText, retUrl)
{
}

function _popAlertIcon(_title, _content, _icon, _onOK, _width)
{
	var _ret = {};
	var _popall = e("popall");
	
	_popall.innerHTML = "";
	
	newT("div", _popall, "popback", "&nbsp;");
	var _ft = newT("div", _popall, "popfront");
	var _pwin;
	if (_icon)
		_pwin = newT("div", _ft, "popwinicon");
	else
		_pwin = newT("div", _ft, "popwinnicon");
	if (_width)
		_pwin.style.width = _width + "px";
	function _doshow() { _popall.style.display = "block"; }
	function _dohide() { _popall.style.display = "none"; }
	_ret.doShow = _doshow;
	_ret.doHide = _dohide;
	newT("div", _pwin, "close", "").onclick = _dohide;
	if (_icon)
	{
		newT("div", _pwin, "icon", "<img src='"+_icon+"' />");
	}
	var _tit = newT("div", _pwin, "tit", _title);
	var _x0, _y0, _mx0, _my0;

	var _cont = newT("div", _pwin, "content");
	_doshow();
	if (_content)
		_content(_cont);
	var _tail = newT("div", _pwin, "tail", "");
	_ret.setAutoHide = function() { autoHide.add(_pwin, _popall); };
	return _ret;
}
popAlertIcon = _popAlertIcon;

function newBtn(_txt, _parent, _className)
{
	var ret;
	try {
		ret = document.createElement("input");
		ret.type="button";
		if (_parent) _parent.appendChild(ret);
		if (_className) ret.className = _className;
		if (_txt) ret.value = _txt;
	} catch (err) {}
	return ret;
}