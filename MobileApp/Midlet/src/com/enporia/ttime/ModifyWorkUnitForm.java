package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ModifyWorkUnitForm extends ModifyForm
{
private static ModifyWorkUnitForm _instance=null;
private WorkUnit workUnit=null;

private OwnStringItem workPlaceItem=null;
private OwnStringItem workTypeItem=null;
private DateField startTimeField=null;
private DateField endTimeField=null;
private TextField effectiveMinutesField=null;
private int effectiveIndex=-1;

private ModifyWorkUnitForm()
	{
	super(Props.get("modify_workunit_title"));
	this.workPlaceItem=new OwnStringItem("","");
	this.workTypeItem=new OwnStringItem("","");
	this.startTimeField=new DateField(Props.get("view_workunit_starttime"),DateField.DATE_TIME);
	this.endTimeField=new DateField(Props.get("view_workunit_endtime"),DateField.DATE_TIME);
	this.effectiveMinutesField=new TextField(Props.get("view_workunit_effectivetime"),"",4,TextField.NUMERIC);
	this.workPlaceItem.appendToForm(this);
	this.workTypeItem.appendToForm(this);
	this.append(this.startTimeField);
	this.append(this.endTimeField);
	this.effectiveIndex=this.append(this.effectiveMinutesField);
	}

public static ModifyWorkUnitForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ModifyWorkUnitForm();
	_instance.workUnit=(WorkUnit)obj;
	_instance.workPlaceItem.setText(_instance.workUnit.getWorkPlace());
	_instance.workTypeItem.setText(_instance.workUnit.getWorkType());
	//_instance.startTimeField.setDate(DateHelper.normalize(new Date(_instance.workUnit.getStartTime())));
	//_instance.endTimeField.setDate(DateHelper.normalize(new Date(_instance.workUnit.getEndTime())));
	
	_instance.startTimeField.setDate((new Date(_instance.workUnit.getStartTime())));
	_instance.endTimeField.setDate((new Date(_instance.workUnit.getEndTime())));
	
	if (_instance.workUnit.getEffectiveTime()!=-1)
		{
		if (_instance.effectiveIndex==-1)
			_instance.effectiveIndex= _instance.append(_instance.effectiveMinutesField);
		_instance.effectiveMinutesField.setString(DateHelper.getEffectiveMinutes(_instance.workUnit.getEffectiveTime()));
		}
	if (_instance.workUnit.getEffectiveTime()==-1 && _instance.effectiveIndex!=-1)
		{
		_instance.delete(_instance.effectiveIndex);
		_instance.effectiveIndex=-1;
		}
	return _instance;	
	}
	
public DataObject getObject()
	{
	//this.workUnit.setStartTime(DateHelper.deNormalize(new Date(this.workUnit.getStartTime()),this.startTimeField.getDate()).getTime());
	//this.workUnit.setEndTime(DateHelper.deNormalize(new Date(this.workUnit.getEndTime()),this.endTimeField.getDate()).getTime());
	
	this.workUnit.setStartTime(this.startTimeField.getDate().getTime());
	this.workUnit.setEndTime(this.endTimeField.getDate().getTime());
	
	long tlong=this.workUnit.getEffectiveTime();
	try	{
		if (this.effectiveIndex!=-1)
			{
			tlong=Long.parseLong(this.effectiveMinutesField.getString());
			tlong=tlong*60000;
			}
		}
	catch (Exception e) {}	
	this.workUnit.setEffectiveTime(tlong);
	return this.workUnit;
	}

}
