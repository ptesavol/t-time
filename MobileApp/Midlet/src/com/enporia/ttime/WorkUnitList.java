package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class WorkUnitList extends BasicList
{
private static WorkUnitList _instance=null;
private static Class _iclass=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static final String _prefix="wrkunitli";

private static Command BACK_WORKUNIT = new Command(Props.get("common_back"), Command.BACK, 2);

//private TimerForm timerForm=null;

public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_midlet=midlet;
	_listener=commandlistener;
	try	{
		_iclass=Class.forName("com.enporia.ttime.WorkUnit");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}
	
private WorkUnitList()
	{
	super("",_midlet,_listener,_iclass,_prefix);
	}
	
public static WorkUnitList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new WorkUnitList();
	
	return _instance;
	}	

public void addItemCommands()
	{
	super.addItemCommands();
	}

public void addScreenCommands()
	{
	super.addScreenCommands();
	addCommand(BACK_WORKUNIT);
	removeCommand(ADD_ITEM);
	}
	
public void removeItemCommands()
	{
	super.removeItemCommands();
	}	

public String getRenderingName()
	{
	return name;
	}

// Overrides superclass
public void onRemoveOk() 
	{
	super.onRemoveOk(); 
	if (super.size()==0)
		{
		int i=WorkUnitFolderList.instance().indexOf(this.getName());
		if (i!=-1)
			WorkUnitFolderList.instance().removeElementAt(i);
		}
	}

/**
* Callback implementations
*/


public void onBackWorkUnit()	
	{
	WorkUnitFolderList.instance().show();
	}
	
/**
* The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==BACK_WORKUNIT)
		this.onBackWorkUnit();
	if (c == List.SELECT_COMMAND)
		{
		super.onViewItem();
		}
	super.commandAction(c,d);
	}	

}
