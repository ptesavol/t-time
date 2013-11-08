package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class TravelBox extends TextBox
{
private static TravelBox _instance=null;
public static Command TRAVEL_OK = new Command(Props.get("common_ok"), Command.OK, 1);
public static Command TRAVEL_CANCEL = new Command(Props.get("common_cancel"), Command.CANCEL, 1);


public static TravelBox instance(String seed)
	{
	if (_instance==null)
		_instance=new TravelBox();
	_instance.setString(seed);
	return _instance;
	}

private TravelBox()
	{
	super(Props.get("travelbox_title"),"",32,TextField.NUMERIC);
	
	addCommand(TRAVEL_OK);
	addCommand(TRAVEL_CANCEL);
	}
	
}
