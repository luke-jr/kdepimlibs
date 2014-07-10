set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories(${CMAKE_BINARY_DIR}/akonadi/kmime)

# TODO apparently QTEST_AKONADIMAIN doesn't like NO_CASTs...
remove_definitions( -DQT_NO_CAST_FROM_ASCII )
remove_definitions( -DQT_NO_CAST_TO_ASCII )

set( requester_srcs foldersrequester.cpp )
add_executable( requester TEST "${requester_srcs}" )
target_link_libraries( requester akonadi-kmime akonadi-kde )
# for racetest
set(requester_exe_string "QLatin1String( \\\"${CMAKE_CURRENT_BINARY_DIR}/requester\\\" )" )
add_definitions( -DREQUESTER_EXE="${requester_exe_string}" )




macro(add_akonadi_isolated_test _source)
  get_filename_component(_targetName ${_source} NAME_WE)
  set(_srcList ${_source} )
  kconfig_add_kcfg_files( _srcList ../specialmailcollectionssettings.kcfgc )

  add_executable(${_targetName} TEST ${_srcList})
  target_link_libraries(${_targetName}
    Qt5::Test
    ${KDE4_AKONADI_LIBS}
    KF5::MailTransport
    KF5::Mime
    akonadi-kde
    akonadi-kmime
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
endif()