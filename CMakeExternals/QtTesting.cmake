#
# QtTesting
#
SET (QtTesting_DEPENDS)
#ctkMacroShouldAddExternalProject(QtTesting_LIBRARIES add_project)
IF(CTK_USE_QTTESTING)
  # Sanity checks
  IF(DEFINED QtTesting_LIBRARIES AND NOT EXISTS ${QtTesting_LIBRARIES})
    MESSAGE(FATAL_ERROR "QtTesting_LIBRARIES variable is defined but corresponds to non-existing library")
  ENDIF()

  SET(QtTesting_enabling_variable QTTESTING_LIBRARY)

  SET(proj QtTesting)
  SET(proj_DEPENDENCIES)

  SET(QtTesting_DEPENDS ${proj})
 
  IF(NOT DEFINED QtTesting_DIR)
    MESSAGE(STATUS "Adding project:${proj}")
    ExternalProject_Add(${proj}
      GIT_REPOSITORY ${git_protocol}://paraview.org/QtTesting.git
      GIT_TAG "origin/master"
      INSTALL_COMMAND ""
      CMAKE_GENERATOR ${gen}
      CMAKE_ARGS
        ${ep_common_args}
        -DBUILD_SHARED_LIBS:BOOL=ON
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(QtTesting_DIR "${CTK_BINARY_DIR}/Utilities/${proj}")
  ELSE()
    ctkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()
ENDIF()

