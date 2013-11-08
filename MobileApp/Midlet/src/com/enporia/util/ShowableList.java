package com.enporia.util;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.util.*;
import java.io.*;

public class ShowableList implements CommandListener
{
protected String name="";
protected MIDlet parentmidlet=null;
protected CommandListener parentlistener=null;
protected List list=null;
protected Display display=null;

public static Command DESTROY_APP = new Command("", Command.EXIT, 1);

public ShowableList(String name, MIDlet parentmidlet, CommandListener parentlistener)
	{
	
	this.name=name;
	this.parentmidlet=parentmidlet;
	this.parentlistener=parentlistener;
	this.display=Display.getDisplay(parentmidlet);
	}
	
public ShowableList(String name, MIDlet parentmidlet, CommandListener parentlistener, String[] content)
	{
	this.name=name;
	this.parentmidlet=parentmidlet;
	this.parentlistener=parentlistener;
	this.display=Display.getDisplay(parentmidlet);
	this.list=new List(this.name, List.IMPLICIT, content, null);
	this.list.setCommandListener(this);
	}
		
public void setName(String name)
	{
	this.name=name;
	}
/**
Returns the name of this list.
@return The name of this list
*/
public String getName()
	{
	return this.name;
	}
	
/**
*Sets this list to the current displayable
*/

public void goCurrent()
	{
	if (this.list==null)
		{
		this.show();
		return;
		}
	else	{
		this.display.setCurrent(this.list);
		}
	}

public void addCommand(Command command)
	{
	if (this.list!=null)
		{
		this.list.addCommand(command);
		}
	}

public void removeCommand(Command command)
	{
	if (this.list!=null)
		{
		this.list.removeCommand(command);
		}
	}
/**
Shows and creates this list.
*/
public void show()
	{
	if (this.list==null)
		this.list=new List(getRenderingName(), List.IMPLICIT);
	this.list.setTitle(getRenderingName());
	
	this.list.setCommandListener(this);
	this.display.setCurrent(this.list);
	}


/**
The CommandListener implementation, calls parenlistener by default
*/

public void commandAction(Command c, Displayable d)
	{
	this.parentlistener.commandAction(c,d);
	}

/**
Gets the selected index of this list
@return The selected index
*/

public int getSelectedIndex()
	{
	return this.list.getSelectedIndex();
	}	

public String getSelectedString()
	{
	return this.list.getString(this.list.getSelectedIndex());
	}

public void append(String stringpart, Image imagepart)
	{
	this.list.append(stringpart, imagepart);
	}
		
public void set(int elementnum,String stringpart, Image imagepart)
	{
	this.list.set(elementnum, stringpart, imagepart);
	}

public void insert(int elementnum,String stringpart, Image imagepart)
	{
	if (this.list.size()>0)
		this.list.insert(elementnum, stringpart, imagepart);
	else this.list.append(stringpart, imagepart);
	}
	
public String getString(int i)
	{
	return this.list.getString(i);
	}

public Image getImage(int i)
	{
	return this.list.getImage(i);
	}

public void delete(int i)
	{
	this.list.delete(i);
	}
	
public String[] getStrings()
	{
	String[] ret = new String[this.list.size()-1];
	for (int i=0; i<(this.list.size()-1); i++)
		ret[i]=this.list.getString(i);
	return ret;
	}	

public String getRenderingName()
	{
	return name;
	}

public void setSelectedIndex(int i)
	{
	this.list.setSelectedIndex(i,true);
	}
	
public void quitApplication()
	{
	parentlistener.commandAction(DESTROY_APP, this.list);
	}
}
