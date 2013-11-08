package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ShowCompletedWorksForm extends Form
{
// 3.6.2010, J.V., Reset/restore counter functionality added. Counter resetting is based on reset time. Completed works before reset time are not counted. 
public static Command OK= new Command(Props.get("common_ok"), Command.BACK, 1);	
public static Command RESETCOUNTER= new Command(Props.get("showcompletedworks_resetcounter"), Command.SCREEN, 2);
public static Command RESTORECOUNTER= new Command(Props.get("showcompletedworks_restorecounter"), Command.SCREEN, 3);
private static ShowCompletedWorksForm _instance=null;

private OwnStringItem headerItem=null;
private OwnStringItem contentItem=null; 
private CompletedWorksThread thread=null;

class CompletedWorksThread extends Thread
{
WorkPlace place=null;

public CompletedWorksThread(WorkPlace place)
	{
	this.place=place;
	}
 
public void run()
	{
	removeCommand(OK);
	removeCommand(RESETCOUNTER);
	removeCommand(RESTORECOUNTER);
	headerItem.setText(Props.get("showcompletedworks_calculating") + " " + place.getName() + " " + Props.get("showcompletedworks_works"));
	contentItem.setText("");

	String wulistname = WorkUnitList.instance().getName();
	DataObject tobj = null;
	WorkUnit tunit = null;
	long ttime = 0;
	Long tlong = null;
	Hashtable ttable = new Hashtable();
	Object obj = null;
	String firstDate = "";
	String lastDate = "";
	String currDate = "";
	for(int i=0; i<WorkUnitFolderList.instance().size(); i++)
	{
		currDate = WorkUnitFolderList.instance().getNameAt(i);
		WorkUnitList.instance().setName(currDate);
		for(int j=0; j<WorkUnitList.instance().size(); j++)
		{
			tobj = WorkUnitList.instance().elementAt(j);
			//if("com.enporia.ttime.WorkUnit".equals(tobj.getClass().getName()))	// 28.6.2013 J.V., returns obfuscated class name => use instanceof instead
			if(tobj instanceof WorkUnit)
			{
				tunit = (WorkUnit)tobj;
				if(place.getName().equals(tunit.getWorkPlace()) && tunit.getStartTime() >= place.getResetTime())
				{
					obj = ttable.get(tunit.getWorkType());
					if(obj != null)
						tlong = (Long)obj;
					else
						tlong = new Long(0);

					ttable.put(tunit.getWorkType(), new Long(tlong.longValue() + tunit.getEffectiveTime()));	
					if("".equals(lastDate))
						lastDate = currDate;
					firstDate = currDate;
				}
			}
		}
	}

	if(ttable.size() == 0)
	{
        headerItem.setText(Props.get("showcompletedworks_inplace") + " " + place.getName() + " " + Props.get("showcompletedworks_noworks") + (place.getResetTime() > 0 ? " " + Props.get("showcompletedworks_counterreset") : ""));
	    addCommand(OK);
	    addCommand(RESETCOUNTER);
	    addCommand(RESTORECOUNTER);
        return;
	}

	String ts = "";
    String ret = "";
	Enumeration iter = ttable.keys();
	while(iter.hasMoreElements())
	{
		ts = (String)iter.nextElement();
		ret += ts;
		ret += " ";
		tlong = (Long)ttable.get(ts);
		ttime = tlong.longValue();
		ttime = ttime / 60000;
		if((ttime / 60) > 0)
			ret += (ttime/60) + "h ";
		ret += (ttime % 60) + "min\n";
	}

	WorkUnitList.instance().setName(wulistname);
	String headerText = Props.get("showcompletedworks_inplace") + " ";
	headerText += place.getName() + " " + Props.get("showcompletedworks_works") + " ";
	headerText += firstDate;
	if(!firstDate.equals(lastDate))
		headerText += "-" + lastDate;
	headerText += ".";
	headerText += (place.getResetTime() > 0 ? " " + Props.get("showcompletedworks_counterreset") : "");	
	headerText += "\n\n";
	headerItem.setText(headerText);
	contentItem.setText(ret);
	addCommand(OK);
	addCommand(RESETCOUNTER);
	addCommand(RESTORECOUNTER);
	}
}

public static ShowCompletedWorksForm instance()
	{
	if (_instance==null)
		_instance=new ShowCompletedWorksForm();
	_instance.headerItem.setText("");
	_instance.contentItem.setText("");
	return _instance;
	}

public ShowCompletedWorksForm()
	{
	super(Props.get("showcompletedworks_title"));
	this.headerItem=new OwnStringItem("","");
	this.contentItem=new OwnStringItem("","");
	this.headerItem.appendToForm(this);
	this.contentItem.appendToForm(this);
	}

public void calculate(WorkPlace place)
	{
	this.thread=new CompletedWorksThread(place);
	this.thread.start();
	}


}