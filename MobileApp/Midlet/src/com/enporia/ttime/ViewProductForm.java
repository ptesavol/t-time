package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ViewProductForm extends ViewForm
{
private static ViewProductForm _instance=null;

/*
private OwnStringItem nameFieldLabel=null;
private OwnStringItem productIdFieldLabel=null;
private OwnStringItem unitFieldLabel=null;
private OwnStringItem buyFieldLabel=null;
private OwnStringItem sellFieldLabel=null;
private OwnStringItem sellTaxedFieldLabel=null;
private OwnStringItem vatPercentFieldLabel=null;
private OwnStringItem inStockFieldLabel=null;
private OwnStringItem unitTypeFieldLabel=null;
*/
private OwnStringItem nameField=null;
private OwnStringItem productIdField=null;
private OwnStringItem unitField=null;
private OwnStringItem buyField=null;
private OwnStringItem sellField=null;
private OwnStringItem sellTaxedField=null;
private OwnStringItem vatPercentField=null;
private OwnStringItem inStockField=null;
//private OwnStringItem unitTypeField=null;
  

private ViewProductForm()
	{
	super(Props.get("view_product_title")); 
	
	/*
	this.nameFieldLabel=new OwnStringItem(Props.get("add_product_name")+": " ,"");
	this.productIdFieldLabel=new OwnStringItem(Props.get("add_product_id")+": ","");
	this.unitFieldLabel=new OwnStringItem(Props.get("add_product_unit")+": ","");
	this.buyFieldLabel=new OwnStringItem(Props.get("view_product_buyprice")+": ","");
	this.sellFieldLabel=new OwnStringItem(Props.get("view_product_sellprice")+": ","");
	this.sellTaxedFieldLabel=new OwnStringItem(Props.get("view_product_taxedsellprice")+": ","");
	this.vatPercentFieldLabel=new OwnStringItem(Props.get("add_product_vatpercent")+": ","");
	this.inStockFieldLabel=new OwnStringItem(Props.get("add_product_instock")+": ","");
	this.unitTypeFieldLabel=new OwnStringItem(Props.get("add_product_unittype")+": ","");
	*/
	
	this.nameField=new OwnStringItem(Props.get("add_product_name")+": " ,"");
	this.productIdField=new OwnStringItem(Props.get("add_product_id")+": ","");
	this.unitField=new OwnStringItem(Props.get("add_product_unit")+": ","");
	this.buyField=new OwnStringItem(Props.get("view_product_buyprice")+": ","");
	this.sellField=new OwnStringItem(Props.get("view_product_sellprice")+": ","");
	this.sellTaxedField=new OwnStringItem(Props.get("view_product_taxedsellprice")+": ","");
	this.vatPercentField=new OwnStringItem(Props.get("add_product_vatpercent")+": ","");
	this.inStockField=new OwnStringItem(Props.get("add_product_instock")+": ","");
	//this.unitTypeField=new OwnStringItem(Props.get("add_product_unittype")+": ","");
	
	
	//this.append(this.nameFieldLabel);
	this.nameField.appendToForm(this);
	//this.append(this.productIdFieldLabel);
	this.productIdField.appendToForm(this);
	//this.append(this.unitFieldLabel);
	this.unitField.appendToForm(this);
	//this.append(this.sellFieldLabel);
	this.sellField.appendToForm(this);
	//this.append(this.sellTaxedFieldLabel);
	this.sellTaxedField.appendToForm(this);
	//this.append(this.vatPercentFieldLabel);
	this.vatPercentField.appendToForm(this);
	//this.append(this.inStockFieldLabel);
	this.inStockField.appendToForm(this);
	//this.append(this.buyFieldLabel);
	this.buyField.appendToForm(this);
	//this.append(this.unitTypeField);
	}
	
public static ViewProductForm instance(DataObject object)
	{
	Product prod=(Product)object;
	if (_instance==null)
		{
		_instance=new ViewProductForm();
		}

	_instance.nameField.setText(prod.getName());
	_instance.productIdField.setText(prod.getProductId());
	_instance.unitField.setText(prod.getUnit());
	
	_instance.buyField.setText(prod.getBuyPrice().toString());
	_instance.sellField.setText(prod.getSellPrice().toString());
	_instance.sellTaxedField.setText(prod.getTaxedSellPrice().toString());
	_instance.vatPercentField.setText(prod.getVatPercent().toString());
	_instance.inStockField.setText(prod.getInStock().toString());
	
	
	return _instance;	
	}	

}
