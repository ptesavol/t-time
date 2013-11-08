package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.*;
import java.io.*;

public class WorkType extends MutableObject
{
private long changeTime = -1;
private int changeToId = -1;
private boolean changeActive = false;	

public WorkType() {}
public WorkType(String name)
	{
	super.name=name;
	this.changeTime = -1;
	this.changeToId = -1;
	}
public WorkType(String name, long changeTime, int changeTarget, boolean changeActive) 
	{
	super.name=name;
	this.changeTime = changeTime;
	this.changeToId = changeTarget;
	this.changeActive = changeActive;
	}


// DataObject implementation

public String getRenderingName()
	{
	return this.name;
	}
	
public Image getRenderingImage() 
	{
	return null;
	}

public void setBytes(byte[] bytes) 
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		this.name=dinput.readUTF();
		this.changeTime = dinput.readLong();
		this.changeToId = dinput.readInt();
		this.changeActive = dinput.readBoolean();
		dinput.close();
		tinput.close();
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}
	}
	
public byte[] getBytes() 
	{
	byte[] data=null;
	try	{	
		super.output.writeUTF(this.name);
		super.output.writeLong(this.changeTime);
		super.output.writeInt(this.changeToId);
		super.output.writeBoolean(this.changeActive);
		
		super.output.flush(); 
		data=super.byteoutput.toByteArray(); 
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}
	super.byteoutput.reset();	
	return data;
	}


public AddForm getAddForm() 
	{
	return AddWorkTypeForm.instance();
	}

public ModifyForm getModifyForm(DataObject obj) 
	{
	return ModifyWorkTypeForm.instance(obj);
	}
	
public CommonRemoveForm getRemoveForm(DataObject obj) 
	{
	return CommonRemoveForm.instance(obj,Props.get("remove_worktype_confirmation") );
	}
	
public ViewForm getViewForm(DataObject obj) 
	{
	return ViewWorkTypeForm.instance(obj);
	}

public long getChangeTime() 
	{
	return changeTime;
	}

public void setChangeTime(long changeTime) 
	{
	this.changeTime = changeTime;
	}

public int getChangeToId() 
	{
	return changeToId;
	}

public void setChangeToId(int changeToId) 
	{
	this.changeToId = changeToId;
	}	

public boolean isChangeActive()
	{
	return this.changeActive;
	}

public void setChangeActive(boolean b)
	{
	this.changeActive = b;
	}
}
