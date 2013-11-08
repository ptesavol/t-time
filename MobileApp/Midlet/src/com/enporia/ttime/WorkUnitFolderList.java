package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class WorkUnitFolderList extends PersistentList
{
private static WorkUnitFolderList _instance=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static Class _iclass=null;

private static final String _prefix="wufolder";
private static Command CHOOSE_WORKUNITFOLDER = new Command(Props.get("workunitfolder_choose"), Command.ITEM, 0);
private static Command BACK_WORKUNITFOLDER = new Command(Props.get("common_back"), Command.BACK, 2);
private static Command REMOVE_WORKUNITFOLDER = new Command(Props.get("workunitfolder_remove"), Command.ITEM, 5); 
private static Command SEND_WORKUNITFOLDER = new Command(Props.get("workunitfolder_send"), Command.ITEM, 3);
private static Command SENDNEW_WORKUNITFOLDER = new Command(Props.get("workunitfolder_sendnew"), Command.SCREEN, 4);

private CommonRemoveForm removeform=null;

public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_midlet=midlet;
	_listener=commandlistener;
	try	{
		_iclass=Class.forName("com.enporia.util.FolderName");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}
	
private WorkUnitFolderList()
	{
	super( Props.get("workunitfolder_title"),_midlet,_listener,_iclass,_prefix);

	}
	
public static WorkUnitFolderList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new WorkUnitFolderList();
	return _instance;
	}	

public void show()
	{
	super.show();
	addScreenCommands();
	if (super.size()>0)
		addItemCommands();
	}
	
public void addScreenCommands()
	{
	addCommand(BACK_WORKUNITFOLDER);
	}
	
public void addItemCommands()
	{
	addCommand(CHOOSE_WORKUNITFOLDER);
	addCommand(REMOVE_WORKUNITFOLDER);
	addCommand(SEND_WORKUNITFOLDER);
	addCommand(SENDNEW_WORKUNITFOLDER);
	}
		
public void removeItemCommands()
	{
	removeCommand(CHOOSE_WORKUNITFOLDER);
	removeCommand(REMOVE_WORKUNITFOLDER);
	removeCommand(SEND_WORKUNITFOLDER);
	removeCommand(SENDNEW_WORKUNITFOLDER);
	}

public void onChooseWorkUnitFolder()
	{
	if (getSelectedIndex()!=size())
		{
		WorkUnitList.instance().setName(this.getSelectedString());
		WorkUnitList.instance().show();
		}
	}

public void onBackWorkUnitFolder()
	{
	WorkPlaceList.instance().show();
	}
	
public void onRemoveWorkUnitFolder()
	{
	if (super.getSelectedIndex()!=super.size())
		{
		MutableObject tobj=(MutableObject)super.elementAt(super.getSelectedIndex());
		removeform=tobj.getRemoveForm(tobj);
		removeform.setCommandListener(this);
		super.display.setCurrent(removeform);
		}
	}

public void onRemoveWorkUnitFolderOk()
	{
	if (getSelectedIndex()!=size())
		{
		WorkUnitList.instance().setName(this.getSelectedString());
		WorkUnitList.instance().deleteFromDisk();
		super.removeElementAt(getSelectedIndex());
		if (super.size()==0)
			removeItemCommands();
		
		goCurrent();
		}
	}
	
public void onSendWorkUnitFolder()
	{
	EmailForm.instance().setCommandListener(this);
	super.display.setCurrent(EmailForm.instance());
	EmailForm.instance().sendEmail(true);
	}
public void onSendNewWorkUnitFolder()
	{
	EmailForm.instance().setCommandListener(this);
	super.display.setCurrent(EmailForm.instance());
	EmailForm.instance().sendEmail(false);
	}	
/**
The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==CHOOSE_WORKUNITFOLDER || c == List.SELECT_COMMAND)
		this.onChooseWorkUnitFolder();
	
	if (c==BACK_WORKUNITFOLDER)
		this.onBackWorkUnitFolder();
	
	if (c==REMOVE_WORKUNITFOLDER)
		this.onRemoveWorkUnitFolder();
	
	if (c==SEND_WORKUNITFOLDER)
		this.onSendWorkUnitFolder();
	
	if (c==SENDNEW_WORKUNITFOLDER)
		this.onSendNewWorkUnitFolder();		
	
	if (c==CommonRemoveForm.OK)
		this.onRemoveWorkUnitFolderOk();
	
	if (c==EmailForm.EMAILFORM_OK || c==CommonRemoveForm.CANCEL)
		this.show();	
			
	super.commandAction(c,d);
	}

}
