# Find CEGUI includes and library
#
# This module defines
#  CEGUI_INCLUDE_DIR
#  CEGUI_LIBRARY, the library to link against to use CEGUI.



FIND_PATH(CEGUI_INCLUDE_DIR
  NAMES cegui/CEGUI.h
  PATHS $ENV{CEGUIDIR}
  PATH_SUFFIXES /include /cegui/include /cegui/include/cegui /include/CEGUI CEGUI.framework/Headers
)

MESSAGE (STATUS "*** CEGUI_INCLUDE_DIR is: ${CEGUI_INCLUDE_DIR}")




FIND_LIBRARY(CEGUI_LIBRARY_BASE
  NAMES CEGUIBase CEGUI CEGUIBase-0
  PATHS $ENV{CEGUIDIR}
  PATH_SUFFIXES lib bin build/lib build/bin
)
FIND_LIBRARY(CEGUI_LIBRARY_COMMON_DIALOGS
  NAMES
    CEGUICommonDialogs CEGUICommonDialogs-0
  PATHS $ENV{CEGUIDIR}
  PATH_SUFFIXES lib bin build/lib build/bin
)
FIND_LIBRARY(CEGUI_LIBRARY_OPENGL3RENDERER
  NAMES
    CEGUIOpenGLRenderer-0 CEGUIOpenGLRenderer
  PATHS $ENV{CEGUIDIR}
  PATH_SUFFIXES lib bin build/lib build/bin
)



SET(CEGUI_LIBRARY ${CEGUI_LIBRARY_BASE} ${CEGUI_LIBRARY_COMMON_DIALOGS} ${CEGUI_LIBRARY_OPENGL3RENDERER})


MESSAGE (STATUS "*** CEGUI_LIBRARY is: ${CEGUI_LIBRARY}")


