package com.enporia.util;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

/**
A persistent MIDP list component with basic operations
*/

public class BasicList extends PersistentList implements CommandListener
{
protected static Command ADD_ITEM = new Command(Props.get("menu_add"), Command.ITEM, 10);
protected static Command REMOVE_ITEM = new Command(Props.get("menu_remove"), Command.ITEM, 10);
protected static Command MODIFY_ITEM = new Command(Props.get("menu_modify"), Command.ITEM, 10);
protected static Command UP_ITEM = new Command(Props.get("menu_up"), Command.ITEM, 10);
protected static Command DOWN_ITEM = new Command(Props.get("menu_down"), Command.ITEM, 10);
protected static Command VIEW_ITEM = new Command(Props.get("menu_view"), Command.ITEM, 3);

private AddForm addform=null;
private CommonRemoveForm removeform=null;
private ModifyForm modifyform=null;
private ViewForm viewform=null;
private int activeIndex=-1;

/**
Constructor 
*/

public BasicList(String name, MIDlet parentmidlet, CommandListener parentlistener, Class itemclass, String pprefix)
	{
	super(name, parentmidlet, parentlistener, itemclass, pprefix);
	}

/**
Shows this list.
*/

public void show()
	{
	super.show();
	addScreenCommands();
	if (super.size()>0)
		addItemCommands();
	}
	
public void addScreenCommands()
	{
	addCommand(ADD_ITEM);
	}
	
public void addItemCommands()
	{
	addCommand(VIEW_ITEM);
	addCommand(REMOVE_ITEM);
	addCommand(MODIFY_ITEM);
	addCommand(UP_ITEM);
	addCommand(DOWN_ITEM);
	}
	
public void removeItemCommands()
	{
	removeCommand(VIEW_ITEM);
	removeCommand(REMOVE_ITEM);
	removeCommand(MODIFY_ITEM);
	removeCommand(UP_ITEM);
	removeCommand(DOWN_ITEM);
	}		

/**
Callback implementations
*/
public void onViewItem() 
	{
	if (super.getSelectedIndex()!=super.size())
		{
		MutableObject tobj=(MutableObject)super.elementAt(super.getSelectedIndex());
		viewform=tobj.getViewForm(tobj);
		viewform.setCommandListener(this);
		super.display.setCurrent(viewform);
		}
	}
	
public void onAddItem() 
	{
	this.activeIndex=super.getSelectedIndex();
	try	{
		addform=((MutableObject)super.itemclass.newInstance()).getAddForm();
		if (addform!=null)	
			{
			addform.setCommandListener(this);
			super.display.setCurrent(addform);
			}
		}
	catch (Exception e) { System.out.println(e);}
	}

public void onRemoveItem() 
	{
	this.activeIndex=super.getSelectedIndex();
	
	if (this.activeIndex!=super.size())
		{
		MutableObject tobj=(MutableObject)super.elementAt(this.activeIndex);
		removeform=tobj.getRemoveForm(tobj);
		removeform.setCommandListener(this);
		super.display.setCurrent(removeform);
		}
	}

public void onModifyItem() 
	{
	this.activeIndex=super.getSelectedIndex();
	
	if (this.activeIndex!=super.size())
		{
		MutableObject tobj=(MutableObject)super.elementAt(this.activeIndex);
		//System.out.println(tobj.getClass().getName());
		modifyform=tobj.getModifyForm(tobj);
		modifyform.setCommandListener(this);
		super.display.setCurrent(modifyform);
		}
	
	} 

public void onUpItem() 
	{
	if (super.getSelectedIndex()!=-1 && super.getSelectedIndex()!=0 
		&& super.getSelectedIndex()!=super.size() )
		{
		super.swapElements(super.getSelectedIndex(),super.getSelectedIndex()-1);
		}
	}

public void onDownItem() 
	{
	if (super.getSelectedIndex()!=-1 && super.getSelectedIndex()!= super.size()
		&& super.getSelectedIndex()!=super.size()-1 )
		{
		super.swapElements(super.getSelectedIndex(),super.getSelectedIndex()+1);
		}
	}
	

public void onAddOk() 
	{
	super.insertElementAt(this.addform.getObject(),this.activeIndex);
	if (super.size()==1)
		addItemCommands();
	super.goCurrent();
	}
	
public void onModifyOk() 
	{
	super.setElementAt(this.modifyform.getObject(),this.activeIndex);
	super.goCurrent();
	}

public void onRemoveOk() 
	{
	super.removeElementAt(this.activeIndex);
	if (super.size()==0)
		removeItemCommands();
	super.goCurrent();
	}

public void onOperationCancel()
	{
	super.goCurrent();
	}
/**
The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==VIEW_ITEM)
		this.onViewItem();
		
	if (c==ADD_ITEM)
		this.onAddItem();
		
	if (c==REMOVE_ITEM)
		this.onRemoveItem();
		
	if (c==MODIFY_ITEM)
		this.onModifyItem();
	
	if (c==UP_ITEM)
		this.onUpItem();
			
	if (c==DOWN_ITEM)
		this.onDownItem();
	
	if (c==CommonRemoveForm.OK)
		this.onRemoveOk();
	
	if (c==ModifyForm.OK)
		this.onModifyOk();
	
	if (c==AddForm.OK)
		this.onAddOk();				
	
	if (c==AddForm.CANCEL || c==CommonRemoveForm.CANCEL || c==ModifyForm.CANCEL || c==ViewForm.OK || c==ViewForm.CANCEL) 	
		this.onOperationCancel();
			
	super.commandAction(c,d);
	}

}
