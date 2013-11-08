package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class WorkPlaceList extends BasicList
{
private static WorkPlaceList _instance=null;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;
private static Class _iclass=null;
private static String _titleprefix="";
private FindBox findBox=null;
private TravelBox travelBox=null;
private TravelTimerForm travelTimerForm=null;
private FeedTravelUnitForm feedTravelUnitForm=null;
private ShowCompletedWorksForm showCompletedWorksForm=null;
private ActivationForm activationForm=null;

private static final String _prefix="wplacel";

private static Command TO_SETTINGSLIST = new Command(Props.get("workplacelist_settings"), Command.ITEM, 11);
private static Command TO_WORKPLACEFOLDERLIST = new Command(Props.get("workplacelist_folderlists"), Command.ITEM, 1);
private static Command TO_WORKUNITFOLDERLIST = new Command(Props.get("workplacelist_logs"), Command.ITEM, 5);
private static Command TO_PRODUCTLIST =new Command(Props.get("workplacelist_products"), Command.ITEM, 6);
private static Command CHOOSE_WORKPLACE = new Command(Props.get("workplacelist_startwork"), Command.BACK, 0);
private static Command FIND_WORKPLACE = new Command(Props.get("workplacelist_find"), Command.ITEM, 4);
private static Command CMD_EXIT = new Command(Props.get("workplacelist_shutdown"), Command.ITEM, 13);
private static Command START_TRAVEL=new Command(Props.get("workplacelist_travel"),Command.ITEM, 7);
private static Command SHOW_WORKS=new Command(Props.get("workplacelist_works"),Command.ITEM, 12);

//private IMAPGetListsForm imapgetlistsform=null; // 21.9.2008, J.V.

public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_titleprefix=Props.get("workplacelist_title");
	_midlet=midlet;
	_listener=commandlistener;
	try	{
		_iclass=Class.forName("com.enporia.ttime.WorkPlace");
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}

private WorkPlaceList()
	{
	super("",_midlet,_listener,_iclass,_prefix);
	
	}

public static WorkPlaceList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new WorkPlaceList();
	return _instance;
	}	

public void setName(String name)
	{
	super.setName(name);
	ProgramState.instance().setSelectedWorkPlaceFolder(name);
	ProgramState.instance().save();
	}

public void addScreenCommands()
	{
	super.addScreenCommands();
	addCommand(TO_SETTINGSLIST);
	addCommand(TO_WORKPLACEFOLDERLIST);
	addCommand(TO_WORKUNITFOLDERLIST);
	addCommand(FIND_WORKPLACE);
	addCommand(CMD_EXIT);
	}

public void addItemCommands()
	{
	super.addItemCommands();
	addCommand(CHOOSE_WORKPLACE);	
	addCommand(TO_PRODUCTLIST);
	addCommand(START_TRAVEL);
	addCommand(SHOW_WORKS);
	}	

public void removeItemCommands()
	{
	super.removeItemCommands();
	removeCommand(CHOOSE_WORKPLACE);	
	removeCommand(TO_PRODUCTLIST);
	removeCommand(START_TRAVEL);
	removeCommand(SHOW_WORKS);
	}
// Callback implementations


public void onChooseWorkPlace()
	{
	if (getSelectedIndex()!=size())
		{
		
		
		if (!ProgramState.instance().isTimerActivated())
			{
			this.activationForm=ActivationForm.instance();
			this.activationForm.setModule(ActivationForm.MODULE_TIME);
			this.activationForm.setCommandListener(this);
			super.display.setCurrent(this.activationForm);
			this.activationForm.requestActivationCode();
			return;
			}
				
		if (ProgramState.instance().isEmpty())
			{
			WorkTypeList.instance().show();
			}
		else	{
			WorkTypeList.instance().show();
			WorkTypeList.instance().startWork(ProgramState.instance().getStartTime());
			}
		}
	}

public void onToProductList()
	{
	if (getSelectedIndex()!=size())
		{
		
		if (!ProgramState.instance().isStorageActivated())
			{
			this.activationForm=ActivationForm.instance();
			this.activationForm.setModule(ActivationForm.MODULE_STORAGE);
			this.activationForm.setCommandListener(this);
			super.display.setCurrent(this.activationForm);
			this.activationForm.requestActivationCode();
			return;
			}

		ProductList.instance().show();
		}
	}			

public void onStartTravel()
	{
	if (getSelectedIndex()!=size())
		{
		
		if (!ProgramState.instance().isTravelActivated())
			{
			this.activationForm=ActivationForm.instance();
			this.activationForm.setModule(ActivationForm.MODULE_TRAVEL);
			this.activationForm.setCommandListener(this);
			super.display.setCurrent(this.activationForm);
			this.activationForm.requestActivationCode();
			return;
			}
			
		this.travelBox=TravelBox.instance("");
		this.travelBox.setCommandListener(this);
		super.display.setCurrent(this.travelBox);
		}
	}
/*
public void onToSettingsList()
	{
	SettingsList.instance().show();
	}

public void onToWorkPlaceFolderList()
	{
	WorkPlaceFolderList.instance().show();
	}

public void onToWorkUnitFolderList()
	{
	WorkUnitFolderList.instance().show();
	}



public void onFindWorkPlace()
	{
	this.findBox=FindBox.instance("");
	this.findBox.setCommandListener(this);
	super.display.setCurrent(this.findBox);
	}

public void onFindOk()
	{
	if (this.findBox.getString()!=null && !"".equals( this.findBox.getString()))
		{
		FindForm.instance().setCommandListener(this);
		super.display.setCurrent(FindForm.instance());
		FindForm.instance().find(this.findBox.getString());
		}
	}

public void onFindCancel()
	{
	this.show();
	}	

public void onFindFormOk()
	{
	this.show();
	}
*/
/**
* Override showablelist
*/

public String getRenderingName()
	{
	return _titleprefix+" "+name;
	}

public void startTravelling(long seedTime, int startm)
	{
	if (getSelectedIndex()!=size())
		{
		this.travelTimerForm=TravelTimerForm.instance(startm);
		super.display.setCurrent(this.travelTimerForm);
		this.travelTimerForm.setCommandListener(this);
		this.travelTimerForm.startClock(seedTime);
		}
	}
	
	
private void saveTravelUnit(DataObject unit)
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
	ProgramState.instance().setTravelStartTime(-1);
	ProgramState.instance().save();
	}

/**
The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==TO_SETTINGSLIST)
		{
		SettingsList.instance().show();
		}
		
	
	if (c==TO_WORKPLACEFOLDERLIST)
		{
		WorkPlaceFolderList.instance().show();
		}
		
		
	if (c==TO_WORKUNITFOLDERLIST)
		{
		WorkUnitFolderList.instance().show();
		}
		
	if (c==TO_PRODUCTLIST)
		{
		this.onToProductList();
		}	
	
	if (c==CHOOSE_WORKPLACE ||  c == List.SELECT_COMMAND)
		{
		this.onChooseWorkPlace();
		}
		
		
	
	if (c==FIND_WORKPLACE)
		{
		this.findBox=FindBox.instance("");
		this.findBox.setCommandListener(this);
		super.display.setCurrent(this.findBox);
		}
		
	
	if (c==FindBox.FIND_OK)
		{
		if (this.findBox.getString()!=null && !"".equals( this.findBox.getString()))
			{
			FindForm.instance().setCommandListener(this);
			super.display.setCurrent(FindForm.instance());
			FindForm.instance().find(this.findBox.getString(), this, WorkPlaceFolderList.instance());
			}
		}
		
	if (c==START_TRAVEL)
		{
		this.onStartTravel();
		}
	
	if (c==SHOW_WORKS)
		{
		if (getSelectedIndex()!=size())
			{
		
			this.showCompletedWorksForm=ShowCompletedWorksForm.instance();
			this.showCompletedWorksForm.setCommandListener(this);
			super.display.setCurrent(this.showCompletedWorksForm);
			this.showCompletedWorksForm.calculate((WorkPlace)(getSelectedElement()));
			}
		}	

	if (c==ShowCompletedWorksForm.OK)
		{
		this.show();
		}

	if (c==ShowCompletedWorksForm.RESETCOUNTER)					// 3.6.2010, J.V., Reset counter, based on time = resetting shows completed works only if they are done after the reset time
		{
		WorkPlace place = (WorkPlace)getSelectedElement();		
		place.setResetTime(System.currentTimeMillis());
		super.setElementAt(place, super.getSelectedIndex());
		this.showCompletedWorksForm.calculate((WorkPlace)(getSelectedElement()));
		}
	
	if (c==ShowCompletedWorksForm.RESTORECOUNTER)				// 3.6.2010, J.V., Restore counter (show all works again)
		{
		WorkPlace place = (WorkPlace)getSelectedElement();		
		place.setResetTime(new Long(0));
		super.setElementAt(place, super.getSelectedIndex());
		this.showCompletedWorksForm.calculate((WorkPlace)(getSelectedElement()));
		}	

	if (c==TravelBox.TRAVEL_OK)
		{
		int startm=0;
		try	{
			startm=Integer.parseInt(this.travelBox.getString());
			}
		catch (Exception e) {}	
		
		
		ProgramState.instance().setSelectedWorkPlace(getSelectedIndex());
		ProgramState.instance().setTravelStartTime(System.currentTimeMillis());
		ProgramState.instance().setTravelStartMeter(startm);
		ProgramState.instance().save();
		this.startTravelling(0, startm );
		}
		
	if (c==TravelTimerForm.STOP_TRAVEL)
		{
		this.travelTimerForm.stopClock();
		//ProgramState.instance().setTravelStartTime(-1);
		//ProgramState.instance().save();
		TravelUnit tunit=(TravelUnit)this.travelTimerForm.getObject();
		this.feedTravelUnitForm=FeedTravelUnitForm.instance(tunit);
		this.feedTravelUnitForm.setCommandListener(this);
		super.display.setCurrent(this.feedTravelUnitForm);
		}
	
	if (c==TravelTimerForm.TRAVEL_CALL)
		this.quitApplication();
	
	if (c==FeedTravelUnitForm.OK)
		{
		TravelUnit tru=(TravelUnit)this.feedTravelUnitForm.getObject();
		tru.setContractor(((WorkPlace)this.getSelectedElement()).getContractor());
		this.saveTravelUnit(tru);
		this.show();
		return;
		}
	
	if (c==FeedTravelUnitForm.CANCEL)
		{
		this.show();
		ProgramState.instance().setTravelStartTime(-1);
		ProgramState.instance().save();
		}		
			
	if (c==FindBox.FIND_CANCEL || c==TravelBox.TRAVEL_CANCEL || c==FindForm.FINDFORM_OK)
		this.show();
					
	
	if (c==ActivationForm.ACTIVATIONFORM_OK)
		{
		this.activationForm.checkActivationCode();
		}
	
	if (c==ActivationForm.ACTIVATIONFORM_CANCEL)
		{
		this.show();
		}
			
	if (c==ActivationForm.ACTIVATIONFORM_COMPLETED)
		{
		if (this.activationForm.isActivated())
			{
			this.activationForm.saveActivationInfo();
			String tempmodule=this.activationForm.getModule();
			if (ActivationForm.MODULE_TIME.equals(tempmodule))
				{
				this.onChooseWorkPlace();
				return;
				}	
			if (ActivationForm.MODULE_TRAVEL.equals(tempmodule))
				{
				this.onStartTravel();
				return;
				}
			if (ActivationForm.MODULE_STORAGE.equals(tempmodule))
				{
				this.onToProductList();
				return;
				}
			}
		this.show();
		}
						
	if (c==CMD_EXIT)
		this.quitApplication();
			
	super.commandAction(c,d);
	}

}
