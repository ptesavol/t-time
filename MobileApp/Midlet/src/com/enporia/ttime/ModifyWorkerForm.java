package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ModifyWorkerForm extends ModifyForm
{
private static ModifyWorkerForm _instance=null;
private TextField nameField=null;
private TextField emailField=null;
private TextField emailServerField=null;
private TextField emailProxyField=null;
private TextField emailIMAPServerField=null; // 17.9.2008, J.V.
private TextField emailIMAPPortField=null; // 4.11.2009, J.V.
private ChoiceGroup emailuseIMAPEncryptedGroup=null; // 4.11.2009, J.V.
private ChoiceGroup nameAddressGroup=null;
private ChoiceGroup roundingGroup=null;
private TextField roundingField=null;
private OwnStringItem roundingItem=null;
private ChoiceGroup stringItemModeGroup=null;

private Worker worker=null;

private ChoiceGroup useProxyGroup=null;

private ModifyWorkerForm()
	{
	super(Props.get("modify_worker_title"));
	this.nameField=new TextField(Props.get("modify_worker_name"),"",64,TextField.ANY);
	this.emailField=new TextField(Props.get("modify_worker_email"),"",64,TextField.EMAILADDR);
	this.emailServerField=new TextField(Props.get("modify_worker_emailserver"),"",64,TextField.URL);
	this.emailProxyField=new TextField(Props.get("modify_worker_emailproxy"),"",64,TextField.URL);
	this.emailIMAPServerField=new TextField(Props.get("modify_worker_imapserver"),"",64,TextField.URL); // 17.9.2008, J.V.
	this.emailIMAPPortField=new TextField(Props.get("modify_worker_imapport"),"",8,TextField.ANY); // 4.11.2009, J.V.
    String[] encrypted = { Props.get("modify_worker_imapencrypted") }; // 4.11.2009, J.V.
	this.emailuseIMAPEncryptedGroup=new ChoiceGroup("",Choice.MULTIPLE,encrypted,null); // 4.11.2009, J.V. 	
	String[] proxynames={Props.get("modify_worker_smtp"),Props.get("modify_worker_http")};
	this.useProxyGroup=new ChoiceGroup(Props.get("modify_worker_connectiontype"),Choice.EXCLUSIVE,proxynames,null);
	String[] nameaddressnames={Props.get("modify_worker_namefirst"),Props.get("modify_worker_addressfirst")};
	this.nameAddressGroup=new ChoiceGroup(Props.get("modify_worker_nameoraddress"),Choice.EXCLUSIVE,nameaddressnames,null);
	String[] roundingnames={Props.get("modify_worker_roundnearest"),Props.get("modify_worker_roundnext")};
	this.roundingGroup=new ChoiceGroup(Props.get("modify_worker_rounding"), Choice.EXCLUSIVE, roundingnames,null);
	this.roundingField=new TextField("","",3, TextField.NUMERIC);
	this.roundingItem=new OwnStringItem(Props.get("modify_worker_roundingminutes"),"");
	String[] stringmodenames={Props.get("modify_worker_stringmodenormal"),Props.get("modify_worker_stringmodebig"),Props.get("modify_worker_stringmodebigenters")};
	this.stringItemModeGroup=new ChoiceGroup(Props.get("modify_worker_stringmode"), Choice.EXCLUSIVE, stringmodenames,null);
	
	this.append(this.nameField);
	this.append(this.emailField);
	this.append(this.useProxyGroup);
	this.append(this.emailServerField);
	this.append(this.emailProxyField);
	this.append(this.emailIMAPServerField); // 17.9.2008, J.V.
	this.append(this.emailIMAPPortField); // 4.11.2009, J.V.
	this.append(this.emailuseIMAPEncryptedGroup); // 4.11.2009, J.V.
	this.append(this.nameAddressGroup);
	this.append(this.roundingGroup);
	this.append(this.roundingField);
	this.roundingItem.appendToForm(this);
	this.append(this.stringItemModeGroup);
	}

public static ModifyWorkerForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ModifyWorkerForm();
	_instance.worker=(Worker)obj;
	_instance.nameField.setString(_instance.worker.getName());
	_instance.emailField.setString(_instance.worker.getEmail());
	_instance.emailServerField.setString(_instance.worker.getEmailServer());
	_instance.emailProxyField.setString(_instance.worker.getEmailProxy());
	_instance.emailIMAPServerField.setString(_instance.worker.getIMAPServer()); // 17.9.2008, J.V.
	_instance.emailIMAPPortField.setString(_instance.worker.getIMAPPort()); // 4.11.2009, J.V.

	if (_instance.worker.useIMAPEncrypted()) // 4.11.2009, J.V.
		_instance.emailuseIMAPEncryptedGroup.setSelectedIndex(0,true);
	else _instance.emailuseIMAPEncryptedGroup.setSelectedIndex(0,false);

	if (_instance.worker.useProxy())
		_instance.useProxyGroup.setSelectedIndex(1,true);
	else _instance.useProxyGroup.setSelectedIndex(0,true);
		
	if (_instance.worker.isNameFirst())
	   _instance.nameAddressGroup.setSelectedIndex(0,true);
	else _instance.nameAddressGroup.setSelectedIndex(1,true);   		
	
	if (_instance.worker.isRoundToNearest())
		_instance.roundingGroup.setSelectedIndex(0,true);
	else	_instance.roundingGroup.setSelectedIndex(1,true);
	
	_instance.roundingField.setString(""+_instance.worker.getRounding());
	
	_instance.stringItemModeGroup.setSelectedIndex(_instance.worker.getStringItemMode(),true);
	return _instance;	
	}
	
public DataObject getObject()
	{
	
	this.worker.setName(this.nameField.getString());
	this.worker.setEmail(this.emailField.getString());
	this.worker.setEmailServer(this.emailServerField.getString());
	this.worker.setEmailProxy(this.emailProxyField.getString());
	this.worker.setIMAPServer(this.emailIMAPServerField.getString()); // 17.9.2008, J.V.
	this.worker.setIMAPPort(this.emailIMAPPortField.getString()); // 4.11.2009, J.V.
	
	if (this.emailuseIMAPEncryptedGroup.isSelected(0)) // 4.11.2009, J.V.
		this.worker.setUseIMAPEncrypted(true);
	else this.worker.setUseIMAPEncrypted(false);

	if (this.useProxyGroup.getSelectedIndex()==0)
		this.worker.setUseProxy(false);
	else this.worker.setUseProxy(true);

	if (this.nameAddressGroup.getSelectedIndex()==0)
	   this.worker.setNameFirst(true);
	else this.worker.setNameFirst(false);   
	
	if (this.roundingGroup.getSelectedIndex()==0)
		this.worker.setRoundToNearest(true);
	else	this.worker.setRoundToNearest(false);
	
	long roo=-1;
	String temp=this.roundingField.getString();
	
	if (temp!=null && !"".equals(temp))
		{
		try 	{
			roo=Long.parseLong(temp);
			}
		catch (Exception e) {}
		}
	
	if (roo>=0)
		this.worker.setRounding(roo);
	
	this.worker.setStringItemMode(this.stringItemModeGroup.getSelectedIndex());
	
	return this.worker;
	}

}
