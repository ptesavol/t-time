package com.enporia.util;


import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class AddFolderNameForm extends AddForm
{
private static AddFolderNameForm _instance=null;
private TextField nameField=null;


private AddFolderNameForm()
	{
	super(Props.get("add_foldername_title"));
	this.nameField=new TextField(Props.get("add_foldername_name"),"",20,TextField.ANY);
	this.append(this.nameField);
	}
	
public static AddFolderNameForm instance()
	{
	if (_instance==null)
		_instance=new AddFolderNameForm();
	_instance.nameField.setString("");
	
	return _instance;	
	}	
public DataObject getObject()
	{
	return new FolderName(this.nameField.getString());
	}
}
