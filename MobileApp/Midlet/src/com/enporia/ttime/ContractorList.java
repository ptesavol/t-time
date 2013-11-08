package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class ContractorList extends BasicList
{
private static ContractorList _instance=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static Class _iclass=null;
private static Command CONTRACTORLIST_BACK = new Command(Props.get("common_back"), Command.BACK, 2);
private static final String _prefix="contli";

private ContractorList() 
	{
	super(Props.get("contractorlist_title"),_midlet,_listener,_iclass,_prefix);
	}


public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_midlet=midlet;
	_listener=commandlistener;
	try	{
		_iclass=Class.forName("com.enporia.ttime.Contractor");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}

public void show()
	{
	super.show();
	addCommand(CONTRACTORLIST_BACK);
	}
	
public static ContractorList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new ContractorList();
	return _instance;
	}	

public void commandAction(Command c, Displayable d)
	{
	if (c==List.SELECT_COMMAND)
		super.onViewItem();
	
	if (c==CONTRACTORLIST_BACK)
		SettingsList.instance().show();
		
	super.commandAction(c,d);
	}
}
