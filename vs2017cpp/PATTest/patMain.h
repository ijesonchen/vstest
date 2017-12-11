#ifndef patMain_h__
#define patMain_h__

#include <string>

void RedirCin(const std::string& fn);
void Tick(void);
void Tock(void);

#include "patBasic.h"
void Basic(void);

#include "patAdvanced.h"
void Advanced(void);

#include "patTop.h"
void Top(void);

void PatMain(void);


#endif // patMain_h__
