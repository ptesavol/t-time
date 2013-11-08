package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class WorkTypeList extends BasicList
{
private static WorkTypeList _instance=null;
private static Class _iclass=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;

private static final String _prefix="wtype";
private static Command CHOOSE_WORKTYPE =  new Command(Props.get("worktypelist_choose"), Command.BACK, 0);
private static Command BACK_WORKTYPE = new Command(Props.get("common_back"), Command.SCREEN, 2);
private static Command ONCE_WORKTYPE = new Command(Props.get("worktypelist_once"), Command.ITEM, 1);

private TimerForm timerForm=null;
private EffectiveTimeBox effectiveBox=null;

public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_midlet=midlet;
	_listener=commandlistener;
	try	{
		_iclass=Class.forName("com.enporia.ttime.WorkType");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}
	
private WorkTypeList()
	{
	super(Props.get("worktypelist_title"),_midlet,_listener,_iclass,_prefix);
	}
	
public static WorkTypeList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new WorkTypeList();
	
	return _instance;
	}	



public void addItemCommands()
	{
	super.addItemCommands();
	addCommand(CHOOSE_WORKTYPE);
	//addCommand(ONCE_WORKTYPE);
	//removeCommand(VIEW_ITEM);
	}

public void addScreenCommands()
	{
	super.addScreenCommands();
	addCommand(BACK_WORKTYPE);
	}
	
public void removeItemCommands()
	{
	super.removeItemCommands();
	removeCommand(CHOOSE_WORKTYPE);
	//removeCommand(ONCE_WORKTYPE);
	}	

public void startWork(long seedTime)
	{
	if (getSelectedIndex()!=size())
		{
		this.timerForm=TimerForm.instance((WorkPlace)WorkPlaceList.instance().getSelectedElement(), 
			(WorkType)getSelectedElement(),Worker.instance());
		this.timerForm.setCommandListener(this);
		super.display.setCurrent(this.timerForm);
		this.timerForm.startClock(seedTime);
		}
	}

/**
* Callback implementations
*/

public void onChooseWorkType()
	{
	long time=System.currentTimeMillis();
	ProgramState.instance().setStartTime(time);
	ProgramState.instance().setSessionStartTime(time);
	ProgramState.instance().setSelectedWorkType(getSelectedIndex());
	ProgramState.instance().setSelectedWorkPlace(WorkPlaceList.instance().getSelectedIndex());
	
	ProgramState.instance().save();
	this.startWork(0);
	}

public void onBackWorkType()	
	{
	WorkPlaceList.instance().show();
	}

public void onStopWork()
	{
	this.timerForm.stopClock();
	
	WorkUnit tunit=(WorkUnit)this.timerForm.getObject();
	this.saveWorkUnit(tunit);
	WorkPlaceList.instance().show();
	}

public void onWorkCall()
	{
	this.quitApplication();
	}

public void onSales()
	{
	this.timerForm.stopClock();
	WorkPlaceList.instance().show();
	}
	
public void onStopWorkModifying()
	{
	this.timerForm.stopClock();
	WorkUnit tunit=(WorkUnit)this.timerForm.getObject();
	this.effectiveBox=EffectiveTimeBox.instance(tunit.getEffectiveTime());
	this.effectiveBox.setCommandListener(this);
	super.display.setCurrent(this.effectiveBox);
	}			

public void onOnceWorkType()
	{
	if (getSelectedIndex()!=size())
		{
		WorkPlace tplace=(WorkPlace)WorkPlaceList.instance().getSelectedElement();
		WorkUnit tunit=new WorkUnit();
		tunit.setWorkPlace(tplace.getName());
		tunit.setWorkType(this.getSelectedString());
		tunit.setStartTime(System.currentTimeMillis());
		tunit.setEndTime(System.currentTimeMillis());
		tunit.setEffectiveTime(-1);
		tunit.setWorker(Worker.instance().getName());
		tunit.setContractor(tplace.getContractor());
		this.saveWorkUnit(tunit);
		WorkPlaceList.instance().show();
		}
	}

public void onEffectiveTimeOk()
	{
	WorkUnit tunit=(WorkUnit)this.timerForm.getObject();
	tunit.setEffectiveTime(this.effectiveBox.getEffectiveTime());
	long tlong=tunit.getStartTime();
	tlong+=(this.effectiveBox.getEffectiveTime());
	tunit.setEndTime(tlong);
	this.saveWorkUnit(tunit);
	WorkPlaceList.instance().show();
	}
	
private void saveWorkUnit(WorkUnit unit)
	{
	String daystring=DateHelper.getDayString();
	WorkUnitList.instance().setName(daystring);
	WorkUnitList.instance().insertElementAt(unit,0);
	FolderName fname=new FolderName(daystring);
	if ( WorkUnitFolderList.instance().size()==0 || 
		(WorkUnitFolderList.instance().size()>0 && 
		WorkUnitFolderList.instance().indexOf(daystring)==-1) )
		{
		WorkUnitFolderList.instance().insertElementAt(fname,0);
		}
	
	
	//WorkSessionUnit sunit = new WorkSessionUnit(unit, ProgramState.instance().getSessionStartTime());
	//WorkUnitList.instance().insertElementAt(sunit,0);
	
	ProgramState.instance().setStartTime(-1);
	ProgramState.instance().setSessionStartTime(-1);
	ProgramState.instance().save();
	}
/**
* The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==CHOOSE_WORKTYPE || c == List.SELECT_COMMAND)
		this.onChooseWorkType();
	
	if (c==BACK_WORKTYPE)
		this.onBackWorkType();
	
	if (c==ONCE_WORKTYPE)
		this.onOnceWorkType();
		
	if (c==TimerForm.STOP_WORK)
		this.onStopWork();
	
	if (c==TimerForm.WORK_CALL)
		this.onWorkCall();
			
	if (c==TimerForm.STOP_WORK_MODIFYING)
		this.onStopWorkModifying();
	
	if (c==EffectiveTimeBox.EFFECTIVE_TIME_OK)
		this.onEffectiveTimeOk();
	
	if (c==TimerForm.SALES)	
		this.onSales();
		
	super.commandAction(c,d);
	}	

}
