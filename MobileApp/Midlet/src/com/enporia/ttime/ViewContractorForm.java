package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ViewContractorForm extends ViewForm
{
private static ViewContractorForm _instance=null;
//private OwnStringItem nameitemlabel=null;
//private OwnStringItem emailitemlabel=null;
private OwnStringItem nameitem=null;
private OwnStringItem emailitem=null;


private ViewContractorForm()
	{
	super(Props.get("view_contractor_title"));
	//this.nameitemlabel=new OwnStringItem(Props.get("view_contractor_name") +"\n","");
	//this.emailitemlabel=new OwnStringItem(Props.get("view_contractor_email") +"\n","");
	this.nameitem=new OwnStringItem(Props.get("view_contractor_name") +"\n","");
	this.emailitem=new OwnStringItem(Props.get("view_contractor_email") +"\n","");	

	//this.append(this.nameitemlabel);
	this.nameitem.appendToForm(this);
	//this.append(this.emailitemlabel);
	this.emailitem.appendToForm(this);
	}
	
public static ViewContractorForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ViewContractorForm();
	Contractor cont=(Contractor)obj;
	_instance.nameitem.setText(cont.getName());
	_instance.emailitem.setText(cont.getEmail());
	
	return _instance;	
	}
		

}
