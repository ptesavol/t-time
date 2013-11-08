package com.enporia.ttime;


import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;

import java.util.*;
import com.enporia.util.*;

public class AddWorkTypeForm extends AddForm
{
private static AddWorkTypeForm _instance=null;
private TextField nameField=null;

private ChoiceGroup cycleGroup = null;
private DateField changeTimeField = null;
private ChoiceGroup changeToGroup = null;
private String[] workTypeNames = null;
private Vector workTypes = null;
private int changeToIndex = -1;

private AddWorkTypeForm()
	{
	super(Props.get("add_worktype_title"));
	

	this.nameField = new TextField(Props.get("add_worktype_name"),"",20,TextField.ANY);
	this.append(this.nameField);
	
	this.workTypes = WorkTypeList.instance().getElements();
	
	String[] yesnonames={Props.get("common_no"),Props.get("common_yes")};
	this.changeTimeField = new DateField(Props.get("add_worktype_changetime"),DateField.TIME);
	Calendar calendar = Calendar.getInstance();
	calendar.setTime(DateHelper.normalize(new Date(System.currentTimeMillis())));
	this.changeTimeField.setDate(calendar.getTime());
	
	this.cycleGroup = new ChoiceGroup(Props.get("add_worktype_cycle"),Choice.EXCLUSIVE,yesnonames,null);
	this.workTypeNames = WorkTypeList.instance().getElementRenderingNames();
	this.changeToGroup = new ChoiceGroup(Props.get("add_worktype_changeto"),Choice.EXCLUSIVE,this.workTypeNames,null);
	this.append(this.cycleGroup);
	this.append(this.changeTimeField);
	this.changeToIndex = this.append(this.changeToGroup);
	}
	
public static AddWorkTypeForm instance()
	{
	if (_instance==null)
		_instance=new AddWorkTypeForm();
	else 
		{
		_instance.workTypes = WorkTypeList.instance().getElements();
		_instance.workTypeNames = WorkTypeList.instance().getElementRenderingNames();
		_instance.changeToGroup = new ChoiceGroup(Props.get("add_worktype_changeto"),Choice.EXCLUSIVE,_instance.workTypeNames,null);
		_instance.set(_instance.changeToIndex,_instance.changeToGroup);
		}
	_instance.nameField.setString("");
	
	return _instance;	
	}	
public DataObject getObject()
	{
	boolean act = false;
	if (this.cycleGroup.getSelectedIndex()==1)
		act = true;
	long cTime = -1;
	int cTarget = -1;
	if (this.workTypes!=null && this.workTypes.size()>0)
		{
		cTarget =((WorkType)this.workTypes.elementAt(this.changeToGroup.getSelectedIndex())).getID(); 
		}
	if (this.changeTimeField.getDate()!=null)
		cTime = this.changeTimeField.getDate().getTime();
	return new WorkType(this.nameField.getString(),cTime,cTarget,act);
	}
}
