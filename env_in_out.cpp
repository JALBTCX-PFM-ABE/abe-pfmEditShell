
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



#include "pfmEditShell.hpp"


//  We need to import a subset of the pfmView settings if we're going to bypass it and shell the editor.  Note that
//  we never save anything from this program.

double settings_version = 7.80;


uint8_t envin (OPTIONS *options, MISC *misc)
{
  double saved_version = 0.0;
  QString string;


  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/" + QString (misc->qsettings_app) + ".ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/" + QString (misc->qsettings_app) + ".ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup (misc->qsettings_app);

  saved_version = settings.value (pfmEditShell::tr ("settings version"), saved_version).toDouble ();


  //  If the settings version has changed we need to leave the values at the new defaults (from set_defaults.cpp) since they may have changed.

  if (settings_version != saved_version) return (NVFalse);


  options->position_form = settings.value (pfmEditShell::tr ("position form"), options->position_form).toInt ();

  options->min_hsv_color = settings.value (pfmEditShell::tr ("minimum hsv color value"), options->min_hsv_color).toInt ();
  options->max_hsv_color = settings.value (pfmEditShell::tr ("maximum hsv color value"), options->max_hsv_color).toInt ();
  options->min_hsv_locked = settings.value (pfmEditShell::tr ("minimum hsv locked flag"), options->min_hsv_locked).toBool ();
  options->max_hsv_locked = settings.value (pfmEditShell::tr ("maximum hsv locked flag"), options->max_hsv_locked).toBool ();
  options->min_hsv_value = (float) settings.value (pfmEditShell::tr ("minimum hsv locked value"), (double) options->min_hsv_value).toDouble ();
  options->max_hsv_value = (float) settings.value (pfmEditShell::tr ("maximum hsv locked value"), (double) options->max_hsv_value).toDouble ();


  QString en = settings.value (pfmEditShell::tr ("3D editor name"), QString (options->edit_name_3D)).toString ();
  strcpy (options->edit_name_3D, en.toLatin1 ());


  options->feature_search_string = settings.value (pfmEditShell::tr ("feature search string"), options->feature_search_string).toString ();

  options->smoothing_factor = settings.value (pfmEditShell::tr ("contour smoothing factor"), options->smoothing_factor).toInt ();

  options->z_factor = (float) settings.value (pfmEditShell::tr ("depth scaling factor"), (double) options->z_factor).toDouble ();

  options->z_offset = (float) settings.value (pfmEditShell::tr ("depth offset value"), (double) options->z_offset).toDouble ();

  options->cint = (float) settings.value (pfmEditShell::tr ("contour interval"), (double) options->cint).toDouble ();
  options->layer_type = settings.value (pfmEditShell::tr ("binned layer type"), options->layer_type).toInt ();


  options->num_levels = settings.value (pfmEditShell::tr ("contour levels"), options->num_levels).toInt ();

  for (int32_t i = 0 ; i < options->num_levels ; i++)
    {
      string.sprintf (pfmEditShell::tr ("contour level %d").toLatin1 (), i);
      options->contour_levels[i] = (float) settings.value (string, (double) options->contour_levels[i]).toDouble ();
    }


  settings.endGroup ();


  return (NVTrue);
}
