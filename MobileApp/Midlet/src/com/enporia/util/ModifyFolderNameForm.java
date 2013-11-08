package com.enporia.util;



import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ModifyFolderNameForm extends ModifyForm
{
private static ModifyFolderNameForm _instance=null;
private static FolderName cont=null;
private TextField nameField=null;



private ModifyFolderNameForm()
	{
	super(Props.get("modify_foldername_title"));
	this.nameField=new TextField(Props.get("modify_foldername_name"),"",20,TextField.ANY);
	this.append(this.nameField);
	}
	
public static ModifyFolderNameForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ModifyFolderNameForm();
	cont=(FolderName)obj;
	_instance.nameField.setString(cont.getName());
	
	return _instance;	
	}
		
public DataObject getObject()
	{
	cont.setName(this.nameField.getString());
	return cont;
	}
}
