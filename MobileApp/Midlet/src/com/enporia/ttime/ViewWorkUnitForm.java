package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ViewWorkUnitForm extends ViewForm
{
private static ViewWorkUnitForm _instance=null;


private OwnStringItem workPlaceItem=null;
private OwnStringItem contractorItem=null;
private OwnStringItem workTypeItem=null;
private OwnStringItem startTimeItem=null;
private OwnStringItem endTimeItem=null;
private OwnStringItem effectiveTimeItem=null;

private ViewWorkUnitForm()
	{
	super(Props.get("view_workunit_title"));
	this.workPlaceItem=new OwnStringItem("","");
	this.contractorItem=new OwnStringItem(Props.get("view_workunit_contractor")+"\n","");
	this.workTypeItem=new OwnStringItem("","");

	startTimeItem=new OwnStringItem(Props.get("view_workunit_starttime")+"\n","");
	endTimeItem=new OwnStringItem(Props.get("view_workunit_endtime")+"\n","");
	effectiveTimeItem=new OwnStringItem(Props.get("view_workunit_effectivetime")+"\n","");

	this.workPlaceItem.appendToForm(this);
	this.workTypeItem.appendToForm(this);
	this.startTimeItem.appendToForm(this);
	this.endTimeItem.appendToForm(this);
	this.effectiveTimeItem.appendToForm(this);
	this.contractorItem.appendToForm(this);
	}

public static ViewWorkUnitForm instance(DataObject obj)
	{

	WorkUnit tunit=(WorkUnit)obj;
	if (_instance==null)
		_instance=new ViewWorkUnitForm();
	
	_instance.workPlaceItem.setText(tunit.getWorkPlace()+"\n");
	_instance.contractorItem.setText(tunit.getContractor()+"\n");
	_instance.workTypeItem.setText(tunit.getWorkType()+"\n");
	_instance.startTimeItem.setText(DateHelper.getDateAsString(tunit.getStartTime())+"\n");
	_instance.endTimeItem.setText(DateHelper.getDateAsString(tunit.getEndTime())+"\n");
	_instance.effectiveTimeItem.setText(DateHelper.getEffectiveMinutes(tunit.getEffectiveTime()));
	return _instance;
	}
}
