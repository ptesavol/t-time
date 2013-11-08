package com.enporia.util;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public abstract class ModifyForm extends Form
{
public static Command CANCEL= new Command(Props.get("common_cancel"), Command.CANCEL, 1);
public static Command OK= new Command(Props.get("common_ok"), Command.OK, 1);

protected ModifyForm(String title)
	{
	super(title);
	this.addCommand(OK);
	this.addCommand(CANCEL);
	}

public abstract DataObject getObject(); 
}
