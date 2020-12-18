
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/



#ifndef __PFMEDITSHELLDEF_H__
#define __PFMEDITSHELLDEF_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <getopt.h>


/* Local Includes. */

#include "nvutility.h"
#include "pfm.h"


#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QSharedMemory>


//  The OPTIONS structure contains all those variables that can be saved to the
//  users pfmView QSettings.


typedef struct
{
  int32_t     position_form;              //  Position format number
  uint16_t    min_hsv_color;              //  HSV color wheel index for color to be used for minimum values in surface (default 0)
  uint16_t    max_hsv_color;              //  HSV color wheel index for color to be used for maximum values in surface (default 315)
  float       min_hsv_value;              //  Locked minimum data value for minimum HSV color
  float       max_hsv_value;              //  Locked maximum data value for maximum HSV color
  uint8_t     min_hsv_locked;             //  Set if min HSV is locked to a value
  uint8_t     max_hsv_locked;             //  Set if max HSV is locked to a value
  char        edit_name_3D[256];          //  3D Editor name
  int32_t     smoothing_factor;           //  Contour smoothing factor (0-10)
  float       z_factor;                   //  Coversion factor for Z values. May be used to convert m to ft...
  float       z_offset;                   //  Offset value for Z values.
  QString     feature_search_string;      //  Text to search for when highlighting features
  int32_t     layer_type;                 //  Type of bin data/contour to display (same as misc.abe_share->layer_type)
  float       cint;                       //  Contour interval (same as misc.abe_share->cint)
  int32_t     num_levels;                 //  Number of contour levels (same as misc.abe_share->num_levels)
  float       contour_levels[200];        //  User defined contour levels (same as misc.abe_share->contour_levels)
} OPTIONS;


//  General stuff.

typedef struct
{
  int32_t     poly_count;                 //  Polygon point count
  double      polygon_x[2000];            //  Polygon X
  double      polygon_y[2000];            //  Polygon Y
  QSharedMemory *abeShare;                //  ABE's shared memory pointer.
  ABE_SHARE   *abe_share;                 //  Pointer to the ABE_SHARE structure in shared memory.
  QString     qsettings_app;              //  Application name for QSettings
  int32_t     process_id;                 //  This program's process ID
  uint8_t     dateline;                   //  Set to NVTrue if any of the PFMs cross the dateline.
  uint8_t     editor_no_invalid;          //  This is set to run pfmEdit(3D) in "no invalid" mode.
} MISC;


#endif
