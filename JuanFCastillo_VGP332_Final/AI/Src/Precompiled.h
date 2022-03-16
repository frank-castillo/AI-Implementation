#pragma once

#include "Common.h"
// Can't find because it is on a different folder, so we have to go to AI and then properties
// Configure for All Platforms and then change the directory location using the macro $(ProjectDir)Inc\
// In order to avoid long times of compilation, specially for code that will never change or hardly do
// We use a precompiled header file to speed upo the build time
// Guidelines:
// We have to make sure that what the precompiled file will pull are things that will never change or rarely do
// If your project uses a precompiled header file (PCH), the PCH file should always be the first include!!!

// For your includes, do it in alphabetical order
// First add your PCH
// Then your own header files
// Then your classes
// Finally system includes
// All of this should be in alphabetical files

// TO tell C++ this is a PCH file, we go to properties of the project, activate the PCH option, and then change
// the PCH file name to our own PCH.h name
// Finally, with the window still opened, click on the .cpp file and on the option that says yes, change to create
// The yes box is the first drop down box menu, same we use to activate the PCH option


