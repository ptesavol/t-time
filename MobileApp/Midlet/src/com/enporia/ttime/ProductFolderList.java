package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class ProductFolderList extends BasicList
{
private static ProductFolderList _instance=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static Class _iclass=null;

private static final String _prefix="prodllfolder";
private static Command CHOOSE_PRODUCTFOLDER = new Command(Props.get("productfolder_choose"), Command.BACK, 0);
private static Command BACK_PRODUCTFOLDER = new Command(Props.get("common_back"), Command.SCREEN, 2);

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
	
private ProductFolderList()
	{
	super( Props.get("productfolderlist_title"),_midlet,_listener,_iclass,_prefix);
	if (size()==0)
		addElement(new FolderName(Props.get("workplacelist_assumed")));
	}
	
public static ProductFolderList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new ProductFolderList();
	return _instance;
	}	

public void show()
	{
	super.show();
	
	}

public void addItemCommands()
	{
	super.addItemCommands();
	addCommand(CHOOSE_PRODUCTFOLDER);
	removeCommand(VIEW_ITEM);
	}
	

public void onChooseProductFolder()
	{
	if (getSelectedIndex()!=size())
		{
		ProductList.instance().setName(this.getSelectedString());
		ProductList.instance().show();
		}
	}

public void onBackProductFolder()
	{
	ProductList.instance().show();
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
		String tname=ProductList.instance().getName();
		String dname=getSelectedElement().getName();
		ProductList.instance().setName(dname);
		ProductList.instance().deleteFromDisk();
		super.onRemoveOk();
		if (dname.equals(tname))
			ProductList.instance().setName(Props.get("workplacelist_assumed"));
		else ProductList.instance().setName(tname);
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
	
	ProductList.instance().setName(tname);
	ProductList.instance().rename(nname);
	}

/**
The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==CHOOSE_PRODUCTFOLDER || c == List.SELECT_COMMAND)
		this.onChooseProductFolder();
	
	if (c==BACK_PRODUCTFOLDER)
		this.onBackProductFolder();
		
	super.commandAction(c,d);
	}

}
