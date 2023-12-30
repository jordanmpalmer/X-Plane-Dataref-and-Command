
// Xcode X-Plane Plugin Boilerplate
// Published by Jordan Palmer

#define XPLM200 = 1;
#define XPLM210 = 1
#define XPLM300 = 1;  // requires SDK3.0

#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMProcessing.h"
#include "XPLMDataAccess.h"
#include "XPLMMenus.h"
#include "XPLMUtilities.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#include "XPLMScenery.h"

#include <string.h>
#include <math.h>

#define MSG_ADD_DATAREF 0x01000000           //  Add dataref to DRE message

// reference for dataref
XPLMDataRef switch_data_ref = NULL;
XPLMCommandRef on_command = NULL;
XPLMCommandRef off_command = NULL;

// give dataref a variable
int     switch_data;

// callbacks
float   first_data_ref_inDRE(float elapsedMe, float elapsedSim, int counter, void * refcon);

// callout command handler
int     on_command_handler(XPLMCommandRef inCommand, XPLMCommandPhase inPhase, void * inRefcon);
int     off_command_handler(XPLMCommandRef inCommand, XPLMCommandPhase inPhase, void * inRefcon);

// getters and setters
int     get_first_data_ref(void* inRefcon);
void    set_first_data_ref(void* inRefcon, int out_value);

PLUGIN_API int XPluginStart(
    char *        outName,
    char *        outSig,
    char *        outDesc)
{
    // Plugin Info for XP
    strcpy(outName, "First Data Ref");
    strcpy(outSig, "JordanPalmer.787plugins.switch_data_ref");
    strcpy(outDesc, "This is my first plugin to test the 787");
    
    // create our integer dataref in XP
    switch_data_ref = XPLMRegisterDataAccessor("Vertex/787-9/switch_data_ref",
                                              xplmType_Int,
                                              1,
                                              get_first_data_ref, set_first_data_ref,
                                              NULL, NULL,
                                              NULL, NULL,
                                              NULL, NULL,
                                              NULL, NULL,
                                              NULL, NULL,
                                              NULL, NULL);
    
    // initialize dataref variable value
    XPLMSetDatai(switch_data_ref, 0);
    
    // register function as callback
    XPLMRegisterFlightLoopCallback(first_data_ref_inDRE, 1, NULL);
    
    
    // create command in XP
    on_command = XPLMCreateCommand("Vertex/787-9/on_command", "Turn on first data");
    off_command = XPLMCreateCommand("Vertex/787-9/off_command", "Turn off first data");
    
    // register command handler in XP
    XPLMRegisterCommandHandler(on_command, on_command_handler, 1, (void*) 0);
    XPLMRegisterCommandHandler(off_command, off_command_handler, 1, (void*) 0);
    
    // display in dataref editor
    XPLMPluginID PluginID = XPLMFindPluginBySignature("xplanesdk.examples.DataRefEditor");
    if (PluginID != XPLM_NO_PLUGIN_ID)
    {
         XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void *)"Vertex/787-9/switch_data_ref");
    }
    
    return 1;
}


PLUGIN_API void     XPluginStop(void)
{
    // clean up dataref
    XPLMUnregisterDataAccessor(switch_data_ref);
    XPLMUnregisterCommandHandler(on_command, on_command_handler, 0, 0);
    XPLMUnregisterCommandHandler(off_command, off_command_handler, 0, 0);
    XPLMUnregisterFlightLoopCallback(first_data_ref_inDRE, NULL);
}

PLUGIN_API void XPluginDisable(void)
{
    
}
 
PLUGIN_API int XPluginEnable(void)
{
    return 1;
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID    inFromWho,
                                     long             inMessage,
                                     void *           inParam)
{
    
}

int get_first_data_ref(void* inRefcon)
{
    return switch_data;
}

void set_first_data_ref(void* inRefcon, int out_value)
{
    
}

float first_data_ref_inDRE(float elapsedMe, float elapsedSim, int counter, void * refcon)
{
    return 0;
}


int on_command_handler(XPLMCommandRef inCommand, XPLMCommandPhase inPhase, void * inRefcon)
{
    if(inPhase == 0)
    {
        switch_data = 0;
    }
    return 0;
}

int off_command_handler(XPLMCommandRef inCommand, XPLMCommandPhase inPhase, void * inRefcon)
{
    if(inPhase == 1)
    {
        switch_data = 1;
    }
    return 0;
}
