//
//  ImageUtils.m
//  Common
//
//  Created by Dan Ginsburg on 6/17/09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

///
//	Load a 24-bit PNG file
//
char*  esLoadPNG ( char *fileName, int *width, int *height )
{
	NSString *filePath = [NSString stringWithUTF8String: fileName];
	NSString *path = [[NSBundle mainBundle] pathForResource: filePath ofType:@"png"];
    NSData *texData = [[NSData alloc] initWithContentsOfFile:path];
    UIImage *image = [[UIImage alloc] initWithData:texData];
    
    *width = CGImageGetWidth(image.CGImage);
    *height = CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc( *height * *width * 4 );
    CGContextRef context = CGBitmapContextCreate( imageData, *width, *height, 8, 4 * *width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
    CGColorSpaceRelease( colorSpace );
    CGContextClearRect( context, CGRectMake( 0, 0, *width, *height ) );
    CGContextTranslateCTM( context, 0, *height - *height );
    CGContextDrawImage( context, CGRectMake( 0, 0, *width, *height ), image.CGImage );
	
    CGContextRelease(context);
	
	[image release];
    [texData release];
	
	return imageData;    
}