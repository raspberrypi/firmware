## Note about using NDK 1.0

If you are using NDK version 1.0, you will need to un-comment out the following in each of the bar-descriptor.xml files.

    <!-- BlackBerry NDK 1.0
    <asset path="${QNX_TARGET}/../target-override/${CPUVARDIR}/usr/lib/libbps.so" type="Qnx/Elf">lib/libbps.so.1</asset>
    -->

Otherwise you will see this warning.

    Asset requires dependency "C:\bbndk-1.0\target\target-override\armle-v7\usr\lib\libbps.so.1" to be included in the BAR package.	bar-descriptor.xml

## Installing the BlackBerry Native SDK for Tablet OS

In order to run the code samples, you will need to download The BlackBerry Native SDK for Tablet OS:

 * [BlackBerry Native SDK for Tablet OS 1.0](https://bdsc.webapps.blackberry.com/native/download)
 * or
 * [BlackBerry Native SDK for Tablet OS 2.0 Beta](https://bdsc.webapps.blackberry.com/native/beta/download/)

## Configuring the Native SDK

Instructions on how to configure the Native SDK and setup the signing keys can be found here:

[Getting started with the NDK](https://bdsc.webapps.blackberry.com/native/documentation/getting_started.html)

## Importing the projects into the workspace

 * Set the workspace to the base BlackBerry directory.
 * Import the projects into the workspace:
   * File > Import... > Existing Projects into Workspace
   * Next
   * Browse...
   * Ok (The workspace directory is selected by default)
   * Finish (All projects should be selected by default)
 * Build All

## Running on the PlayBook

Before attempting to deploy to the device, make sure that you have followed 
the instructions up to "Configure your environment for development and deployment".

[Getting started with the NDK](https://bdsc.webapps.blackberry.com/native/documentation/getting_started.html)

 * Enable Development Mode on your PlayBook
   * Go to Options by swiping down from the top of the homescreen
   * Security > Development Mode
   * Turn on Development mode
   * Note the Development Address
 * In the IDE, Create a BlackBerry Tablet OS Target
   * Connect your PlayBook via USB to your desktop and make sure that development mode is enabled
   * New > Other... > BlackBerry Tablet OS Target > Next
   * Enter your "Development Address" (probably 169.254.0.1)
   * Enter your PlayBook's password
   * Finish
   * A BlackBerry Tablet OS Target will appear under the Project Explorer. The name will be the same as the development address.
 * [Launching an application](https://bdsc.webapps.blackberry.com/native/documentation/com.qnx.doc.native_sdk.quickstart/topic/prepare_launch.html)
   * Create a launch configuration for each sample.
