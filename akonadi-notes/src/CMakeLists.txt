set(akonadinotes_LIB_SRC
  noteutils.cpp
)

ecm_qt_declare_logging_category(akonadinotes_LIB_SRC HEADER akonadi_notes_debug.h IDENTIFIER AKONADINOTES_LOG CATEGORY_NAME log_akonadi_notes)

add_library(KF5AkonadiNotes ${akonadinotes_LIB_SRC})

generate_export_header(KF5AkonadiNotes BASE_NAME akonadi-notes)

add_library(KF5::KF5AkonadiNotes ALIAS KF5AkonadiNotes)

kde_target_enable_exceptions(KF5AkonadiNotes PUBLIC)

target_include_directories(KF5AkonadiNotes INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Notes;${KDE_INSTALL_INCLUDEDIR_KF5}/akonadi/notes;${Boost_INCLUDE_DIR}>")
target_include_directories(KF5AkonadiNotes PUBLIC "$<BUILD_INTERFACE:${Akonadi-Notes_SOURCE_DIR}/src;${Akonadi-Notes_BINARY_DIR}/src;>")

target_link_libraries(KF5AkonadiNotes
PUBLIC
    KF5::Mime
PRIVATE
    Qt5::Xml
    KF5::I18n
)

set_target_properties(KF5AkonadiNotes PROPERTIES
    VERSION ${AKONADINOTES_VERSION_STRING}
    SOVERSION ${AKONADINOTES_SOVERSION}
    EXPORT_NAME AkonadiNotes
)

install(TARGETS
    KF5AkonadiNotes
    EXPORT KF5AkonadiNotesTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS}
)

ecm_generate_headers(AkonadiNotes_CamelCase_HEADERS
  HEADER_NAMES

  NoteUtils
  REQUIRED_HEADERS AkonadiNotes_HEADERS
  PREFIX Akonadi/Notes
)

install(FILES
    ${AkonadiNotes_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/Akonadi/Notes
    COMPONENT Devel
)

install(FILES
    ${AkonadiNotes_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/akonadi-notes_export.h
    ${AkonadiNotes_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/akonadi/notes
    COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME AkonadiNotes
   LIB_NAME KF5AkonadiNotes
   DEPS "Mime" FILENAME_VAR PRI_FILENAME
)

install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
