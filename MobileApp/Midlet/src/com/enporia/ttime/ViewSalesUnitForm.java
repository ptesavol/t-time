package com.enporia.ttime;

import com.enporia.util.*;
import javax.microedition.lcdui.*;

public class ViewSalesUnitForm extends ViewForm
{
private static ViewSalesUnitForm _instance=null;

private OwnStringItem customerField=null;
private OwnStringItem contractorField=null;
private OwnStringItem productField=null;
private OwnStringItem unitField=null;
private OwnStringItem amountField=null;
private OwnStringItem unitPriceField=null;
private OwnStringItem vatPercentField=null;
private OwnStringItem taxedUnitPriceField=null;
private OwnStringItem totalPriceField=null;
private OwnStringItem taxedTotalPriceField=null;
private OwnStringItem salesTimeField=null;

/*
private StringItem customerFieldLabel=null;
private StringItem productFieldLabel=null;
private StringItem unitFieldLabel=null;
private StringItem amountFieldLabel=null;
private StringItem unitPriceFieldLabel=null;
private StringItem vatPercentFieldLabel=null;
private StringItem taxedUnitPriceFieldLabel=null;
private StringItem totalPriceFieldLabel=null;
private StringItem taxedTotalPriceFieldLabel=null;
private StringItem salesTimeFieldLabel=null;
*/

private ViewSalesUnitForm()
	{
	super(Props.get("view_salesunit_title")); 
	/*
	this.customerFieldLabel=new StringItem(Props.get("view_salesunit_customer")+": " ,"");
	this.productFieldLabel=new StringItem(Props.get("view_salesunit_product")+": ","");
	this.unitFieldLabel=new StringItem(Props.get("view_salesunit_unit")+": ","");
	this.amountFieldLabel=new StringItem(Props.get("view_salesunit_amount")+": ","");
	this.unitPriceFieldLabel=new StringItem(Props.get("view_salesunit_unitprice")+": ","");
	this.taxedUnitPriceFieldLabel=new StringItem(Props.get("view_salesunit_taxedunitprice")+": ","");
	this.vatPercentFieldLabel=new StringItem(Props.get("add_product_vatpercent")+": ","");
	this.totalPriceFieldLabel=new StringItem(Props.get("view_salesunit_totalprice")+": ","");
	this.taxedTotalPriceFieldLabel=new StringItem(Props.get("view_salesunit_taxedtotalprice")+": ","");
	this.salesTimeFieldLabel=new StringItem(Props.get("view_salesunit_salestime")+": ","");
	*/
	this.customerField=new OwnStringItem(Props.get("view_salesunit_customer")+": ","");
	this.contractorField=new OwnStringItem(Props.get("view_salesunit_contractor")+": ","");
	this.productField=new OwnStringItem( Props.get("view_salesunit_product")+": ","");
	this.unitField=new OwnStringItem(Props.get("view_salesunit_unit")+": ","");
	this.amountField=new OwnStringItem(Props.get("view_salesunit_amount")+": ","");
	this.unitPriceField=new OwnStringItem(Props.get("view_salesunit_unitprice")+": ","");
	this.taxedUnitPriceField=new OwnStringItem(Props.get("view_salesunit_taxedunitprice")+": ","");
	this.vatPercentField=new OwnStringItem(Props.get("add_product_vatpercent")+": ","");
	this.totalPriceField=new OwnStringItem(Props.get("view_salesunit_totalprice")+": ","");
	this.taxedTotalPriceField=new OwnStringItem(Props.get("view_salesunit_taxedtotalprice")+": ","");
	this.salesTimeField=new OwnStringItem(Props.get("view_salesunit_salestime")+": ","");
	
	
	//this.append(this.customerFieldLabel);
	this.customerField.appendToForm(this);
	this.contractorField.appendToForm(this);
	//this.append(this.productFieldLabel);
	this.productField.appendToForm(this);
	//this.append(this.unitFieldLabel);
	this.unitField.appendToForm(this);
	//this.append(this.amountFieldLabel);
	this.amountField.appendToForm(this);
	//this.append(this.unitPriceFieldLabel);
	this.unitPriceField.appendToForm(this);
	//this.append(this.vatPercentFieldLabel);
	this.vatPercentField.appendToForm(this);
	//this.append(this.taxedUnitPriceFieldLabel);
	this.taxedUnitPriceField.appendToForm(this);
	//this.append(this.totalPriceFieldLabel);
	this.totalPriceField.appendToForm(this);
	//this.append(this.taxedTotalPriceFieldLabel);
	this.taxedTotalPriceField.appendToForm(this);
	//this.append(this.salesTimeFieldLabel);
	this.salesTimeField.appendToForm(this);
	}
	
public static ViewSalesUnitForm instance(DataObject object)
	{
	SalesUnit tunit=(SalesUnit)object;
	if (_instance==null)
		{
		_instance=new ViewSalesUnitForm();
		}

	_instance.customerField.setText(tunit.getCustomerName()+"\n");
	_instance.contractorField.setText(tunit.getContractor()+"\n");
	_instance.productField.setText(tunit.getProductName()+"\n");
	_instance.unitField.setText(tunit.getUnit()+"\n");

	_instance.amountField.setText(tunit.getAmount().toString()+"\n");
	_instance.unitPriceField.setText(tunit.getUnitPrice().toString()+"\n");
	_instance.vatPercentField.setText(tunit.getVatPercent().toString()+"\n");
	
	

	_instance.taxedUnitPriceField.setText(tunit.getTaxedUnitPrice().toString()+"\n");
	_instance.totalPriceField.setText(tunit.getTotalPrice().toString()+"\n");

	
	_instance.taxedTotalPriceField.setText(tunit.getTaxedTotalPrice().toString()+"\n");
	_instance.salesTimeField.setText(DateHelper.getHoursAndMinutes(tunit.getSalesTime())+"\n");
	
	return _instance;	
	}	

}
