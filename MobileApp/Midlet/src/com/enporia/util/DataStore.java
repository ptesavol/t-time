package com.enporia.util;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.util.*;
import java.io.*;

/**
*This class encapsulates all the rms activity in the framework
*/

public class DataStore
{
protected Class itemclass=null;
private RecordStore store=null;
private String name="";

protected static ByteArrayOutputStream byteoutput=new ByteArrayOutputStream();
protected static DataOutputStream output=new DataOutputStream(byteoutput);

public DataStore(String name, Class itemc)
	{
	this.name=name;
	//this.itemclass=itemc;
	}

public void setName(String name)
	{
	if (this.name!=null && this.name.equals(name))
		return;
	this.name=name;
	this.close();
	this.open();
	}
	
public void deleteFromDisk()
	{
	this.close();
	try	{
		RecordStore.deleteRecordStore(name);
		this.name=null;
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}	

public void open()
	{
	try	{
		this.store=RecordStore.openRecordStore(name,true);
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}

public void close()
	{
	if (this.store!=null)
		{
		try 	{
			this.store.closeRecordStore();
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}	
		this.store=null;
		}
	}

public DataObject getObject(int id)
	{
	try	{
		
		byte[] data=this.store.getRecord(id);
		if (data==null)
			return null;
		
		ByteArrayInputStream tinput=new ByteArrayInputStream(data);
		DataInputStream dinput=new DataInputStream(tinput);
		String className=dinput.readUTF();
		byte[] data2=new byte[dinput.available()];
		int boff=data.length-dinput.available();
		dinput.close();
		tinput.close();
		
		for (int i=0; i<data2.length; i++)
			data2[i]=data[i+boff];
		
		//DataObject o=(DataObject)itemclass.newInstance();
		//System.out.println(className);
		DataObject o=(DataObject)Class.forName(className).newInstance();
		
		o.setBytes(data2);
		o.setID(id);
		return o;
		}
	catch (Exception e)
		{
		e.printStackTrace();
		return null;
		}
	}	

public void setObject(DataObject obj, int id)
	{
	try	{
		byte[] data=obj.getBytes();	
		String className=obj.getClass().getName();
		//System.out.println(className);
		this.output.writeUTF(className);
		this.output.write(data,0, data.length);
		this.output.flush(); 
		byte[] data2=this.byteoutput.toByteArray(); 
		this.byteoutput.reset();
		
			
		this.store.setRecord(id, data2, 0, data2.length);
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

public int addObject(DataObject obj)
	{
	int ret=-1;
	try	{
		byte[] data=obj.getBytes();	
		String className=obj.getClass().getName();
		this.output.writeUTF(className);
		this.output.write(data,0, data.length);
		this.output.flush(); 
		byte[] data2=this.byteoutput.toByteArray(); 
		this.byteoutput.reset();
		
		
		ret=this.store.addRecord(data2,0,data2.length);
		obj.setID(ret);
		}
	catch (Exception e)
		{
		e.printStackTrace();	
		}	
	return ret;
	}

public void deleteObject(int id)
	{
	try 	{
		this.store.deleteRecord(id);
		}
	catch (Exception e)
		{
		e.printStackTrace();	
		}	
	}

/**
*Saves the object as the only object in this recordstore
*/
public void saveObject(DataObject obj)
	{
	try	{
		byte[] data=obj.getBytes();
		String className=obj.getClass().getName();
		//System.out.println(className);
		this.output.writeUTF(className);
		this.output.write(data,0, data.length);
		this.output.flush(); 
		byte[] data2=this.byteoutput.toByteArray(); 
		this.byteoutput.reset();
		
		RecordEnumeration iter=this.store.enumerateRecords(null,null,false);
		try	{
			this.store.setRecord(iter.nextRecordId(),data2,0,data2.length);
			}
		catch (Exception e) 
			{
			this.store.addRecord(data2,0,data2.length);		
			}	
		}
	catch (Exception e) 
		{
		e.printStackTrace();
		}	
	
	}

public DataObject getSavedObject()
	{
	DataObject ret=null;
	try	{
		RecordEnumeration iter=this.store.enumerateRecords(null,null,false);
		ret=this.getObject(iter.nextRecordId()); 
		}
	catch (Exception e) 
		{
		return null;
		//e.printStackTrace();
		}	
	return ret;
	}

}
