#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
void InnerLoopController(void);
void OuterLoopController(void);
void UpdateDuty(uint16_t  motor[]);
void YawOutputSmooth(void);
void PitchOutputSmooth(void);
void RollOutputSmooth(void);
#endif
