package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ModifyContractorForm extends ModifyForm
{
private static ModifyContractorForm _instance=null;
private static Contractor cont=null;
private TextField nameField=null;
private TextField emailField=null;


private ModifyContractorForm()
	{
	super(Props.get("modify_contractor_title"));
	this.nameField=new TextField(Props.get("modify_contractor_name"),"",64,TextField.ANY);
	this.emailField=new TextField(Props.get("modify_contractor_email"),"",64,TextField.EMAILADDR);
	this.append(this.nameField);
	this.append(this.emailField);
	}
	
public static ModifyContractorForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ModifyContractorForm();
	cont=(Contractor)obj;
	_instance.nameField.setString(cont.getName());
	_instance.emailField.setString(cont.getEmail());
	
	return _instance;	
	}
		
public DataObject getObject()
	{
	cont.setName(this.nameField.getString());
	cont.setEmail(this.emailField.getString());
	return cont;
	}
}
