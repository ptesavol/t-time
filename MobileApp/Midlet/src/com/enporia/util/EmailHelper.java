package com.enporia.util;

import java.util.*;
import java.io.*;

public class EmailHelper
{

public static byte[] createEmail(String from, String to, String subject , byte[] message, byte[] attachment)
	{
	//construct email message
	try {
	ByteArrayOutputStream payload=new ByteArrayOutputStream(message.length+attachment.length);
	
	payload.write("MIME-Version: 1.0\n".getBytes());
	payload.write(("From: "+from+"\n").getBytes());
	payload.write(("To: "+to+"\n").getBytes());
	payload.write(("Subject: "+subject+"\n").getBytes());
	payload.write("Content-Type: multipart/mixed; boundary=raja-1\n\n".getBytes());
	payload.write("--raja-1\n".getBytes());
	payload.write("Content-Type: Text/plain; charset=ISO-8859-1\n".getBytes());
	payload.write("Content-Transfer-Encoding: base64\n\n".getBytes());
	System.out.println("base64 alkaa");
	ByteArrayHolder holder=new ByteArrayHolder(message);
	int i=Base64.encodeText(holder);
	payload.write(holder.data, 0, i);
	payload.write("\n\n".getBytes());
	System.out.println("base64 p‰‰ttynyt");
	holder.data=null;
	message=null;
	System.gc();
	payload.write("--raja-1\n".getBytes());
	payload.write(("Content-Type: Application/x-tti; charset=ISO-8859-1; name="+subject+".tti\n").getBytes());
	payload.write(("Content-Disposition: attachment; filename="+subject+".tti\n").getBytes());
	payload.write("Content-Transfer-Encoding: base64\n\n".getBytes());
	holder.data=attachment;
	i=Base64.encodeText(holder);
	
	payload.write(holder.data,0,i);
	attachment=null;
	holder.data=null;
	holder=null;
	System.gc();
	
	payload.write("\n\n".getBytes());
	payload.write("--raja-1\n".getBytes());
	return payload.toByteArray();
	} catch (Exception e) {e.printStackTrace(); return null;}
	
	}

public static byte[] createEmail_lists(String from, String to, String subject , byte[] message, byte[] attachment)
	{ // 6.10.2008, J.V.
	//construct email message
	try {
		ByteArrayOutputStream payload=new ByteArrayOutputStream(message.length+attachment.length);

		payload.write("MIME-Version: 1.0\n".getBytes());
		payload.write(("From: "+from+"\n").getBytes());
		payload.write(("To: "+to+"\n").getBytes());
		payload.write(("Subject: "+subject+"\n").getBytes());
		payload.write("Content-Type: multipart/mixed; boundary=raja-1\n\n".getBytes());
		payload.write("--raja-1\n".getBytes());
		payload.write("Content-Type: Text/plain; charset=ISO-8859-1\n".getBytes());
		payload.write("Content-Transfer-Encoding: base64\n\n".getBytes());
		System.out.println("base64 alkaa");
		ByteArrayHolder holder=new ByteArrayHolder(message);
		int i=Base64.encodeText(holder);
		payload.write(holder.data, 0, i);
		payload.write("\n\n".getBytes());
		System.out.println("base64 p‰‰ttynyt");
		holder.data=null;
		//message=null;
		System.gc();
		payload.write("--raja-1\n".getBytes());
		payload.write(("Content-Type: Application/x-tta; charset=ISO-8859-1; name="+subject+".tta\n").getBytes());
		payload.write(("Content-Disposition: attachment; filename="+subject+".tta\n").getBytes());
		payload.write("Content-Transfer-Encoding: base64\n\n".getBytes());
		holder.data=attachment;
		i=Base64.encodeText(holder);

		payload.write(holder.data,0,i);
		//attachment=null;
		holder.data=null;
		holder=null;
		System.gc();

		payload.write("\n\n".getBytes());
		payload.write("--raja-1\n".getBytes());
		return payload.toByteArray();
	} catch (Exception e) {e.printStackTrace(); return null;}

	}
	
}
