package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ModifyWorkPlaceForm extends ModifyForm
{
private static ModifyWorkPlaceForm _instance=null;

private TextField nameField=null;
private TextField addressField=null;
private TextField noteField=null;
private TextField shortNoteField=null;
private TextField infoField=null;
private ChoiceGroup contractorGroup=null;
private int choiceindex=-1;

private ModifyWorkPlaceForm()
	{
	super(Props.get("modify_workplace_title")); 
	this.nameField=new TextField(Props.get("add_workplace_name"),"",160,TextField.ANY);
	this.addressField=new TextField(Props.get("add_workplace_address"),"",160,TextField.ANY);
	this.noteField=new TextField(Props.get("add_workplace_note"),"",160,TextField.ANY);
	this.shortNoteField=new TextField(Props.get("add_workplace_shortnote"),"",160,TextField.ANY);
	this.infoField=new TextField(Props.get("add_workplace_info"),"",160,TextField.ANY);
	
	String[] contractornames=ContractorList.instance().getElementRenderingNames();
	this.contractorGroup=new ChoiceGroup(Props.get("add_workplace_contractor"),Choice.EXCLUSIVE,contractornames,null);
	
	this.append(this.nameField);
	this.append(this.addressField);
	this.choiceindex=this.append(this.contractorGroup);
	this.append(this.noteField);
	this.append(this.shortNoteField);
	this.append(this.infoField);
	}
	
public static ModifyWorkPlaceForm instance(DataObject object)
	{
	WorkPlace place=(WorkPlace)object;
	if (_instance==null)
		_instance=new ModifyWorkPlaceForm();
	
	String[] contractornames=ContractorList.instance().getElementRenderingNames();
	_instance.contractorGroup=new ChoiceGroup(Props.get("add_workplace_contractor"),Choice.EXCLUSIVE,contractornames,null);
	_instance.set(_instance.choiceindex,_instance.contractorGroup);
	
	
	String tcont=place.getContractor();
	for (int i=0; i<contractornames.length; i++)
		{
		if (tcont.equals(contractornames[i]))
			_instance.contractorGroup.setSelectedIndex(i,true);		
		}
	
	_instance.nameField.setString(place.getName());
	_instance.addressField.setString(place.getAddress());
	_instance.noteField.setString(place.getNote());
	_instance.shortNoteField.setString(place.getShortNote());
	_instance.infoField.setString(place.getInfo());
	
	
	
	
	return _instance;	
	}	
public DataObject getObject()
	{
	return new WorkPlace( this.nameField.getString(),this.addressField.getString(),
			this.noteField.getString(), 
			this.contractorGroup.getString(this.contractorGroup.getSelectedIndex()),
			this.shortNoteField.getString(), this.infoField.getString());
	}
}
