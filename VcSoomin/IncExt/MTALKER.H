#define R_SUCCESSFUL	0
#define E_MEMALLOC	(-1)
#define E_TTSBUSY	(-2)
#define E_TTSWARNING	(-3)
#define E_TTSERROR	(-4)
#define E_DEVICEERROR	(-5)
#define E_NOTAUTHORIZED	(-6)


#ifdef __cplusplus
extern "C" {
#endif
int  Init_TTSSystem(char *RootDir);
int  Close_TTSSystem(void);
int  Change_TTSMode(int bDefaults,int ParamVolume,int ParamSpeaker,int ParamSpeechRate,int ParamPitch,int EffectId);
int  Get_TTSMode(int *ParamVolume,int *ParamSpeaker,int *ParamSpeechRate,int *ParamPitch,int *EffectId);
int  Play_TTSText(char *text,int bFullSentenceBuffering);
int Play_TTSShortText(char *text);
int  Stop_TTSSystem(void);
int  Pause_TTSSystem(void);
int  Resume_TTSSystem(void);
int  IsTTSBusy(void);
int  GetVolume(void);
void SetVolume(int Vol);
char *Get_TTSErrorMsg(char *buf,int nByte);
int  Pause_TTSSystem(void);
int  Resume_TTSSystem(void);
int GetStopPosition(void);

/* For Special Purpose, Use Carefully */

/* Set "Current Play Position in Text" CallBack Function*/
void SetPosCallBack( void (*CallBack)(int,int)); 


void SetCallBack( void (*CallBack)(int,int,short*));
long GetPlayPosition(void);

void PlayPCMData(int FlagSop,int NumData,short *Buf);
void ClearTTSUse(void);

void SetWaveVolume(int WaveVol); /* 1 - 9 , Default=7 */
int GetWaveVolume(void);		 /* 1 - 9 */

short *TextToPCM(char *Text,int *LengthInByte);
int   SavePCM2Wave(char *FileName,short *PCMData,int LengthInByte);
int   SavePCM2Wave8(char *FileName,short *PCMData,int LengthInByte);
void  FreePCMData(void *Buf);
/*           */


#ifdef __cplusplus
};
#endif

