```html
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
  "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=us-utf8" />
<meta name="keywords" content="PDFNet, tutorial, ios, pdf"/>
<title>Getting Started with PDFNet for iOS</title>
<link rel="stylesheet" href="./assets/fonts-min.css" type="text/css" />
</head>
<body>
<h1>Getting started with iOS: Basic Tutorial</h1>



<h2>Introduction</h2>

This tutorial shows the minimum steps needed to open a PDF using PDFNet. It also shows how to add support for annotations,
and opening encrypted documents.

Note that a completed project can be found on our GitHub repository here. You should use the latest versions of 
libPDFNet.a and libTools.a, available by request <a href="http://www.pdftron.com/pdfnet/mobile/request_trial.html">on our website<a/>.<br/><br/>

The tutorial is divided into three parts:<br/>

<ul>
<li><a href="#part1">Part 1: Showing a PDF<a/>.</li>
<li><a href="#part2">Part 2: Adding support for text selection, annotation creation and editing, link following and form filling.</a></li>
<li><a href="#part3">Part 3: Adding support for encrypted PDF documents.</a></li>
<li><a href="#part4">Part 4: Next Steps</a></li>
</ul>
(Note that PDFNet for iOS includes the sample project "PDFViewCtrl", which implements the features contained in this sample plus more.)

<h2><a id="part1">Part 1: Showing a PDF</a></h2>

<ol>
<li><h3>Create a new project.</h3>
<p>
Open XCode and create a new iOS Project, choosing "Single View Application" from the list of available templates. After clicking "next",
name the project PTTest. Save the new project at the location of your choosing.
</p></li>
<li><h3>Edit the project's settings.</h3>
<p>The project's default settings need to be adjusted so that the project compiles properly with PDFNet's internal C++ code.
To make these changes, click on the PTTest project in the navigation pane. Click on the Build Settings tab. The required changes are:
<ul>
<li>Under Linking, add the linker flag -lstdc++ to Other Linker Flags, as shown below.<br><div align="center"><img src="./images/settings-edit.png"/></div></li>
<li>Under Apple LLVM [version] - Language, change the C++ standard library to libstdc++ from the drop down menu.</li>
<li>If you are using XCode 4.6 or earlier, you will need to explicity link with certain iOS frameworks. Again in the project's settings, but
under the Build Phases tab, exapnd the Link Binary With Libraries section. In addition to the standard frameworks CoreGraphics, UIKit and Foundation,
add CoreText and QuartzCore.
</ul>
</p></li>
<li><h3>Add the required PDFNet files, and a PDF Document.</h3><p>After downloading the SDK, you will need to add the following files to the
project. They are all found in Headers/ObjC folder:
<ul>
<li>PDFViewCtrl.h - The header file that gives access to the pre-built iOS PDF reader control.</li>
<li>PDFNetOBJC.h - The header file that gives Objective-C access to PDFNet.</li>
<li>Private.h - Needed by PDFNetOBJC.h.</li>
<li>NSObjectInitWithCptr.{h,m} - Adds a needed category to NSObject.</li>
</ul></p>
<p>
You will also need to add the PDFNet library itself, found in the Lib folder:
<ul>
<li>libPDFNet.a</li>
</ul></p>
<p>
Finally, you will need to ad a PDF file. For the purposes of this tutorial, we will use "mech.pdf", which is included in the Samples folder.

<ul>
<li>mech.pdf</li>
</ul></p>
You may use any PDF you wish, just replace "mech" with the name of your PDF in the code snippets that follow.
</li>

<li><h3>Add code to show a PDF.</h3>
<p>
Change ViewController.m to the following. The changes are the two additional #import statements,
and the code in the viewDidLoad selector.<br/>
<script src="https://gist.github.com/PDFTron/6011378.js"></script>
</p></li>
<li><h3>Run the app.</h3>
<p>
You can now run the app. If you run in the simulator, you will see the following. Note that the PDF can be scrolled and
zoomed.
</p>
<p align="center">
<img src="./images/iPad-Simulator.png"/>
<p>
When zooming, you might notice that the gray area behind the pages does not match the white background of the root view.
You can fix this by adding the following code at the end of the viewDidLoad selector.
<script src="https://gist.github.com/PDFTron/6016029.js"></script>
</p>
</li>
</ol>

<h2><a id="part2">Part 2: Adding support for Annotations, Text Selection and Form Filling.</a></h2>
<p>
PDFNet comes with built-in support for text selection, interactive annotation creation and editing, form filling and link following.
These features have been implemented using <a href="http://www.pdftron.com/pdfnet/mobile/iOSHTMLDoc/classes.html" target="_blank">PDFNet's
Objective-C API</a>, and are shipped in a separate static library, libTools.a. Licensed users are provided with the source code to libTools.a,
giving them complete flexibility and control to customize how users interact with the PDF so that it can fit their requirements
exactly.
</p>
<p>
To add support for annotations, text selection, etc:
<ol>
<li>Add libTools.a to the project, found in the Lib folder.</li>
<li>Add all of the files in /Lib/libTools Required Files/ to the project</li>
<li>Add Tool.h and PanTool.h, found in /Headers/ObjC/Tools/, top the project</li>
<li>Add #import Tool.h and #import PanTool.h at the top of ViewController.m</li>
<li>Add the following line as the last line of the viewDidLoad selector in ViewController.m<br/><br/>
<script src="https://gist.github.com/PDFTron/6016648.js"></script>
</li>
</ol>
</p>
<p>
The Color Picker's .m files (found in "libTools Required Files/Third Party/Color Picker/") do not use ARC for compatibilty with projects that do not use ARC.
As this tutorial does use ARC, these source files must be compiled withe the compiler flag -fno-objc-arc. Under the project's build phases tab, expand Compile
Sources and add the flag -fno-objc-arc to all of the Color Picker .m files.
</p>
<p>
You are now ready to run the project again. Now, when you run the project, you can select text, follow links and create and edit annotaitons.
To create a new annotion, long press on an area of the document to trigger a popup with annotation types to create. This example behavior is shown
in the blow screenshot.
</p>
<div align="center">
<img src="./Images/annotations.png" style="border:1px solid black"/>
</div>
<h2><a id="part3">Part 3: Opening encrypted documents.</a></h2>
<p>
PDFNet supports opening encrypted PDF documents. To open an encrypted document, all you need to do is initialize a PDFDoc's security handler with
the correct password. Add the following code snippet after creating the PDFDoc in order to display an encrypted PDF.
</p>
<p>
<script src="https://gist.github.com/PDFTron/6023297.js"></script>
</p>
<p>
Of course a "real" app would require that the password be obtained from the user, which is implemented in the sample viewer that is included
with the PDFNet for iOS download.
</p>
<h2><a id="part4">Part 4: Next Steps</a></h2>
<p>
This concludes our introductory PDFNet for iOS Tutorial. The completed tutorial project can be downloaded from <a href="#">GitHub<a/>. For more help, please see our
<a href="http://www.pdftron.com/pdfnet/samplecode.html">sample code page</a>, as well as our <a href="#">other tutorials</a>.
</p>

</body>
```
