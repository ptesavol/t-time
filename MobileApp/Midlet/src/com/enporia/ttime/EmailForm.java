package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.io.*;
import java.util.*;

public class EmailForm extends Form
{
class EmailThread extends Thread
{
private static final int MAXUNITS=100;

boolean folderMode=true;
EmailConnection connection=null;
Sendable tunit=null;
ByteArrayOutputStream asciiBuffer=null;
byte[] body=Props.get("emailform_body").getBytes();
byte[] payload=null;
Contractor tcont=null;
int numberOfContractors=0;
int numberOfDays=0;
Vector[][] ids=null;
Contractor[] contractors=null;
String statusString = "";

private void reportStatus(String s)
	{
	statusString = statusString+"\n"+s;
	statusItem.setText(statusString);
	}

public EmailThread(boolean foldermode)
	{
	this.folderMode=foldermode;
	}

public void run()
	{
	removeCommand(EMAILFORM_OK);
	
		
	reportStatus(Props.get("emailform_compiling"));
	WorkUnitList.instance().setName(WorkUnitFolderList.instance().getSelectedElement().getName());
		

	numberOfDays=1;
		
	if (!folderMode)
		numberOfDays=WorkUnitFolderList.instance().size();
	
		
	numberOfContractors=ContractorList.instance().size();
		
	//create a table of ids of workunits to be sent
		
	ids = new Vector[numberOfDays] [numberOfContractors];
		
	for (int i=0; i<numberOfDays; i++)
		for (int j=0; j<numberOfContractors; j++)			
			ids[i][j]=new Vector();
		
	//create array of contractors
		
	contractors=new Contractor[ContractorList.instance().size()];
	for (int i=0; i<ContractorList.instance().size(); i++)
	contractors[i]=(Contractor)ContractorList.instance().elementAt(i);
		
	//fill the table of ids of workunits to be sent		
	
	//go through all the days 

	int filled=0, c=0;
	Vector unknBillers = new Vector();
	for (int i=0; i<numberOfDays ; i++)	
		{
		if (!folderMode)
			WorkUnitList.instance().setName(WorkUnitFolderList.instance().elementAt(i).getName());
		else
			WorkUnitList.instance().setName(WorkUnitFolderList.instance().getSelectedElement().getName());

		// go through all the workunits of the day
		for (int j=0; j<WorkUnitList.instance().size(); j++ )
			{
			boolean billerNotFound = true; 
			tunit=(Sendable)WorkUnitList.instance().elementAt(j);
			for (c=0; c<contractors.length; c++)
				{
				if ( contractors[c].getName().equals(tunit.getContractor()) )
					{
					billerNotFound = false;
					if (folderMode || !tunit.isSent())
						{
						ids[i][c].addElement(new Integer(j));
						filled++;
						}
					}
				}
			
			if(billerNotFound)		// 22.8.2011, biller was not found on the billers list -> make a list of names
				{
				if(!unknBillers.contains(tunit.getContractor()))
					unknBillers.addElement(tunit.getContractor());
				}
			}
		}

	if(unknBillers.size() > 0)			// 22.8.2011, show the list of unknown billers
		{
		String str = Props.get("unkn_billers1") + " ";
		for(int k=0; k<unknBillers.size(); k++)
			str += (String)unknBillers.elementAt(k) + (k < unknBillers.size() - 1 ? ", " : "");
		reportStatus("\n" + str + ". " + Props.get("unkn_billers2") + "\n");			
		}

	if (filled == 0)
		{
			reportStatus(Props.get("emailform_nothingtosend"));

		addCommand(EMAILFORM_OK);
		return;
		}
	/*reportStatus("OK FOR SEND");
	addCommand(EMAILFORM_OK);
	if(true) return;*/
	
	// make the email connection
		
	try	{
		 if ( Worker.instance().useProxy() ) 
			{
			connection=new HttpEmailConnection();
			connection.open(Worker.instance().getEmailProxy(),Props.get("emailform_localhost"));
			}
		else	{
			connection=new SmtpEmailConnection();
			connection.open(Worker.instance().getEmailServer(),Props.get("emailform_localhost"));
			}
			
		// create the emails and send them
			
		//go through all contractors in the ids table
			
		int unitsInMail=0;
		int i=0;
		int j=0;
		int k=0;
		int oldelementindex=0;
		int olddayindex=0;
		
		for (i=0; i<numberOfContractors; i++ )
			{
			asciiBuffer=new ByteArrayOutputStream();
			DocumentCreator.bufferAscii(asciiBuffer,Worker.instance().getName(),contractors[i].getName());	
				
			//go through all the days for this contractor
			
			oldelementindex=0;
			olddayindex=0;
				
			for (j=0; j<numberOfDays; j++)
				{
				if (!folderMode)
					WorkUnitList.instance().setName(WorkUnitFolderList.instance().elementAt(j).getName());
				else 	WorkUnitList.instance().setName(WorkUnitFolderList.instance().getSelectedElement().getName());
				
				for (k=0; k<ids[j][i].size(); k++)
					{
					if (unitsInMail>MAXUNITS)
						{
						sendAndMark(i,j,k,olddayindex, oldelementindex);			
						olddayindex=j;
						oldelementindex=k;
						unitsInMail=0;
						asciiBuffer=null;
						System.gc();
						asciiBuffer=new ByteArrayOutputStream();
						DocumentCreator.bufferAscii(asciiBuffer,Worker.instance().getName(),contractors[i].getName());
						}
					
					tunit=(Sendable)WorkUnitList.instance().elementAt((((Integer)ids[j][i].elementAt(k)).intValue()));
					tunit.bufferAsciiBytes(asciiBuffer);
					System.out.println(new String(asciiBuffer.toByteArray()));
					unitsInMail++;
					}
				}
			if (unitsInMail>0)
				{
				sendAndMark(i,j-1,k,olddayindex, oldelementindex );
				olddayindex=j;
				oldelementindex=k;
				unitsInMail=0;
				asciiBuffer=null;
				System.gc();
				}
			}

			//connection.close();
			reportStatus(Props.get("emailform_completed"));
			}
			catch (Exception e1)
				{
				connection.close();
				reportStatus(Props.get("emailform_connectionfailure")+e1.toString());
				e1.printStackTrace();
				}		
		
	addCommand(EMAILFORM_OK);
	}
/*
*Sends email and marks the workunits sent in the workunitlist if sending succeeds
*@param contractorindex the index of the current contractor
*@param dayindex the index of the last day included
*@param unitindex the index of the last workunit included in the email from the last day
*/	
private void sendAndMark(int contractorindex, int dayindex, int unitindex, int olddayindex, int oldelementindex) throws Exception
	{
	//send email
	payload= asciiBuffer.toByteArray();
	asciiBuffer=null;
	System.gc();
	payload=EmailHelper.createEmail(Worker.instance().getEmail(), contractors[contractorindex].getEmail(),
							Props.get("emailform_mailtitle")+System.currentTimeMillis(), body, payload);
	System.gc();
	reportStatus(Props.get("emailform_sending")+" "+contractors[contractorindex].getName());
	try	{
		connection.sendEmail(Worker.instance().getEmail(),contractors[contractorindex].getEmail() ,
		Props.get("emailform_mailtitle")+System.currentTimeMillis(),payload);
		}
	catch (EmailException e)
		{
		reportStatus(Props.get("emailform_failure"));
		System.gc();
		return;
		}
	reportStatus(Props.get("emailform_success"));
	payload=null;
	System.gc();
	
	//mark as sent
	
	// go through all the days
	for (int i=olddayindex; i<=dayindex; i++)
		{
		if (!folderMode)
			WorkUnitList.instance().setName(WorkUnitFolderList.instance().elementAt(i).getName());
		else 	WorkUnitList.instance().setName(WorkUnitFolderList.instance().getSelectedElement().getName());
		for (int j=oldelementindex; j<ids[i][contractorindex].size() ;j++)	
			{
			if (j==unitindex && i==dayindex )
				return ;

			tunit=(Sendable)WorkUnitList.instance().elementAt((((Integer)ids[i][contractorindex].elementAt(j)).intValue()));
			if (!tunit.isSent())
				{
				tunit.setSent(true);
				WorkUnitList.instance().setElementAt((DataObject) tunit,(((Integer)ids[i][contractorindex].elementAt(j)).intValue()));
				}
			}
		oldelementindex=0;
		}	
	}
}
	
public static Command EMAILFORM_OK = new Command(Props.get("common_ok"), Command.OK, 1);
private static EmailForm _instance=null;
private OwnStringItem statusItem=null;
private EmailThread emailThread=null;

public static EmailForm instance()
	{
	if (_instance==null)
		_instance=new EmailForm();
	return _instance;
	}

private EmailForm()
	{
	super(Props.get("emailform_title"));
	
	this.statusItem=new OwnStringItem("","");
	this.statusItem.appendToForm(this);
	}
	
public void sendEmail(boolean foldermode)
	{
	this.emailThread=new EmailThread(foldermode);
	this.emailThread.start();
	}

}
