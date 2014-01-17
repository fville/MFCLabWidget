#include "stdafx.h"
#include "LabScale.h"


CLabScale::CLabScale(CLabBase *parent, double minimum, double maximum, double increment):
_parent(parent),
_min(minimum),
_max(maximum),
_logMapping(false),
_tickIncrement(increment),
_majorTickFrequency(5),
_tickMarkFrequency(5),
_precision(2),
_autoScale(false)
{
}

double CLabScale::getTickSpace()
{
   _nbOfTick = (int)((_max - _min) / _tickIncrement);
   return ((double)(getScaleLength()-1) / (double)_nbOfTick);
}


