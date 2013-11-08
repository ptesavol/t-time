package com.enporia.util;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class CommonRemoveForm extends Form
{
private static CommonRemoveForm _instance=null;
private OwnStringItem confirmation=null;
//private StringItem confirmationLabel=null;
public static Command CANCEL= new Command(Props.get("common_cancel"), Command.CANCEL, 1);
public static Command OK= new Command(Props.get("common_ok"), Command.OK, 1);

private CommonRemoveForm()
	{
	super(Props.get("common_confirmation"));
	this.addCommand(OK);
	this.addCommand(CANCEL);
		
	this.confirmation=new OwnStringItem("","");
	//this.confirmationLabel=new StringItem("","");
	//this.append(this.confirmationLabel);
	this.confirmation.appendToForm(this);
	}
	
public static CommonRemoveForm instance(DataObject obj, String confirmation)
	{
	if (_instance==null)
		_instance=new CommonRemoveForm();
	
	_instance.confirmation.setLabel(confirmation+"\n");
	_instance.confirmation.setText(obj.getRenderingName());
	return _instance;	
	}
		

}
