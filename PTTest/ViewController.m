//
//  ViewController.m
//  PTTest
//
//  Created by PDFTron on 2013-07-09.
//  Copyright (c) 2013 PDFTron. All rights reserved.
//

#import "ViewController.h"
#import "PDFNetOBJC.h"
#import "PDFViewCtrl.h"
#import "Tool.h"
#import "PanTool.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib
    
    // Initilize PDFNet (in demo mode - pages will be watermarked)
    [PDFNet initialize];
    
    // Get the path to document in the app bundle.
    NSString* fullPath = [[NSBundle mainBundle] pathForResource:@"mech" ofType:@"pdf"];
    
    // Initialize a new PDFDoc with the path to the file
    PDFDoc* docToOpen = [[PDFDoc alloc] initWithFilepath:fullPath];
    
    // Create a new PDFViewCtrl that is the size of the entire screen
    PDFViewCtrl* pdfViewCtrl = [[PDFViewCtrl alloc] initWithFrame:[self.view bounds]];
    
    // Set the document to display
    [pdfViewCtrl SetDoc:docToOpen];
    
    // Add the PDFViewCtrl to the root view
    [self.view addSubview:pdfViewCtrl];
    
    [self.view setBackgroundColor:[UIColor scrollViewTexturedBackgroundColor]];
    
    [pdfViewCtrl SetBackgroundColor:255 g:255 b:255 a:0];
    
    [pdfViewCtrl setTool:[[PanTool alloc] initWithPDFViewCtrl:pdfViewCtrl]];
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
