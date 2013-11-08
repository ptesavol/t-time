package com.enporia.ttime;


import com.enporia.util.*;
import java.util.*;
import javax.microedition.lcdui.*;
import java.io.*;
import java.util.*;

public class TravelUnit extends MutableObject implements Sendable
{
private static Calendar cal=Calendar.getInstance();
private static Date dat=new Date();
private final static byte[] DOT=".".getBytes();
private final static byte[] SPACE=" ".getBytes();
private final static byte[] TAB="	".getBytes();
private final static byte[] LF="\n".getBytes();
//private final static byte[] ONCE="kerta".getBytes();

private int startMeter=0;
private int endMeter=0;
private int privateKilometers=0;
private long startTime=-1;
private long endTime=-1;
private String origin="";
private String destination="";
private String purpose="";
private String worker="";
private String contractor="";
private int id=-1;
private boolean sent=false;

public TravelUnit()
	{}

public TravelUnit(int startMeter, int endMeter, int privateKilometers, long startTime, long endTime, 
		String origin, String destination, String purpose,	
		String worker, String contractor,int id)
	{
	this.startMeter=startMeter;
	this.endMeter=endMeter;
	this.privateKilometers=privateKilometers;
	this.startTime=startTime;
	this.endTime=endTime;
	this.origin=origin;
	this.destination=destination;
	this.purpose=purpose;
	this.worker=worker;
	this.contractor=contractor;
	this.id=id;
	}
	
public void setStartMeter(int startMeter)
	{
	this.startMeter=startMeter;
	}
	
public void setEndMeter(int endMeter)
	{
	this.endMeter=endMeter;
	}
	
public void setPrivateKilometers(int kilometers)
	{
	this.privateKilometers=kilometers;
	}

public void setStartTime(long startTime)
	{
	this.startTime=startTime;
	}

public void setEndTime(long endTime)
	{
	this.endTime=endTime;
	}

public void setOrigin(String origin)
	{
	this.origin=origin;
	}
	
public void setDestination(String destination)	
	{
	this.destination=destination;
	}

public void setPurpose(String purpose)
	{
	this.purpose=purpose;
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
		
public int getStartMeter()
	{
	return this.startMeter;
	}

public int getEndMeter()
	{
	return this.endMeter;
	}
	
public int getPrivateKilometers()
	{
	return this.privateKilometers;
	}
	
public long getStartTime()
	{
	return this.startTime;
	}

public long getEndTime()
	{
	return this.endTime;
	}
	
public String getOrigin()
	{
	return this.origin;
	}
	
public String getDestination()
	{
	return this.destination;
	}
	
public String getPurpose()
	{
	return this.purpose;
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
	buffer.write((this.startMeter+"").getBytes());
	buffer.write(TAB);
	buffer.write((this.endMeter+"").getBytes());
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
	buffer.write((this.privateKilometers+"").getBytes());
	buffer.write(TAB);
	buffer.write(("TYPE_TRAVEL").getBytes());
	buffer.write(TAB);
	buffer.write(this.origin.getBytes());
	buffer.write(TAB);
	buffer.write(this.destination.getBytes());
	buffer.write(TAB);
	buffer.write(this.purpose.getBytes());
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
	+Props.get("travelunit_name");
	/*
	+ this.workPlace+" "+this.workType+" ";
	String temp=DateHelper.getEffectiveMinutes(this.effectiveTime); 
	if (!"kerta".equals(temp))
		return ret+temp+" min";
	
	else 	return ret+temp;
	*/
	return ret;
	}

public Image getRenderingImage()
	{
	return  this.sent ? null : ImageLoader.instance().getUnsentIcon();	
	}

public byte[] getBytes()
	{
	byte[] data=null;
	try	{	
		super.output.writeInt(this.startMeter);
		super.output.writeInt(this.endMeter);
		super.output.writeInt(this.privateKilometers);
		super.output.writeLong(this.startTime);
		super.output.writeLong(this.endTime);
		super.output.writeUTF(this.origin);
		super.output.writeUTF(this.destination);
		super.output.writeUTF(this.purpose);
		super.output.writeUTF(this.worker);
		super.output.writeUTF(this.contractor);
		super.output.writeBoolean(this.sent);
		
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

		this.startMeter=dinput.readInt();
		this.endMeter=dinput.readInt();
		this.privateKilometers=dinput.readInt();
		this.startTime=dinput.readLong();
		this.endTime=dinput.readLong();
		this.origin=dinput.readUTF();
		this.destination=dinput.readUTF();
		this.purpose=dinput.readUTF();
		this.worker=dinput.readUTF();
	  	this.contractor=dinput.readUTF();
		this.sent=dinput.readBoolean();
		
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
	return ModifyTravelUnitForm.instance(this);
	}

public CommonRemoveForm getRemoveForm(DataObject obj)
	{
	return CommonRemoveForm.instance(this,Props.get("remove_workunit_confirmation"));
	}	

public ViewForm getViewForm(DataObject obj)
	{
	return ViewTravelUnitForm.instance(this);
	}

}
