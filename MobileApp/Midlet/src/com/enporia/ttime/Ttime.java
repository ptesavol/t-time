package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class Ttime extends MIDlet implements CommandListener
{
private boolean firstStart=true;

public Ttime()
	{
	ContractorList.init(this,this);
	WorkPlaceList.init(this,this);
	WorkPlaceFolderList.init(this,this);
	SettingsList.init(this,this);
	WorkTypeList.init(this,this);
	WorkUnitFolderList.init(this,this);
	WorkUnitList.init(this,this);
	ProductList.init(this,this);
	ProductFolderList.init(this,this);
	OwnStringItem.init(Worker.instance().getStringItemMode());
	}

public void startApp()
	{
	if (this.firstStart)
		{	
		DataInserter.insertDefaultContractors();
		DataInserter.insertWorkPlacesFromDisk();
		
		DataInserter.insertDefaultWorker();
		DataInserter.insertDefaultWorkTypes();
        System.gc();
        	//DataInserter.insertProductsFromDisk();
		//DataInserter.insertTestWorkUnits();
		
		this.firstStart=false;
		}
	String foldername=ProgramState.instance().getSelectedWorkPlaceFolder();	
	WorkPlaceList.instance().setName(foldername);
	ProductList.instance().setName(ProgramState.instance().getSelectedProductFolder());
	
	if (ProgramState.instance().isTravelling())
	   {
	   WorkPlaceList.instance().buildVisibleList();
	   WorkPlaceList.instance().setSelectedIndex(ProgramState.instance().getSelectedWorkPlace());
	   WorkPlaceList.instance().show();
	   WorkPlaceList.instance().startTravelling(ProgramState.instance().getTravelStartTime(), ProgramState.instance().getTravelStartMeter());
	   return;
	   }
	try 	{	
		if (ProgramState.instance().isEmpty())
			{	
			WorkPlaceList.instance().show();
			}
		
		else 	{
			WorkPlaceList.instance().buildVisibleList();
			WorkTypeList.instance().buildVisibleList();
			
			WorkPlaceList.instance().setSelectedIndex(ProgramState.instance().getSelectedWorkPlace());
			WorkTypeList.instance().setSelectedIndex(ProgramState.instance().getSelectedWorkType());
			WorkTypeList.instance().show();
			WorkTypeList.instance().startWork(ProgramState.instance().getStartTime());
			}
		}
	catch (Exception e)
		{
		WorkPlaceList.instance().show();
		}		
	}

public void pauseApp()
	{}

public void destroyApp(boolean unconditional)
	{}

public void commandAction(Command c, Displayable d)
	{
	if (c==ShowableList.DESTROY_APP)
		{
		this.destroyApp(false);
        	this.notifyDestroyed();
		}
	
	}
}
