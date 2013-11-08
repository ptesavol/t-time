package com.enporia.ttime;



import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;

import java.util.*;

import com.enporia.util.*;

public class ModifyWorkTypeForm extends ModifyForm
{
private static ModifyWorkTypeForm _instance=null;
private static WorkType cont=null;
private TextField nameField=null;

private ChoiceGroup cycleGroup = null;
private DateField changeTimeField = null;
private ChoiceGroup changeToGroup = null;
private String[] workTypeNames = null;
private Vector workTypes = null;
private int changeToIndex = -1;


private ModifyWorkTypeForm()
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
	
public static ModifyWorkTypeForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ModifyWorkTypeForm();
	
	_instance.workTypes = WorkTypeList.instance().getElements();
	_instance.workTypeNames = WorkTypeList.instance().getElementRenderingNames();
	_instance.changeToGroup = new ChoiceGroup(Props.get("add_worktype_changeto"),Choice.EXCLUSIVE,_instance.workTypeNames,null);
	_instance.set(_instance.changeToIndex,_instance.changeToGroup);
	
	cont=(WorkType)obj;
	_instance.nameField.setString(cont.getName());
	
	if (cont.isChangeActive())
		_instance.cycleGroup.setSelectedIndex(1,true);
	else
		_instance.cycleGroup.setSelectedIndex(0,true);
	if (cont.getChangeTime()!=-1)
		_instance.changeTimeField.setDate(new Date(cont.getChangeTime()));
	
	int index = 0;
	WorkType temp = null;
	for (int i=0; i<_instance.workTypes.size(); i++)
		{
		temp = (WorkType)_instance.workTypes.elementAt(i);
		if (temp.getID()==cont.getChangeToId())
			{
			index=i;
			break;
			}
		}
	_instance.changeToGroup.setSelectedIndex(index,true);

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
