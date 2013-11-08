package com.enporia.ttime;

import java.io.ByteArrayOutputStream;
import java.util.Vector;

import javax.microedition.lcdui.Choice;
import javax.microedition.lcdui.ChoiceGroup;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.StringItem;
import javax.microedition.lcdui.TextField;

import com.enporia.ttime.IMAPGetListsForm.IMAPGetEmailThread;
import com.enporia.util.Attachments;
import com.enporia.util.CommonRemoveForm;
import com.enporia.util.CustomException;
import com.enporia.util.DataObject;
import com.enporia.util.EmailConnection;
import com.enporia.util.EmailException;
import com.enporia.util.EmailHelper;
import com.enporia.util.GetLine;
import com.enporia.util.HttpEmailConnection;
import com.enporia.util.IMAPEmailConnection;
import com.enporia.util.OwnStringItem;
import com.enporia.util.Props;
import com.enporia.util.SmtpEmailConnection;

public class IMAPSendListsForm extends Form implements CommandListener
{
	class IMAPSendEmailThread extends Thread
	{
		Integer cntr = new Integer(0);
		private byte[] payload = null;
		private byte[] sendload = null;
		private String[] addresses = null;
		private byte[] body = null;
		private String subject = "";
		private String from = "";
		private String alladdr = "";
		private String server = "";
		private ByteArrayOutputStream asciiBuffer = null;
		private EmailConnection connection = null;
		private String strhelp;
		
		private final String[] SECO = {";"};
		private final char[] IGNORENONE = {};
		
		public IMAPSendEmailThread() {}

		private void reportStatus(String str)
		{
			//String lf = (status_text.equals("") ? "" : "\n");
			
			status_text = /*status_text + lf + */str;
			statusItem.setText(status_text);
		}
		
		public void run()
		{
		ThreadRunning = true;
			
		removeCommand(IMAPSENDFORM_CANCEL);  // Disable input, remove all the controls from the form, excluding statusItem
		removeCommand(IMAPSENDFORM_OK);
		while(_instance.size() > 1) _instance.delete(0);
		
		try {
				// Select email connection object and server url
				if(Worker.instance().useProxy())
				{
					server = Worker.instance().getEmailProxy();
					connection = new HttpEmailConnection();
				}
				else
				{
					server = Worker.instance().getEmailServer();
					connection = new SmtpEmailConnection();
				}
			
				// Buffer for attachment data
			    asciiBuffer = new ByteArrayOutputStream();		
			    
				// Parse email addresses
				if((addresses = GetLine.splitLine(emailAddress.getString(), SECO, IGNORENONE, GetLine.TRIMSPACE|GetLine.IGNOREEMPTY)).length == 0)
					throw new CustomException(Props.get("sendlists_norcpt"));

			    // Compile email
			    reportStatus(Props.get("sendlists_compiling"));
			    
				DocumentCreator.bufferAscii_Lists(asciiBuffer, "");  // Document header
				
				if(ContractorList.instance().size() > 0 && contractor.isSelected(contractor.size() - 1) == true)
					DocumentCreator.insert_Contractors(asciiBuffer); // Contractors must be the first block in the list file
				
				if(WorkPlaceFolderList.instance().size() > 0 && workPlace.isSelected(workPlace.size() - 1) == true)
					DocumentCreator.insert_WorkPlaces(asciiBuffer);  // WorkPlaces

				if(WorkTypeList.instance().size() > 0 && workType.isSelected(workType.size() - 1) == true)
					DocumentCreator.insert_WorkTypes(asciiBuffer);   // WorkTypes
								
				if(ProductFolderList.instance().size() > 0 && product.isSelected(product.size() - 1) == true)
					DocumentCreator.insert_Products(asciiBuffer);    // Products

			    // Connect to server
				reportStatus(Props.get("sendgetlists_open") + " '" + server + "'...");
				connection.open(server, Props.get("emailform_localhost"));

				// Send message to all the addresses
				from = Worker.instance().getEmail();
				subject = Props.get("lists_title") + Props.get("lists_identifier") + System.currentTimeMillis();
				body = Props.get("sendlists_body").getBytes();
				alladdr = new Integer(addresses.length).toString() + " ";
				sendload = asciiBuffer.toByteArray();

				for(int i=0; i<addresses.length; i++)
				{
					strhelp = (addresses.length == 1 ? Props.get("sendlists_sending_singular") : Props.get("sendlists_sending_plural"));
					cntr = i + 1; reportStatus(strhelp + "\n" + cntr.toString() + "/" + alladdr + addresses[i]);
					
					payload = EmailHelper.createEmail_lists(from, addresses[i], subject, body, sendload);
				
					connection.sendEmail(from, addresses[i], subject, payload);
					
					payload = null; System.gc();
				}

				// Message send
				reportStatus(Props.get("sendlists_success"));
			}
		catch (EmailException e)
			{
			reportStatus(Props.get("sendlists_failure"));
			}
		catch (CustomException e1)
			{
			reportStatus(Props.get("sendgetlists_error") + " " + e1.toString());
			}
		catch(Exception e1)
			{
			reportStatus(Props.get("sendlists_connectionfailure") + e1.toString());
			e1.printStackTrace();
			}
		finally
			{
			connection.close();
			
			body = null;
			asciiBuffer = null;
			payload = null;
			sendload = null;
			connection = null;
			addresses = null;
			System.gc();
			}

		addCommand(IMAPSENDFORM_CANCEL);
		
		ThreadRunning = false;
		}
	}

public static Command IMAPSENDFORM_CANCEL = new Command(Props.get("common_back"), Command.CANCEL, 2);
public static Command IMAPSENDFORM_OK = new Command(Props.get("common_send"), Command.OK, 1);
	
private TextField emailAddress = null;
private ChoiceGroup saveEmailAddress = null;
private ChoiceGroup workPlace = null;
private ChoiceGroup contractor = null;
private ChoiceGroup workType = null;
private ChoiceGroup product = null;
private StringItem selSave = null;
private OwnStringItem statusItem=null;

private static IMAPSendListsForm _instance=null;
private IMAPEmailSend imapemailsend = null;
private IMAPSendEmailThread IMAPSendThread=null;
private boolean ThreadRunning = false;

String status_text = "";

private IMAPSendListsForm()
	{
	super(Props.get("sendlists_sendlists"));
	setCommandListener(this);

	this.emailAddress = new TextField(Props.get("sendlists_rcpt"),"",512,TextField.ANY);
	String[] se = { Props.get("sendlists_savercpt") };
	this.saveEmailAddress = new ChoiceGroup("",Choice.MULTIPLE,se,null);
	this.selSave = new StringItem("", Props.get("sendlists_selsave"));
	String[] wp = {Props.get("sendlists_workplace")};
	this.workPlace = new ChoiceGroup("", Choice.MULTIPLE, wp, null);
	String[] cu = {Props.get("sendlists_contractor")};
	this.contractor = new ChoiceGroup("", Choice.MULTIPLE, cu, null);	
	String[] wt = { Props.get("sendlists_worktype") };
	this.workType = new ChoiceGroup("",Choice.MULTIPLE,wt,null);
	String[] pr = { Props.get("sendlists_product") };
	this.product = new ChoiceGroup("",Choice.MULTIPLE,pr,null);
	
	this.statusItem = new OwnStringItem("","");
	}

public static IMAPSendListsForm instance(DataObject obj)
{
if (_instance==null)
	_instance=new IMAPSendListsForm();

	_instance.deleteAll();
	_instance.append(_instance.emailAddress);
	_instance.append(_instance.saveEmailAddress);
	_instance.append(_instance.selSave);
	_instance.append(_instance.workPlace);
	_instance.append(_instance.contractor);
	_instance.append(_instance.workType);
	_instance.append(_instance.product);
	_instance.statusItem.appendToForm(_instance);

	_instance.removeCommand(IMAPSENDFORM_OK);
	_instance.removeCommand(IMAPSENDFORM_CANCEL);
	_instance.addCommand(IMAPSENDFORM_OK);
	_instance.addCommand(IMAPSENDFORM_CANCEL);
	_instance.statusItem.setText("");
	
	_instance.status_text = "";
	
	if(obj != null) _instance.imapemailsend = (IMAPEmailSend)obj;

	if(_instance.imapemailsend.isSaveEmailAddress())
    {
		_instance.saveEmailAddress.setSelectedIndex(_instance.saveEmailAddress.size() - 1, true);
		_instance.emailAddress.setString(_instance.imapemailsend.getEmailAddress());
    }
	else
	{
		_instance.saveEmailAddress.setSelectedIndex(_instance.saveEmailAddress.size() - 1, false);
		_instance.emailAddress.setString("");
	}
	
	_instance.workPlace.setSelectedIndex(_instance.workPlace.size() - 1, true);
	_instance.contractor.setSelectedIndex(_instance.contractor.size() - 1, true);
	_instance.workType.setSelectedIndex(_instance.workType.size() - 1, true);
	_instance.product.setSelectedIndex(_instance.product.size() - 1, true);
	
	return _instance;
}

public void commandAction(Command c, Displayable d)
	{
		if (c==IMAPSENDFORM_CANCEL || c==CommonRemoveForm.CANCEL)
		{
		((IMAPEmailSend)this.getObject()).save();
		SettingsList.instance().show();
		}

		if(c==IMAPSENDFORM_OK)
		{
			this.IMAPSendThread = new IMAPSendEmailThread();
			this.IMAPSendThread.start();
		}
	}

public DataObject getObject()
	{
	boolean sel = this.saveEmailAddress.isSelected(this.saveEmailAddress.size() - 1);

	this.imapemailsend.setSaveEmailAddress(sel);
	if(sel) this.imapemailsend.setEmailAddress(this.emailAddress.getString());
	else this.imapemailsend.setEmailAddress("");

	return this.imapemailsend;
	}

}
