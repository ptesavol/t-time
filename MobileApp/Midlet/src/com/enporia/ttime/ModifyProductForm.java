package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ModifyProductForm extends ModifyForm implements ItemStateListener
{
private static ModifyProductForm _instance=null;

private TextField nameField=null;
private TextField productIdField=null;
private TextField unitField=null;
private TextField buyEurosField=null;
private TextField buyCentsField=null;
private TextField sellEurosField=null;
private TextField sellCentsField=null;
private TextField sellTaxedEurosField=null;
private TextField sellTaxedCentsField=null;

private TextField vatPercentField=null;
private TextField inStockIntegerField=null;
private TextField inStockDecimalField=null;
private OwnStringItem dotItem=null;
private OwnStringItem dotItem2=null;
private OwnStringItem dotItem3=null;

private ChoiceGroup unitTypeGroup=null;

private String oldSellEurosString="";
private String oldSellCentsString="";
private String oldSellTaxedEurosString="";
private String oldSellTaxedCentsString="";
private String oldVatPercentString="";


private ModifyProductForm()
	{
	super(Props.get("modify_product_title")); 
	this.setItemStateListener(this);
	this.nameField=new TextField(Props.get("add_product_name"),"",64,TextField.ANY);
	this.productIdField=new TextField(Props.get("add_product_id"),"",16,TextField.ANY);
	this.unitField=new TextField(Props.get("add_product_unit"),"",16,TextField.ANY);
	
	this.buyEurosField=new TextField(Props.get("add_product_buyeuros"),"",6,TextField.NUMERIC);
	this.buyCentsField=new TextField(Props.get("add_product_buycents"),"",2,TextField.NUMERIC);
	this.sellEurosField=new TextField(Props.get("add_product_selleuros"),"",6,TextField.NUMERIC);
	this.sellCentsField=new TextField(Props.get("add_product_sellcents"),"",2,TextField.NUMERIC);
	this.inStockIntegerField=new TextField(Props.get("add_product_instock"),"",6,TextField.NUMERIC);
	this.inStockDecimalField=new TextField(",","",2,TextField.NUMERIC);
	this.vatPercentField=new TextField(Props.get("add_product_vatpercent"),"",2,TextField.NUMERIC);
	this.sellTaxedEurosField=new TextField(Props.get("add_product_selltaxedeuros"),"",6,TextField.NUMERIC);
	this.sellTaxedCentsField=new TextField(Props.get("add_product_selltaxedcents"),"",2,TextField.NUMERIC);
	
	
	this.dotItem=new OwnStringItem("",",");
	this.dotItem2=new OwnStringItem("",",");
	this.dotItem3=new OwnStringItem("",",");
	String[] unittypenames=new String[3];
	unittypenames[0]=Props.get("add_product_numerictype");
	unittypenames[1]=Props.get("add_product_timetype");
	unittypenames[2]=Props.get("add_product_traveltype");
	
	this.unitTypeGroup=new ChoiceGroup(Props.get("add_product_unittype"),Choice.EXCLUSIVE,unittypenames,null);
	
	
	this.append(this.nameField);
	this.append(this.productIdField);
	this.append(this.unitField);
	this.append(this.buyEurosField);
	this.dotItem.appendToForm(this);
	this.append(this.buyCentsField);
	this.append(this.sellEurosField);
	this.dotItem2.appendToForm(this);
	this.append(this.sellCentsField);
	this.append(this.sellTaxedEurosField);
	this.dotItem3.appendToForm(this);
	this.append(this.sellTaxedCentsField);
    	this.append(this.vatPercentField);
	this.append(this.inStockIntegerField);
	this.append(this.inStockDecimalField);
	
	//this.append(this.unitTypeGroup);
	}
	
public static ModifyProductForm instance(DataObject object)
	{
	Product prod=(Product)object;
	if (_instance==null)
		{
		_instance=new ModifyProductForm();
		}

	_instance.nameField.setString(prod.getName());
	_instance.productIdField.setString(prod.getProductId());
	_instance.unitField.setString(prod.getUnit());
	_instance.buyEurosField.setString(prod.getBuyPrice().getIntString());
	_instance.buyCentsField.setString(prod.getBuyPrice().getDecString());
	_instance.sellEurosField.setString(prod.getSellPrice().getIntString());
	_instance.sellCentsField.setString(prod.getSellPrice().getDecString());
	
	
	
	_instance.sellTaxedEurosField.setString(prod.getTaxedSellPrice().getIntString());
	_instance.sellTaxedCentsField.setString(prod.getTaxedSellPrice().getDecString());
	
	_instance.inStockIntegerField.setString(prod.getInStock().getIntString());
	_instance.inStockDecimalField.setString(prod.getInStock().getDecString());
	_instance.vatPercentField.setString(prod.getVatPercent().getIntString());
	//_instance.unitTypeGroup.setSelectedIndex(prod.getUnitType(),true);
	return _instance;	
	}	
public DataObject getObject()
	{
	FixedFloat buyprice=new FixedFloat(buyEurosField.getString(),buyCentsField.getString() );
	FixedFloat sellprice=new FixedFloat(sellEurosField.getString(),sellCentsField.getString() );
	FixedFloat instock=new FixedFloat(inStockIntegerField.getString(), inStockDecimalField.getString() );
	FixedFloat vatpercent=new FixedFloat(vatPercentField.getString(),"");
	
	int unittype=this.unitTypeGroup.getSelectedIndex();
	
	
	return new Product(this.nameField.getString(), this.productIdField.getString(), this.unitField.getString(),
			  buyprice,sellprice,instock, unittype,vatpercent);
	}

public void itemStateChanged(Item item)	
	{
	String sellEurosString = this.sellEurosField.getString();
	String sellCentsString = this.sellCentsField.getString();
	String vatPercentString = this.vatPercentField.getString();
	if (vatPercentString.length()<2)
		vatPercentString="0"+vatPercentString;
	String sellTaxedEurosString = this.sellTaxedEurosField.getString();
	String sellTaxedCentsString = this.sellTaxedCentsField.getString();
	
	
	// if taxless sellprice or vatpercent have changed
	if (
		!sellEurosString.equals(oldSellEurosString) || !sellCentsString.equals(oldSellCentsString) ||
		!vatPercentString.equals(oldVatPercentString)
		)
		{
		oldSellEurosString=sellEurosString;
		oldSellCentsString=sellCentsString;
		oldVatPercentString=vatPercentString;
		
		FixedFloat taxedPrice=new FixedFloat(sellEurosString, sellCentsString );		
		FixedFloat vatPercent=new FixedFloat("1",vatPercentString);		
		taxedPrice.multiplyBy(vatPercent);
		
		this.sellTaxedEurosField.setString(taxedPrice.getIntString());
		this.sellTaxedCentsField.setString(taxedPrice.getDecString());		
		oldSellTaxedEurosString=taxedPrice.getIntString();
		oldSellTaxedCentsString=taxedPrice.getDecString();		

		return;
		}
		
	//if taxed price has changed	

	if (!sellTaxedEurosString.equals(oldSellTaxedEurosString) || !sellTaxedCentsString.equals(oldSellTaxedCentsString))
		
		{
		oldSellTaxedEurosString=sellTaxedEurosString;
		oldSellTaxedCentsString=sellTaxedCentsString;
		
		
		FixedFloat taxlessPrice = new FixedFloat(sellTaxedEurosString,sellTaxedCentsString); 
		FixedFloat vatPercent = new FixedFloat("1",vatPercentString);
		taxlessPrice.divideBy(vatPercent);
		
		this.sellEurosField.setString(taxlessPrice.getIntString());
		this.sellCentsField.setString(taxlessPrice.getDecString());

		oldSellEurosString = taxlessPrice.getIntString();
		oldSellCentsString = taxlessPrice.getDecString();

		}
	}
}
