package com.enporia.ttime;

import javax.microedition.lcdui.Choice;
import javax.microedition.lcdui.ChoiceGroup;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.CustomItem;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Item;
import javax.microedition.lcdui.ItemStateListener;
import javax.microedition.lcdui.TextField;

import com.enporia.util.*;
import com.enporia.util.Attachments.Attachment;

import java.io.*;
import java.util.Vector;

public class IMAPGetListsForm extends Form implements CommandListener
{	
	class IMAPGetEmailThread extends Thread
	{
		IMAPEmailConnection connection=null;
		
		public IMAPGetEmailThread() {}

		private void reportStatus(String str)
		{
			//String lf = (status_text.equals("") ? "" : "\n");
			
			status_text = /*status_text + lf +*/ str;
			statusItem.setText(status_text);
		}
		
		public void run()
		{
		ThreadRunning = true;
			
		removeCommand(IMAPGETFORM_CANCEL);  // Disable input, remove all the controls from the form, excluding statusItem
		removeCommand(IMAPGETFORM_OK);
		while(_instance.size() > 1) _instance.delete(0);
		
		try {
			/*String mes = "dC1haWthLWxpc3RhdDoJMDYuMTAuMjAwOAkxMTozNwpbbGFza3V0dGFqYXRdCTcKQS5TCQpBYXJuZQkKSk9VTkkJCkxhc2t1dHRhamEgMTAJCkxhc2t1dHRhamEgMTcJZW1hbGlAZW1hbGlhCkxhc2t1dHRhamEgMTkJCkxhc2t1dHRhamEgMjEJaGVpcHBhClthc2lha2thYXRdCTExMwo5CVN5duRyaW50aWUgMjkJc2FtYSBvc29pdGUJaHVvbQlseWh5dAlsaXPkCUpPVU5JCSAKCVN5duRyaW4gcmFudGEJCQkJCUEuUwkxMAoJU3l25HJpbiBwdWlzdG8JCQkJCUEuUwkgCglTeXbkcmkgMgkJCQkJQS5TCSAKCUlsbWFyaW50aSBlNAkJCQkJQS5TCSAKCVJhbnRhcHVpc3RvCQkJCQlBLlMJIyMjCglKYWFra28gUmFudHNpCQkJCQlBLlMJIyMjCglUb3Jpbmt1bG1hCQkJCQlBLlMJIyMjCglTeXbkcmluIG5paXR0eQkJCQkJQS5TCSMjIwoJU3l25HJpbiBrdWxtYQkJCQkJQS5TCSMjIwoJVG9pbmkgUGlyaW5lbgkJCQkJQS5TCSMjIwo0CVJlaWpvIEhlaXNrYW5lbgkJCQkJQS5TCSMjIwo3CVdlZW1hbiBKYW5pCQkJCQlBLlMJIyMjCglTYXZvbGFpbmVuIE9sYXZpCQkJCQlBLlMJIyMjCglQZWtrYSBIYXJ0aWthaW5lbgkJCQkJQS5TCSMjIwoJSm9ybWEgQXV0aW8JCQkJCUEuUwkjIyMKCUxlcHDka3VqYQkJCQkJQS5TCSMjIwoJUORpdmluZW4gTWlra28JCQkJCUEuUwkjIyMKCUtvaXZ1cmFudGEJCQkJCUEuUwkjIyMKCUvkcmtr5GluZW4gUmVpam8JCQkJCUEuUwkjIyMKCVRpaWhvbmVuIFBla2thCQkJCQlBLlMJIyMjCglVbnRvIE5pc2thbmVuCQkJCQlBLlMJIyMjCglLb3BvbmVuIFJhaW1vCQkJCQlBLlMJIyMjCglFc2tvIFLkc+RuZW4JCQkJCUEuUwkjIyMKCVbk5HTkaW5lbiBNYXR0aQkJCQkJQS5TCSMjIwoJU2luaWtrYSBIYXJ0aWthaW5lbgkJCQkJQS5TCSMjIwoJSGFhcGFyaW5uZQkJCQkJQS5TCSMjIwoJTGV25G5pZW1lbnRpZSAzLzUJCQkJCUEuUwkjIyMKCVBpdGvkbmVuIEF1bGlzCQkJCQlBLlMJIyMjCglIaXJ2b25lbiBUb2l2bwkJCQkJQS5TCSMjIwoJIEhhcnJpICAgaGFydG9qb2tpCQkJCQlBLlMJIyMjCglQ5Gl25HJhbnRhCQkJCQlBLlMJIyMjCgkgUmlubmVwb2xrdSA0CQkJCQlBLlMJIyMjCjEwCUpvcm1hbmt1bG1hCQkJCQlBLlMJIyMjCglBcnZvIExpZXZvbmVuCQkJCQlBLlMJIyMjCglLaXJra290aWUgMQkJCQkJQS5TCSMjIwoJTmlza2FuZW4gSmFha2tvCQkJCQlBLlMJIyMjCglBaG9uZW4gTWFya2t1CQkJCQlBLlMJIyMjCglQaXJpbmVuIEVpbm8JCQkJCUEuUwkjIyMKCU5pbHNp5G4gRWxla3Ryb25paWtrYQkJCQkJQS5TCSMjIwoJTWFpamEgUuRz5G5lbgkJCQkJQS5TCSMjIwoxMQlNYWxpbmVuIEp1aG8JCQkJCUEuUwkjIyMKCUFob25lbiBLYXJpCQkJCQlBLlMJIyMjCglIb2xvcGFpbmVuIFRvaXZvCQkJCQlBLlMJIyMjCglTZXBwbyBIZWlra2luZW4JCQkJCUEuUwkjIyMKCU1hdGhhbHQgSmFyaQkJCQkJQS5TCSMjIwoJVGF1bm8gVG9pdmFuZW4JCQkJCUEuUwkjIyMKCVRhc2tpbmVuL1RhbGd2aXN0CQkJCQlBLlMJIyMjCglLYXRyaSBUb2l2YW5lbgkJCQkJQS5TCSMjIwoJQWxhdGFsbyBNYXJra3UJCQkJCUEuUwkjIyMKCU11bW1vCQkJCQlBLlMJIyMjCglWZWlra28gSGFydGlrYWluZW4JCQkJCUEuUwkjIyMKCVJpc3RvIEhlaWtraW5lbgkJCQkJQS5TCSMjIwoJQXJpIEhhc3NpbmVuCQkJCQlBLlMJIyMjCglNaWV0dGluZW4gTWFya2t1CQkJCQlBLlMJIyMjCglMaWlzYSBKb3VzaWxhaHRpCQkJCQlBLlMJIyMjCglKdWhvbGFucGVsdG8JCQkJCUEuUwkjIyMKCVBhYXZpbGFpbmVuIE1hdHRpCQkJCQlBLlMJIyMjCglSaXNzYW5lbiBWZWVyYQkJCQkJQS5TCSMjIwoJSGlsdHVuZW4gUmlpdHRhCQkJCQlBLlMJIyMjCglIeXb2bmVuIE1pa+QJCQkJCUEuUwkjIyMKCUhlbGx1bnRhaSBzcmsJCQkJCUEuUwkjIyMKCVB59nLkLSBNYW5uaW5lbgkJCQkJQS5TCSMjIwoJUGVudGlr5GluZW4gSnVra2EJCQkJCUEuUwkjIyMKMTUJU3l25HJpbiBwaWhhCQkJCQlBLlMJIyMjCjgJTVAtVGFoa29z5Ghr9gkJCQkJQS5TCSMjIwoJUGlzYW50aWUgMjAJCQkJCUEuUwkjIyMKCVN5duRyaW50aWUgMTIJCQkJCUEuUwkjIyMKCVBhc2kga29ya2FsYWluZW4JCQkJCUEuUwkjIyMKMwlSaXR2YSBLdW9zbWFuZW4JCQkJCUEuUwkjIyMKCVBlbnR0aSBLb3Job25lbgkJCQkJQS5TCSMjIwoJS290aXBvbGt1IDkJCQkJCUEuUwkjIyMKCVRlcnR0dSBTYWFyZWxhaW5lbgkJCQkJQS5TCSMjIwoJTeRudHl0aWUgMTcJCQkJCUEuUwkjIyMKCUtvdGlwb2xrdSAxMQkJCQkJQS5TCSMjIwoJUGV0cmkgRHVyY2htYW4JCQkJCUEuUwkjIyMKMTYJQWlub2xhCQkJCQlBLlMJIyMjCglQaXJqbyBW5OR05GluZW4JCQkJCUEuUwkjIyMKCUh1dXNrb25lbiBUaW1vCQkJCQlBLlMJIyMjClNla2FsYWlzZXQJQXkJCQkJCUEuUwkjIyMKCU9tYXQgcGVsbG90CQkJCQlBLlMJIyMjCglUdW9tYXMJCQkJCUEuUwkjIyMKCUthcmkJCQkJCUEuUwkjIyMKCU9zbW8JCQkJCUEuUwkjIyMKCUhhYXJhIFRlcnR0dQkJCQkJQS5TCSMjIwoJRXNhCQkJCQlBLlMJIyMjCglBaHRpIEh1b3RhcmkJCQkJCUEuUwkjIyMKCVNhdm9uIFZvaW1hCQkJCQlBLlMJIyMjCgnEeQkJCQkJQS5TCSMjIwpLdXRzdXBhaWthdAlNZXJqYSBIaWx0dW5lbgkJCQkJQS5TCSMjIwoJVmFsa29uZW4gbGlpdC4gKzEwY20JCQkJCUEuUwkjIyMKCVDkaXbkcmFudGEJCQkJCUEuUwkjIyMKCU9sbGluIGt1bG1hCQkJCQlBLlMJIyMjCglSaW5uZXBvbGt1IDQJCQkJCUEuUwkjIyMKCUthbGxlbmt1bG1hCQkJCQlBLlMJIyMjCjIJbXV1bnRvYXNlbWEJCQkJCUEuUwkjIyMKCWzkbXD2a2Vza3VzCQkJCQlBLlMJIyMjCglTdixwYWx2ZWx1dG9pbWlzdG8JCQkJCUEuUwkjIyMKMTIJTGVpdm9udGllIDYJCQkJCUEuUwkjIyMKCUxlaXZvbnRpZSA0CQkJCQlBLlMJIyMjCglMZWl2b250aWUgMgkJCQkJQS5TCSMjIwoJTGVpdm9udGllIDEJCQkJCUEuUwkjIyMKMTMJVGlsaGludGllIDEtMyBUaWxoaWzkCQkJCQlBLlMJIyMjCglUaWxoaW50aWUgMgkJCQkJQS5TCSMjIwoJU2llbml0aWUgMi00IHZhbmguc3Vvai4JCQkJCUEuUwkjIyMKMTgJS2FyaGl0aWUgMwkJCQkJQS5TCSMjIwoxNAlMYWF0b2thbnRpZSAyLTQJCQkJCUEuUwkjIyMKMQlLYXVwdW5raSwga2lpbnRlaXN09nQJCQkJCUEuUwkjIyMKUmVodW50ZWtvCUVzYSAJCQkJCUEuUwkjIyMKQXV0b21hYXR0aW5lbglQZXJ0dGkgVG9pdmFuZW4JCQkJCUFhcm5lCSMjIwoJUmVpbm8gTmlpcmFuZW4JCQkJCUFhcm5lCSMjIwoJTWlpYSBIb2xsYW5kZXIJCQkJCUFhcm5lCSMjIwpLWUxBCUFCQwkJCQkJSk9VTkkJIyMjClRZSErEClt0efZ0eXlwaXRdCTMwCkx1bWl0efYsIHRyYWt0b3JpbGxhCXZpCkx1bWl0efYsIG1pZXMJClB1dXJvc2thdCwgbWllcwkKCSMjI18xCkhpZWtvaXR1cywgdHJha3RvcmkJIyMjClD2eWhpbnTkCSMjIwpNdXUgdHn2CSMjIwpOaWl0dG8JIyMjClRpZW4gbGFuYXVzCSMjIwpSZWh1bnRla28JIyMjClBpaGF0efYsIHRyYWt0b3JpCSMjIwpQdXVyb3NrYXQsIHRyYWt0b3JpCSMjIwpQdXVuYWpvLCB0cmFrdG9yaQkjIyMKSHVvbHRvdHn2CSMjIwpLeWx29gkjIyMKSnly5HlzCSMjIwrEZXN0eXMJIyMjCktpdmVuIGFqbwkjIyMKTGFubm9pdHVzIGvkcnJpbGzkCSMjIwpIaWVrYW5wb2lzdG8sIG1pZXMJIyMjCktpcmphbnBpdG8JIyMjCkthdHRvbHVtZXQsIG1pZXMJIyMjCkhpZWthbnBvaXN0bywgdHJha3RvcmkJIyMjClZhbHZvbnRhCSMjIwpNaWVzdHn2CSMjIwpWYXJhc3RvaW50aQkjIyMKUGFhbGF1cyAJIyMjCmx1bWl0efYJIyMjClN1dW5uaXR0ZWx1CSMjIwpoaWVrb2l0dXMJIyMjClt0dW90dGVldF0JNgpPbGV0dXMJS09JVlVMQUEJSjVNMzMJTAkxMi43OAkxMi4yCTAuMDAKCUhFTExBUFVVCSMjIwkgCSAJIAkgCkhBTEtPCUxFUFDECTEyMDkzCW1vdHRpCTAJMAkwLjAwCmhhbGFrbwlNQU5TSUtLQQkjIyMJIAkwCTAJMAoJTVVTVElLS0EJIyMjCQkwCTAJMTIKVFlISsQK";
			connection = new IMAPEmailConnection();	
			Attachments.instance().addAttachment(mes.getBytes(), "", "base64", Attachments.DECODE);
			DataInserter.insertFromAttachment(Attachments.instance().getAttachmentBytes(0), true);
			if(true) throw new CustomException("ohi");*/

			// Open connection
			reportStatus(Props.get("sendgetlists_open") + " '" + Worker.instance().getIMAPServer() + "'...");
			connection = new IMAPEmailConnection();
			connection.open(Worker.instance().getIMAPServer(), "", Worker.instance().getIMAPPort(), Worker.instance().useIMAPEncrypted());
				
			// Confirm connection, login, select inbox, get attachment(s), ...
			Attachments.instance().clear();                          // free previous
			reportStatus(Props.get("getlists_login"));
			connection.login(usernameField.getString(), passwordField.getString(), statusItem);

			// Process attachments
			if(Attachments.instance().getSize() > 0)
			{
				// Add data from the attachment(s)
				reportStatus(Props.get("getlists_attfound_1") + " " + Attachments.instance().getSize() + " " + Props.get("getlists_addfound_2") + "\n" + Props.get("getlists_examlist"));

				for(int i=0; i<Attachments.instance().getSize(); i++)
					DataInserter.insertFromAttachment(Attachments.instance().getAttachmentBytes(i), getMode.getSelectedIndex() == 0 ? false : true);

				reportStatus(Props.get("getlists_ok"));
			}
			}
		catch (CustomException e1)
			{
			reportStatus(Props.get("sendgetlists_error") + " " + e1.toString());
			}
		catch (Exception e1)
			{
			reportStatus(Props.get("emailform_connectionfailure") + "\n" + e1.toString());
			e1.printStackTrace();
			}
		finally
			{
			if(connection != null) connection.close();
			}

		addCommand(IMAPGETFORM_CANCEL);
		//addCommand(IMAPGETFORM_OK);
		
		ThreadRunning = false;
		}
	}

public static Command IMAPGETFORM_CANCEL = new Command(Props.get("common_back"), Command.CANCEL, 2);
public static Command IMAPGETFORM_OK = new Command(Props.get("common_get"), Command.OK, 1);

private TextField usernameField = null;
private TextField passwordField = null;
private ChoiceGroup storeUsername = null;
private ChoiceGroup storePassword = null;
private ChoiceGroup getMode = null;
private OwnStringItem statusItem=null;

private static IMAPGetListsForm _instance=null;
private IMAPGetEmailThread IMAPGetThread=null;

private IMAPEmail imapemail=null;

private boolean ThreadRunning = false;

private String status_text = "";

private IMAPGetListsForm()
	{
	super(Props.get("getlists_getlists"));
	setCommandListener(this);
	
	this.usernameField = new TextField(Props.get("getlists_username"),"",64,TextField.ANY);
	this.passwordField = new TextField(Props.get("getlists_password"),"",64,TextField.ANY|TextField.PASSWORD|TextField.SENSITIVE);
    String[] un = { Props.get("getlists_storeusername") };
	this.storeUsername = new ChoiceGroup("",Choice.MULTIPLE,un,null);
    String[] pw = { Props.get("getlists_storepassword") };
	this.storePassword = new ChoiceGroup("",Choice.MULTIPLE,pw,null);
	String[] mode = {Props.get("getlists_update"), Props.get("getlists_clear")};
	this.getMode = new ChoiceGroup(Props.get("getlists_modeprompt"), Choice.EXCLUSIVE, mode, null);
	this.statusItem = new OwnStringItem("","");
	}

public static IMAPGetListsForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new IMAPGetListsForm();
	
		_instance.deleteAll();
		_instance.append(_instance.usernameField);
		_instance.append(_instance.storeUsername);
		_instance.append(_instance.passwordField);
		_instance.append(_instance.storePassword);
		_instance.append(_instance.getMode);
		_instance.statusItem.appendToForm(_instance);

		_instance.removeCommand(IMAPGETFORM_OK);
		_instance.removeCommand(IMAPGETFORM_CANCEL);
		_instance.addCommand(IMAPGETFORM_OK);
		_instance.addCommand(IMAPGETFORM_CANCEL);
		_instance.statusItem.setText("");
		
		_instance.status_text = "";
		
		if(obj != null) _instance.imapemail = (IMAPEmail)obj;
	
		if(_instance.imapemail.isStoreUsername())
        {
			_instance.storeUsername.setSelectedIndex(_instance.storeUsername.size() - 1, true);
			_instance.usernameField.setString(_instance.imapemail.getStored_Username());
        }
		else
		{
			_instance.storeUsername.setSelectedIndex(_instance.storeUsername.size() - 1, false);
			_instance.usernameField.setString("");
		}
		
		if(_instance.imapemail.isStorePassword())
        {
			_instance.storePassword.setSelectedIndex(_instance.storePassword.size() - 1, true);
			_instance.passwordField.setString(_instance.imapemail.getStored_Password());
        }
		else
		{
			_instance.storePassword.setSelectedIndex(_instance.storePassword.size() - 1, false);
			_instance.passwordField.setString("");
		}
		
		/*if (_instance.imapemail.getAtt_GetMode())
			_instance.getMode.setSelectedIndex(1,true);
		else
			_instance.getMode.setSelectedIndex(0,true);*/
		_instance.getMode.setSelectedIndex(0, true);
		
		return _instance;
	}

public void commandAction(Command c, Displayable d)
	{
		if (c==IMAPGETFORM_CANCEL || c==CommonRemoveForm.CANCEL)
		{
			Attachments.instance().clear();                          // free up some memory
		
			((IMAPEmail)this.getObject()).save();
			SettingsList.instance().show();
		}

		if(c==IMAPGetListsForm.IMAPGETFORM_OK)
		{
			this.IMAPGetThread = new IMAPGetEmailThread();
			this.IMAPGetThread.start();
		}
	}

public DataObject getObject()
{
	boolean sel_un = this.storeUsername.isSelected(this.storeUsername.size() - 1);
	//boolean sel_pw = this.storePassword.isSelected(this.storePassword.size() - 1);

	this.imapemail.setStoreUsername(sel_un);
	if(sel_un) this.imapemail.setStored_Username(this.usernameField.getString());
	else this.imapemail.setStored_Username("");

	this.imapemail.setStorePassword(sel_un);
	if(sel_un) this.imapemail.setStored_Password(this.passwordField.getString());
	else this.imapemail.setStored_Password("");

	/*if (this.getMode.getSelectedIndex() == 0) this.imapemail.setAtt_GetMode(false);
	else this.imapemail.setAtt_GetMode(true);*/

	return this.imapemail;
	}
}