package com.enporia.util;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public abstract class ViewForm extends Form
{
protected static Command CANCEL =  new Command(Props.get("common_cancel"), Command.CANCEL, 1);
protected static Command OK = new Command(Props.get("common_ok"), Command.OK, 1);

protected ViewForm(String title)
	{
	super(title);
	this.addCommand(OK);
	this.addCommand(CANCEL);
	}

 
}
