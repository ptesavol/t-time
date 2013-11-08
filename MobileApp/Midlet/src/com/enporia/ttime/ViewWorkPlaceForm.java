package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ViewWorkPlaceForm extends ViewForm
{
private static ViewWorkPlaceForm _instance=null;

private OwnStringItem nameItem = null;
private OwnStringItem addressItem = null;
private OwnStringItem noteItem = null;
private OwnStringItem infoItem = null;



private ViewWorkPlaceForm()
	{
	super(Props.get("view_workplace_title"));
	this.nameItem=new OwnStringItem("","");
	this.addressItem=new OwnStringItem("","");
	this.noteItem=new OwnStringItem("","");
	this.infoItem=new OwnStringItem("","");
	
	this.nameItem.appendToForm(this);
	this.addressItem.appendToForm(this);
	this.noteItem.appendToForm(this);
	this.infoItem.appendToForm(this);
	}

public static ViewWorkPlaceForm instance(DataObject obj)
	{
	WorkPlace tplace=(WorkPlace)obj;
	
	if (_instance==null)
		_instance=new ViewWorkPlaceForm();

	_instance.nameItem.setText(tplace.getName()+"\n"); 
	_instance.addressItem.setText(tplace.getAddress()+"\n"); 
	_instance.noteItem.setText("".equals(tplace.getNote()) ?"":(tplace.getNote()+"\n")); 
	_instance.infoItem.setText(tplace.getInfo()); 
	
	return _instance;
	}
}
