package com.enporia.util;

import java.io.*;

/**
 * Provides a method to encode any string into a URL-safe
 * form, the so-called "x-www-form-urlencoded" form.
 * Non-ASCII characters are first encoded as sequences of
 * two or three bytes, using the UTF-8 algorithm, before being
 * encoded in "x-www-form-urlencoded".
 */
public class UrlEncoder
{

public static void encode(ByteArrayHolder holder)
	{
	ByteArrayOutputStream buffer = new ByteArrayOutputStream();
	int lower=0;
	int b=0;
	for (int i =0; i<holder.data.length; i++)
		{
		b=holder.data[i];
		if 	( 
			('A' <= b && b <= 'Z') ||
			('a' <= b && b <= 'z') ||
			('0' <= b && b <= '9') ||
			(b=='-') ||
        		(b=='_') ||
        		(b=='.') ||
        		(b=='*') ||
			(b==' ')
			)
			{
			if (b==' ')
				b='+';
			buffer.write(b);
			}
		else 	{
                	buffer.write('%');
                	lower=b&0x0f; 
			b=b>>4;
			if (b<10)
				b='0'+b;
			else b = (b-10) + 'A';
			buffer.write(b);
			if (lower<10)
				lower='0'+lower;
			else lower = (lower-10) + 'A';
			buffer.write(lower);
            		}
		}
	holder.data=buffer.toByteArray();
	}
}
