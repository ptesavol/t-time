package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class AddContractorForm extends AddForm
{
private static AddContractorForm _instance=null;
private TextField addContractorNameField=null;
private TextField addContractorEmailField=null;


private AddContractorForm()
	{
	super(Props.get("add_contractor_title"));
	this.addContractorNameField=new TextField(Props.get("add_contractor_name"),"",32,TextField.ANY);
	this.addContractorEmailField=new TextField(Props.get("add_contractor_email") ,"",32,TextField.EMAILADDR);
	this.append(this.addContractorNameField);
	this.append(this.addContractorEmailField);
	}
	
public static AddContractorForm instance()
	{
	if (_instance==null)
		_instance=new AddContractorForm();
	_instance.addContractorNameField.setString("");
	_instance.addContractorEmailField.setString("");
	
	return _instance;	
	}	
public DataObject getObject()
	{
	return new Contractor(this.addContractorNameField.getString(),this.addContractorEmailField.getString());
	}
}
