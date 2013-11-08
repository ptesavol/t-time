package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class TimerForm extends Form
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
	
	//tarkistetaan, onko aihetta vaihtaa työtyyppiä
	if (workType.isChangeActive() && changeTime!=-1 && workType.getChangeToId()!=-1)
		{
		if (System.currentTimeMillis()>changeTime)
			{
			changeWorkType();
			}
		}
	}
public void reset()
	{
	this.seconds=0;
	this.minutes=0;
	this.hours=0;
	this.timerSeconds=0;
	}
}



private static TimerForm _instance = null;
public static Command STOP_WORK = new Command(Props.get("timerform_stop"), Command.STOP, 1);
public static Command WORK_CALL = new Command(Props.get("timerform_phone"), Command.SCREEN, 1);
public static Command STOP_WORK_MODIFYING = new Command(Props.get("timerform_stopmodifying"), Command.SCREEN, 1);
public static Command SALES= new Command(Props.get("timerform_sales"), Command.SCREEN,2);

private long changeTime = -1;
private long startTime=-1;
private long endTime=-1;
private WorkPlace workPlace=null;
private WorkType workType = null;
private Worker worker=null;

//private String workTypeName=null;

private OwnStringItem placeItem=null;
private OwnStringItem typeItem=null;
private OwnStringItem clockItem=null;
private Timer timer=null;
private WorkClock clock=null;

private TimerForm()
	{
	super(Props.get("timerform_title"));
	
	this.typeItem=new OwnStringItem("","");
	this.placeItem=new OwnStringItem("","");
	this.clockItem=new OwnStringItem("","");
	this.placeItem.appendToForm(this);
	this.typeItem.appendToForm(this);
	this.clockItem.appendToForm(this);
	this.addCommand(STOP_WORK);
	this.addCommand(WORK_CALL);
	this.addCommand(STOP_WORK_MODIFYING);
	this.addCommand(SALES);
	}

public static TimerForm instance(WorkPlace place, WorkType workType, Worker worker)
	{
	if (_instance==null)
		_instance=new TimerForm();
	_instance.typeItem.setText(workType.getRenderingName()+"\n");
	_instance.placeItem.setText(place.getName()+"\n");
	_instance.clockItem.setText("00:00:00");
	_instance.workPlace=place;
	_instance.workType=workType;
	_instance.worker=worker;
	_instance.calculateNextChangeTime();
	return _instance;
	}	

private synchronized void changeWorkType()
	{
	WorkType tempType = (WorkType)WorkTypeList.instance().getElementById(this.workType.getChangeToId());
	if (tempType==null)
		return;
	this.stopClock();
	this.saveWorkUnit((WorkUnit)this.getObject());
	
	WorkTypeList.instance().setSelectedId(this.workType.getChangeToId());
	this.workType = tempType;
	this.typeItem.setText(workType.getRenderingName()+"\n");
	this.clockItem.setText("00:00:00");
	this.calculateNextChangeTime();
	
	ProgramState.instance().setStartTime(System.currentTimeMillis());
	ProgramState.instance().setSelectedWorkType(WorkTypeList.instance().getSelectedIndex());
	ProgramState.instance().setSelectedWorkPlace(WorkPlaceList.instance().getSelectedIndex());
	ProgramState.instance().save();
	this.startClock(0);
	}

private synchronized void saveWorkUnit(WorkUnit unit)
	{
	String daystring=DateHelper.getDayString();
	WorkUnitList.instance().setName(daystring);
	WorkUnitList.instance().insertElementAt(unit,0);
	FolderName fname=new FolderName(daystring);
	if ( WorkUnitFolderList.instance().size()==0 || 
			(WorkUnitFolderList.instance().size()>0 && 
					WorkUnitFolderList.instance().indexOf(daystring)==-1) )
		{
		WorkUnitFolderList.instance().insertElementAt(fname,0);
		}
	ProgramState.instance().setStartTime(-1);
	ProgramState.instance().save();
}

private synchronized void calculateNextChangeTime()
	{
	if (workType.getChangeTime()!=-1)
		{
		Calendar currCal = Calendar.getInstance();
		currCal.setTime(new Date(System.currentTimeMillis()));
		Date currDate = currCal.getTime(); 
		long currTime = currDate.getTime();
		
		Date changeDate = new Date(workType.getChangeTime());
	
		int year = currCal.get(Calendar.YEAR); 
		int month = currCal.get(Calendar.MONTH); 
		int day = currCal.get(Calendar.DAY_OF_MONTH); 
	
		Calendar changeCal = Calendar.getInstance();
		changeCal.setTime(changeDate);
	
		changeCal.set(Calendar.YEAR,year);
		changeCal.set(Calendar.MONTH,month);
		changeCal.set(Calendar.DAY_OF_MONTH,day);
	
		long tempTime = changeCal.getTime().getTime();
		
		
		if (currTime >= tempTime)
			tempTime = tempTime + (24*60*60*1000);
		
		changeTime=tempTime;
		
		}
	else changeTime = -1;
	}
public synchronized void startClock(long seedTime)
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
	
public synchronized void stopClock()		
	{
	this.endTime=System.currentTimeMillis();
	this.timer.cancel();
	}

public synchronized DataObject getObject()	
	{
	WorkUnit tunit=new WorkUnit();
	
	long pastTime=this.endTime-this.startTime;
	long startt=this.startTime;
	long endt=this.endTime;

	long rounding=Worker.instance().getRounding();
	
	if (rounding>0)
		{
		pastTime=this.endTime-this.startTime;	//pyöristetään kulunut aika 
		long quantity=pastTime/(60000*rounding);	// montako viisitoistaminuuttista
		
		// lisätään yksi, jos pyöristys ylempään, ttai jos ylempi on myös lähempi
		if ( (!Worker.instance().isRoundToNearest()) ||
		     ((pastTime%(60000*rounding)) >= ((60000*rounding)/2)) )
			{
			quantity+=1;				// lisätään 1	
			}	
				
		pastTime=quantity*(60000*rounding);		// lasketaan kulunut aika
	
		long stime=this.startTime/(60000*rounding);		//pyöristetään alkuaika lähimpään pyöristysminuuttiin
		if ((this.startTime%(60000*rounding)) >= ((60000*rounding)/2))
			stime+=1;
		startt=stime*(60000*rounding);
		endt=startt+pastTime;	//lasketaan loppuaika lisäämällä alkuaikaan pyöristetty kulunut aika
		}

	tunit.setWorkPlace(this.workPlace.getName());
	tunit.setWorkType(this.workType.getName());
	tunit.setStartTime(startt);
	tunit.setEndTime(endt);
	tunit.setEffectiveTime(pastTime);
	tunit.setWorker(this.worker.getName());
	tunit.setContractor(this.workPlace.getContractor());
	tunit.setCustomerListName(WorkPlaceList.instance().getName());
	return tunit;
	}
}
