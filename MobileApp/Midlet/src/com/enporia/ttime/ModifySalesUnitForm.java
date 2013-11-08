package com.enporia.ttime;

import com.enporia.util.*;

import javax.microedition.midlet.*;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import javax.microedition.lcdui.*;
import java.util.*;

public class ModifySalesUnitForm extends ModifyForm implements ItemStateListener
{
private static ModifySalesUnitForm _instance=null;
private SalesUnit salesUnit=null;

private OwnStringItem customerNameItem=null;
private OwnStringItem productNameItem=null;
private TextField amountIntegerField=null;
private TextField amountDecimalField=null;
private OwnStringItem dotItem=null;
private OwnStringItem dotItem2=null;
//private OwnStringItem dotItem3=null;
private OwnStringItem dotItem4=null;
private OwnStringItem dotItem5=null;
private OwnStringItem unitItem=null;
private TextField unitEurosField=null;
private TextField unitCentsField=null;
private TextField unitTaxedEurosField=null;
private TextField unitTaxedCentsField=null;
private TextField totalEurosField=null;
private TextField totalCentsField=null;
private DateField salesTimeField=null;
private TextField totalTaxedEurosField=null;
private TextField totalTaxedCentsField=null;
private TextField vatPercentField=null;

private String oldamountintString="";
private	String oldamountdecString="";
private	String olduniteurosString="";
private	String oldunitcentsString="";
private	String oldtaxeduniteurosString="";
private	String oldtaxedunitcentsString="";
//private	String oldtotaleurosString="";
//private	String oldtotalcentsString="";
//private	String oldtaxedtotaleurosString="";
//private	String oldtaxedtotalcentsString="";
private	String oldvatpercentString="";

private ModifySalesUnitForm()
	{
	super(Props.get("modify_salesunit_title"));
	this.setItemStateListener(this);
	
	this.customerNameItem=new OwnStringItem("","");
	this.productNameItem=new OwnStringItem("","");
	this.salesTimeField=new DateField(Props.get("sell_numeric_salestime"),DateField.TIME);
	this.amountIntegerField=new TextField(Props.get("sell_numeric_amount"),"",6,TextField.NUMERIC);
	this.amountDecimalField=new TextField("","",2,TextField.NUMERIC);
	this.unitItem=new OwnStringItem("","");
	this.unitEurosField=new TextField(Props.get("sell_numeric_unitprice"),"",6,TextField.NUMERIC);
	this.unitCentsField=new TextField("","",2,TextField.NUMERIC);
	this.totalEurosField=new TextField(Props.get("sell_numeric_totalprice"),"",6,TextField.NUMERIC);
	this.totalCentsField=new TextField(",","",2,TextField.NUMERIC);
	this.dotItem=new OwnStringItem("",",");
	this.dotItem2=new OwnStringItem("",",");
	
	this.totalTaxedEurosField=new TextField(Props.get("sell_numeric_taxedtotalprice"),"",6,TextField.NUMERIC);
	this.totalTaxedCentsField=new TextField("","",2,TextField.NUMERIC);
	//this.dotItem3=new OwnStringItem("",",");
	this.dotItem4=new OwnStringItem("",",");
	this.dotItem5=new OwnStringItem("",",");
	this.unitTaxedEurosField=new TextField(Props.get("sell_numeric_taxedunitprice"),"",6,TextField.NUMERIC);
	this.unitTaxedCentsField=new TextField("","",2,TextField.NUMERIC);
	this.vatPercentField=new TextField(Props.get("add_product_vatpercent"),"",2,TextField.NUMERIC);
	
	this.productNameItem.appendToForm(this);
	this.append(this.amountIntegerField);
	this.dotItem.appendToForm(this);
	this.append(this.amountDecimalField);
	this.unitItem.appendToForm(this);
	this.append(this.unitEurosField);
	this.dotItem2.appendToForm(this);
	this.append(this.unitCentsField);
	this.append(this.vatPercentField);
	this.append(this.unitTaxedEurosField);
	this.dotItem5.appendToForm(this);
	this.append(this.unitTaxedCentsField);
	this.append(this.totalEurosField);
	this.append(this.totalCentsField);
	this.append(this.totalTaxedEurosField);
	this.dotItem4.appendToForm(this);
	this.append(this.totalTaxedCentsField);
	}

public static ModifySalesUnitForm instance(DataObject obj)
	{
	if (_instance==null)
		_instance=new ModifySalesUnitForm();
	
	_instance.salesUnit=(SalesUnit)obj;
	
	_instance.customerNameItem.setText(_instance.salesUnit.getCustomerName());
	_instance.productNameItem.setText(_instance.salesUnit.getProductName());
	_instance.salesTimeField.setDate(DateHelper.normalize(new Date(_instance.salesUnit.getSalesTime())));
	_instance.amountIntegerField.setString(_instance.salesUnit.getAmount().getIntString());
	_instance.amountDecimalField.setString(_instance.salesUnit.getAmount().getDecString());
	_instance.unitItem.setText(_instance.salesUnit.getUnit());
	_instance.unitEurosField.setString(_instance.salesUnit.getUnitPrice().getIntString());
	_instance.unitCentsField.setString(_instance.salesUnit.getUnitPrice().getDecString());
	_instance.totalEurosField.setString(_instance.salesUnit.getTotalPrice().getIntString());
	_instance.totalCentsField.setString(_instance.salesUnit.getTotalPrice().getDecString());
	
	
	_instance.vatPercentField.setString(_instance.salesUnit.getVatPercent().getIntString());
	_instance.unitTaxedEurosField.setString(_instance.salesUnit.getTaxedUnitPrice().getIntString());
	_instance.unitTaxedCentsField.setString(_instance.salesUnit.getTaxedUnitPrice().getDecString()); 
	_instance.totalTaxedEurosField.setString(_instance.salesUnit.getTaxedTotalPrice().getIntString());
	_instance.totalTaxedCentsField.setString(_instance.salesUnit.getTaxedTotalPrice().getDecString());
	
	_instance.oldamountintString=_instance.amountIntegerField.getString();
	_instance.oldamountdecString=_instance.amountDecimalField.getString();
	_instance.olduniteurosString=_instance.unitEurosField.getString();
	_instance.oldunitcentsString=_instance.unitCentsField.getString();
	_instance.oldtaxeduniteurosString=_instance.unitTaxedEurosField.getString();
	_instance.oldtaxedunitcentsString=_instance.unitTaxedCentsField.getString();
	_instance.oldvatpercentString= _instance.vatPercentField.getString();

	return _instance;	
	}
	
public DataObject getObject()
	{
	this.salesUnit.setSalesTime(DateHelper.deNormalize(new Date(this.salesUnit.getSalesTime()),this.salesTimeField.getDate()).getTime());
	
	FixedFloat amount = new FixedFloat(amountIntegerField.getString(), amountDecimalField.getString()); 
	FixedFloat unitPrice= new FixedFloat(unitEurosField.getString(),unitCentsField.getString()); 
	FixedFloat totalPrice= new FixedFloat(totalEurosField.getString(),totalCentsField.getString()); 
	FixedFloat vatPercent= new FixedFloat(vatPercentField.getString(),""); 
	
	this.salesUnit.setAmount(amount);
	this.salesUnit.setUnitPrice(unitPrice);
	this.salesUnit.setTotalPrice(totalPrice);
	this.salesUnit.setVatPercent(vatPercent);
	
	return this.salesUnit;
	}


//ItemStateListener implementation
	
public void itemStateChanged(Item item)
	{
	String amountintString=this.amountIntegerField.getString();
	String amountdecString=this.amountDecimalField.getString();
	String uniteurosString=this.unitEurosField.getString();
	String unitcentsString=this.unitCentsField.getString();
	String taxeduniteurosString=this.unitTaxedEurosField.getString();
	String taxedunitcentsString=this.unitTaxedCentsField.getString();
	//String totaleurosString=this.totalEurosField.getString();
	//String totalcentsString=this.totalCentsField.getString();
	//String taxedtotaleurosString=this.totalTaxedEurosField.getString();
	//String taxedtotalcentsString=this.totalTaxedCentsField.getString();
	String vatpercentString=this.vatPercentField.getString();
	if (vatpercentString.length()<2)
		vatpercentString="0"+vatpercentString;
		
	FixedFloat amount = new FixedFloat(amountintString,amountdecString);
	FixedFloat unitPrice = new FixedFloat(uniteurosString, unitcentsString);
	FixedFloat taxedUnitPrice = new FixedFloat(taxeduniteurosString, taxedunitcentsString);
	//FixedFloat totalPrice = new FixedFloat(totaleurosString, totalcentsString);
	//FixedFloat taxedTotalPrice = new FixedFloat(taxedtotaleurosString,taxedtotalcentsString); 
	FixedFloat vatPercent = new FixedFloat("1",vatpercentString);


	// if taxless unitprice or vat percent have changed

	if (!olduniteurosString.equals(uniteurosString) ||
		!oldunitcentsString.equals(unitcentsString) ||
		!oldvatpercentString.equals(vatpercentString) 
		)
		{
		olduniteurosString=uniteurosString;
		oldunitcentsString=unitcentsString;
		oldvatpercentString=vatpercentString;
		
		// calculate the taxed unitprice
		FixedFloat taxedUnit=new FixedFloat(unitPrice);	
		taxedUnit.multiplyBy(vatPercent);

		this.unitTaxedEurosField.setString(taxedUnit.getIntString());
		this.unitTaxedCentsField.setString(taxedUnit.getDecString());
		oldtaxeduniteurosString=(taxedUnit.getIntString());
		oldtaxedunitcentsString=taxedUnit.getDecString();
		

		FixedFloat taxlessTotal=new FixedFloat(unitPrice);
		taxlessTotal.multiplyBy(amount);
		this.totalEurosField.setString(taxlessTotal.getIntString());
		this.totalCentsField.setString(taxlessTotal.getDecString());
		
		// calculate the taxed total price
		
		taxedUnit.multiplyBy(amount);
	
		this.totalTaxedEurosField.setString(taxedUnit.getIntString());
		this.totalTaxedCentsField.setString(taxedUnit.getDecString());
		
		return;
		}
	
	// if taxed unit price has changed	

	if (
		!oldtaxeduniteurosString.equals(taxeduniteurosString) ||
		!oldtaxedunitcentsString.equals(taxedunitcentsString) 
		)
		
		{
		oldtaxeduniteurosString=taxeduniteurosString;
		oldtaxedunitcentsString=taxedunitcentsString;
		
		// calculate taxless unit price 
		
		FixedFloat taxlessUnit=new FixedFloat(taxedUnitPrice);
		taxlessUnit.divideBy(vatPercent);	
	
		this.unitEurosField.setString(taxlessUnit.getIntString());
		this.unitCentsField.setString(taxlessUnit.getDecString());
		
		olduniteurosString=taxlessUnit.getIntString();
		oldunitcentsString=taxlessUnit.getDecString();
		
		//calculate taxless total price

		taxlessUnit.multiplyBy(amount);
		this.totalEurosField.setString(taxlessUnit.getIntString());
		this.totalCentsField.setString(taxlessUnit.getDecString());
		
		// calculate taxed total price 
		
		taxedUnitPrice.multiplyBy(amount);
		
		this.totalTaxedEurosField.setString(taxedUnitPrice.getIntString());
		this.totalTaxedCentsField.setString(taxedUnitPrice.getDecString());
		return;
		}
		
	// if amount has changed

	if (!oldamountintString.equals(amountintString) || 
		!oldamountdecString.equals(amountdecString)
		)
		
		{
		oldamountintString=amountintString;
		oldamountdecString=amountdecString;
		
		// calculate taxless total price
		
		unitPrice.multiplyBy(amount);
		
		this.totalEurosField.setString(unitPrice.getIntString());
		this.totalCentsField.setString(unitPrice.getDecString());

		// calculate taxed total price 
		
		taxedUnitPrice.multiplyBy(amount);
		
		this.totalTaxedEurosField.setString(taxedUnitPrice.getIntString());
		this.totalTaxedCentsField.setString(taxedUnitPrice.getDecString());
		}
		
	}




}
