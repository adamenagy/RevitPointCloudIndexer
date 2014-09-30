RevitPointCloudIndexer
======================

Point Cloud indexer for Revit 2012

This sample shows how you can index your own point cloud file format, 
i.e. turn it into a *.pcg file that Autodesk products can open.

The project contains two User Macros to make things easier:

$(RVTPROGRAM) = C:/Program Files/Autodesk/Revit Architecture 2012/Program/ 
$(RVTSDK) = C:/Revit SDK 2012/

If on your system these values are not correct, then inside Visual Studio 2010 you 
can go to View >> Property Manager, then double-click on the Microsoft.Cpp.Win32.user entry
and under User Macros you'll find them and can modify them. 
Or you can also define Environment Variables.  

The project is a simple Win32 DLL project with the extra files added inside the Reader folder,
and an include folder added under 
Project Properties >> Configuration Properties >> VC++ Directories >> Include Directories 

To debug the project, you can just set the following values under 
Project Properties >> Configuration Properties >> Debugging: 

Command = $(RVTPROGRAM)AdPointCloudIndexer.exe
Command Arguments = "$(ProjectDir)Demo Head - Point Cloud.ASC" "$(ProjectDir)Demo Head - Point Cloud.pcg"

Written by Adam Nagy
Developer Technical Services 

(C) Copyright 2011 by Autodesk, Inc. 

Permission to use, copy, modify, and distribute this software in
object code form for any purpose and without fee is hereby granted, 
provided that the above copyright notice appears in all copies and 
that both that copyright notice and the limited warranty and
restricted rights notice below appear in all supporting 
documentation.

AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
UNINTERRUPTED OR ERROR FREE.
