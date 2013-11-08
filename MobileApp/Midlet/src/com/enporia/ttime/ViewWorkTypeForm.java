package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ViewWorkTypeForm extends ViewForm
{
private static ViewWorkTypeForm _instance=null;

private OwnStringItem nameItem = null;
private OwnStringItem explanationItem = null;


private ViewWorkTypeForm()
	{
	super(Props.get("view_worktype_title"));
	this.nameItem=new OwnStringItem("","");
	this.explanationItem = new OwnStringItem("","");
	
	this.nameItem.appendToForm(this);
	this.explanationItem.appendToForm(this);
	}

public static ViewWorkTypeForm instance(DataObject obj)
	{
	WorkType ttype=(WorkType)obj;
	
	if (_instance==null)
		_instance=new ViewWorkTypeForm();
	
	
	_instance.nameItem.setText(ttype.getRenderingName()+"\n"); 
	String temp="";
	if (ttype.isChangeActive())
		{
		WorkType typeTwo = (WorkType) WorkTypeList.instance().getElementById(ttype.getChangeToId());
		if (typeTwo!=null)
			{
			temp = Props.get("view_worktype_explanation");
			temp += " "+typeTwo.getRenderingName()+" "+Props.get("common_clock")+" ";
			temp += DateHelper.getHoursAndMinutes(ttype.getChangeTime());
			}
		}
	_instance.explanationItem.setText(temp+"\n"); 
	return _instance;
	}
}
