package com.enporia.ttime;

import com.enporia.util.*;
import java.util.*;
import java .io.*;

public class DocumentCreator
{
//private final static byte[] DOT=".".getBytes();
private final static byte[] TAB="	".getBytes(); // 6.10.2008, J.V.
private final static byte[] LF="\n".getBytes();
private final static byte[] SPACE=" ".getBytes();
private final static byte[] DOUBLEDOT=":".getBytes();
private final static byte[] CONTRACTORS="[laskuttajat]".getBytes(); // 6.10.2008, J.V.
private final static byte[] WORKPLACES="[asiakkaat]".getBytes();
private final static byte[] WORKTYPES="[työtyypit]".getBytes();
private final static byte[] PRODUCTS="[tuotteet]".getBytes();
/*
public static String createXml(String workername, String contractorname, Vector workunits)
	{
	Calendar cal = Calendar.getInstance();
	String daystring=""+ 
	cal.get(Calendar.DATE)+"."+
	DateHelper.getMonth(cal)+"."+
	cal.get(Calendar.YEAR)+" "+cal.get(Calendar.HOUR_OF_DAY)+":"+
	cal.get(Calendar.MINUTE)+":"+cal.get(Calendar.SECOND);
	
	
	String ret="<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
	ret+="<report>\n";
	ret+="<contractor><![CDATA["+contractorname+"]]></contractor>\n";
	ret+="<worker><![CDATA["+workername+"]]></worker>\n";
	ret+="<created>"+daystring+"</created>\n";
	
	for (int i=0; i<workunits.size(); i++)	//workunits.size
		ret+=((WorkUnit)workunits.elementAt(i)).getXml2();
	
	ret+="</report>";
	
	return ret;
	}

public static String createAscii(String workername, String contractorname, Vector workunits)
	{
	String ret="Työaikaraportti ";
	Calendar cal = Calendar.getInstance();
	String daystring=""+ 
	cal.get(Calendar.DATE)+"."+
	DateHelper.getMonth(cal)+"."+
	cal.get(Calendar.YEAR)+" "+cal.get(Calendar.HOUR_OF_DAY)+":"+
	cal.get(Calendar.MINUTE)+":"+cal.get(Calendar.SECOND);
	ret+=daystring+"\n\n";
	ret+="Työntekijä: "+workername+"\n";
	ret+="Laskuttaja: "+contractorname+"\n\n";
	ret+="Työkohde	Työtyyppi	Aloitusaika	Lopetusaika	Tehokas työaika (min)\n\n";	
	for (int i=0; i<workunits.size(); i++)	//workunits.size()
		ret+=((WorkUnit)workunits.elementAt(i)).toString();
	return ret;
	}
*/	
public static void bufferAscii(OutputStream buffer, String workername, String contractorname)
	{
	try	{
		buffer.write("Työaikaraportti".getBytes());
		buffer.write(DOUBLEDOT);
		buffer.write(TAB);
		Calendar cal=Calendar.getInstance();
		buffer.write(DateHelper.getDayString().getBytes());		
		buffer.write(SPACE);
		buffer.write(DateHelper.getHoursAndMinutes(cal).getBytes());
		buffer.write(LF);
		buffer.write(Props.get("settings_worker").getBytes());
		buffer.write(DOUBLEDOT);
		buffer.write(TAB);
		buffer.write(workername.getBytes());
		buffer.write(LF);
		buffer.write(Props.get("add_workplace_contractor").getBytes());
		buffer.write(DOUBLEDOT);
		buffer.write(TAB);
		buffer.write(contractorname.getBytes());
		buffer.write(LF);
		buffer.write(LF);
		buffer.write(Props.get("documentcreator_header").getBytes());
		buffer.write(LF);
		buffer.write(LF);
		} 
	catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

public static void bufferAscii_Lists(OutputStream buffer, String info) // 6.10.2008, J.V.
{
	try	{
		buffer.write("t-aika-listat".getBytes());
		buffer.write(DOUBLEDOT);
		buffer.write(TAB);
		Calendar cal=Calendar.getInstance();
		buffer.write(DateHelper.getDayString().getBytes());		
		buffer.write(SPACE);
		buffer.write(DateHelper.getHoursAndMinutes(cal).getBytes());
		buffer.write(LF);
		
		if(!info.equals(""))
		{
		buffer.write("info".getBytes());
		buffer.write(DOUBLEDOT);
		buffer.write(TAB);
		buffer.write(info.getBytes());
		buffer.write(LF);
		}
		} 
		catch (Exception e) 
		{
		e.printStackTrace();
		}
	}

public static void insert_Contractors(OutputStream buffer) throws IOException // 6.10.2008, J.V.
	{
	int i, s;
	Vector vect = new Vector();
	Contractor cont = new Contractor();
	
	vect = ContractorList.instance().getElements();                  // Get Contractors and the size
    s = vect.size();
	
	buffer.write(DocumentCreator.CONTRACTORS);                       // Write CONTRACTORS block header
	buffer.write(DocumentCreator.TAB);
	buffer.write(new Integer(s).toString().getBytes());
	buffer.write(DocumentCreator.LF);
	
	for(i=0; i<s; i++)                                               // Write the Contractors
	{ // line: name, email
		cont.setBytes(((Contractor)vect.elementAt(i)).getBytes());
		
		buffer.write(cont.getName().getBytes());
		buffer.write(TAB);
		buffer.write(cont.getEmail().getBytes());
		buffer.write(LF);
	}
	
	vect.removeAllElements();
	}

public static void insert_WorkPlaces(OutputStream buffer) throws IOException // 6.10.2008, J.V.
	{
	String name;
	int i, j, wpf, wp, lines = 0;
	Vector vect_wpf = null;
	Vector vect_wp = null;
	WorkPlace work = new WorkPlace();
	ByteArrayOutputStream tempbuf = new ByteArrayOutputStream();

	vect_wpf = WorkPlaceFolderList.instance().getElements();             // Get WorkPlaceFolders and the size
	wpf = vect_wpf.size();

	for(i=0; i<wpf; i++)
	{ // line: workplacefolder_name, workplace_name, address, note, shortnote, info , contractor, id
		name = ((DataObject)vect_wpf.elementAt(i)).getName();            // Get WorkPlaceFolder name and change folder
		WorkPlaceList.instance().setName(name);
		wp = (vect_wp = WorkPlaceList.instance().getElements()).size();  // Get WorkPlaces for this WorkPlaceFolder and size

		tempbuf.write(name.getBytes());                                  // Write WorkPlaceFolder name first...
		for(j=0; j<wp; j++)                                              // ... then the WorkPlaces
		{
			work.setBytes(((WorkPlace)vect_wp.elementAt(j)).getBytes());

			tempbuf.write(TAB);
			tempbuf.write(work.getName().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(work.getAddress().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(work.getNote().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(work.getShortNote().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(work.getInfo().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(work.getContractor().getBytes());
			tempbuf.write(TAB);
			tempbuf.write("".getBytes());
			tempbuf.write(LF);
			
			lines++;
		}
		if(wp == 0) { tempbuf.write(LF); lines++; }                      // WorkPlaceFolder name only, no WorkPlaces?
	}

	buffer.write(DocumentCreator.WORKPLACES);                            // Write WORKPLACES block header now that we know the line count...
	buffer.write(DocumentCreator.TAB);
	buffer.write(new Integer(lines).toString().getBytes());
	buffer.write(DocumentCreator.LF);	
	buffer.write(tempbuf.toByteArray());                                 // ...and then the "pay load"
	
	tempbuf = null;
	System.gc();
	}

public static void insert_WorkTypes(OutputStream buffer) throws IOException // 6.10.2008, J.V.
	{
	int i, s;
	Vector vect = new Vector();
	WorkType work = new WorkType();

	vect = WorkTypeList.instance().getElements();                    // Get WorkTypes and the size
	s = vect.size();

	buffer.write(DocumentCreator.WORKTYPES);                         // Write WORKTYPES block header
	buffer.write(DocumentCreator.TAB);
	buffer.write(new Integer(s).toString().getBytes());
	buffer.write(DocumentCreator.LF);

	for(i=0; i<s; i++)                                               // Write the WorkTypes
	{ // line: name, id
		work.setBytes(((WorkType)vect.elementAt(i)).getBytes());
	
		buffer.write(work.getName().getBytes());
		buffer.write(TAB);
		buffer.write("".getBytes());
		buffer.write(LF);
	}

	vect.removeAllElements();
	}

public static void insert_Products(OutputStream buffer) throws IOException // 6.10.2008, J.V.
{
	String name;
	int i, j, pf, p, lines = 0;
	Vector vect_pf = null;
	Vector vect_p = null;
	Product prod = new Product();
	ByteArrayOutputStream tempbuf = new ByteArrayOutputStream();

	vect_pf = ProductFolderList.instance().getElements();                // Get ProductFolders and the size
	pf = vect_pf.size();

	for(i=0; i<pf; i++)
	{ // line: productfolder_name, product_name, idx, unit, buyprice, sellprice, vat%
		name = ((DataObject)vect_pf.elementAt(i)).getName();             // Get ProductFolder name and change folder
		ProductList.instance().setName(name);
		p = (vect_p = ProductList.instance().getElements()).size();      // Get Products for this ProductFolder and size

		tempbuf.write(name.getBytes());                                  // Write ProductFolder name first...
		for(j=0; j<p; j++)                                              // ... then the Products
		{
			prod.setBytes(((Product)vect_p.elementAt(j)).getBytes());

			tempbuf.write(TAB);
			tempbuf.write(prod.getName().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(prod.getProductId().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(prod.getUnit().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(prod.getBuyPrice().toStringWithDot().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(prod.getSellPrice().toStringWithDot().getBytes());
			tempbuf.write(TAB);
			tempbuf.write(prod.getVatPercent().toStringWithDot().getBytes());
			tempbuf.write(LF);
			
			lines++;
		}
		if(p == 0) { tempbuf.write(LF); lines++; }                       // ProductFolder name only, no Products?
	}

	buffer.write(DocumentCreator.PRODUCTS);                              // Write PRODUCTS block header now that we know the line count...
	buffer.write(DocumentCreator.TAB);
	buffer.write(new Integer(lines).toString().getBytes());
	buffer.write(DocumentCreator.LF);	
	buffer.write(tempbuf.toByteArray());                                 // ...and then the "pay load"

	tempbuf = null;
	System.gc();
}
}	
