package com.enporia.ttime;

import com.enporia.util.*;
import java.util.*;
import java.io.*;
import javax.microedition.rms.*;

public class ProgramState extends DataObject implements Saveable
{
private static ProgramState _instance=null;

private long startTime = -1;
private long travelStartTime= -1;
private int selectedWorkPlace = 0;
private int selectedWorkType = 0;
private String selectedWorkPlaceFolder = Props.get("workplacelist_assumed");
private String selectedProductFolder = Props.get("productlist_assumed");
private int travelStartMeter=0;
private boolean timerActivated=false;
private boolean travelActivated=false;
private boolean storageActivated=false;
private long sessionStartTime = -1;

public static ProgramState instance()
	{
	if (_instance==null)
		{
		DataObject tobj=ProgramStateStore.instance().getSavedObject();
		if (tobj==null)
			_instance=new ProgramState();
		else _instance=(ProgramState)tobj;
		}
	return _instance;
	}

public ProgramState()
	{}
	

	
public boolean isEmpty()
	{
	if (this.startTime==-1)
		return true;
	else return false;
	}

public boolean isTravelling()
	{
	if (this.travelStartTime==-1)
		return false;
	else return true;
	}

public void setID(int id)
	{
	this.id=id;
	}

public void setStartTime(long startTime)
	{
	this.startTime=startTime;
	}

public void setTravelStartTime(long time)
	{
	this.travelStartTime=time;
	}
	
public void setSelectedWorkPlace(int selectedWorkPlace)
	{
	this.selectedWorkPlace = selectedWorkPlace;
	}

public void setSelectedWorkType(int selectedWorkType)
	{
	this.selectedWorkType = selectedWorkType;
	}
	
public void setSelectedWorkPlaceFolder(String selectedWorkPlaceFolder)
	{
	this.selectedWorkPlaceFolder = selectedWorkPlaceFolder;
	}

public void setSelectedProductFolder(String selectedProductFolder)
	{
	this.selectedProductFolder = selectedProductFolder;
	}
	
public void setTravelStartMeter(int meter)
	   {
	   this.travelStartMeter=meter;
	   }	
public int getID()
	{
	return this.id;
	}

public long getStartTime()
	{
	return this.startTime;
	}
	
public long getTravelStartTime()
	{
	return this.travelStartTime;
	}
	
public int getTravelStartMeter()
	{
	return this.travelStartMeter;
	}

public int getSelectedWorkPlace()
	{
	return this.selectedWorkPlace;
	}

public int getSelectedWorkType()
	{
	return this.selectedWorkType;
	}
		
public String getSelectedWorkPlaceFolder()
	{
	return this.selectedWorkPlaceFolder;
	}	

public String getSelectedProductFolder()
	{
	return this.selectedProductFolder;
	}	
	
public boolean  isTimerActivated()
	{
	return this.timerActivated;
	}
	
public void setTimerActivated(boolean val)
	{
	this.timerActivated=val;
	}	

public boolean  isTravelActivated()
	{
	return this.travelActivated;
	}
	
public void setTravelActivated(boolean val)
	{
	this.travelActivated=val;
	}	

public boolean isStorageActivated()
	{
	return this.storageActivated;
	}
	
public void setStorageActivated(boolean val)
	{
	this.storageActivated=val;
	}

public long getSessionStartTime()
	{
	return this.sessionStartTime;
	}
	
public void setSessionStartTime(long time)
	{
	this.sessionStartTime = time;
	}

public void setBytes(byte[] bytes)
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		this.startTime=dinput.readLong();
		this.selectedWorkPlace=dinput.readInt();
		this.selectedWorkType=dinput.readInt();
		this.selectedWorkPlaceFolder=dinput.readUTF();
		this.selectedProductFolder=dinput.readUTF();
		this.travelStartTime=dinput.readLong();
		this.travelStartMeter=dinput.readInt();
		this.timerActivated=dinput.readBoolean();
		this.travelActivated=dinput.readBoolean();
		this.storageActivated=dinput.readBoolean();
		this.sessionStartTime=dinput.readLong();
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
		super.output.writeLong(this.startTime);
		super.output.writeInt(this.selectedWorkPlace);	
		super.output.writeInt(this.selectedWorkType);	
		super.output.writeUTF(this.selectedWorkPlaceFolder);	
		super.output.writeUTF(this.selectedProductFolder);	
		super.output.writeLong(this.travelStartTime);
		super.output.writeInt(this.travelStartMeter);
		super.output.writeBoolean(this.timerActivated);
		super.output.writeBoolean(this.travelActivated);
		super.output.writeBoolean(this.storageActivated);
		super.output.writeLong(this.sessionStartTime);
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

public void save()
	{
	ProgramStateStore.instance().saveObject(this);
	_instance=this;
	}
}
