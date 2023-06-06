#pragma once
#include <JuceHeader.h>

// DryWet parameters
#define DW_SMOOTHING_TIME 0.02f

#define NAME_DW "dw"
#define DEFAULT_DW 0.5f

// Delay parameters
#define MAX_DELAY_TIME 0.08f
#define MIN_DELAY_TIME 0.02f
//#define DT_SMOOTHING_TIME 0.02f

#define NAME_DT "dt"
#define DEFAULT_DT 0.03f

// Oscillator parameters
#define GLIDE_TIME 0.01

#define NAME_FREQ "rate"
#define	DEFAULT_FREQ 0.3f

#define NAME_WF "wf"
#define DEFAULT_WF 0

#define NAME_PD "phase"
#define DEFAULT_PD 0.2f

// ParameterModulation parameters
#define PM_SMOOTHING_TIME 0.04f

#define NAME_AM "amount"
#define DEFAULT_AM 0.010f
