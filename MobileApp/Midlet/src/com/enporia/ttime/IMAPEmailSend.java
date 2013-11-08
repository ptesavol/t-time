package com.enporia.ttime;

import com.enporia.util.DataObject;
import com.enporia.util.Saveable;
import java.io.*;

public class IMAPEmailSend extends DataObject implements Saveable
{
	private static IMAPEmailSend _instance=null;
	private String email="";
	private boolean save=false;
	
public static IMAPEmailSend instance()
	{
	if (_instance==null)
		{
		DataObject tobj=IMAPEmailSendStore.instance().getSavedObject();
		if (tobj==null) _instance=new IMAPEmailSend();
		else _instance=(IMAPEmailSend)tobj;
		}
	return _instance;
	}
	
public IMAPEmailSend()
	{}

public IMAPEmailSend(String name)
	{
	this.name=name;
	}

public void setEmailAddress(String email)
	{
	this.email = email;
	}

public void setSaveEmailAddress(boolean save)
	{
	this.save = save;
	}

public String getEmailAddress()
	{
	return this.email;
	}

public boolean isSaveEmailAddress()
	{
	return this.save;
	}
	
public byte[] getBytes()
	{
	byte[] data=null;
	try	{
		super.output.writeUTF(this.name);
		super.output.writeUTF(this.email);
		super.output.writeBoolean(this.save);
		//super.output.writeBoolean(this.att_getmode);
		super.output.flush(); 
		data=super.byteoutput.toByteArray(); 
		}
	catch (Exception e)	
	{ System.out.println(e); }

	super.byteoutput.reset();	
	return data;
	}


public void setBytes(byte[] bytes)
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		this.name=dinput.readUTF();
		this.email=dinput.readUTF();
		this.save=dinput.readBoolean();
		//this.att_getmode=dinput.readBoolean();
		}
	catch (Exception e)	
	{ System.out.println(e); }	
	}

public void save()
	{
	IMAPEmailSendStore.instance().saveObject(this);
	_instance=this;
	}
}




