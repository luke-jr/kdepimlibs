find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS Test Widgets)

add_subdirectory(messagetests)

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro(add_akonadi_isolated_test _source)
  get_filename_component(_targetName ${_source} NAME_WE)
  set(_srcList ${_source} )
  kconfig_add_kcfg_files( _srcList ../src/specialmailcollectionssettings.kcfgc )

  add_executable(${_targetName} ${_srcList})
  target_link_libraries(${_targetName}
    Qt5::Test
    KF5::MailTransport
    KF5::Mime
    KF5::AkonadiMime
    Qt5::Widgets
  )

  # based on kde4_add_unit_test
  if (WIN32)
    get_target_property( _loc ${_targetName} LOCATION )
    set(_executable ${_loc}.bat)
  else()
    set(_executable ${EXECUTABLE_OUTPUT_PATH}/${_targetName})
  endif()
  if (UNIX)
    set(_executable ${_executable}.shell)
  endif()

  find_program(_testrunner akonaditest)

  if (KDEPIMLIBS_RUN_ISOLATED_TESTS)
    add_test( akonadikmime-${_targetName} ${_testrunner} -c ${CMAKE_CURRENT_SOURCE_DIR}/unittestenv/config.xml ${_executable} )
  endif()
endmacro()


if (KDEPIMLIBS_RUN_KDEPIMRUNTIME_ISOLATED_TESTS)
  add_akonadi_isolated_test( localfolderstest.cpp )
  add_akonadi_isolated_test( localfoldersrequestjobtest.cpp )
  add_akonadi_isolated_test( racetest.cpp )
  add_akonadi_isolated_test(collectionjobtest.cpp)

endif()

add_subdirectory(benchmarker)
