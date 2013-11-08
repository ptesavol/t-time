package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.*;
import java.io.*;

public class WorkPlace extends MutableObject
{
private String address="";
private String note="";
private String contractor="";
private String shortnote="";
private String info="";
private Long resetTime=new Long(0);										// 3.6.2010, J.V.

public WorkPlace()
	{}

public WorkPlace(String name, String address, String note, String contractor)
	{
	this.name=name;
	this.address=address;
	this.note=note;
	this.contractor=contractor;
	}

public WorkPlace(String name, String address, String note, String contractor, String shortnote, String info)
	{
	this.name=name;
	this.address=address;
	this.note=note;
	this.contractor=contractor;
	this.shortnote=shortnote;
	this.info=info;
	}

/*	
public WorkPlace(String name, String address, String note, String contractor, String shortnote, String info,int id)
	{
	this.name=name;
	this.address=address;
	this.note=note;
	this.contractor=contractor;
	this.shortnote=shortnote;
	this.info=info;
	this.id=id;
	}
*/

public void setAddress(String address)
	{
	this.address=address;
	}

public void setNote(String note)
	{
	this.note=note;
	}

public void setContractor(String contractor)
	{
	this.contractor=contractor;
	}
	
public void setShortNote(String shortnote)
	{
	this.shortnote=shortnote;
	}
	
public void setInfo(String info)	
	{
	this.info=info;
	}
					
public void setResetTime(Long resetTime)								// 3.6.2010, J.V.	
	{
	this.resetTime=resetTime;
	}	

public String getName()													// 22.8.2011
	{
	return this.name;
	}

public String getAddress()
	{
	return this.address;
	}
	
public String getNote()
	{
	return this.note;
	}

public String getContractor()
	{
	return this.contractor;
	}

public String getShortNote()
	{
	return this.shortnote;
	}

public String getShortNoteRendered()
	{
	if (this.shortnote.equals(""))
		return "";
	return ("| "+this.shortnote);
	}


public String getInfo()
	{
	return this.info;
	}
			
public long getResetTime()												// 3.6.2010, J.V.
	{
	return this.resetTime.longValue();
	}

// DataObject implementation

public String getRenderingName()
	{
	String ret=this.name;
	if (!Worker.instance().isNameFirst())
	   ret=this.address;
	if (!this.shortnote.equals(""))
		ret+="| "+this.shortnote;
	return ret;
	}
	
public Image getRenderingImage()
	{
	if (this.note!=null && !"".equals(this.note))
		return ImageLoader.instance().getNoteIcon();
	else return null;
	}

public void setBytes(byte[] bytes) 
	{
	try	{
		ByteArrayInputStream tinput=new ByteArrayInputStream(bytes);
		DataInputStream dinput=new DataInputStream(tinput);

		this.name=dinput.readUTF();
		this.address=dinput.readUTF();
		this.note=dinput.readUTF();
		this.contractor=dinput.readUTF();
		this.shortnote=dinput.readUTF();
		this.info=dinput.readUTF();
		this.resetTime = (dinput.available() > 0 ? dinput.readLong() : new Long(0));	// 3.6.2010, J.V.

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
		super.output.writeUTF(this.address);
		super.output.writeUTF(this.note);
		super.output.writeUTF(this.contractor);
		super.output.writeUTF(this.shortnote);
		super.output.writeUTF(this.info);
		super.output.writeLong(this.resetTime);							// 3.6.2010, J.V.		
		
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
	return AddWorkPlaceForm.instance();
	}

public ModifyForm getModifyForm(DataObject obj) 
	{
	return ModifyWorkPlaceForm.instance(obj);
	}
public CommonRemoveForm getRemoveForm(DataObject obj) 
	{
	return CommonRemoveForm.instance(obj,Props.get("remove_workplace_confirmation"));
	}
public ViewForm getViewForm(DataObject obj) 
	{
	return ViewWorkPlaceForm.instance(obj);
	}
}
