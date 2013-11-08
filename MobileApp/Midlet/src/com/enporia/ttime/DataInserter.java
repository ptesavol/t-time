package com.enporia.ttime;

import com.enporia.util.*;

import java.io.*;
import java.util.Enumeration;
import java.util.Vector;

public class DataInserter
{
	// 2.10.2008, J.V.
	private static final byte[] LF = new byte[] {10};
	private static final String[] TABULATOR = new String[] {"\t"};
	private static final char[] IGNORENONE = new char[] {};
	private static final String LISTAT = "t-aika-listat:";
	private static String INFO = "info:";
	private static String ASIAKKAAT = "[asiakkaat]";
	private static String LASKUTTAJAT = "[laskuttajat]";
	private static String TYOTYYPIT = "[työtyypit]";
	private static String TUOTTEET = "[tuotteet]";
	
public DataInserter()
	{}

public static void insertWorkPlaces(InputStream stream)
	{
	WorkPlaceParser parser=new WorkPlaceParser(stream);
	String [] temp=new String[5];
	WorkPlace tplace=null;
	Vector vec=ContractorList.instance().getElements();	
	
	while ((temp=parser.getNext()) !=null)
		{
		if (!"".equals(temp[0]))
			{
			//create new folder
			WorkPlaceFolderList.instance().addElement(new FolderName(temp[0]));
			WorkPlaceList.instance().setName(temp[0]);
			}
		if (!"".equals(temp[1]))
			{
			//add new workplace
			tplace=new WorkPlace(temp[1],temp[2],temp[5],temp[3],temp[4],"") ;
			WorkPlaceList.instance().addElement(tplace);
			
			if ((! "".equals(tplace.getContractor())) && (DataObjectHelper.indexOf(vec,tplace.getContractor().toLowerCase()))==-1)
				{
				//System.out.println("."+tplace.getContractor()+".");
				Contractor tcont=new Contractor(tplace.getContractor(),"");
				ContractorList.instance().addElement(tcont);
				vec.addElement(tcont);
				}
			}
		}	
	}

public static void insertWorkPlacesFromDisk()
	{
	InputStream stream=null;
			
	try 	{
		if (WorkPlaceFolderList.instance().size()<2)
			{
			stream=Class.forName("com.enporia.ttime.DataInserter").getResourceAsStream(Props.get("workplacefilename"));
			DataInserter.insertWorkPlaces(stream);
			if (WorkPlaceFolderList.instance().size()>1)
				{
				WorkPlaceList.instance().setName(WorkPlaceFolderList.instance().elementAt(1).getName());
				}
			}
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}


public static void insertProducts(InputStream stream)
	{
	Tokenizer parser=new Tokenizer(stream);
	String [] temp=null;
	Product tproduct=null;
	//Vector vec=ContractorList.instance().getElements();	
	//System.out.println("before loop");
    FixedFloat tempVat=new FixedFloat();
	while ((temp=parser.getNext()) !=null)
		{
        //System.out.println("loop top");
		if (!"".equals(temp[0]))
			{
            //System.out.println("creating folder");
			//create new folder
			ProductFolderList.instance().addElement(new FolderName(temp[0]));
			ProductList.instance().setName(temp[0]);
			}
		if (!"".equals(temp[1]))
			{
			//add new product
			tproduct=new Product();
	        
            tproduct.setProductId(temp[1]);
            tproduct.setName(temp[2]);
            tproduct.setUnit(temp[3]);
            tproduct.setVatPercent(new FixedFloat(temp[4]));		
            tempVat.fromStrings("1",temp[4]);
            if (temp.length>6)
                {
			
                FixedFloat taxedPrice=new FixedFloat(temp[6]);
				taxedPrice.divideBy(tempVat);
				
				tproduct.setSellPrice(taxedPrice);
                }

            ProductList.instance().addElement(tproduct);
			
			/*if ((! "".equals(tplace.getContractor())) && (DataObjectHelper.indexOf(vec,tplace.getContractor().toLowerCase()))==-1)
				{
				//System.out.println("."+tplace.getContractor()+".");
				Contractor tcont=new Contractor(tplace.getContractor(),"");
				ContractorList.instance().addElement(tcont);
				vec.addElement(tcont);
				}
			*/
            }
		}	
	}

public static int parseDecimal(String input)
    {
    int ret=0;
    if (input!=null && !"".equals(input))
        {
        try {
            int i=input.indexOf(".");
            if (i==-1)
                {
                ret=Integer.parseInt(input)*100;
                }
            else
                {
                String intPart=input.substring(0,i);
                String decPart=input.substring(i+1);
                ret=(Integer.parseInt(intPart)*100)+Integer.parseInt(decPart);
                }
            }
        catch (Exception e) 
            {
            System.out.println(e);
            }
        }
    return ret;
    }

public static void insertProductsFromDisk()
	{
	InputStream stream=null;
			
	try 	{
		if (ProductFolderList.instance().size()<2)
			{
			stream=Class.forName("com.enporia.ttime.DataInserter").getResourceAsStream(Props.get("productfilename"));
			DataInserter.insertProducts(stream);
			if (ProductFolderList.instance().size()>1)
				{
				ProductList.instance().setName(ProductFolderList.instance().elementAt(1).getName());
				}
			}
		}
	catch (Exception e)
		{
		e.printStackTrace();
		}
	}

public static void insertDefaultWorker()
	{
	if (WorkerStore.instance().getSavedObject()==null)
		{
		Worker.instance().setEmail("");
		Worker.instance().setEmailServer("mail.inet.fi");
		Worker.instance().setEmailProxy("enporia.com/mailproxy.php");
		Worker.instance().setIMAPServer("mail.inet.fi"); // 17.9.2008, J.V.
		Worker.instance().setIMAPPort("143"); // 4.11.2009, J.V.
		Worker.instance().setUseIMAPEncrypted(false);
		Worker.instance().setUseProxy(false);
		WorkerStore.instance().saveObject(Worker.instance());
		}
	}
public static void insertDefaultContractors() 
	{
	if (ContractorList.instance().size()==0)
		{
		/*
		ContractorList.instance().addElement(new Contractor("Aarne","aarne.soininen@reppu.net"));
		ContractorList.instance().addElement(new Contractor("Reijo","reijo.soininen@dnainternet.net"));
		ContractorList.instance().addElement(new Contractor("TR","katajamaen.saha@pp.inet.fi"));
		ContractorList.instance().addElement(new Contractor("JL","jaakko_leskinen@reppu.net"));
		ContractorList.instance().addElement(new Contractor("JP","jani.pentikainen@jippii.fi"));
		
		ContractorList.instance().addElement(new Contractor("A.S","aarne.soininen@pp1.inet.fi"));
		ContractorList.instance().addElement(new Contractor("R.S","reijo.soininen@dnainternet.net"));
		ContractorList.instance().addElement(new Contractor("T.R","pentti.roininen@dnainternet.net"));
		ContractorList.instance().addElement(new Contractor("J.L","jaakko_leskinen@reppu.net"));
		ContractorList.instance().addElement(new Contractor("J.K","kaija.fohr@pp.nic.fi"));
		*/
		//ContractorList.instance().addElement(new Contractor("JP","jani.pentikainen@jippii.fi"));
		//ContractorList.instance().addElement(new Contractor("Talonhoito","mauri.boman@varkaudentalonhoito.fi"));
		//ContractorList.instance().addElement(new Contractor("Janne","janra80@dnainternet.net"));
		//ContractorList.instance().addElement(new Contractor("Malmin Lumikone","pete@malminlumikone.fi"));
		
		// varkaus 1.10.2008
		//ContractorList.instance().addElement(new Contractor("Talonhoito","mauri.boman@wartalo.fi"));
		
		ContractorList.instance().addElement(new Contractor("Oletus",""));
		}
	}

public static void insertDefaultWorkTypes()
	{
	if (WorkTypeList.instance().size()==0)
		{
		/*
		WorkTypeList.instance().addElement(new WorkType("Lumityö, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Lumityö, mies"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus, mies"));
		WorkTypeList.instance().addElement(new WorkType("Kattolumet, mies"));
		WorkTypeList.instance().addElement(new WorkType("Puuroskat, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Puuroskat, mies"));
		WorkTypeList.instance().addElement(new WorkType("Pihatyö, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Pihatyö, mies"));
		WorkTypeList.instance().addElement(new WorkType("Lehtipuhallintyö"));
		WorkTypeList.instance().addElement(new WorkType("Moottorisahatyö"));
		WorkTypeList.instance().addElement(new WorkType("Raivaussahatyö"));
		WorkTypeList.instance().addElement(new WorkType("Pientareen niitto"));
		WorkTypeList.instance().addElement(new WorkType("Tien lanaus"));
		WorkTypeList.instance().addElement(new WorkType("Kattotyöt"));
		WorkTypeList.instance().addElement(new WorkType("Miestyö"));
		WorkTypeList.instance().addElement(new WorkType("Hakkeen ajo"));
		WorkTypeList.instance().addElement(new WorkType("Soran seulonta"));
		WorkTypeList.instance().addElement(new WorkType("Valvonta"));
		*/
		
		/*
		WorkTypeList.instance().addElement(new WorkType("Auraus alle 10/krt"));
		WorkTypeList.instance().addElement(new WorkType("Auraus yli 10/krt"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus"));
		WorkTypeList.instance().addElement(new WorkType("Polanteen poisto"));
		WorkTypeList.instance().addElement(new WorkType("Penkan siirto"));
		WorkTypeList.instance().addElement(new WorkType("Karhun jäljet"));
		WorkTypeList.instance().addElement(new WorkType("Sepelilaat. täyttö"));
		WorkTypeList.instance().addElement(new WorkType("Sohjon poisto"));
		WorkTypeList.instance().addElement(new WorkType("Harj-hiekan peräk."));
		WorkTypeList.instance().addElement(new WorkType("Pihan tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Avoharjaus"));
		WorkTypeList.instance().addElement(new WorkType("Keräävä harjaus"));
		WorkTypeList.instance().addElement(new WorkType("Mullan ajo/tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Oksien/puutarhaj."));
		WorkTypeList.instance().addElement(new WorkType("Viheral. kunnostus"));
		WorkTypeList.instance().addElement(new WorkType("Kaatopaikkakuorma"));
		WorkTypeList.instance().addElement(new WorkType("Nostokorityö"));
		WorkTypeList.instance().addElement(new WorkType("Soranajo/tasaus"));
		WorkTypeList.instance().addElement(new WorkType("H-laatikkohiek."));
		WorkTypeList.instance().addElement(new WorkType("Peräkärrityö"));
		WorkTypeList.instance().addElement(new WorkType("Kauhatyöt"));
		WorkTypeList.instance().addElement(new WorkType("Kattolumien kuorm."));
		WorkTypeList.instance().addElement(new WorkType("Muu konetyö"));
		*/
		/*
		WorkTypeList.instance().addElement(new WorkType("Auraus alle 10/krt"));
		WorkTypeList.instance().addElement(new WorkType("Auraus yli 10/krt"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus"));
		WorkTypeList.instance().addElement(new WorkType("Sepelilaat. täyttö"));
		WorkTypeList.instance().addElement(new WorkType("Karhun jäljet"));
		WorkTypeList.instance().addElement(new WorkType("Penkan siirto"));
		WorkTypeList.instance().addElement(new WorkType("Polanteen poisto"));
		WorkTypeList.instance().addElement(new WorkType("Sohjon poisto"));
		WorkTypeList.instance().addElement(new WorkType("Avoharjaus"));
		WorkTypeList.instance().addElement(new WorkType("Harj-hiekan peräk."));
		WorkTypeList.instance().addElement(new WorkType("H-laatikkohiek. a."));
		WorkTypeList.instance().addElement(new WorkType("Kaatopaikkakuorma"));
		WorkTypeList.instance().addElement(new WorkType("Kattolumien kuorm."));
		WorkTypeList.instance().addElement(new WorkType("Kauhatyöt"));
		WorkTypeList.instance().addElement(new WorkType("Keräävä harjaus"));
		WorkTypeList.instance().addElement(new WorkType("Mullan ajo/tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Muu konetyö"));
		WorkTypeList.instance().addElement(new WorkType("Nostokorityö"));
		WorkTypeList.instance().addElement(new WorkType("Oksien/puutarhaj."));
		WorkTypeList.instance().addElement(new WorkType("Peräkärrityö"));
		WorkTypeList.instance().addElement(new WorkType("Pihan tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Soranajo/tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Viheral. kunnostus"));
		*/
		
		/*WorkTypeList.instance().addElement(new WorkType("auraus"));
		WorkTypeList.instance().addElement(new WorkType("1/2 auraus"));
		WorkTypeList.instance().addElement(new WorkType("hiekoitus"));
		WorkTypeList.instance().addElement(new WorkType("hiekoituksen tarkistus"));
		WorkTypeList.instance().addElement(new WorkType("kuormaus"));
		WorkTypeList.instance().addElement(new WorkType("muu tuntityö"));
		WorkTypeList.instance().addElement(new WorkType("harjaus"));*/
		
		/*
		WorkTypeList.instance().addElement(new WorkType("Lumityö, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Lumityö, mies"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus, mies"));
		WorkTypeList.instance().addElement(new WorkType("Kattolumet, mies"));
		WorkTypeList.instance().addElement(new WorkType("Hiekanpoisto, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Hiekanpoisto, mies"));
		WorkTypeList.instance().addElement(new WorkType("Puuroskat, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Puuroskat, mies"));
		WorkTypeList.instance().addElement(new WorkType("Puunajo, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Pihatyö, traktori"));
		WorkTypeList.instance().addElement(new WorkType("Pihatyö, mies"));
		WorkTypeList.instance().addElement(new WorkType("Lehtipuhallintyö"));
		WorkTypeList.instance().addElement(new WorkType("Moottorisahatyö"));
		WorkTypeList.instance().addElement(new WorkType("Raivaussahatyö"));
		WorkTypeList.instance().addElement(new WorkType("Pientareen niitto"));
		WorkTypeList.instance().addElement(new WorkType("Rehunteko"));
		WorkTypeList.instance().addElement(new WorkType("Tien lanaus"));
		WorkTypeList.instance().addElement(new WorkType("Kattotyöt"));
		WorkTypeList.instance().addElement(new WorkType("Miestyö"));
		WorkTypeList.instance().addElement(new WorkType("Hakkeen ajo"));
		WorkTypeList.instance().addElement(new WorkType("Hakepuun ajo"));
		WorkTypeList.instance().addElement(new WorkType("Soran seulonta"));
		WorkTypeList.instance().addElement(new WorkType("Kirjanpito"));
		WorkTypeList.instance().addElement(new WorkType("Valvonta"));
		WorkTypeList.instance().addElement(new WorkType("Muu työ"));
		*/
		
		/* Varkaus 1.10.2008
		WorkTypeList.instance().addElement(new WorkType("Auraus alle 10/krt"));
		WorkTypeList.instance().addElement(new WorkType("Auraus yli 10/krt"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitus/krt"));
		WorkTypeList.instance().addElement(new WorkType("Hiekoitussepelilaatikoiden täyttö"));
		WorkTypeList.instance().addElement(new WorkType("Karhun jäljet"));
		WorkTypeList.instance().addElement(new WorkType("Penkan siirto"));
		WorkTypeList.instance().addElement(new WorkType("Polanteen poisto"));
		WorkTypeList.instance().addElement(new WorkType("Sohjon poisto"));
		WorkTypeList.instance().addElement(new WorkType("Avoharjaus"));
		WorkTypeList.instance().addElement(new WorkType("Harjaushiekan peräkärrityö"));
		WorkTypeList.instance().addElement(new WorkType("Hiekkalaatikkohiekkojen ajo"));
		WorkTypeList.instance().addElement(new WorkType("Kaatopaikkakuorma"));
		WorkTypeList.instance().addElement(new WorkType("Kattolumien kuormaus"));
		WorkTypeList.instance().addElement(new WorkType("Kauhatyöt"));
		WorkTypeList.instance().addElement(new WorkType("Keräävä harjaus"));
		WorkTypeList.instance().addElement(new WorkType("Mullan ajo ja tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Muu konetyö"));
		WorkTypeList.instance().addElement(new WorkType("Nostokorityö"));
		WorkTypeList.instance().addElement(new WorkType("Oksien/puutarhajätteiden ajo"));
		WorkTypeList.instance().addElement(new WorkType("Peräkärrityö"));
		WorkTypeList.instance().addElement(new WorkType("Pihan tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Soranajo ja tasaus"));
		WorkTypeList.instance().addElement(new WorkType("Viheralueiden kunnostus"));*/
		
		WorkTypeList.instance().addElement(new WorkType("Lumityö"));
		}
	}
/*
public static void insertTestWorkUnits()
	{
	if (WorkUnitFolderList.instance().size()==0)
		{
		WorkUnitFolderList.instance().addElement(new FolderName(DateHelper.getDayString()));
		WorkUnitList.instance().setName(DateHelper.getDayString());
		for (int i=0; i<60; i++)
			{
			WorkUnitList.instance().addElement(new WorkUnit("Antti Paldanius_"+i,"lumityö",1234567890,1234567,1234567,"Petri","Aarne") );
			WorkUnitList.instance().addElement(new WorkUnit("Jätekukko_"+i,"lumityö",1234567890,1234567,1234567,"Petri","Reijo") );
			WorkUnitList.instance().addElement(new WorkUnit("Kadut_"+i,"lumityö",1234567890,1234567,1234567,"Petri","Tapani") );
			if ((i%20)==0)
				{
				WorkUnitFolderList.instance().addElement(new FolderName((i%30)+".2.2004"));
				WorkUnitList.instance().setName((i%30)+".2.2004");
				
				}
			}
		}
	}
*/

public static void makeIndexes()
	{
	/*
	 	class Existing
	{
	public String name = "";
	public int id = 0;
	}
	 */
	
	/*h = WorkPlaceFolderList.instance().size();
	Existing ex_WorkPlaceFolderList[] = new Existing[h];
	
	h = ProductFolderList.instance().size();
	Existing ex_ProductFolderList[] = new Existing[h];
	
	for(i=0; i<h; i++)
	{
		ex_WorkPlaceFolderList[i].id = WorkPlaceFolderList.instance().elementAt(i).getID();
		ex_WorkPlaceFolderList[i].name = WorkPlaceFolderList.instance().elementAt(i).getName();
	}*/
	}

public static void insertFromAttachment(byte[] attachment, boolean clear) throws IOException // 2.10.2008, J.V.
	{
	String name;
	int mode = 0, idx, i;
	String tokens[] = null;
	Vector vect = new Vector();
	
	// Clear existing data, except contractors. Contractors are needed when sending journals.
	if(clear)
	{
		vect = WorkPlaceFolderList.instance().getElements();
		for(i=0; i<vect.size(); i++)
		{
			name = ((DataObject)vect.elementAt(i)).getName();

			WorkPlaceList.instance().setName(name);                  // Clear all WorkPlaces from WorkPlaceFolders and all the WorkPlaceFolders
			//WorkPlaceList.instance().clear();
			WorkPlaceList.instance().deleteFromDisk();

			if(!name.equals(Props.get("workplacelist_assumed")))
			  WorkPlaceFolderList.instance().removeElementAt(WorkPlaceFolderList.instance().indexOf(name));
		}

		vect = ProductFolderList.instance().getElements();           // Clear all Products from ProductFolder and all the ProductFolders
		for(i=0; i<vect.size(); i++)
		{
			name = ((DataObject)vect.elementAt(i)).getName();

			ProductList.instance().setName(name);
			//ProductList.instance().clear();
			ProductList.instance().deleteFromDisk();

			if(!name.equals(Props.get("productlist_assumed")))
				ProductFolderList.instance().removeElementAt(ProductFolderList.instance().indexOf(name));
		}
		
		// WorkTypeList.instance().clear(); // <- For some reason clear doesn't work. Leaves some, apparently arbitrary, items on the list.
		while(WorkTypeList.instance().size() > 0)                  // Clear all WorkTypes
			WorkTypeList.instance().removeElementAt(0);
		
		vect.removeAllElements();
		System.gc();
	}

	// Add data to lists
	Index indxWP = new Index();                                      // Init search indexes
	Index indxP = new Index();
	Index indxC = newIndex(ContractorList.instance());
	Index indxWT = newIndex(WorkTypeList.instance());
	Index indxWPF = newIndex(WorkPlaceFolderList.instance());
	Index indxPF = newIndex(ProductFolderList.instance());
	
	GetLine gl = new GetLine(attachment, LF);
	while((tokens = gl.getNextTokenizedLine(TABULATOR, IGNORENONE, 0)) != null)
	{
		if(tokens.length == 0) continue;		 // skip empty lines

	/*String str = new String("");
for(int ii=0; ii<tokens.length; ii++)
	str += "'" + tokens[ii] + "' :: ";
System.out.println(str);*/
		
		// Control the parsing mode based on known qualifiers
		if(tokens[0].equalsIgnoreCase(LISTAT))
		{ continue; }
		else if(tokens[0].equalsIgnoreCase(INFO))
		{ continue; }
		else if(tokens[0].equalsIgnoreCase(LASKUTTAJAT)) 
		{ mode = 1; continue; }
		else if(tokens[0].equalsIgnoreCase(ASIAKKAAT))
		{ mode = 2; continue; }
		else if(tokens[0].equalsIgnoreCase(TYOTYYPIT))
		{ mode = 3; continue; }
		else if(tokens[0].equalsIgnoreCase(TUOTTEET))
		{ mode = 4; continue; }

		if(mode == 1)                            // Contractors, line: name = tokens[0], email = tokens[1]
		{
            idx = indxC.get(tokens[0]);
			if(idx == -1)                                            // Add new contractor + append to index
			{
				ContractorList.instance().addElement(new Contractor(tokens[0], tokens[1])); // name, email
				indxC.put(tokens[0], -2); // -2=not an index to a ContractorList element
			}
			else if(idx >= 0)                                        // Update existing Contractor
				ContractorList.instance().setElementAt(new Contractor(tokens[0], tokens[1]), idx);
		}
		else if(mode == 2)                       // WorkPlaceFolders/WorkPlaces (and contractors), line: workplacefolder_name = tokens[0], workplace_name = tokens[1], address = tokens[2], note = tokens[3], shortnote = tokens[4], info = tokens[5], contractor = tokens[6], id = tokens[7]
		{
			if(!tokens[0].equals(""))                                // Line begins with a WorkPlaceFolder name - setup folder for new workplaces?
			{	
				if(indxWPF.get(tokens[0]) == -1)                     // WorkPlaceFolder doesn't exist - create new
					WorkPlaceFolderList.instance().addElement(new FolderName(tokens[0]));
                 
				WorkPlaceList.instance().setName(tokens[0]);         // New index is created for this WorkPlaceFolder WorkPlaces
				indxWP = null; System.gc();
				indxWP = newIndex(WorkPlaceList.instance());
			}

			if(tokens.length == 1) continue;                         // Only WorkPlaceFolder name on this line -> continue to next line

			if((idx = indxWP.get(tokens[1])) == -1)                  // Add new WorkPlace
				WorkPlaceList.instance().addElement(new WorkPlace(tokens[1], tokens[2], tokens[3], tokens[6], tokens[4], tokens[5])); // name, address, note, contractor, shortnote, info
			else                                                     // Update existing WorkPlace
				WorkPlaceList.instance().setElementAt(new WorkPlace(tokens[1], tokens[2], tokens[3], tokens[6], tokens[4], tokens[5]), idx);

			if(indxC.get(tokens[6]) == -1)                           // Contractor not in the ContractorList? -> Add
			{
              ContractorList.instance().addElement(new Contractor(tokens[6], ""));
              indxC.put(tokens[6], -2); // -2=not an index to a ContractorList element
			}
		}
		else if(mode == 3)                       // WorkTypes, line: name = tokens[0], id = tokens[1] >> TODO: token[2] = changeTime, token[3] = changeTarget, token[4] = changeActive
		{
			if((idx = indxWT.get(tokens[0])) == -1)                  // Add new WorkType
				WorkTypeList.instance().addElement(new WorkType(tokens[0])); // name
			//else                                                     // Update existing WorkType - nothing to update for now!
			//	WorkTypeList.instance().setElementAt(new WorkType(tokens[0]));
		}
		else if(mode == 4)                       // ProductFolderList/Products, line: productfolder_name = tokens[0], product_name = tokens[1], idx = tokens[2], unit = tokens[3], buyprice = tokens[4], sellprice = tokens[5], vat% = tokens[6]
		{
			if(!tokens[0].equals(""))                                // Line begins with a ProductGroupFolder name - setup folder for new Products?
			{	
				if(indxPF.get(tokens[0]) == -1)                      // ProductGroupFolder doesn't exist - create new
					ProductFolderList.instance().addElement(new FolderName(tokens[0])); 

				ProductList.instance().setName(tokens[0]);          // New index is created for this ProductFolderList Products
				indxP = null; System.gc();
				indxP = newIndex(ProductList.instance());
			}
			
			if(tokens.length == 1) continue;                         // Only ProductFolder name on this line -> continue to next line

			if((idx = indxP.get(tokens[1])) == -1)                   // Add new Product
				ProductList.instance().addElement(new Product(tokens[1], tokens[2], tokens[3], new FixedFloat(tokens[4]), new FixedFloat(tokens[5]), new FixedFloat("0.0"), Product.TYPE_NUMERIC, new FixedFloat(tokens[6]))); // name, id, unit, buyprice, sellprice, instock, unittype, vat
			else                                                     // Update existing Product
			{
				Product p = new Product();                           // Preserve instock value >> TODO: instock to Windows-program
				p.setBytes(ProductList.instance().elementAt(idx).getBytes());
				ProductList.instance().setElementAt(new Product(tokens[1], tokens[2], tokens[3], new FixedFloat(tokens[4]), new FixedFloat(tokens[5]), p.getInStock(), Product.TYPE_NUMERIC, new FixedFloat(tokens[6])), idx);
			}
		}
	}

	indxWP = indxP = indxC= indxWT = indxWPF = indxPF = null;        // Dispose of some garbage
	System.gc();
	                                                                 // Refresh program state
	ProgramState.instance().setSelectedWorkPlaceFolder(Props.get("workplacelist_assumed"));
	ProgramState.instance().setSelectedWorkPlace(0);
	ProgramState.instance().setSelectedProductFolder(Props.get("productlist_assumed"));
	ProgramState.instance().setSelectedWorkType(0);
	ProgramState.instance().save();
                                                                     // Set assumed
	WorkPlaceList.instance().setName(Props.get("workplacelist_assumed"));
	ProductList.instance().setName(Props.get("productlist_assumed"));
	}

private static Index newIndex(PersistentList pl) // 4.10.2008, J.V.
	{
	int i, s;
	String name;
	Vector elements = pl.getElements();
	Index index = new Index((s = elements.size()));
	
	for(i=0; i<s; i++)
	{	
		name = ((DataObject)elements.elementAt(i)).getName();
		index.put(name, pl.indexOf(name));
	}
	
	return index;
	}
}
