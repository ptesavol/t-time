package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ModifyTravelUnitForm extends ModifyForm
{
private TravelUnit travelUnit=null; 

private TextField startMeterField=null;
private TextField endMeterField=null;
private TextField privateKilometersField=null;
private TextField originField=null;
private TextField destinationField=null;
private TextField purposeField=null;
private DateField startTimeField=null;
private DateField endTimeField=null;

private static ModifyTravelUnitForm _instance;

private ModifyTravelUnitForm()
	{
	super(Props.get("modify_travelunit_title"));
	this.startMeterField=new TextField(Props.get("modify_travelunit_startmeter"),"",12,TextField.NUMERIC);
	this.endMeterField=new TextField(Props.get("modify_travelunit_endmeter"),"",12,TextField.NUMERIC);
	this.privateKilometersField=new TextField(Props.get("modify_travelunit_privatekilometers"),"",7,TextField.NUMERIC);
	this.originField=new TextField(Props.get("modify_travelunit_origin"),"",64,TextField.ANY);
	this.destinationField=new TextField(Props.get("modify_travelunit_destination"),"",64,TextField.ANY);
	this.purposeField=new TextField(Props.get("modify_travelunit_purpose"),"",64,TextField.ANY);
	this.startTimeField=new DateField(Props.get("modify_travelunit_starttime"),DateField.DATE_TIME);
	this.endTimeField=new DateField(Props.get("modify_travelunit_endtime"),DateField.DATE_TIME);
	
	this.append(this.startMeterField);
	this.append(this.endMeterField);
	this.append(this.privateKilometersField);
	this.append(this.originField);
	this.append(this.destinationField);
	this.append(this.purposeField);
	this.append(this.startTimeField);
	this.append(this.endTimeField);
	}

public static ModifyTravelUnitForm instance(DataObject obj)
	{
	if (_instance==null)
		{
		_instance=new ModifyTravelUnitForm();
		}
	TravelUnit unit=(TravelUnit)obj;	
	_instance.travelUnit=unit;
	_instance.startMeterField.setString(""+unit.getStartMeter());
	if (unit.getEndMeter()==0)
		_instance.endMeterField.setString("");
	else
		_instance.endMeterField.setString(""+unit.getEndMeter());
	_instance.privateKilometersField.setString(""+unit.getPrivateKilometers());
	_instance.originField.setString(unit.getOrigin());
	_instance.destinationField.setString(unit.getDestination());
	_instance.purposeField.setString(unit.getPurpose());
	//_instance.startTimeField.setDate(DateHelper.normalize(new Date(unit.getStartTime())));
	//_instance.endTimeField.setDate(DateHelper.normalize(new Date(unit.getEndTime())));
	
	_instance.startTimeField.setDate((new Date(unit.getStartTime())));
	_instance.endTimeField.setDate((new Date(unit.getEndTime())));
	
	return _instance;
	}

public DataObject getObject()
	{
	int startmeter=0;
	int endmeter=0;
	int privatekm=0;
	
	try	{
		startmeter=Integer.parseInt(this.startMeterField.getString());
		}
	catch (Exception e) {}
	 
	 try	{
		endmeter=Integer.parseInt(this.endMeterField.getString());
		}
	catch (Exception e) {}
	 
	
	 try	{
		privatekm=Integer.parseInt(this.privateKilometersField.getString());
		}
	catch (Exception e) {}
	 
	//this.travelUnit.setStartTime(DateHelper.deNormalize(new Date(this.travelUnit.getStartTime()),this.startTimeField.getDate()).getTime());
	//this.travelUnit.setEndTime(DateHelper.deNormalize(new Date(this.travelUnit.getEndTime()),this.endTimeField.getDate()).getTime());
	
	this.travelUnit.setStartTime(this.startTimeField.getDate().getTime());
	this.travelUnit.setEndTime(this.endTimeField.getDate().getTime());
	
	this.travelUnit.setStartMeter(startmeter);
	this.travelUnit.setEndMeter(endmeter);
	this.travelUnit.setPrivateKilometers(privatekm);
	this.travelUnit.setOrigin(this.originField.getString());
	this.travelUnit.setDestination(this.destinationField.getString());
	this.travelUnit.setPurpose(this.purposeField.getString());
	 
	 
	return this.travelUnit;
	}
}
