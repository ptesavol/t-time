package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class AddWorkPlaceForm extends AddForm
{
private static AddWorkPlaceForm _instance=null;

private TextField nameField=null;
private TextField addressField=null;
private TextField noteField=null;
private TextField shortNoteField=null;
private TextField infoField=null;
private ChoiceGroup contractorGroup=null;
private int choiceindex=-1;

private AddWorkPlaceForm()
	{
	super(Props.get("add_workplace_title")); 
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
	
public static AddWorkPlaceForm instance()
	{
	if (_instance==null)
		{
		if (ContractorList.instance().size()==0)
			return null;
		_instance=new AddWorkPlaceForm();
		}
	else	{
		String[] contractornames=ContractorList.instance().getElementRenderingNames();
		_instance.contractorGroup=new ChoiceGroup(Props.get("add_workplace_contractor"),Choice.EXCLUSIVE,contractornames,null);
		_instance.set(_instance.choiceindex,_instance.contractorGroup);
		}	
	_instance.nameField.setString("");
	_instance.addressField.setString("");
	_instance.noteField.setString("");
	_instance.shortNoteField.setString("");
	_instance.infoField.setString("");
	_instance.contractorGroup.setSelectedIndex(0,true);
	return _instance;	
	}	
public DataObject getObject()
	{
	
	return new WorkPlace( this.nameField.getString(),this.addressField.getString(),
			this.noteField.getString(), 
			this.contractorGroup.getString(this.contractorGroup.getSelectedIndex()),
			this.shortNoteField.getString(), this.infoField.getString()
			 );
	}
}
