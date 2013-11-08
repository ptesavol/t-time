package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class EffectiveTimeBox extends TextBox
{
private static EffectiveTimeBox _instance=null;
public static Command EFFECTIVE_TIME_OK = new Command(Props.get("common_ok"), Command.OK, 1);
private long time=-1;

public static EffectiveTimeBox instance(long time)
	{
	if (_instance==null)
		_instance=new EffectiveTimeBox(time);
	_instance.time=time;
	_instance.setString(DateHelper.getEffectiveMinutes(time));
	
	return _instance;
	}

private EffectiveTimeBox(long time)
	{
	super(Props.get("effective_time_title"),"",32,TextField.NUMERIC);
	
	this.time=time;
	addCommand(EFFECTIVE_TIME_OK);
	}
	
public long getEffectiveTime()
	{
	long ret=this.time;
	try	{
		ret=(60000*Long.parseLong(this.getString()));
		}
	catch (Exception e)
		{}
	return ret;
	}
}
