
#ifndef __UNF_MCE_DEF_H__
#define __UNF_MCE_DEF_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MCE_DEF_BASEPARAM_SIZE       (8*1024)
#define MCE_DEF_LOGOPARAM_SIZE		 (8*1024)
#define MCE_DEF_PLAYPARAM_SIZE		 (8*1024)


#define MCE_BASE_TABLENAME_HD0          "BASE_TABLE_HD0"

#define MCE_BASE_KEYNAME_FMT            "BASE_KEY_FMT"
#define MCE_BASE_KEYNAME_INTF_YPBPR     "BASE_KEY_YPBPR"
#define MCE_BASE_KEYNAME_INTF_CVBS      "BASE_KEY_CVBS"
#define MCE_BASE_KEYNAME_INTF_RGB	    "BASE_KEY_RGB"
#define MCE_BASE_KEYNAME_INTF_SVIDEO    "BASE_KEY_SVIDEO"
#define MCE_BASE_KEYNAME_PF             "BASE_KEY_PF"
#define MCE_BASE_KEYNAME_DISPW          "BASE_KEY_DISPW"
#define MCE_BASE_KEYNAME_DISPH          "BASE_KEY_DISPH"
#define MCE_BASE_KEYNAME_SCRX           "BASE_KEY_SCRX"
#define MCE_BASE_KEYNAME_SCRY           "BASE_KEY_SCRY"
#define MCE_BASE_KEYNAME_SCRW           "BASE_KEY_SCRW"
#define MCE_BASE_KEYNAME_SCRH           "BASE_KEY_SCRH"
#define MCE_BASE_KEYNAME_HULEP          "BASE_KEY_HULEP"
#define MCE_BASE_KEYNAME_SATU           "BASE_KEY_SATU"
#define MCE_BASE_KEYNAME_CONTR          "BASE_KEY_CONTR"
#define MCE_BASE_KEYNAME_BRIG           "BASE_KEY_BRIG"
#define MCE_BASE_KEYNAME_BGCOLOR        "BASE_KEY_BGCOLOR"
#define MCE_BASE_KEYNAME_ASP_R          "BASE_KEY_ASP_R"
#define MCE_BASE_KEYNAME_ASP_C          "BASE_KEY_ASP_C"
#define MCE_BASE_KEYNAME_MACRSN         "BASE_KEY_MACRSN"
#define MCE_BASE_KEYNAME_TIMING         "BASE_KEY_TIMING"
#define MCE_BASE_KEYNAME_GAMA           "BASE_KEY_GAMA"

#define MCE_LOGO_TABLENAME              "LOGO_TABLE"
#define MCE_LOGO_KEYNAME_FLAG           "LOGO_KEY_FLAG"
#define MCE_LOGO_KEYNAME_CONTLEN        "LOGO_KEY_LEN"

#define MCE_PLAY_TABLENAME              "PLAY_TABLE"
#define MCE_PLAY_KEYNAME_FLAG           "PLAY_KEY_FLAG"
#define MCE_PLAY_KEYNAME_DATALEN        "PLAY_KEY_DATALEN"
#define MCE_PLAY_KEYNAME_PARAM          "PLAY_KEY_PARAM"


#ifdef __cplusplus
}
#endif

#endif