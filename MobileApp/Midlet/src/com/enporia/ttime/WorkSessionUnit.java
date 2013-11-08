package com.enporia.ttime;


import java.io.OutputStream;
import java.util.Calendar;

import com.enporia.util.*;

public class WorkSessionUnit extends WorkUnit
{
public WorkSessionUnit()
	{
	super();
	}

public WorkSessionUnit(WorkUnit other, long starttime)
	{
	this.setWorkPlace(other.getWorkPlace());
	this.setWorkType(Props.get("worksessionunit_title"));
	this.setWorker(other.getWorker());
	this.setContractor(other.getContractor());
	this.setCustomerListName(other.getCustomerListName());
	long etime=other.getEndTime()-starttime;
	
	if (etime > other.getEffectiveTime())
		{
		this.setStartTime(starttime);
		this.setEffectiveTime(etime);
		}
	else
		{
		this.setStartTime(other.getStartTime());
		this.setEffectiveTime(other.getEffectiveTime());
		}
	
	this.setEndTime(other.getEndTime());
	}
/*
public String getRenderingName()
	{
	return Props.get("worksessionunit_title")+": "+super.getRenderingName();
	}
*/
public void bufferAsciiBytes(OutputStream buffer)
	{

	try	{
	buffer.write(this.getWorkPlace().getBytes());
	buffer.write(TAB);
	buffer.write(this.getWorkType().getBytes());
	buffer.write(TAB);
	dat.setTime(this.getStartTime());
	cal.setTime(dat);
	buffer.write((cal.get(Calendar.DAY_OF_MONTH)+"").getBytes());
	buffer.write(DOT);
	buffer.write((DateHelper.getMonth(cal)+"").getBytes());
	buffer.write(DOT);
	buffer.write((cal.get(Calendar.YEAR)+"").getBytes());
	buffer.write(SPACE);
	buffer.write((DateHelper.getHoursAndMinutes(cal)+"").getBytes());
	buffer.write(TAB);
	dat.setTime(this.getEndTime());
	cal.setTime(dat);
	buffer.write((cal.get(Calendar.DAY_OF_MONTH)+"").getBytes());
	buffer.write(DOT);
	buffer.write((DateHelper.getMonth(cal)+"").getBytes());
	buffer.write(DOT);
	buffer.write((cal.get(Calendar.YEAR)+"").getBytes());
	buffer.write(SPACE);
	buffer.write((DateHelper.getHoursAndMinutes(cal)).getBytes());
	buffer.write(TAB);
	if (this.getEffectiveTime()==-1)
		buffer.write(ONCE);
	else buffer.write((DateHelper.getEffectiveMinutes(this.getEffectiveTime())).getBytes());
	buffer.write(TAB);
	buffer.write("TYPE_WORKSESSION".getBytes());
	buffer.write(TAB);
	//System.out.println("custlistname:"+this.customerListName);
	buffer.write(this.getCustomerListName().getBytes());
	buffer.write(TAB);
	if (this.getEffectiveTime()==-1)
		buffer.write(ONCE);
	else buffer.write((DateHelper.getEffectiveHours(this.getEffectiveTime())).getBytes());
	buffer.write(LF);
	}
catch (Exception e) {e.printStackTrace();}
	}		
	
}