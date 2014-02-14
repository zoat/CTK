#
# QtSOAP
#

ctkMacroShouldAddExternalproject(QtSOAP_LIBRARIES add_project)
if(${add_project})

  # Sanity checks
  if(DEFINED QtSOAP_DIR AND NOT EXISTS ${QtSOAP_DIR})
    message(FATAL_ERROR "QtSOAP_DIR variable is defined but corresponds to non-existing directory")
  endif()

  set(QtSOAP_enabling_variable QtSOAP_LIBRARIES)

  set(proj QtSOAP)
  set(proj_DEPENDENCIES)

  list(APPEND CTK_DEPENDENCIES ${proj})

  set(${QtSOAP_enabling_variable}_LIBRARY_DIRS QtSOAP_LIBRARY_DIRS)
  set(${QtSOAP_enabling_variable}_INCLUDE_DIRS QtSOAP_INCLUDE_DIRS)
  set(${QtSOAP_enabling_variable}_FIND_PACKAGE_CMD QtSOAP)

  if(CTK_SUPERBUILD)

    if(NOT DEFINED QtSOAP_DIR)

      set(revision_tag 3e49f7a4a1a684779eb66215bad46140d9153731)
      if(${proj}_REVISION_TAG)
        set(revision_tag ${${proj}_REVISION_TAG})
      endif()
      
      set(location_args )
      if(${proj}_URL)
        set(location_args URL ${${proj}_URL})
      elseif(${proj}_GIT_REPOSITORY)
        set(location_args GIT_REPOSITORY ${${proj}_GIT_REPOSITORY}
                          GIT_TAG ${revision_tag})
      else()
        set(location_args GIT_REPOSITORY "${git_protocol}://github.com/commontk/QtSOAP.git"
                          GIT_TAG ${revision_tag})
      endif()

      #     message(STATUS "Adding project:${proj}")
      ExternalProject_Add(${proj}
        SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}
        BINARY_DIR ${proj}-build
        PREFIX ${proj}${ep_suffix}
        ${location_args}
        CMAKE_GENERATOR ${gen}
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        CMAKE_CACHE_ARGS
          ${ep_common_cache_args}
          -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:STRING=${CTK_CMAKE_RUNTIME_OUTPUT_DIRECTORY}
          -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
        DEPENDS
          ${proj_DEPENDENCIES}
        )
      set(QtSOAP_DIR "${CMAKE_BINARY_DIR}/${proj}-build")

      # Since the QtSOAP dll is created directly in CTK-build/bin, there is not need to add a
      # library output directory to CTK_EXTERNAL_LIBRARY_DIRS

    else()
      ctkMacroEmptyExternalproject(${proj} "${proj_DEPENDENCIES}")
    endif()

    list(APPEND CTK_SUPERBUILD_EP_VARS QtSOAP_DIR:PATH)

  endif()

endif()
