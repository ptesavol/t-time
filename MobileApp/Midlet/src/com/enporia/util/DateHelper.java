package com.enporia.util;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.MIDlet;
import java.util.*;

public class DateHelper
{
public static int getMonth(Calendar cal)
	{
	return cal.get(Calendar.MONTH)+1;
	/*
	if (month==Calendar.JANUARY)
		return 1;
	
	if (month==Calendar.FEBRUARY)
		return 2;
		
	if (month==Calendar.MARCH)
		return 3;
	
	if (month==Calendar.APRIL)
		return 4;
	
	if (month==Calendar.MAY)
		return 5;
	
	if (month==Calendar.JUNE)
		return 6;
	
	if (month==Calendar.JULY)
		return 7;
	
	if (month==Calendar.AUGUST)
		return 8;
	
	if (month==Calendar.SEPTEMBER)
		return 9;
	
	if (month==Calendar.OCTOBER)
		return 10;
	
	if (month==Calendar.NOVEMBER)
		return 11;
	
	if (month==Calendar.DECEMBER)
		return 12;
	else return -1;
	*/
	}
	
public static Date normalize(Date date)
	{
	Calendar cal=Calendar.getInstance();
	cal.setTime(date);
	long i=0;
	i+=3600000*cal.get(Calendar.HOUR_OF_DAY);
	i+=60000*cal.get(Calendar.MINUTE);
	i+=1000*cal.get(Calendar.SECOND);
	return new Date(i);
	}

public static Date deNormalize(Date base, Date offset)
	{
	Calendar cal=Calendar.getInstance();
	cal.setTime(base);
	long i=0;
	i+=3600000*cal.get(Calendar.HOUR_OF_DAY);
	i+=60000*cal.get(Calendar.MINUTE);
	i+=1000*cal.get(Calendar.SECOND);
	i+=cal.get(Calendar.MILLISECOND);
	
	long basenum=base.getTime();
	basenum-=i;
	return new Date(basenum+offset.getTime());
	}

public static String getDayString()
	{
	Calendar cal = Calendar.getInstance();
	String daystring=""+ 
	cal.get(Calendar.DATE)+"."+
	DateHelper.getMonth(cal)+"."+
	cal.get(Calendar.YEAR);
	return daystring;
	}
	
public static String getHoursAndMinutes(long time)
	{
	Calendar cal=Calendar.getInstance();
	cal.setTime(new Date(time));
	return getHoursAndMinutes(cal);
	}

public static String getEffectiveMinutes(long time)
	{
	String seftime="";
	if (time==-1)
		{
		seftime="kerta";
		}
	else	{
		long seconds=time/1000;
		long minutes=seconds/60;
		if ((seconds%60)>=30)
			minutes++;
		seftime=minutes+"";
		}
	return seftime;
	}

public static String getEffectiveHours(long time)
	{
	String seftime="";
	if (time==-1)
		{
		seftime="kerta";
		}
	else	{
		long seconds=time/1000;
		long minutes=seconds/60;
		if ((seconds%60)>=30)
			minutes++;
		long hours=minutes/60;
		long fraction = minutes%60;
		fraction=fraction*100;
		long hundredths = fraction/60;
		if (fraction%60>30)
			hundredths++;
		String temp=hundredths+"";
		while (temp.length()<2)
			temp="0"+temp;
		seftime=hours+","+temp.substring(0,2);
		}
	return seftime;
	}

public static String getHoursAndMinutes(Calendar cal)
	{
	String hours=cal.get(Calendar.HOUR_OF_DAY)+"";
	if (hours.length()==1)
		hours="0"+hours;
	String minutes=cal.get(Calendar.MINUTE)+"";
	if (minutes.length()==1)
		minutes="0"+minutes;
	return hours+"."+minutes;
	}

public static String getDateAsString(long time)
	{
	Calendar cal=Calendar.getInstance();
	cal.setTime(new Date(time));
	return getDateAsString(cal);
	}

public static String getDateAsString(Calendar cal)
	{
	String daystring=""+ 
	cal.get(Calendar.DATE)+"."+
	DateHelper.getMonth(cal)+"."+
	cal.get(Calendar.YEAR);
	String hours=cal.get(Calendar.HOUR_OF_DAY)+"";
	if (hours.length()==1)
		hours="0"+hours;
	String minutes=cal.get(Calendar.MINUTE)+"";
	if (minutes.length()==1)
		minutes="0"+minutes;
	return daystring+" "+hours+"."+minutes;
	}
}
