package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class WorkPlaceFolderList extends BasicList
{
private static WorkPlaceFolderList _instance=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static Class _iclass=null;

private static final String _prefix="wplfolder";
private static Command CHOOSE_WORKPLACEFOLDER = new Command(Props.get("workplacefolder_choose"), Command.BACK, 0);
private static Command BACK_WORKPLACEFOLDER = new Command(Props.get("common_back"), Command.SCREEN, 2);

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
	
private WorkPlaceFolderList()
	{
	super( Props.get("workplacefolderlist_title"),_midlet,_listener,_iclass,_prefix);
	if (size()==0)
		addElement(new FolderName(Props.get("workplacelist_assumed")));
	}
	
public static WorkPlaceFolderList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new WorkPlaceFolderList();
	return _instance;
	}	

public void show()
	{
	super.show();
	
	}

public void addItemCommands()
	{
	super.addItemCommands();
	addCommand(CHOOSE_WORKPLACEFOLDER);
	removeCommand(VIEW_ITEM);
	}
	

public void onChooseWorkPlaceFolder()
	{
	if (getSelectedIndex()!=size())
		{
		WorkPlaceList.instance().setName(this.getSelectedString());
		WorkPlaceList.instance().show();
		}
	}

public void onBackWorkPlaceFolder()
	{
	WorkPlaceList.instance().show();
	}

public void onRemoveItem()
	{
	if (super.getSelectedIndex()!=super.size())
		{
		if (getSelectedString().equals(Props.get("workplacelist_assumed")))
			return;
		super.onRemoveItem();
		}
	}
public void onRemoveOk()
	{
	
	if (super.getSelectedIndex()!=super.size())
		{
		String tname=WorkPlaceList.instance().getName();
		String dname=getSelectedElement().getName();
		WorkPlaceList.instance().setName(dname);
		WorkPlaceList.instance().deleteFromDisk();
		super.onRemoveOk();
		if (dname.equals(tname))
			WorkPlaceList.instance().setName(Props.get("workplacelist_assumed"));
		else WorkPlaceList.instance().setName(tname);
		}
	
	}
	
public void onModifyItem()
	{
	if (super.getSelectedIndex()!=super.size())
		{
		if (getSelectedString().equals(Props.get("workplacelist_assumed")))
			return;
		super.onModifyItem();
		}
	}
		
public void onModifyOk()
	{
	String tname=getSelectedElement().getName();
	super.onModifyOk();
	String nname=getSelectedElement().getName();
	
	WorkPlaceList.instance().setName(tname);
	WorkPlaceList.instance().rename(nname);
	}

/**
The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==CHOOSE_WORKPLACEFOLDER || c == List.SELECT_COMMAND)
		this.onChooseWorkPlaceFolder();
	
	if (c==BACK_WORKPLACEFOLDER)
		this.onBackWorkPlaceFolder();
		
	super.commandAction(c,d);
	}

}
