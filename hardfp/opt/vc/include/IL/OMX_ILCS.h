/*=============================================================================
Copyright © 2010 Broadcom Europe Limited.

All rights reserved.

Project  :  OpenMAX IL
Module   :

FILE DESCRIPTION
OpenMAX IL - ILCS specific types
=============================================================================*/

#ifndef OMX_ILCS_h
#define OMX_ILCS_h

typedef struct OMX_PARAM_PORTSUMMARYTYPE {
   OMX_U32 nSize;            /**< Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
   OMX_U32 nNumPorts;        /**< Total number of ports */
   OMX_U32 reqSet;           /**< Which set of ports is details below, portIndex[0] is port reqSet*32 */
   OMX_U32 portDir;          /**< Bitfield, 1 if output port, 0 if input port, max 256 ports */
   OMX_U32 portIndex[32];    /**< Port Indexes */
} OMX_PARAM_PORTSUMMARYTYPE;

typedef struct OMX_PARAM_MARKCOMPARISONTYPE {
   OMX_U32 nSize;            /**< Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
   OMX_PTR mark;             /**< Pointer to be used for mark comparisons */
} OMX_PARAM_MARKCOMPARISONTYPE;

typedef struct OMX_PARAM_BRCMRECURSIONUNSAFETYPE {
   OMX_U32 nSize;
   OMX_VERSIONTYPE nVersion;
   OMX_S32 (*pRecursionUnsafe)(OMX_PTR param);
   OMX_PTR param;
} OMX_PARAM_BRCMRECURSIONUNSAFETYPE;

typedef struct OMX_PARAM_TUNNELSTATUSTYPE {
   OMX_U32 nSize;            /**< Size of the structure in bytes */
   OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
   OMX_U32 nPortIndex;       /**< Port being queried */
   OMX_U32 nIndex;           /**< Query the nIndex'th port and fill in nPortIndex */
   OMX_BOOL bUseIndex;       /**< If OMX_TRUE read nIndex, otherwise read nPortIndex */
   OMX_PTR hTunneledComponent; /**< Component currently tunnelling with */
   OMX_U32 nTunneledPort;    /**< Port on tunnelled component */
} OMX_PARAM_TUNNELSTATUSTYPE;

#endif
