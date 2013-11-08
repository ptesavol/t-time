package com.enporia.ttime;


import com.enporia.util.*;

import java.util.*;
import javax.microedition.lcdui.*;
import java.io.*;
import java.util.*;

public class WorkUnit extends MutableObject implements Sendable
{
protected static Calendar cal=Calendar.getInstance();
protected static Date dat=new Date();
public final static byte[] DOT=".".getBytes();
public final static byte[] SPACE=" ".getBytes();
public final static byte[] TAB="	".getBytes();
public final static byte[] LF="\n".getBytes();
public final static byte[] ONCE="kerta".getBytes();

private String workPlace="";
private String workType="";
private long startTime=-1;
private long endTime=-1;
private long effectiveTime=0;
private String worker="";
private String contractor="";
private int id=-1;
private boolean sent=false;
private String customerListName="";

public WorkUnit()
	{}

public WorkUnit(String workPlace, String workType, long startTime, long endTime, long effectiveTime, String worker, String contractor,int id)
	{
	this.workPlace=workPlace;
	this.workType=workType;
	this.startTime=startTime;
	this.endTime=endTime;
	this.effectiveTime=effectiveTime;
	this.worker=worker;
	this.contractor=contractor;
	this.id=id;
	}

public WorkUnit(String workPlace, String workType, long startTime, long endTime, long effectiveTime, String worker, String contractor)
	{
	this.workPlace=workPlace;
	this.workType=workType;
	this.startTime=startTime;
	this.endTime=endTime;
	this.effectiveTime=effectiveTime;
	this.worker=worker;
	this.contractor=contractor;
	}
	
public void setWorkPlace(String workPlace)
	{
	this.workPlace=workPlace;
	}
	
public void setCustomerListName(String _name)
	{
	this.customerListName=_name;
	}
	

public void setWorkType(String workType)
	{
	this.workType=workType;
	}

public void setStartTime(long startTime)
	{
	this.startTime=startTime;
	}

public void setEndTime(long endTime)
	{
	this.endTime=endTime;
	}

public void setEffectiveTime(long effectiveTime)
	{
	this.effectiveTime=effectiveTime;
	}

public void setWorker(String worker)
	{
	this.worker=worker;
	}

public void setContractor(String contractor)
	{
	this.contractor=contractor;
	}

public void setID(int id)
	{
	this.id=id;
	}

public void setSent(boolean sent)
	{
	this.sent=sent;
	}
		
public String getWorkPlace()
	{
	return this.workPlace;
	}
	
public String getCustomerListName()
	{
	return this.customerListName;
	}
	
public String getWorkType()
	{
	return this.workType;
	}
	
public long getStartTime()
	{
	return this.startTime;
	}

public long getEndTime()
	{
	return this.endTime;
	}
	
public long getEffectiveTime()
	{
	return this.effectiveTime;
	}

public String getWorker()
	{
	return this.worker;
	}

public String getContractor()
	{
	return this.contractor;
	}
	
public int getID()
	{
	return this.id;
	}
	
public boolean isSent()
	{
	return this.sent;
	}	
/*
public String getXml()
	{
	return "<workunit>\n"+
	"<id>"+this.id+"</id>\n"+
	"<workplace><![CDATA["+this.workPlace+"]]></workplace>\n"+
	"<worktype><![CDATA["+this.workType+"]]></worktype>\n"+ 
	"<starttime>"+this.startTime+"</starttime>\n"+
	"<endtime>"+this.endTime+"</endtime>\n"+
	"<effectivetime>"+this.effectiveTime+"</effectivetime>\n"+
	"</workunit>\n";

	}
	
public String getXml2()
	{
	return "<a>"+	
	"<b>"+this.id+"</b>"+
	"<c><![CDATA["+this.workPlace+"]]></c>"+
	"<d><![CDATA["+this.workType+"]]></d>"+ 
	"<e>"+this.startTime+"</e>"+
	"<f>"+this.endTime+"</f>"+
	"<g>"+this.effectiveTime+"</g>"+
	"</a>\n";
	}
*/
/*
public void bufferXml(StringBuffer buf)
	{
	
	}
	
public void bufferAscii(StringBuffer buffer)
	{
	buffer.append(this.workPlace);
	buffer.append(TAB);
	buffer.append(this.workType);
	buffer.append(TAB);
	dat.setTime(this.startTime);
	cal.setTime(dat);
	buffer.append(cal.get(Calendar.DAY_OF_MONTH));
	buffer.append(DOT);
	buffer.append(DateHelper.getMonth(cal));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.YEAR));
	buffer.append(TAB);
	buffer.append(cal.get(Calendar.HOUR_OF_DAY));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.MINUTE));
	buffer.append(TAB);
	dat.setTime(this.endTime);
	cal.setTime(dat);
	buffer.append(cal.get(Calendar.DAY_OF_MONTH));
	buffer.append(DOT);
	buffer.append(DateHelper.getMonth(cal));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.YEAR));
	buffer.append(TAB);
	buffer.append(cal.get(Calendar.HOUR_OF_DAY));
	buffer.append(DOT);
	buffer.append(cal.get(Calendar.MINUTE));
	buffer.append(TAB);
	if (this.effectiveTime==-1)
		buffer.append(ONCE);
	else buffer.append(this.effectiveTime/60000);
	buffer.append(LF);
	}
*/
public void bufferAsciiBytes(OutputStream buffer)
	{
	try	{
	buffer.write(this.workPlace.getBytes());
	buffer.write(TAB);
	buffer.write(this.workType.getBytes());
	buffer.write(TAB);
	dat.setTime(this.startTime);
	cal.setTime(dat);
	buffer.write((cal.get(Calendar.DAY_OF_MONTH)+"").getBytes());
	buffer.write(DOT);
	buffer.write((DateHelper.getMonth(cal)+"").getBytes());
	buffer.write(DOT);
	buffer.write((cal.get(Calendar.YEAR)+"").getBytes());
	buffer.write(SPACE);
	buffer.write((DateHelper.getHoursAndMinutes(cal)+"").getBytes());
	buffer.write(TAB);
	dat.setTime(this.endTime);
	cal.setTime(dat);
	buffer.write((cal.get(Calendar.DAY_OF_MONTH)+"").getBytes());
	buffer.write(DOT);
	buffer.write((DateHelper.getMonth(cal)+"").getBytes());
	buffer.write(DOT);
	buffer.write((cal.get(Calendar.YEAR)+"").getBytes());
	buffer.write(SPACE);
	buffer.write((DateHelper.getHoursAndMinutes(cal)).getBytes());
	buffer.write(TAB);
	if (this.effectiveTime==-1)
		buffer.write(ONCE);
	else buffer.write((DateHelper.getEffectiveMinutes(this.effectiveTime)).getBytes());
	buffer.write(TAB);
	buffer.write("TYPE_WORKUNIT".getBytes());
	buffer.write(TAB);
	//System.out.println("custlistname:"+this.customerListName);
	buffer.write(this.customerListName.getBytes());
	buffer.write(TAB);
	if (this.getEffectiveTime()==-1)
		buffer.write(ONCE);
	else buffer.write((DateHelper.getEffectiveHours(this.getEffectiveTime())).getBytes());
	buffer.write(LF);
	}
	catch (Exception e) {e.printStackTrace();}
	}	
/*				
public String toString()
	{
	String ret="";
	ret+=this.workPlace+"	"+this.workType+"	";
	Calendar cal=Calendar.getInstance();
	cal.setTime(new Date(this.startTime));
	ret+=cal.get(Calendar.DAY_OF_MONTH)+"."+DateHelper.getMonth(cal)+".";
	ret+=cal.get(Calendar.YEAR)+" "+cal.get(Calendar.HOUR_OF_DAY)+"."+cal.get(Calendar.MINUTE)+"	";
	cal.setTime(new Date(this.endTime));
	ret+=cal.get(Calendar.DAY_OF_MONTH)+"."+DateHelper.getMonth(cal)+".";
	ret+=cal.get(Calendar.YEAR)+" ";
	String temp=""+cal.get(Calendar.HOUR_OF_DAY);
	if (temp.length()==1)
		temp="0"+temp;
	ret+=temp+".";
	temp=""+cal.get(Calendar.MINUTE);
	if (temp.length()==1)
		temp="0"+temp;
	String seftime="";
	if (this.effectiveTime==-1) 
		seftime="kerta";
	else seftime=""+(this.effectiveTime/60000);
	ret+=temp+"	"+seftime+"\n";
	return ret;
	}
*/
public String getRenderingName()
	{
	String ret= DateHelper.getHoursAndMinutes(this.startTime)+" "
	+ this.workPlace+" "+this.workType+" ";
	String temp=DateHelper.getEffectiveMinutes(this.effectiveTime); 
	if (!"kerta".equals(temp))
		return ret+temp+" min";
	
	else 	return ret+temp;
	}

public Image getRenderingImage()
	{
	return  this.sent ? null : ImageLoader.instance().getUnsentIcon();	
	}

public byte[] getBytes()
	{
	byte[] data=null;
	try	{	
		super.output.writeUTF(this.workPlace);
		super.output.writeUTF(this.workType);
		super.output.writeLong(this.startTime);
		super.output.writeLong(this.endTime);
		super.output.writeLong(this.effectiveTime);
		super.output.writeUTF(this.worker);
		super.output.writeUTF(this.contractor);
		super.output.writeBoolean(this.sent);
		super.output.writeUTF(this.customerListName);
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

		this.workPlace=dinput.readUTF();
		this.workType=dinput.readUTF();
		this.startTime=dinput.readLong();
		this.endTime=dinput.readLong();
		this.effectiveTime=dinput.readLong();
		this.worker=dinput.readUTF();
	  	this.contractor=dinput.readUTF();
		this.sent=dinput.readBoolean();
		this.customerListName=dinput.readUTF();
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
	return null;
	}

public ModifyForm getModifyForm(DataObject obj)
	{
	return ModifyWorkUnitForm.instance(this);
	}

public CommonRemoveForm getRemoveForm(DataObject obj)
	{
	return CommonRemoveForm.instance(this,Props.get("remove_workunit_confirmation"));
	}	

public ViewForm getViewForm(DataObject obj)
	{
	return ViewWorkUnitForm.instance(this);
	}

}
