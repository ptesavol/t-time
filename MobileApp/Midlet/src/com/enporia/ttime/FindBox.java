package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class FindBox extends TextBox
{
private static FindBox _instance=null;
public static Command FIND_OK = new Command(Props.get("common_ok"), Command.OK, 1);
public static Command FIND_CANCEL = new Command(Props.get("common_cancel"), Command.CANCEL, 1);


public static FindBox instance(String seed)
	{
	if (_instance==null)
		_instance=new FindBox();
	_instance.setString(seed);
	return _instance;
	}

private FindBox()
	{
	super(Props.get("findbox_title"),"",32,TextField.ANY);
	
	addCommand(FIND_OK);
	addCommand(FIND_CANCEL);
	}
	
}
