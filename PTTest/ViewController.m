//
//  ViewController.m
//  PTTest
//
//  Created by PDFTron on 2013-07-25.
//  Copyright (c) 2013 PDFTron. All rights reserved.
//

#import <PDFNet/PDFNetOBJC.h>
#import <PDFNet/PDFViewCtrl.h>
#import "ViewController.h"
#import "ToolManager.h"
#import "PanTool.h"


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    // Initilize PDFNet (in demo mode - pages will be watermarked)
    [PTPDFNet Initialize:@""];
	
	// Set resource path
	NSString* resourcePath = [[NSBundle mainBundle] pathForResource:@"pdfnet" ofType:@"res"];
	[PTPDFNet SetResourcesPath:resourcePath];;
    
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
	
	[pdfViewCtrl setTranslatesAutoresizingMaskIntoConstraints:NO];
	
	NSArray *imageViewConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[pdfViewCtrl]|" options:0 metrics:nil views:@{@"pdfViewCtrl": pdfViewCtrl}];
	[self.view addConstraints:imageViewConstraints];
	
	imageViewConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[pdfViewCtrl]|" options:0 metrics:nil views:@{@"pdfViewCtrl": pdfViewCtrl}];
	[self.view addConstraints:imageViewConstraints];
    
    // Makes the background light gray
    [self.view setBackgroundColor:[UIColor lightGrayColor]];
    
    // sets the non-page content of the PDFViewCtrl to transparent
    [pdfViewCtrl SetBackgroundColor:255 g:255 b:255 a:0];
    
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
