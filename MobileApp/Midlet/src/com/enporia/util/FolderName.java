package com.enporia.util;

import com.enporia.util.*;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.*;
import java.io.*;

public class FolderName extends MutableObject
{


public FolderName() {}

public FolderName(String name) 
	{
	super.name=name;
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
	return AddFolderNameForm.instance();
	}

public ModifyForm getModifyForm(DataObject obj) 
	{
	return ModifyFolderNameForm.instance(obj);
	}
	
public CommonRemoveForm getRemoveForm(DataObject obj) 
	{
	return CommonRemoveForm.instance(obj,Props.get("remove_foldername_confirmation") );
	}
	
public ViewForm getViewForm(DataObject obj) 
	{
	return null;
	}	

}
