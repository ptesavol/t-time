package com.enporia.ttime;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;

import com.enporia.util.*;

public class IMAPEmail extends DataObject implements Saveable
{
private static IMAPEmail _instance=null;
private boolean storeusername=false;
private String stored_username="";
private boolean storepassword=false;
private String stored_password="";
//private boolean att_getmode=false;

public static IMAPEmail instance()
	{
	if (_instance==null)
		{
		DataObject tobj=IMAPEmailStore.instance().getSavedObject();
		if (tobj==null) _instance=new IMAPEmail();
		else _instance=(IMAPEmail)tobj;
		}
	return _instance;
	}
	
public IMAPEmail()
	{}

public IMAPEmail(String name)
	{
	this.name=name;
	}

public void setStoreUsername(boolean storeusername)
	{ this.storeusername = storeusername; }

public void setStored_Username(String stored_username)
	{ this.stored_username = stored_username; }

public void setStorePassword(boolean storepassword)
{ this.storepassword = storepassword; }

public void setStored_Password(String stored_password)
{ this.stored_password = stored_password; }

/*public void setAtt_GetMode(boolean att_getmode)
{ this.att_getmode = att_getmode; }*/

public boolean isStoreUsername()
	{ return this.storeusername; }

public String getStored_Username()
	{ return this.stored_username; }

public boolean isStorePassword()
{ return this.storepassword; }

public String getStored_Password()
{ return this.stored_password; }

/*public boolean getAtt_GetMode()
{ return this.att_getmode; }*/

public byte[] getBytes()
	{
	byte[] data=null;
	try	{
		super.output.writeUTF(this.name);
		super.output.writeBoolean(this.storeusername);
		super.output.writeUTF(this.stored_username);
		super.output.writeBoolean(this.storepassword);
		super.output.writeUTF(this.stored_password);
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
		this.storeusername=dinput.readBoolean();
		this.stored_username=dinput.readUTF();
		this.storepassword=dinput.readBoolean();
		this.stored_password=dinput.readUTF();
		//this.att_getmode=dinput.readBoolean();
		}
	catch (Exception e)	
	{ System.out.println(e); }	
	}

public void save()
	{
	IMAPEmailStore.instance().saveObject(this);
	_instance=this;
	}
}