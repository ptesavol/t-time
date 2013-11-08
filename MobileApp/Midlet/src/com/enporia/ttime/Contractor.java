package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.Image;
import java.io.*;

public class Contractor extends MutableObject 
{
private String email="";
private String code="";


public Contractor()
	{}

public Contractor(String name, String email)
	{
	this.name=name;
	this.email=email;
	}
/*		
public Contractor(String name, String email, String code, int id)
	{
	this.name=name;
	this.email=email;
	this.code=code;
	this.id=id;
	}
*/	
	
public void setEmail(String email)
	{
	this.email=email;
	}
/*
public void setCode(String code)
	{
	this.code=code;
	}
*/

	
public String getEmail()
	{
	return this.email;
	}

/*	
public String getCode()
	{
	return this.code;
	}
*/	

public String getRenderingName()
	{
	return this.name;
	}


public byte[] getBytes()
	{
	byte[] data=null;
	try	{
		super.output.writeUTF(this.name);
		super.output.writeUTF(this.email);
		super.output.writeUTF(this.code);	
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
	
public void setBytes(byte[] bytes)
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);
		this.name=dinput.readUTF();
		this.email=dinput.readUTF();
		this.code=dinput.readUTF();
		dinput.close();
		tinput.close();
		}
	catch (Exception e)	
		{
		System.out.println(e);
		}	
	}

public AddForm getAddForm() 
	{
	return AddContractorForm.instance();
	}
	
public ModifyForm getModifyForm(DataObject obj) 
	{
	return ModifyContractorForm.instance(obj);
	}
	
public CommonRemoveForm getRemoveForm(DataObject obj) 
	{
	return CommonRemoveForm.instance(obj, Props.get("remove_contractor_confirmation"));
	}

public ViewForm getViewForm(DataObject obj) 
	{
	return ViewContractorForm.instance(obj);
	}
	


}
