package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ViewTravelUnitForm extends ViewForm
{
private static ViewTravelUnitForm _instance=null;

private OwnStringItem startMeterItem=null;
private OwnStringItem endMeterItem=null;
private OwnStringItem privateKilometersItem=null;
private OwnStringItem originItem=null;
private OwnStringItem destinationItem=null;
private OwnStringItem purposeItem=null;
private OwnStringItem startTimeItem=null;
private OwnStringItem endTimeItem=null;

/*
private StringItem startMeterItemLabel=null;
private StringItem endMeterItemLabel=null;
private StringItem privateKilometersItemLabel=null;
private StringItem originItemLabel=null;
private StringItem destinationItemLabel=null;
private StringItem purposeItemLabel=null;
private StringItem startTimeItemLabel=null;
private StringItem endTimeItemLabel=null;
*/

private ViewTravelUnitForm()
	{
	super(Props.get("modify_travelunit_title"));
	/*
	this.startMeterItemLabel=new StringItem(Props.get("modify_travelunit_startmeter")+": ","");
	this.endMeterItemLabel=new StringItem(Props.get("modify_travelunit_endmeter")+": ","");
	this.privateKilometersItemLabel=new StringItem(Props.get("modify_travelunit_privatekilometers")+": ","");
	this.originItemLabel=new StringItem(Props.get("modify_travelunit_origin")+": ","");
	this.destinationItemLabel=new StringItem(Props.get("modify_travelunit_destination")+": ","");
	this.purposeItemLabel=new StringItem(Props.get("modify_travelunit_purpose")+": ","");
	this.startTimeItemLabel=new StringItem(Props.get("view_workunit_starttime")+"\n","");
	this.endTimeItemLabel=new StringItem(Props.get("view_workunit_endtime")+"\n","");
	*/
	startMeterItem=new OwnStringItem(Props.get("modify_travelunit_startmeter")+": ","");
	endMeterItem=new OwnStringItem(Props.get("modify_travelunit_endmeter")+": ","");
	privateKilometersItem=new OwnStringItem(Props.get("modify_travelunit_privatekilometers")+": ","");
	originItem=new OwnStringItem(Props.get("modify_travelunit_origin")+": ","");
	destinationItem=new OwnStringItem(Props.get("modify_travelunit_destination")+": ","");
	purposeItem=new OwnStringItem(Props.get("modify_travelunit_purpose")+": ","");
	startTimeItem=new OwnStringItem(Props.get("view_workunit_starttime")+"\n","");
	endTimeItem=new OwnStringItem(Props.get("view_workunit_endtime")+"\n","");


	//this.append(this.startMeterItemLabel);
	this.startMeterItem.appendToForm(this);
	//this.append(this.endMeterItemLabel);
	this.endMeterItem.appendToForm(this);
	//this.append(this.privateKilometersItemLabel);
	this.privateKilometersItem.appendToForm(this);
	//this.append(this.originItemLabel);
	this.originItem.appendToForm(this);
	//this.append(this.destinationItemLabel);
	this.destinationItem.appendToForm(this);
	//this.append(this.purposeItemLabel);
	this.purposeItem.appendToForm(this);
	//this.append(this.startTimeItemLabel);
	this.startTimeItem.appendToForm(this);
	//this.append(this.endTimeItemLabel);
	this.endTimeItem.appendToForm(this);
	}

public static ViewTravelUnitForm instance(DataObject obj)
	{

	TravelUnit tunit=(TravelUnit)obj;
	if (_instance==null)
		_instance=new ViewTravelUnitForm();

	
	_instance.startMeterItem.setText(tunit.getStartMeter()+"\n");
	_instance.endMeterItem.setText(tunit.getEndMeter()+"\n");
	_instance.privateKilometersItem.setText(tunit.getPrivateKilometers()+"\n");
	_instance.originItem.setText(tunit.getOrigin()+"\n");
	_instance.destinationItem.setText(tunit.getDestination()+"\n");
	_instance.purposeItem.setText(tunit.getPurpose()+"\n");
	_instance.startTimeItem.setText(DateHelper.getDateAsString(tunit.getStartTime())+"\n");
	_instance.endTimeItem.setText(DateHelper.getDateAsString(tunit.getEndTime())+"\n");
	return _instance;
	}
}
