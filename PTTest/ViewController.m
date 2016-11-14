//---------------------------------------------------------------------------------------
// Copyright (c) 2001-2016 by PDFTron Systems Inc. All Rights Reserved.
// Consult legal.txt regarding legal and license information.
//---------------------------------------------------------------------------------------


#import "ViewController.h"
#import <PDFNet/PDFNet.h>
#import <Tools/Tools.h>


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    // Initilize PDFNet (in demo mode - pages will be watermarked)
    [PTPDFNet Initialize:@""];
	
	// Get the path to document in the app bundle.
	NSString* fullPath = [[NSBundle mainBundle] pathForResource:@"mech" ofType:@"pdf"];
	
	// Initialize a new PDFDoc with the path to the file
	PTPDFDoc* docToOpen = [[PTPDFDoc alloc] initWithFilepath:fullPath];
	
	// Create a new PDFViewCtrl that is the size of the entire screen
	PTPDFViewCtrl* pdfViewCtrl = [[PTPDFViewCtrl alloc] init];
	
	// Set the document to display
	[pdfViewCtrl SetDoc:docToOpen];
	
	// Add the PDFViewCtrl to the root view
	[self.view addSubview:pdfViewCtrl];
	
	// set size of PDFViewCtrl
	[pdfViewCtrl setTranslatesAutoresizingMaskIntoConstraints:NO];
	
	[NSLayoutConstraint activateConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|[pdfViewCtrl]|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(pdfViewCtrl)]];
	
	[NSLayoutConstraint activateConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|[pdfViewCtrl]|" options:0 metrics:nil views:NSDictionaryOfVariableBindings(pdfViewCtrl)]];
	
	// Makes the background light gray
	[self.view setBackgroundColor:[UIColor lightGrayColor]];
	
	// sets the non-page content of the PDFViewCtrl to transparent
	[pdfViewCtrl SetBackgroundColor:0 g:0 b:0 a:0];
	
	// creates a new tool manager using the designated initializer
	ToolManager* toolManager = [[ToolManager alloc] initWithPDFViewCtrl:pdfViewCtrl];
	
	// registers the tool manager to receive events
	[pdfViewCtrl setToolDelegate:toolManager];
	
	// sets the initial tool
	[toolManager changeTool:[PanTool class]];

}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
