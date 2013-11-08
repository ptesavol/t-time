T-Time
======e

T-Time is a work time monitoring system for Java ME devices. Thois includes not only Nokia Series 40 and Series 60 devices, but also modern smartphones and Tablets (Android, Windows Phone, Meego).

Copyright
-------------------------------------------

The T-time (T-aika) Work Time Monitoring System by Enporia Oy. Copyright (C) 2004-2013 Enporia Oy, Finland. All rights reserved.
Released as open source under the GNU GENERAL PUBLIC LICENSE Version 2 (see LICENSE for details). Please contact petri.savolainen@hiit.fi for other (commercial or less restrictive open source) licencing options.

Building and running in an emulator
-------------------------------------------

1. Download and extract the Eclipse ADT Bundle from: http://developer.android.com/sdk/index.html#download

2. Download Microemulator from http://www.microemu.org/index.html and extract into the root of the adt bundle you just downloaded.

3. Install Eclipse Mobile Tools for Java into the Eclipse ADT Bundle by following the guide in http://www.oracle.com/technetwork/java/javame/javamobile/download/sdk/index.html
 
- In the Eclipse ADT, rename the file eclipse/plugins/org.eclipse.jetty.server_8.1.3.v20120522.jar to eclipse/plugins/org.eclipse.jetty.server_8.1.3.v20120522.old
- Add the following repository on your Eclipse Install Manager (Help > Software Updates... > Available Software > Add Site... ): http://download.eclipse.org/releases/indigo/. Install MTJ.
- If you are running Linux, Install the Sun wireless toolkit in order to get the "preverifier": http://www.oracle.com/technetwork/java/download-135801.html

4. Clone the T-Time repository from github into a folder OUTSIDE of your Eclipse workspace (this is important, if you clone to inside the workspace, the "import" function of Eclipse will fail silently), say,  "t-time" on your hard drive and open it using the Eclipse ADT using the menu "File->Import...->Java ME->EclipseME Project" and choosing the
"t-time/MobileApp/Midlet" as the root directory for projects to import. Import project T-time. When prompted for a device, choose the Microemulator devices you extracted in istallation step (2).

5. On a 64-bit Linux, use the preverifier of Sun WTK and the emulator of Microemulator. The WTK emulator does not work on 64-bit Linux, and microemulator does not include a preverifier. But surprisingly, this combination works! 

Running on Modern Smartphones and Tablets
-------------------------------------------

T-Time works om modern Smartphones and tablets (Android, Windows Phone, Meego) with PhoneME (Tested to work with Android): http://davy.preuveneers.be/phoneme.

I8N
-------------------------------------------

The texts shown in the user interface are located in res/taika_xx.properties files, where xx is a language code such as "en". By default, the properties files are written usiang a 8-bit ISO encoding.
You can choose the active properties file by editing the src/util/Props.java file. Feel free to translate T-time to new languages.


