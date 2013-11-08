package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class FindForm extends Form
{
class FindThread extends Thread
{
private String name="";
BasicList list=null;
BasicList folderlist;

public FindThread(String name, BasicList list, BasicList folderlist)
	{
	this.name=name;
	this.list=list;
	this.folderlist=folderlist;
	}
	
public void run()
	{
	FindForm.instance().removeCommand(FINDFORM_OK);
	statusItem.setText(Props.get("findform_searching")+ " "+name+" "+Props.get("findform_folder")+"\n");
	int startPlace=list.getSelectedIndex()+1;
	int startFolder=folderlist.indexOf(list.getName());
	String temp="";
	int result=-1;
	int currentFolder=startFolder;
	boolean firsttime=true;
	
	while(true)
		{
		temp=folderlist.elementAt(currentFolder).getName();
		statusItem.setText(temp);
		System.gc();
		list.setName(temp);
		
		result=list.indexOf(name, startPlace);
		if (result!=-1)
			{
			list.buildVisibleList();
			list.setSelectedIndex(result);
			list.show();
			return;
			}
		if (currentFolder==startFolder && !firsttime)
			break;
		firsttime=false;
		startPlace=0;
		currentFolder++;
		if ( currentFolder==folderlist.size() )
			currentFolder=0;
		}
	list.setSelectedIndex(startPlace);
	statusItem.setText(Props.get("findform_notfound")+"\n");
	statusItem.setText(name);
	FindForm.instance().addCommand(FINDFORM_OK);
	}
}
public static Command FINDFORM_OK =  new Command(Props.get("common_ok"), Command.OK, 1);
private static FindForm _instance=null;
private OwnStringItem statusItem=null;
private FindThread findThread=null;

public static FindForm instance()
	{
	if (_instance==null)
		_instance=new FindForm();
	return _instance;
	}

private FindForm()
	{
	super(Props.get("findform_title"));
	this.statusItem=new OwnStringItem("","");
	this.statusItem.appendToForm(this);
	}
	
public void find(String name, BasicList list, BasicList folderlist)
	{
	this.findThread=new FindThread(name, list, folderlist);
	this.findThread.start();
	}
}
