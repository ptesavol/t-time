package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class TravelTimerForm extends Form
{
class WorkClock extends TimerTask 
{
private int timerSeconds=0;
private int hours=0;
private int minutes=0;
private int seconds=0;
String sseconds="";
String sminutes="";
String shours="";

StringBuffer buf=new StringBuffer("00:00:00");
public WorkClock()
	{} 

public WorkClock(long seedmillis)
	{
	timerSeconds=(int)(seedmillis/1000);
	this.hours=timerSeconds/3600;
	this.minutes=(timerSeconds%3600)/60;
	this.seconds=(timerSeconds%3600)%60;
	this.shours=this.hours+"";
	if (this.shours.length()==1)
		this.shours="0"+this.shours;	
	this.sminutes=this.minutes+"";
	if (this.sminutes.length()==1)
		this.sminutes="0"+this.sminutes;	
	this.sseconds=this.seconds+"";
	if (this.sseconds.length()==1)
		this.sseconds="0"+this.sseconds;
	clockItem.setText(this.shours+":"+this.sminutes+":"+this.sseconds);
	} 

public void run()
	{
	this.timerSeconds++;
	this.hours=timerSeconds/3600;
	this.minutes=(timerSeconds%3600)/60;
	this.seconds=(timerSeconds%3600)%60;
	
	buf.setCharAt(0,(char)((this.hours/10)+'0') );
	buf.setCharAt(1,(char)((this.hours%10)+'0') );
	buf.setCharAt(3,(char)((this.minutes/10)+'0') );
	buf.setCharAt(4,(char)((this.minutes%10)+'0') );
	buf.setCharAt(6,(char)((this.seconds/10)+'0') );
	buf.setCharAt(7,(char)((this.seconds%10)+'0') );
	
	clockItem.setText(buf.toString());
	if (this.timerSeconds%10==0)
		System.gc();
	}
public void reset()
	{
	this.seconds=0;
	this.minutes=0;
	this.hours=0;
	this.timerSeconds=0;
	}
}



private static TravelTimerForm _instance = null;
public static Command STOP_TRAVEL = new Command(Props.get("timerform_stop"), Command.STOP, 1);
public static Command TRAVEL_CALL = new Command(Props.get("timerform_phone"), Command.SCREEN, 1);
//public static Command STOP_WORK_MODIFYING = new Command(Props.get("timerform_stopmodifying"), Command.SCREEN, 1);

private long startTime=-1;
private long endTime=-1;
private int startMeter=0;
//private WorkPlace workPlace=null;
//private WorkType workType=null;
//private Worker worker=null;

//private OwnStringItem placeItem=null;
//private OwnStringItem typeItem=null;
private OwnStringItem clockItem=null;
private Timer timer=null;
private WorkClock clock=null;

private TravelTimerForm()
	{
	super(Props.get("traveltimerform_title"));
	
	//this.typeItem=new StringItem("","");
	//this.placeItem=new StringItem("","");
	this.clockItem=new OwnStringItem("","");
	//this.append(this.placeItem);
	//this.append(this.typeItem);
	
	this.clockItem.appendToForm(this);
	this.addCommand(STOP_TRAVEL);
	this.addCommand(TRAVEL_CALL);
	//this.addCommand(STOP_WORK_MODIFYING);
	}

public static TravelTimerForm instance(int startMeter)
	{
	if (_instance==null)
		_instance=new TravelTimerForm();
	
	_instance.startMeter=startMeter;
	_instance.clockItem.setText("00:00:00");
	
	return _instance;
	}
	
public void startClock(long seedTime)
	{
	if (seedTime==0)
		{
		this.startTime=System.currentTimeMillis();
		this.clock=new WorkClock();
		}
	else 	{
		this.startTime=seedTime;
		this.clock=new WorkClock(System.currentTimeMillis()-seedTime);
		}
	this.timer=new Timer();
	this.timer.schedule(this.clock,1000,1000);
	}
	
public void stopClock()		
	{
	this.endTime=System.currentTimeMillis();
	this.timer.cancel();
	}

public DataObject getObject()	
	{
	TravelUnit tunit=new TravelUnit();
	tunit.setStartTime(this.startTime);
	tunit.setEndTime(this.endTime);
	tunit.setStartMeter(this.startMeter);
	return tunit;
	
	}
}
