package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;


public class SettingsList extends ShowableList
{
private static String[] data = 	{
				Props.get("settings_contractors"),
				Props.get("settings_email"),
				Props.get("getlists_getlists"), // 29.9.2008, J.V.
				Props.get("sendlists_sendlists") // 6.10.2008, J.V.
				};
private static Command MODIFY_SETTING = new Command(Props.get("settings_modify"), Command.ITEM, 2);
private static Command SETTINGS_BACK = new Command(Props.get("common_back"), Command.BACK, 2);

private static SettingsList _instance;
private static MIDlet _midlet=null;
private static CommandListener _listener=null;

private ModifyWorkerForm modifyworkerform=null;
private IMAPGetListsForm imapgetlistsform=null; // 29.9.2008, J.V.
private IMAPSendListsForm imapsendlistsform=null; // 6.10.2008, J.V.

public static void init(MIDlet midlet, CommandListener commandlistener)
	{
	_midlet=midlet;
	_listener=commandlistener;
	}
	
private SettingsList()
	{
	super(Props.get("settingslist_title"),_midlet,_listener,data);
	
	}

public static SettingsList instance()
	{
	if (_midlet==null)
		return null;
	if (_instance==null)
		_instance=new SettingsList();
	return _instance;
	}	

public void show()
	{
	super.show();
	addCommand(MODIFY_SETTING);	
	addCommand(SETTINGS_BACK);	
	}

// Callback implementations

public void onModifySetting()
	{
	if (super.getSelectedString().equals(Props.get("settings_contractors")))
		{
		ContractorList.instance().show();
		}
	if (super.getSelectedString().equals(Props.get("settings_email")))
		{
		this.modifyworkerform=ModifyWorkerForm.instance(Worker.instance());	
		this.modifyworkerform.setCommandListener(this);
		super.display.setCurrent(this.modifyworkerform);
		}
	if (super.getSelectedString().equals(Props.get("getlists_getlists"))) // 29.9.2008, J.V.
		{
		this.imapgetlistsform = IMAPGetListsForm.instance(IMAPEmail.instance());
		super.display.setCurrent(this.imapgetlistsform);
		}
    if (super.getSelectedString().equals(Props.get("sendlists_sendlists"))) // 6.10.2008, J.V.
    	{
		this.imapsendlistsform = IMAPSendListsForm.instance(IMAPEmailSend.instance());
		super.display.setCurrent(this.imapsendlistsform);
    	}
	
	}

public void onSettingsBack()
	{
	WorkPlaceList.instance().buildVisibleList();
	WorkPlaceList.instance().show();
	}

public void onModifyWorkerOk()
	{
	((Worker)this.modifyworkerform.getObject()).save();
	this.show();
	}
	
public void onModifyWorkerCancel()
	{
	this.show();
	}

/**
* The CommandListener implementation
*/

public void commandAction(Command c, Displayable d)
	{
	if (c==MODIFY_SETTING || c == List.SELECT_COMMAND)
		this.onModifySetting();
			
	if (c==SETTINGS_BACK)
		this.onSettingsBack();
	
	if (c==ModifyWorkerForm.OK)
		this.onModifyWorkerOk();
	
	if (c==ModifyWorkerForm.CANCEL)
		this.onModifyWorkerCancel();
		
	super.commandAction(c,d);
	}

}
